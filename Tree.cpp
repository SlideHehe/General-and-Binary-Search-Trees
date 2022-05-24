#include "Tree.h"

TNode::TNode(int data, TNode *parent) { //Конструктор для создания элемента на определенном узле
    this->data = data;
    this->parent = parent;
}

TNode::TNode(int data) { //Конструктор для создания элемента в качестве корня дерева
    this->data = data;
    parent = nullptr;
}

TNode::TNode() {
    data = 0;
    parent = nullptr;
}

TNode::~TNode() {
    data = 0;
    parent = nullptr;
    children.clear();
}

void TNode::setChild(TNodePtr &child) { children.push_back(std::move(child)); }
//Заталкиваем узел в список детей и передаем управление этим узлом элементу списка

int TNode::getData() const { return data; }

TNode *TNode::findByValue(int value) {
    for (TNodePtr &child: children) //Проходим список детей
        if (child->data == value)
            return child.get(); //При совпадении возвращаем указатель на узел

    for (TNodePtr &child: children) { //Организуем рекурсию
        TNode *tmp = child->findByValue(value);
        if (tmp) return tmp; //Если найденный элемент не нулевой, возвращаем его
    }

    return nullptr;
}

void TNode::delByValue(int value) {
//    for (List::iterator tmp: children)
//        if (child->data == value)
//            children.erase(child);
//            child.get_deleter();
//
//    for (TNodePtr &child: children) {
//        child->delByValue(value);
//    }
}

void TNode::printNode() {
    cout << data << " ";
//    if(children.empty()) cout << ". ";
//    else
    for (TNodePtr &child: children)
        child->printNode();
}

Tree::Tree(TNode *root) { //Конструктор для создания дерева с корнем
    this->root = std::make_unique<TNode>(root->getData()); //Создаем умный указатель на элемент
    count = 1;
}

Tree::Tree() { //Конструктор для создания пустого дерева
    root.reset(nullptr); //Обнуляем указатель на корень дерева
    count = 0;
}

Tree::~Tree() = default;

void Tree::changeRoot(TNodePtr newRoot) {
    root.swap(newRoot); //Меняем местами указатели на указанный узел и корень
    if (!count) count++; //Если заносится корень в пустое дерево, прибавляем счетчик на 1
}

void Tree::push(int data, TNode *parent) {
    TNodePtr newChild = std::make_unique<TNode>(data, parent); //Создаем умный указатель на элемент

    if (!parent)
        changeRoot(std::move(newChild)); //Если указатель на родителя нулевой, то элемент занимает позицию корня
    else if (count > 0) {
        parent->setChild(newChild); //Если нет, то заносим элемент в список детей у его родителя
        count++;
    }
}

List Tree::pop() {

}

void Tree::print() {
    if (count > 0) {
        root->printNode();
        cout << endl;
    } else cerr << "Tree is empty";

}

TNode *Tree::find(int data) {
    if (count > 0) {
    if (root->getData() == data)
        return root.get(); //При нахождении нужного элемента возврат указателя
    return root->findByValue(data);
    } else cerr << "Tree is empty";
}

int Tree::getCount() { return (count); }

int Tree::height() {

}

void Tree::swap(Tree &otherTree) { root.swap(otherTree.root); }

void Tree::exclude(int value) {
    if (count > 0) {
        if (root->getData() == value) {
            root.get_deleter();
            return;
        }
        root->delByValue(value);
    } else cerr << "Tree is empty";
}

Vector Tree::path() {

}

bool Tree::operator==(const Tree &otherTree) const { return (count == otherTree.count); }

bool Tree::operator!=(const Tree &otherTree) const { return (count != otherTree.count); }

bool Tree::operator>(const Tree &otherTree) const { return (count > otherTree.count); }

bool Tree::operator>=(const Tree &otherTree) const { return (count >= otherTree.count); }

bool Tree::operator<(const Tree &otherTree) const { return (count < otherTree.count); }

bool Tree::operator<=(const Tree &otherTree) const { return (count <= otherTree.count); }