/**
 * @file     main.cpp
 * @description  Program burada toplanıyor. Ana kod yeri
 * @course   1. Öğretim C Grubu
 * @assignment   2.Ödev
 * @date     17.12.2024
 * @author   Hasan Yasir ARSLAN   yasir.arslan@ogr.sakarya.edu.tr
 */

#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.hpp"
#include <iomanip>
int boslukMiktari = 3;
int startIndex = 0;
const int pageSize = 10;
int index = 0;
LinkedList list;

void cizgiYaz()
{
    cout << "........";
    for (int i = 0; i < boslukMiktari; i++)
        cout << " ";
}

void isaretYaz(int globalIndex)
{
    // globalIndex'teki eleman sayfa içinde hangi konumda?
    int localPos = globalIndex - startIndex;
    if (localPos < 0)
        localPos = 0;
    if (localPos >= pageSize)
        localPos = pageSize - 1;
    if (localPos > 0 && localPos < pageSize)
        for (int i = 0; i < localPos; i++)
        {
            cout << "        ";
            for (int i = 0; i < boslukMiktari; i++)
                cout << " ";
        }
    cout << "^^^^^^^^" << endl;

    if (localPos > 0 && localPos < pageSize)
        for (int i = 0; i < localPos; i++)
        {
            cout << "        ";
            for (int i = 0; i < boslukMiktari; i++)
                cout << " ";
        }
    cout << "||||||||";
}

void degerYaz(int deger)
{
    cout << ".";
    cout << setw(6) << deger;
    cout << ".";
    for (int i = 0; i < boslukMiktari; i++)
        cout << " ";
}

void degerYazAdres(ListNode *adres)
{
    unsigned long long val = (unsigned long long)adres;
    unsigned int last4 = (unsigned int)(val % 10000); // Son 4 basamağı al
    cout << ".";
    cout << setw(6) << last4;
    cout << ".";
    for (int i = 0; i < boslukMiktari; i++)
        cout << " ";
}

void bagliListeYaz()
{
    // Sayfada gösterilecek aralık
    int endIndex = (startIndex + pageSize < list.agacSayisi) ? startIndex + pageSize : list.agacSayisi;
    int toplamGosterilecek = endIndex - startIndex;

    // startIndex kadar eleman atla
    ListNode *temp = list.head;
    for (int i = 0; i < startIndex && temp != nullptr; i++)
    {
        temp = temp->next;
    }

    // 1. Satır çizgiler:
    for (int i = 0; i < toplamGosterilecek; i++)
        cizgiYaz();
    cout << endl;

    // Adresleri yaz:
    {
        ListNode *t = temp;
        for (int i = 0; i < toplamGosterilecek && t != nullptr; i++)
        {
            degerYazAdres(t);
            t = t->next;
        }
    }
    cout << endl;

    // 2. Satır çizgiler:
    for (int i = 0; i < toplamGosterilecek; i++)
        cizgiYaz();
    cout << endl;

    // Değerleri yaz (calculateTotal()):
    {
        ListNode *t = temp;
        for (int i = 0; i < toplamGosterilecek && t != nullptr; i++)
        {
            degerYaz(t->tree->calculateTotal());
            t = t->next;
        }
    }
    cout << endl;

    // 3. Satır çizgiler:
    for (int i = 0; i < toplamGosterilecek; i++)
        cizgiYaz();
    cout << endl;

    // Bir sonrakileri yaz (adresler), +0 işaretçisi
    ListNode *t = temp;
    if (t != nullptr)
        t = t->next;
    for (int i = 1; i < toplamGosterilecek && t != nullptr; i++)
    {
        degerYazAdres(t);
        t = t->next;
    }
    if (endIndex == list.agacSayisi)
    {
        // Son eleman için 0 bas:
        cout << "." << setw(6) << "0" << ".";
        cout << endl;
    }
    else
    {

        if (t != nullptr)
        {
            // Bir sonraki sayfanın ilk düğümünün adresini bas
            unsigned long long val = (unsigned long long)t;
            unsigned int last4 = (unsigned int)(val % 10000); // Son 4 basamağı al
            cout << ".";
            cout << setw(6) << last4 << "." << endl;
        }
        else
        {
            cout << "." << setw(6) << "0" << "." << endl;
        }
    }
    // 4. Satır çizgiler:
    for (int i = 0; i < toplamGosterilecek; i++)
        cizgiYaz();
    cout << endl;
}

// index değiştiğinde sayfa dışına çıkıyor mu kontrol et
void checkPageBoundary()
{
    if (index < startIndex)
    {
        // index önceki sayfada kalmış, sayfayı geri al
        startIndex = (index / pageSize) * pageSize;
    }
    else if (index >= startIndex + pageSize)
    {
        // index ileri sayfaya taşmış, sayfayı ileri al
        startIndex = (index / pageSize) * pageSize;
    }
}

BinaryTree *createTreeFromLine(const string &line)
{
    BinaryTree *tree = new BinaryTree();
    for (char ch : line)
    {
        tree->insert(ch);
    }
    return tree;
}

int main()
{

    ifstream file("agaclar.txt");
    if (!file)
    {
        cerr << "Dosya acilamadi.\n";
        return 1;
    }

    string line;
    while (getline(file, line))
    {
        if (!line.empty())
        {
            BinaryTree *tree = createTreeFromLine(line);
            list.addNode(tree);
        }
    }
    file.close();

    checkPageBoundary(); // startIndex'i ayarla

    while (true)
    {
        system("cls");
        if (list.head)
        {
            bagliListeYaz();
            cout << endl;
            isaretYaz(index);
            cout << endl;
            cout << endl;
            list.drawCurrentTree();
            cout << endl
                 << endl;
            cout << "secim: ";
            int secim = cin.get();
            if (secim == 'q')
                break;
            if (secim == 'a')
            {
                if (index > 0)
                {
                    index--;
                    list.moveLeft();
                    checkPageBoundary();
                }
            }
            else if (secim == 's')
            {
                list.deleteCurrentNode();
                if (index >= list.agacSayisi && list.agacSayisi > 0)
                {
                    index = list.agacSayisi - 1;
                }
                checkPageBoundary();
            }

            else if (secim == 'd')
            {
                if (index < list.agacSayisi - 1)
                {
                    index++;
                    list.moveRight();
                    checkPageBoundary();
                }
            }
            else if (secim == 'w')
            {
                list.mirrorCurrentTree();
            }
        }
        else
        {
            cout << "Agac kalmadi." << endl;
            break;
        }
    }
    return 0;
}
