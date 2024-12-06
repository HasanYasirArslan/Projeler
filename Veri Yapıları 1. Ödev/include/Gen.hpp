#ifndef Gen_hpp
#define Gen_hpp
#include <iostream>

using namespace std;

class Gen
{
public:
    Gen(char veri, Gen *sonraki = nullptr);
    char veri;
    Gen *sonraki;
};

#endif