#ifndef Kromozom_hpp
#define Kromozom_hpp
#include "Gen.hpp"

class Kromozom
{
public:
    int GenSayisi;
    Gen *ilk;
    Kromozom *sonraki;
    Kromozom();
    ~Kromozom();
    bool isEmpty();
    void ekle(char);
    bool isEven();
    string sol();
    string sag();
    string genler();
    void stringEkle(string);
    void yazdir();
    void GeniBul(int);
    Gen *listeyiTersle();
    string tersListeyiIsle();
};

#endif