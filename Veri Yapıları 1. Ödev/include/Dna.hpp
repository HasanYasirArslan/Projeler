#ifndef Dna_hpp
#define Dna_hpp
#include "Kromozom.hpp"
class Dna
{
public:
    Dna();
    ~Dna();
    void ekle(Kromozom *);
    bool isEmpty();
    void yazdir();
    void Caprazlama(int, int);
    void Mutasyon(int, int);
    int OtomatikIslem();
    void EkranaYaz();

private:
    Kromozom *ilk;
    int KromozomSayisi;
};

#endif