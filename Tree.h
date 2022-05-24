#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <list>
#include <memory>
#include <vector>

class TNode;

using std::cout;
using std::endl;
using std::cerr;
using TNodePtr = std::unique_ptr<TNode>; //Использование умных указателей на узлы дерева
using List = std::vector<TNodePtr>; //Список состоящий из указателей на узлы
using Vector = std::vector<int>;

class TNode {
public:
    TNode(int data, TNode *parent); //Конструктор для создания элемента на определенном узле

    explicit TNode(int data); //Конструктор для создания элемента в качестве корня дерева

    TNode();

    ~TNode();

    void setChild(TNodePtr &child);

    int getData() const;

    TNode *findByValue(int value);

    void delByValue(int value);

    void printNode();


private:
    int data;
    TNode *parent;
    List children; //Делаем список указателей на детей узла
};

class Tree {
public:
    Tree(TNode *root); //Конструктор для создания дерева с корнем
    
    Tree(); //Конструктор для создания пустого дерева

    ~Tree();
    
    void changeRoot(TNodePtr newRoot);

    void push(int data, TNode *parent);

    List pop();

    void print();

    TNode *find(int data);

    int getCount();

    int height();

    void swap(Tree &otherTree);

    void exclude(int value);

    Vector path();

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
