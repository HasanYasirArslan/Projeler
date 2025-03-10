/**
 * @file     Queue.cpp
 * @description  Ağaçları ekrana yazdırırken levelOrder okuma yöntemini kullanmak için kuyruğa, okunan her bir veriyi ekleyip sırayla yazdırmayı sağlayan kuyruk sınıfın kaynak kodları burada yer almaktadır.
 * @course   1. Öğretim C Grubu
 * @assignment   2.Ödev
 * @date     17.12.2024
 * @author   Hasan Yasir ARSLAN   yasir.arslan@ogr.sakarya.edu.tr
 */

#include "Queue.hpp"
#include <iostream>

Queue::Queue() : front(nullptr), rear(nullptr) {}

Queue::~Queue()
{
    while (!isEmpty())
    {
        dequeue();
    }
}

void Queue::enqueue(TreeNode *node, int level)
{
    QueueNode *newNode = new QueueNode{node, level, nullptr};
    if (rear == nullptr)
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

void Queue::dequeue()
{
    if (front == nullptr)
        return;

    QueueNode *temp = front;
    front = front->next;
    if (front == nullptr)
        rear = nullptr;

    delete temp;
}

QueueNode *Queue::peek()
{
    return front;
}

bool Queue::isEmpty()
{
    return front == nullptr;
}
