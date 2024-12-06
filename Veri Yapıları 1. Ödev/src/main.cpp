/**
 * @file     main.cpp
 * @description  Program burada toplanıyor. Ana kod yeri
 * @course   1. Öğretim C Grubu
 * @assignment   1.Ödev
 * @date     20.11.2024
 * @author   Hasan Yasir ARSLAN   yasir.arslan@ogr.sakarya.edu.tr
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Dna.hpp"
using namespace std;
Dna dna;
void Menu()
{
    char secim;
    char karar;
    int kromozom_indis1;
    int kromozom_indis2;
    int gen_indis;
    do
    {
        cout << "Yapmak istediginiz islemi tuslayiniz." << endl;
        cout << "1-Tum Kromozomlari Goster" << endl;
        cout << "2-Caprazlama" << endl;
        cout << "3-Mutasyon" << endl;
        cout << "4-Otomatik Islemler" << endl;
        cout << "5-Ekrana Yaz" << endl;
        cin >> secim;
        switch (secim)
        {
        case '1':
            dna.yazdir();
            break;
        case '2':
            cout << "ilk kromozom indisini girin: ";
            cin >> kromozom_indis1;
            cout << endl
                 << "ikinci kromozom indisini girin: ";
            cin >> kromozom_indis2;
            dna.Caprazlama(kromozom_indis1, kromozom_indis2);
            break;
        case '3':
            cout << "kromozom indisini girin: ";
            cin >> kromozom_indis1;
            cout << endl
                 << "gen indisini girin: ";
            cin >> gen_indis;
            dna.Mutasyon(kromozom_indis1, gen_indis);
            break;
        case '4':
            cout << "Dosyadan islemler yapiliyor..." << endl;
            dna.OtomatikIslem();
            break;
        case '5':
            cout << "Ekrana yazdiriliyor..." << endl;
            dna.EkranaYaz();
            cout << endl;
            break;
        default:
            cout << "Yanlis tuslama yaptiniz." << endl;
            break;
        }
        cout << "Devam etmek icin e/E yaziniz." << endl;
        cin >> karar;
        system("cls");
    } while (karar == 'e' || karar == 'E');
}
int main()
{
    ifstream DosyaOku("Dna.txt");
    string satir;
    if (!DosyaOku.is_open())
    {
        cerr << "Dosya açilamadi: " << "Dna.txt" << endl;
        return 1;
    }
    while (getline(DosyaOku, satir))
    {
        Kromozom *kromozom = new Kromozom();
        for (char ch : satir)
        {
            if (ch != ' ')
            {
                kromozom->ekle(ch);
            }
        }
        dna.ekle(kromozom);
    }
    DosyaOku.close();
    Menu();
    return 0;
}