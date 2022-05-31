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

    auto iter = children.begin();
    while (iter != children.end()) {
        TNode *currChild = iter->get(); //Создаем указатель на текущий эелент
        if (currChild->data == value) { //Если есть совпадение
            auto tmp = iter;
            iter++;//переводим итератор к следующему

            delCount += currChild->childCount();

            children.erase(tmp); //и стираем текущий элемент из списка детей
            delCount++;

        } else iter++;
    }

    for (TNodePtr &child: children)
        delCount += child->delByValue(value); //увеличиваем счетчик удаленных элементов

    return delCount;
}

int TNode::popLeaf() {
    for (auto iter = children.begin();
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
    int tmp;

    for (auto iter = children.begin(); iter != children.end(); iter++) {
        TNode *currChild = iter->get();

        if (currChild->children.empty()) {
            if (!shift) { //если дошли до shift элемента
                tmp = currChild->data;
                children.erase(iter); //стираем его
                return tmp;
            } else shift--;
        }
    }

    for (TNodePtr &child: children) {
        tmp = child->popLeaf(shift);
        if (tmp != -1) return tmp;
    }

    return -1;
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
    for (TNodePtr &child: children) {
        cout << "( ";
        child->printNode();
        cout << ")";
    }
}

int TNode::childCount() {
    int childCount = 0;

    for (TNodePtr &child: children)   // считаем количество детей у удаляемых элементов
        childCount += child->childCount() + 1;

    return childCount;
}

Tree::Tree() { //Конструктор для создания пустого дерева
    root.reset(nullptr); //Обнуляем указатель на корень дерева
    count = 0;
}

Tree::~Tree() = default;

void Tree::push(int data, TNode *parent) { //вставка в произвольный узел
    TNodePtr newChild = std::make_unique<TNode>(data, parent); //Создаем умный указатель на элемент

    if (parent) //если не нулевой родитель
        if (count > 0) {
            parent->setChild(newChild);//добавляем новый элемент к списку детей указанного узла
            count++;
        } else cerr << "Such parent node doesn't exist\n";
}

void Tree::push(int data) { //вставка корневого элемента
    TNodePtr newChild = std::make_unique<TNode>(data, nullptr); //Создаем умный указатель на элемент

    root.swap(newChild); //Меняем местами указатели на указанный узел и корень
    count = 1;
}

int Tree::pop() {
    if (count > 0) {
        count--;
        return root->popLeaf();
    } else cerr << "Tree is empty\n";

    return -1;
}

int Tree::pop(int shift) {
    if (count > 0) {
        count--;
        int tmp = root->popLeaf(shift);
        if (tmp != -1) return tmp;
        else cerr << "Such element doesn't exist\n";
    } else cerr << "Tree is empty\n";

    return -1;
}

void Tree::print() {
    if (count > 0) {
        cout << "( ";
        root->printNode();
        cout << ")\n";
    } else cerr << "Tree is empty\n";
}

TNode *Tree::find(int data) {
    if (count > 0) {
        TNode *ret;

        if (root->getData() == data)
            return root.get(); //Если корень совпадает, возвращаем его значение

        ret = root->findByValue(data);
        if (ret) return ret;
        else cerr << "Such element doesn't exist\n";
    } else cerr << "Tree is empty\n";

    return nullptr;
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
        else cerr << "Such element doesn't exist\n";

    } else cerr << "Tree is empty\n";

    return nullptr;
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
            root.release(); //то очищаем список
            count = 0;

            return;
        }
        count -= root->delByValue(value);
    } else cerr << "Tree is empty\n";
}

Vector Tree::path(int value) {
    Vector paths = {0}; //0-ой элемент вектора требуется для хранения длины пути

    if (count > 0) {
        if (root->getData() == value)
            paths.push_back(paths.at(0));
        root->findPath(value, paths);

        paths.erase(paths.begin());//затем он стирается
        if (paths.empty()) {
            cerr << "Such element doesn't exist\n";
        }
        return paths;
    } else cerr << "Tree is empty\n";

    paths.erase(paths.begin());
    return paths;
}

bool Tree::operator==(const Tree &otherTree) const { return (count == otherTree.count); }

bool Tree::operator!=(const Tree &otherTree) const { return (count != otherTree.count); }

bool Tree::operator>(const Tree &otherTree) const { return (count > otherTree.count); }

bool Tree::operator>=(const Tree &otherTree) const { return (count >= otherTree.count); }

bool Tree::operator<(const Tree &otherTree) const { return (count < otherTree.count); }

bool Tree::operator<=(const Tree &otherTree) const { return (count <= otherTree.count); }