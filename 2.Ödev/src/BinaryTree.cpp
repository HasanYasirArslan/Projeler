/**
 * @file     BinaryTree.cpp
 * @description  İkili Arama Ağacının kaynak kodları burada yer alıyor.Ekleme,aynalama,yazdırma,silme.
 * @course   1. Öğretim C Grubu
 * @assignment   2.Ödev
 * @date     17.12.2024
 * @author   Hasan Yasir ARSLAN   yasir.arslan@ogr.sakarya.edu.tr
 */

#include "BinaryTree.hpp"
#include <cmath>
#include <iomanip>

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree()
{
    clear(root);
}

void BinaryTree::insert(char value)
{
    insert(root, value);
}

void BinaryTree::insert(TreeNode *&node, char value)
{
    if (!node)
    {
        node = new TreeNode(value);
    }
    else if (value < node->data)
    {
        insert(node->left, value);
    }
    else
    {
        insert(node->right, value);
    }
}

void BinaryTree::mirror()
{
    mirror(root);
}

void BinaryTree::mirror(TreeNode *&node)
{
    if (node)
    {
        mirror(node->left);
        mirror(node->right);
        swap(node->left, node->right);
    }
}

int BinaryTree::height()
{
    return height(root);
}

void BinaryTree::draw()
{
    if (root == nullptr)
    {
        cout << "Ağaç boş." << endl;
        return;
    }

    int Height = height(root);
    Queue queue;
    queue.enqueue(root, 0);

    const int MAX_NODES = 1 << (Height + 1);
    TreeNode *currentLevelNodes[MAX_NODES];
    TreeNode *nextLevelNodes[MAX_NODES];

    // İlk seviyede 1 adet düğüm var (root)
    int currentCount = 1;
    currentLevelNodes[0] = root;

    // İlk seviyenin çocuklarını kuyruğa atalım:
    queue.dequeue();
    queue.enqueue(root->left, 1);
    queue.enqueue(root->right, 1);

    for (int currentLevel = 0; currentLevel <= Height; currentLevel++)
    {
        // currentLevelNodes dizisinde currentCount kadar düğüm var
        // Bunları hizalı olarak bas
        if (currentCount > 0)
            leaveSpace(Height + 1 - currentLevel);

        for (int i = 0; i < currentCount; i++)
        {
            TreeNode *node = currentLevelNodes[i];
            if (node)
                cout << node->data;
            else
                cout << " ";

            if (i < currentCount - 1)
            {
                // Aynı seviyedeki düğümler arası boşluk
                leaveSpace(Height - currentLevel + 2);
                cout << " ";
            }
        }
        cout << endl;

        // Şimdi dalları çizelim
        // Eğer bir düğümün çocuğu varsa, o yönde '.' basacağız
        if (currentCount > 0)
            leaveSpace(Height - currentLevel);

        for (int i = 0; i < currentCount; i++)
        {
            TreeNode *node = currentLevelNodes[i];
            bool hasLeft = (node && node->left);
            bool hasRight = (node && node->right);

            // '.' çizim aralığı hesaplama
            int spaceCount = (int)pow(2, (Height - currentLevel));
            if (hasLeft && hasRight)
            {
                for (int s = 0; s <= spaceCount * 2; s++)
                    cout << '.';
            }
            else if (hasLeft)
            {
                for (int s = 0; s <= spaceCount; s++)
                    cout << '.';
                for (int s = 0; s < spaceCount; s++)
                    cout << ' ';
            }
            else if (hasRight)
            {
                for (int s = 0; s < spaceCount; s++)
                    cout << ' ';
                for (int s = 0; s <= spaceCount; s++)
                    cout << '.';
            }
            else
            {
                for (int s = 0; s <= spaceCount * 2; s++)
                    cout << ' ';
            }

            if (i < currentCount - 1)
            {
                // İki düğüm arası dallar için boşluk
                int gapCount = (int)pow(2, (Height - currentLevel + 1)) - 1;
                for (int g = 0; g < gapCount; g++)
                    cout << ' ';
            }
        }
        cout << endl;

        // Bir sonraki seviye için hazırlık
        // Mevcut seviyedeki düğümlerden çocukları alacağız
        int nextCount = 0;
        for (int i = 0; i < currentCount; i++)
        {
            TreeNode *node = currentLevelNodes[i];
            // Kuyruktan sıradaki node'ları alalım
            // Zaten enqueue etmiştik, şimdi dequeue edip nextLevelNodes'a koyalım.
            // currentLevel+1 seviyedekileri kuyruktan çekiyoruz.

            if (!queue.isEmpty())
            {
                QueueNode *info = queue.peek();
                queue.dequeue();
                nextLevelNodes[nextCount++] = info->treeNode;
            }
            else
            {
                nextLevelNodes[nextCount++] = nullptr;
            }

            if (!queue.isEmpty())
            {
                QueueNode *info = queue.peek();
                queue.dequeue();
                nextLevelNodes[nextCount++] = info->treeNode;
            }
            else
            {
                nextLevelNodes[nextCount++] = nullptr;
            }
        }

        // Şimdi bir sonraki seviyeyi queue'ya ekleyelim (varsa)
        // currentLevel+1 seviyesi için çocukları enqueue edelim
        for (int i = 0; i < nextCount; i++)
        {
            TreeNode *n = nextLevelNodes[i];
            if (n)
            {
                queue.enqueue(n->left, currentLevel + 1);
                queue.enqueue(n->right, currentLevel + 1);
            }
            else
            {
                // Boş node için iki tane nullptr enqueue edelim ki ağaç yapısı korunabilsin
                queue.enqueue(nullptr, currentLevel + 1);
                queue.enqueue(nullptr, currentLevel + 1);
            }
        }

        // nextLevelNodes'u currentLevelNodes yap
        currentCount = nextCount;
        for (int i = 0; i < currentCount; i++)
        {
            currentLevelNodes[i] = nextLevelNodes[i];
        }
    }
}

int BinaryTree::calculateTotal()
{
    return root->data + calculateTotal(root);
}

int BinaryTree::calculateTotal(TreeNode *node)
{
    int leftValue = 0;
    int rightValue = 0;

    if (!node)
        return 0;
    if (node->left)
    {
        leftValue = node->left->data * 2;
        leftValue += calculateTotal(node->left);
    }
    if (node->right)
    {
        rightValue = node->right->data;
        rightValue += calculateTotal(node->right);
    }
    return leftValue + rightValue;
}

int BinaryTree::height(TreeNode *node)
{
    if (node)
    {
        return 1 + max(height(node->left),
                       height(node->right));
    }
    return -1;
}

void BinaryTree::leaveSpace(int space)
{
    int startSpace = pow(2, space) - 2;
    for (int i = 0; i < startSpace; i++)
        cout << " ";
}

void BinaryTree::clear(TreeNode *&node)
{
    if (node)
    {
        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
    }
}
