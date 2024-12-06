/**
 * @file     Gen.cpp
 * @description  Gen düğümlerinin kaynak kodu.
 * @course   1. Öğretim C Grubu
 * @assignment   1.Ödev
 * @date     20.11.2024
 * @author   Hasan Yasir ARSLAN   yasir.arslan@ogr.sakarya.edu.tr
 */
#include "Gen.hpp"
Gen::Gen(char veri, Gen *sonraki)
{
    this->veri = veri;
    this->sonraki = sonraki;
}