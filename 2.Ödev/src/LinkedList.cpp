/**
 * @file     LinkedList.cpp
 * @description  Ağaçlar birbirine tek yönlü bağlı liste ile bağlanıyor. Listenin gerçeklendiği kaynak kod burada yer alıyor.
 * @course   1. Öğretim C Grubu
 * @assignment   2.Ödev
 * @date     17.12.2024
 * @author   Hasan Yasir ARSLAN   yasir.arslan@ogr.sakarya.edu.tr
 */

#include "LinkedList.hpp"

LinkedList::LinkedList() : head(nullptr), current(nullptr) {}

LinkedList::~LinkedList()
{
    while (head)
    {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::addNode(BinaryTree *tree)
{
    ListNode *newNode = new ListNode();
    newNode->tree = tree;
    if (!head)
    {
        head = newNode;
        current = head;
        agacSayisi++;
    }
    else
    {
        ListNode *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        agacSayisi++;
    }
}

void LinkedList::deleteCurrentNode()
{
    if (!current)
        return;

    if (current == head)
    {
        ListNode *temp = head;
        head = head->next;
        delete temp;
        agacSayisi--;
        current = head;
        return;
    }

    ListNode *prev = head;
    while (prev && prev->next != current)
    {
        prev = prev->next;
    }

    if (prev)
    {
        prev->next = current->next;
        delete current;
        agacSayisi--;
        current = prev->next ? prev->next : prev;
    }
}

void LinkedList::moveLeft()
{
    if (!current || current == head)
        return;

    ListNode *temp = head;
    while (temp->next && temp->next != current)
    {
        temp = temp->next;
    }
    current = temp;
}

void LinkedList::moveRight()
{
    if (current && current->next)
    {
        current = current->next;
    }
}

void LinkedList::drawCurrentTree()
{
    if (current && current->tree)
    {
        current->tree->draw();
    }
    else
    {
        cout << "No tree selected." << endl;
    }
}

void LinkedList::mirrorCurrentTree()
{
    if (current && current->tree)
    {
        current->tree->mirror();
    }
}

int LinkedList::calculateCurrentTreeTotal()
{
    if (current && current->tree)
    {
        return current->tree->calculateTotal();
    }
    return 0;
}

bool LinkedList::isEnd()
{
    ListNode *temp = head;
    while (temp->next)
    {
        temp = temp->next;
    }
    return current == temp;
}
