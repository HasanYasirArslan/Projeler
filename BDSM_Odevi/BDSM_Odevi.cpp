#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

// DFA yapısını temsil eden bir sınıf
class DFA
{
public:
    vector<string> states;                       // Durumlar
    string startState;                           // Başlangıç durumu
    set<string> acceptStates;                    // Kabul durumları
    vector<char> alphabet;                       // Alfabe
    map<pair<string, char>, string> transitions; // Geçiş fonksiyonu

    DFA() {}

    // Ulaşılamayan durumları kaldır
    void removeUnreachable()
    {
        set<string> reachable;
        queue<string> toVisit;

        toVisit.push(startState);
        reachable.insert(startState);

        while (!toVisit.empty())
        {
            string current = toVisit.front();
            toVisit.pop();

            for (char symbol : alphabet)
            {
                auto transition = transitions.find({current, symbol});
                if (transition != transitions.end())
                {
                    string nextState = transition->second;
                    if (reachable.find(nextState) == reachable.end())
                    {
                        reachable.insert(nextState);
                        toVisit.push(nextState);
                    }
                }
            }
        }

        // Filtreleme
        vector<string> newStates;
        for (const string &state : states)
        {
            if (reachable.find(state) != reachable.end())
            {
                newStates.push_back(state);
            }
        }
        states = newStates;

        // Kabul durumlarını filtrele
        set<string> newAcceptStates;
        for (const string &state : acceptStates)
        {
            if (reachable.find(state) != reachable.end())
            {
                newAcceptStates.insert(state);
            }
        }
        acceptStates = newAcceptStates;
    }

    // Denk durumları birleştir
    void minimize()
    {
        set<string> nonAcceptStates;
        for (const string &state : states)
        {
            if (acceptStates.find(state) == acceptStates.end())
            {
                nonAcceptStates.insert(state);
            }
        }

        vector<set<string>> partitions = {acceptStates, nonAcceptStates};
        bool changed;

        do
        {
            changed = false;
            vector<set<string>> newPartitions;

            for (const auto &partition : partitions)
            {
                map<vector<int>, set<string>> groups;

                for (const string &state : partition)
                {
                    vector<int> signature;
                    for (char symbol : alphabet)
                    {
                        string nextState = transitions[{state, symbol}];
                        int groupIndex = -1;
                        for (size_t i = 0; i < partitions.size(); i++)
                        {
                            if (partitions[i].find(nextState) != partitions[i].end())
                            {
                                groupIndex = i;
                                break;
                            }
                        }
                        signature.push_back(groupIndex);
                    }
                    groups[signature].insert(state);
                }

                for (const auto &group : groups)
                {
                    newPartitions.push_back(group.second);
                }

                if (groups.size() > 1)
                {
                    changed = true;
                }
            }

            partitions = newPartitions;
        } while (changed);

        // Yeni durumları oluştur
        map<string, string> stateMapping;
        for (const auto &partition : partitions)
        {
            string representative = *partition.begin();
            for (const string &state : partition)
            {
                stateMapping[state] = representative;
            }
        }

        // Yeni durumları ve geçiş fonksiyonunu güncelle
        set<string> newStatesSet;
        for (const auto &mapping : stateMapping)
        {
            newStatesSet.insert(mapping.second);
        }
        vector<string> newStates(newStatesSet.begin(), newStatesSet.end());
        map<pair<string, char>, string> newTransitions;

        // Geçiş fonksiyonunu güncelle (structured binding olmadan)
        for (const auto &entry : transitions)
        {
            const auto &key = entry.first;
            const auto &value = entry.second;

            if (stateMapping.find(key.first) == stateMapping.end() || stateMapping.find(value) == stateMapping.end())
            {
                cout << "Hata: stateMapping'de bulunamayan durum. (" << key.first << ", " << key.second << ") -> " << value << endl;
                continue; // Hatalı geçişi atla
            }

            newTransitions[{stateMapping[key.first], key.second}] = stateMapping[value];
        }

        // Kabul durumlarını güncelle
        set<string> newAcceptStates;
        for (const string &state : acceptStates)
        {
            newAcceptStates.insert(stateMapping[state]);
        }

        // DFA'yı güncelle
        states = newStates;
        transitions = newTransitions;
        acceptStates = newAcceptStates;
    }

    // DFA'yı yazdır
    void print() const
    {
        cout << "States: ";
        for (const string &state : states)
        {
            cout << state << " ";
        }
        cout << "\nStart State: " << startState << "\n";
        cout << "Accept States: ";
        for (const string &state : acceptStates)
        {
            cout << state << " ";
        }
        cout << "\nTransitions:\n";
        for (const auto &entry : transitions)
        {
            const auto &key = entry.first;
            const auto &value = entry.second;
            cout << "(" << key.first << ", " << key.second << ") -> " << value << "\n";
        }
    }
};

int main()
{
    DFA dfa;

    // Kullanıcıdan giriş alın
    int numStates, numAcceptStates, numAlphabet, numTransitions;
    cout << "Durum sayisini giriniz: ";
    cin >> numStates;
    cout << "Durum isimlerini giriniz: ";
    for (int i = 0; i < numStates; ++i)
    {
        string state;
        cin >> state;
        dfa.states.push_back(state);
    }

    cout << "Baslangic durumunu giriniz: ";
    cin >> dfa.startState;

    cout << "Kabul durumlarinin sayisini giriniz: ";
    cin >> numAcceptStates;
    cout << "Kabul durumlarini giriniz: ";
    for (int i = 0; i < numAcceptStates; ++i)
    {
        string state;
        cin >> state;
        dfa.acceptStates.insert(state);
    }

    cout << "Alfabenin boyutunu giriniz: ";
    cin >> numAlphabet;
    cout << "Alfabeyi giriniz: ";
    for (int i = 0; i < numAlphabet; ++i)
    {
        char symbol;
        cin >> symbol;
        dfa.alphabet.push_back(symbol);
    }

    cout << "Gecis sayisini giriniz: ";
    cin >> numTransitions;
    cout << "Gecisleri giriniz (durum, sembol, hedef_durum):\n";
    for (int i = 0; i < numTransitions; ++i)
    {
        string from, to;
        char symbol;
        cin >> from >> symbol >> to;
        dfa.transitions[{from, symbol}] = to;
    }

    // Ulaşılamayan durumları kaldır
    dfa.removeUnreachable();
    cout << "\nUlasilamayan durumlar kaldirildi:\n";
    dfa.print();

    // Denk durumları birleştir
    dfa.minimize();
    cout << "\nDFA indirgeme tamamlandi:\n";
    dfa.print();

    return 0;
}
