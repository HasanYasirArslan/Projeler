// include/BinaryTree.h
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include "Queue.hpp"
#include "TreeNode.hpp"
#include <iostream>
#include <string>
class BinaryTree
{
private:
    TreeNode *root;

    void insert(TreeNode *&, char);
    void mirror(TreeNode *&);
    int calculateTotal(TreeNode *);
    int height(TreeNode *);

public:
    BinaryTree();
    ~BinaryTree();
    void insert(char);
    void mirror();
    int height();
    void leaveSpace(int);
    void draw();
    int calculateTotal();
    void clear(TreeNode *&);
};

#endif
