/**
 * @file     Dna.cpp
 * @description Dna Bağlı Listesinin Kaynak Kodu. Kromozomlar düğüm olarak Dna Bağlı Listesinde yer almaktadır.
 * @course   1. Öğretim C Grubu
 * @assignment   1.Ödev
 * @date     20.11.2024
 * @author   Hasan Yasir ARSLAN   yasir.arslan@ogr.sakarya.edu.tr
 */
#include "Dna.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
Dna::Dna()
{
    ilk = 0;
    KromozomSayisi = 0;
}
Dna::~Dna()
{
    if (isEmpty())
        return;
    Kromozom *gecici = ilk;

    while (gecici != 0)
    {
        Kromozom *silinecek = gecici;

        gecici = gecici->sonraki;
        delete silinecek;
    }
}

bool Dna::isEmpty()
{
    return KromozomSayisi == 0;
}

void Dna::ekle(Kromozom *yeniKromozom)
{
    if (yeniKromozom == nullptr)
    {
        cerr << "Hata: Ekleme işlemi için geçersiz Kromozom işaretçisi!" << endl;
        return;
    }

    if (ilk == 0)
    {
        ilk = yeniKromozom;
        KromozomSayisi++;
        return;
    }

    Kromozom *gecici = ilk;
    while (gecici->sonraki != 0)
        gecici = gecici->sonraki;
    gecici->sonraki = yeniKromozom;
    KromozomSayisi++;
}
void Dna::yazdir()
{
    Kromozom *gecici = ilk;
    while (gecici != 0)
    {
        gecici->yazdir();
        gecici = gecici->sonraki;
    }
}

void Dna::Caprazlama(int index, int index2)
{
    if (index >= KromozomSayisi || index2 >= KromozomSayisi || index < 0 || index2 < 0)
        throw "girilen index yanlis";
    Kromozom *gecici = ilk;
    Kromozom *birinci = 0;
    Kromozom *ikinci = 0;

    Kromozom *YeniKromozom = new Kromozom();
    Kromozom *YeniKromozom2 = new Kromozom();
    string Kromozom1;
    string Kromozom2;
    for (int i = 0; i < KromozomSayisi; i++)
    {
        if (index == i)
            birinci = gecici;
        else if (index2 == i)
            ikinci = gecici;

        gecici = gecici->sonraki;
    }

    Kromozom1 = birinci->sol() + ikinci->sag();
    YeniKromozom->stringEkle(Kromozom1);
    Kromozom2 = birinci->sag() + ikinci->sol();
    YeniKromozom2->stringEkle(Kromozom2);

    ekle(YeniKromozom);
    ekle(YeniKromozom2);

    YeniKromozom->yazdir();
    YeniKromozom2->yazdir();
}

void Dna::Mutasyon(int kromozomIndex, int genIndex)
{
    int gen_sayisi;
    Kromozom *gecici = ilk;
    Kromozom *kromozomAdres = 0;
    if (kromozomIndex >= KromozomSayisi || kromozomIndex < 0)
        throw "girilen kromozom index yanlis";
    for (int i = 0; i < KromozomSayisi; i++)
    {
        if (kromozomIndex == i)
        {
            kromozomAdres = gecici;
        }
        gecici = gecici->sonraki;
    }
    kromozomAdres->GeniBul(genIndex);
    kromozomAdres->yazdir();
}
int Dna::OtomatikIslem()
{
    char islem;
    int kromozomIndex;
    int kromozom_or_genIndex;
    string satir;
    ifstream DosyaOku2("Islemler.txt");
    if (!DosyaOku2.is_open())
    {
        cerr << "Dosya acilamadi: " << "Islemler.txt" << endl;
        return 1;
    }
    while (getline(DosyaOku2, satir))
    {
        stringstream ss(satir);
        if (ss >> islem >> kromozomIndex >> kromozom_or_genIndex)
        {
            if (islem == 'C')
            {
                Caprazlama(kromozomIndex, kromozom_or_genIndex);
            }
            else if (islem == 'M')
            {
                Mutasyon(kromozomIndex, kromozom_or_genIndex);
            }
            else
            {
                cerr << "Geçersiz işlem: " << islem << endl;
            }
        }
        else
        {
            cerr << "Hatalı veya eksik satır: " << satir << endl;
        }
    }
    DosyaOku2.close();
}

void Dna::EkranaYaz()
{
    Kromozom *gecici = ilk;
    while (gecici != 0)
    {
        cout << gecici->tersListeyiIsle();
        gecici = gecici->sonraki;
    }
}
