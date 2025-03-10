#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "ListNode.hpp"

class LinkedList
{
public:
    ListNode *head;
    ListNode *current;
    int agacSayisi = 0;
    LinkedList();
    ~LinkedList();
    void addNode(BinaryTree *);
    void deleteCurrentNode();
    void moveLeft();
    void moveRight();
    void drawCurrentTree();
    void mirrorCurrentTree();
    int calculateCurrentTreeTotal();
    bool isEnd();
};

#endif
