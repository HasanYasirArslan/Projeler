/**
 * @file     TreeNode.cpp
 * @description  Tek yönlü bağlı listeden farklı olarak ağaç içerisinde sol ve sağ olmak üzere iki yön olduğu için ağaç içinde dolaşımı sağlayan iki yönlü bağlı listenin düğümü burada yer alıyor.
 * @course   1. Öğretim C Grubu
 * @assignment   2.Ödev
 * @date     17.12.2024
 * @author   Hasan Yasir ARSLAN   yasir.arslan@ogr.sakarya.edu.tr
 */
#include "TreeNode.hpp"

TreeNode::TreeNode(char data)
{
    this->data = data;
    left = nullptr;
    right = nullptr;
}
