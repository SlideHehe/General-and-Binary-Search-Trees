#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

class BSTNode;

using std::cout;
using std::endl;
using std::cerr;
using BSTNodePtr = std::unique_ptr<BSTNode>; //Использование умных указателей на узлы дерева
using Vector = std::vector<int>;

class BSTNode {
public:
    BSTNode(int data); //Конструктор для создания элемента на определенном узле

    BSTNode();

    ~BSTNode();

    int getData() const;

    BSTNode *findByValue(int value);

    BSTNode *findByValue(int value, int &shift); //Поиск элемента со смещением в shift элементов

    Vector findPath(int value, Vector &paths);

    int delByValue(int value);

    void pushLeaf(int value, BSTNodePtr &root);

    int popLeaf(BSTNodePtr &root);

    int popLeaf(int &shift, BSTNodePtr &root); //Выталкивание элемента со смещением в shift элементов

    int findDepth(BSTNodePtr &root);

    void printNode();

    void arrayConv(Vector &tmp, BSTNodePtr &root); //функция для преобразования дерева в массив


private:
    int data;
    BSTNodePtr left, right;

    int childCount(); //считает количество детей у узла
};

class BSTree {
public:
    BSTree();

    ~BSTree();

    void push(int data);

    int pop();

    int pop(int shift);

    void print();

    BSTNode *find(int data);

    BSTNode *find(int data, int shift);

    int getCount() const;

    int height();

    void swap(BSTree &otherTree);

    void exclude(int value);

    Vector path(int value);

    void treeBalance();

    bool operator==(const BSTree &otherTree) const;

    bool operator!=(const BSTree &otherTree) const;

    bool operator>(const BSTree &otherTree) const;

    bool operator>=(const BSTree &otherTree) const;

    bool operator<(const BSTree &otherTree) const;

    bool operator<=(const BSTree &otherTree) const;

private:
    BSTNodePtr root;
    int count;

    void arrayToBSTree(BSTree &store, Vector &array, int left, int right);
};

#endif //BSTREE_H
