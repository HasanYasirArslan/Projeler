/**
 * @file     ListNode.cpp
 * @description  Ağaçları birbirine bağlamak için tanımlanan tek yönlü bağlı listenin düğümü burada yer alıyor.
 * @course   1. Öğretim C Grubu
 * @assignment   2.Ödev
 * @date     17.12.2024
 * @author   Hasan Yasir ARSLAN   yasir.arslan@ogr.sakarya.edu.tr
 */

#include "ListNode.hpp"

ListNode::ListNode() : tree(new BinaryTree()), next(nullptr) {}

ListNode::~ListNode()
{
    delete tree;
}
