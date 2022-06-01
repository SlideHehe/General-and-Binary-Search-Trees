#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include <cmath>

class TNode;

using std::cout;
using std::endl;
using std::cerr;
using TNodePtr = std::unique_ptr<TNode>; //Использование умных указателей на узлы дерева
using List = std::list<TNodePtr>; //Список состоящий из указателей на узлы
using Vector = std::vector<int>;

class TNode {
public:
    TNode(int data); //Конструктор для создания элемента на определенном узле

    TNode();

    ~TNode();

    void setChild(TNodePtr &child);

    int getData() const;

    TNode *findByValue(int value);

    TNode *findByValue(int value, int &shift); //Поиск элемента со смещением в shift элементов

    Vector findPath(int value, Vector &paths);

    int delByValue(int value);

    int popLeaf();

    int popLeaf(int &shift); //Выталкивание элемента со смещением в shift элементов

    int findDepth(TNodePtr &root);

    void printNode();


private:
    int data;
    List children; //Делаем список указателей на детей узла

    int childCount();
};

class Tree {
public:
    Tree(); //Конструктор для создания пустого дерева

    ~Tree();

    void push(int data, TNode *parent);

    void push(int data); //вставка корневого элемента

    int pop();

    int pop(int shift);

    void print();

    TNode *find(int data);

    TNode *find(int data, int shift);

    int getCount() const;

    int height();

    void swap(Tree &otherTree);

    void exclude(int value);

    Vector path(int value);

    bool operator==(const Tree &otherTree) const;

    bool operator!=(const Tree &otherTree) const;

    bool operator>(const Tree &otherTree) const;

    bool operator>=(const Tree &otherTree) const;

    bool operator<(const Tree &otherTree) const;

    bool operator<=(const Tree &otherTree) const;

private:
    TNodePtr root;
    int count;
};

#endif //TREE_H
