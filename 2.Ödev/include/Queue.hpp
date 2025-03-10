#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "TreeNode.hpp"

struct QueueNode
{
    TreeNode *treeNode;
    int level;
    QueueNode *next;
};

class Queue
{
private:
    QueueNode *front;
    QueueNode *rear;

public:
    Queue();
    ~Queue();

    void enqueue(TreeNode *, int);
    void dequeue();
    QueueNode *peek();
    bool isEmpty();
};

#endif
