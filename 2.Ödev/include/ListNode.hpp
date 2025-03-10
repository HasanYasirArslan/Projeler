// include/ListNode.h
#ifndef LISTNODE_HPP
#define LISTNODE_HPP

#include "BinaryTree.hpp"

class ListNode
{
public:
    BinaryTree *tree;
    ListNode *next;

    ListNode();
    ~ListNode();
};

#endif
