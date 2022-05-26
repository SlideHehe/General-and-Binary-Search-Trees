#include "Tree.h"

TNode::TNode(int data, TNode *parent) { //Конструктор для создания элемента на определенном узле
    this->data = data;
    this->parent = parent;
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
    for (TNodePtr &child: children) {//Проходим список детей
        if (child->data == value)
            return child.get(); //При совпадении возвращаем указатель на узел
    }

    for (TNodePtr &child: children) {
        TNode *tmp = child->findByValue(value); //Организуем рекурсию
        if (tmp) return tmp; //Если найденный элемент не нулевой, возвращаем его
    }

    return nullptr;
}

TNode *TNode::findByValue(int value, int &shift) { //Поиск элемента со смещением в shift элементов
    for (TNodePtr &child: children) {
        if (child->data == value) {
            if (!shift) return child.get(); //Проверяем дошли ли мы до нужного элемента
            else shift--;
        }
    }

    for (TNodePtr &child: children) {
        TNode *tmp = child->findByValue(value, shift);
        if (tmp) return tmp;
    }

    return nullptr;
}

Vector TNode::findPath(int value, Vector &paths) {
    paths.at(0)++; //вычисляем текущий уровень
    for (TNodePtr &child: children) {
        if (child->data == value)
            paths.push_back(paths.at(0)); //при совпадении сохраняем в вектор

        child->findPath(value, paths); //создаем рекурсию
    }
    paths.at(0)--;
    return paths;
}

int TNode::delByValue(int value) {
    int delCount = 0;

    for (List::iterator iter = children.begin(); iter != children.end(); iter++) {
        TNode *currChild = iter->get(); //Создаем указатель на текущий эелент
        if (currChild->data == value) { //Если есть совпадение
            List::iterator tmp = iter;
            iter++; //переводим итератор к следующему элементу
            delCount += currChild->children.size() + 1; //считаем какое количество элементов мы удалили

            children.erase(tmp); //и стираем текущий элемент из списка детей
        }
    }

    for (TNodePtr &child: children)
        delCount += child->delByValue(value); //увеличиваем счетчик удаленных элементов

    return delCount;
}

int TNode::popLeaf() {
    for (List::iterator iter = children.begin();
         iter != children.end(); iter++) { //используем итератор для прохода по списку
        int tmp; //переменная для сохранения выталкиваемого значения
        TNode *currChild = iter->get();

        if (currChild->children.empty()) { // при нахождении листа
            tmp = currChild->data; //сохраняем данные
            children.erase(iter); // удаляем элемент из списка
            return tmp;
        }
    }

    for (TNodePtr &child: children)
        return child->popLeaf();

    return data;
}

int TNode::popLeaf(int &shift) { //Выталкивание элемента со смещением в shift элементов
    for (List::iterator iter = children.begin(); iter != children.end(); iter++) {
        int tmp;
        TNode *currChild = iter->get();

        if (currChild->children.empty()) {
            if (!shift) { //если дошли до shift элемента
                tmp = currChild->data;
                children.erase(iter); //стираем его
                return tmp;
            } else shift--;
        }
    }

    for (TNodePtr &child: children)
        return child->popLeaf(shift);

    return data;
}

int TNode::findDepth(TNode *root) {
    if (root == nullptr) {
        return 0;
    }

    int depth = 0;
    for (TNodePtr &child: root->children)
        depth = std::max(depth, findDepth(child.get())); //находим максимальную высоту среди всех узлов
    return depth + 1;
}

void TNode::printNode() {
    cout << data << " ";
//    if(children.empty()) cout << ". ";
//    else
    for (TNodePtr &child: children)
        child->printNode();
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

void Tree::push(int data, TNode *parent) { //вставка в произвольный узел
    TNodePtr newChild = std::make_unique<TNode>(data, parent); //Создаем умный указатель на элемент

    if (parent) //если не нулевой родитель
        if (count > 0) {
            parent->setChild(newChild);//добавляем новый элемент к списку детей указанного узла
            count++;
        } else cerr << "Such parent node doesn't exist";
}

void Tree::push(int data) { //вставка корневого элемента
    TNodePtr newChild = std::make_unique<TNode>(data, nullptr); //Создаем умный указатель на элемент

    changeRoot(std::move(newChild)); //Если указатель на родителя нулевой, то элемент занимает позицию корня
    count = 1;
}

int Tree::pop() {
    if (count > 0) {
        count--;
        return root->popLeaf();
    } else cerr << "Tree is empty";

    return -1;
}

int Tree::pop(int shift) {
    if (count > 0) {
        count--;
        return root->popLeaf(shift);
    } else cerr << "Tree is empty";

    return -1;
}

void Tree::print() {
    if (count > 0) {
        root->printNode();
        cout << endl;
    } else cerr << "Tree is empty";
}

TNode *Tree::find(int data) {
    if (count > 0) {
        TNode *ret;

        if (root->getData() == data)
            return root.get(); //Если корень совпадает, возвращаем его значение

        ret = root->findByValue(data);
        if (ret) return ret;
        else cerr << "Such element doesn't exist";
    } else cerr << "Tree is empty";
}

TNode *Tree::find(int data, int shift) {
    if (count > 0) {
        TNode *ret;

        if (root->getData() == data) {
            if (!shift) {
                return root.get();
            } else shift--;
        }
        ret = root->findByValue(data, shift);

        if (ret) return ret;
        else cerr << "Such element doesn't exist";

        return nullptr;
    } else cerr << "Tree is empty";
}

int Tree::getCount() const { return count; }

int Tree::height() { return root->findDepth(root.get()); } //передаем указатель на узел TNode

void Tree::swap(Tree &otherTree) {
    root.swap(otherTree.root); //меняем местами объекты у умных указателей
    std::swap(count, otherTree.count);
}

void Tree::exclude(int value) {
    if (count > 0) {
        if (root->getData() == value) { //Если исключяем корень
            root.reset(nullptr); //то очищаем список
            count = 0;

            return;
        }
        count = count - root->delByValue(value);
    } else cerr << "Tree is empty";
}

Vector Tree::path(int value) {
    if (count > 0) {
        Vector paths = {1}; //0-ой элемент вектора требуется для хранения длины пути
        if (root->getData() == value)
            paths.push_back(paths.at(0));
        root->findPath(value, paths);

        paths.erase(paths.begin());//затем он стирается
        return paths;
    } else cerr << "Tree is empty";
}

bool Tree::operator==(const Tree &otherTree) const { return (count == otherTree.count); }

bool Tree::operator!=(const Tree &otherTree) const { return (count != otherTree.count); }

bool Tree::operator>(const Tree &otherTree) const { return (count > otherTree.count); }

bool Tree::operator>=(const Tree &otherTree) const { return (count >= otherTree.count); }

bool Tree::operator<(const Tree &otherTree) const { return (count < otherTree.count); }

bool Tree::operator<=(const Tree &otherTree) const { return (count <= otherTree.count); }