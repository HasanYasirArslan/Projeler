/**
 * @file     Kromozom.cpp
 * @description  Kromozom Bağlı Listesinin kaynak kodu.Genler düğüm olarak Kromozom Bağlı Listesinde yer almaktadır.
 * @course   1. Öğretim C Grubu
 * @assignment   1.Ödev
 * @date     20.11.2024
 * @author   Hasan Yasir ARSLAN   yasir.arslan@ogr.sakarya.edu.tr
 */

#include "Kromozom.hpp"
#include <iostream>
#include <iomanip>
Kromozom::Kromozom()
{
    ilk = 0;
    sonraki = 0;
    GenSayisi = 0;
}
Kromozom::~Kromozom()
{
    if (isEmpty())
        return;
    Gen *gecici = ilk;

    while (gecici != 0)
    {
        Gen *silinecek = gecici;

        gecici = gecici->sonraki;
        delete silinecek;
    }
}

bool Kromozom::isEmpty()
{
    return GenSayisi == 0;
}

void Kromozom::ekle(char veri)
{
    Gen *yeni = new Gen(veri);
    if (ilk == 0)
    {
        ilk = yeni;
        GenSayisi++;
        return;
    }

    Gen *gecici = ilk;
    while (gecici->sonraki != 0)
        gecici = gecici->sonraki;
    gecici->sonraki = yeni;
    GenSayisi++;
}

bool Kromozom::isEven()
{
    return GenSayisi % 2 == 0;
}

string Kromozom::sol()
{
    if (isEmpty())
        throw "Kromozomda eleman yok";
    string solGenler;
    Kromozom *solParca = new Kromozom();
    Gen *gecici = ilk;
    if (isEven())
    {
        for (int i = 0; i < GenSayisi / 2; i++)
        {
            solParca->ekle(gecici->veri);
            gecici = gecici->sonraki;
        }
    }
    else
    {
        for (int i = 0; i < (GenSayisi - 1) / 2; i++)
        {
            solParca->ekle(gecici->veri);
            gecici = gecici->sonraki;
        }
    }
    solGenler = solParca->genler();
    delete solParca;
    return solGenler;
}
string Kromozom::sag()
{
    if (isEmpty())
        throw "Kromozomda eleman yok";
    Kromozom *sagParca = new Kromozom();
    Gen *gecici = ilk;
    string sagGenler;
    if (isEven())
    {
        for (int i = 0; i < GenSayisi; i++)
        {
            if (i >= GenSayisi / 2)
                sagParca->ekle(gecici->veri);
            gecici = gecici->sonraki;
        }
    }
    else
    {
        for (int i = 0; i < GenSayisi; i++)
        {
            if (i >= ((GenSayisi + 1) / 2))
                sagParca->ekle(gecici->veri);
            gecici = gecici->sonraki;
        }
    }
    sagGenler = sagParca->genler();
    delete sagParca;
    return sagGenler;
}

string Kromozom::genler()
{
    if (isEmpty())
        throw "Kromozom bos";
    Gen *gecici = ilk;
    string genler;
    while (gecici != 0)
    {
        genler.push_back(gecici->veri);
        gecici = gecici->sonraki;
    }
    return genler;
}

void Kromozom::stringEkle(string genler)
{
    const char *karakterler = genler.data();
    while (*karakterler != '\0')
    {
        if (*karakterler != ' ')
            ekle(*karakterler);
        karakterler++;
    }
}

void Kromozom::yazdir()
{
    Gen *gecici = ilk;
    while (gecici != 0)
    {
        cout << gecici->veri << " ";
        gecici = gecici->sonraki;
    }
    cout << endl;
}

void Kromozom::GeniBul(int gen_index)
{
    Gen *genAdres = 0;
    Gen *gecici = ilk;
    if (gen_index >= GenSayisi || gen_index < 0)
    {
        throw "girilen gen index yanlis";
    }
    for (int i = 0; i < GenSayisi; i++)
    {
        if (gen_index == i)
        {
            gecici->veri = 'X';
        }
        gecici = gecici->sonraki;
    }
}

Gen *Kromozom::listeyiTersle()
{
    Gen *onceki = nullptr;
    Gen *gecici = ilk;
    while (gecici != nullptr)
    {
        Gen *sonrakiDugum = gecici->sonraki;
        gecici->sonraki = onceki;
        onceki = gecici;
        gecici = sonrakiDugum;
    }
    return onceki;
}

string Kromozom::tersListeyiIsle()
{
    Gen *tersIlk = listeyiTersle();
    Gen *gecici = tersIlk;
    Gen *gecici2 = tersIlk;
    while (gecici->sonraki != nullptr)
    {
        gecici = gecici->sonraki;
    }
    Gen *tersSon = gecici;
    while (gecici2->sonraki != nullptr)
    {
        if (gecici2->veri < tersSon->veri)
        {
            return string(1, gecici2->veri);
        }
        gecici2 = gecici2->sonraki;
    }
    return string(1, tersSon->veri);
}
