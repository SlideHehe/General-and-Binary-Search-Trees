#include "BSTree.h"

BSTNode::BSTNode(int data) { //Конструктор для создания элемента на определенном узле
    this->data = data;
}

BSTNode::BSTNode() {
    data = 0;
}

BSTNode::~BSTNode() {
    left.reset(nullptr);
    right.reset(nullptr);
    data = 0;
}

int BSTNode::getData() const { return data; }

BSTNode *BSTNode::findByValue(int value) {
    if (left != nullptr && left->data == value) return left.get();
    if (right != nullptr && right->data == value) return right.get();

    BSTNode *tmp;

    if (left) {
        tmp = left->findByValue(value);
        if (tmp) return tmp;
    }

    if (right) {
        tmp = right->findByValue(value);
        if (tmp) return tmp;
    }

    return nullptr;
}

BSTNode *BSTNode::findByValue(int value, int &shift) { //Поиск элемента со смещением в shift элементов
    if (left && left->data == value) {
        if (!shift) return left.get();
        else shift--;
    }

    if (right && right->data == value) {
        if (!shift) return right.get();
        else shift--;
    }

    BSTNode *tmp;

    if (left) {
        tmp = left->findByValue(value, shift);
        if (tmp) return tmp;
    }

    if (right) {
        tmp = right->findByValue(value, shift);
        if (tmp) return tmp;
    }

    return nullptr;
}

Vector BSTNode::findPath(int value, Vector &paths) {
    paths.at(0)++; //вычисляем текущий уровень

    if (left && left->data == value) paths.push_back(paths.at(0));
    if (right && right->data == value) paths.push_back(paths.at(0));

    if (left) left->findPath(value, paths);
    if (right) right->findPath(value, paths);

    paths.at(0)--;
    return paths;
}

int BSTNode::delByValue(int value) {
    int delCount = 0;

    if (left && left->data == value) {
        delCount = left->childCount();

        left.reset(nullptr);
        delCount++;
    }

    if (right && right->data == value) {
        delCount = right->childCount();

        right.reset(nullptr);
        delCount++;
    }

    if (left) delCount += left->delByValue(value);
    if (right) delCount += right->delByValue(value);

    return delCount;

}

void BSTNode::pushLeaf(int value, BSTNodePtr &root) {
    if (!root) { //Если корня нет
        BSTNodePtr newChild = std::make_unique<BSTNode>(value);
        root.swap(newChild);//То создаем его
        return;
    }

    if (value <= root->data) { root->left->pushLeaf(value, root->left); }
    else { root->right->pushLeaf(value, root->right); }
}


int BSTNode::popLeaf(BSTNodePtr &root) {
    int tmp;

    if (!root->left && !root->right) {
        tmp = root->data;
        root.reset(nullptr);
        return tmp;

    } else if (root->left) {
        tmp = popLeaf(root->left);
        if (tmp != -1) return tmp;

    } else if (root->right) {
        tmp = popLeaf(root->right);
        if (tmp != -1) return tmp;
    }

    return -1;
}

int BSTNode::popLeaf(int &shift, BSTNodePtr &root) { //Выталкивание элемента со смещением в shift элементов
    int tmp;

    if (!root->left && !root->right) {
        if (!shift) {
            tmp = root->data;
            root.reset(nullptr);
            return tmp;
        } else shift--;
    }

    if (root->left) {
        tmp = popLeaf(shift, root->left);
        if (tmp != -1) return tmp;
    }

    if (root->right) {
        tmp = popLeaf(shift, root->right);
        if (tmp != -1) return tmp;
    }

    return -1;
}

int BSTNode::findDepth(BSTNodePtr &root) {
    if (!root) {
        return 0;
    }

    int depth = 0;

    depth = std::fmax(depth, findDepth(root->left));
    depth = std::fmax(depth, findDepth(root->right));

    return depth + 1;
}

void BSTNode::printNode() {
    cout << data << " ";

    if (left) {
        cout << "( ";
        left->printNode();
        cout << ")";
    }

    if (right) {
        cout << "( ";
        right->printNode();
        cout << ")";
    }
}

void BSTNode::arrayConv(Vector &tmp, BSTNodePtr &root) { //функция для преобразования дерева в массив
    if (!root) return;

    arrayConv(tmp, root->left);
    tmp.push_back(root->data);
    arrayConv(tmp, root->right);
}


int BSTNode::childCount() { //считает количество детей у узла
    int childCnt = 0;

    if (left) childCnt += left->childCount() + 1;
    if (right) childCnt += right->childCount() + 1;

    return childCnt;
}

BSTree::BSTree() { //Конструктор для создания пустого дерева
    root.reset(nullptr); //Обнуляем указатель на корень дерева
    count = 0;
}

BSTree::~BSTree() = default;

void BSTree::push(int data) {
    root->pushLeaf(data, root);
    count++;
}

int BSTree::pop() {
    if (count > 0) {
        count--;
        return root->popLeaf(root);
    } else cerr << "BSTree is empty\n";

    return -1;
}

int BSTree::pop(int shift) {
    if (count > 0) {
        count--;
        int tmp = root->popLeaf(shift, root);
        if (tmp != -1) return tmp;
        else cerr << "Such element doesn't exist\n";
    } else cerr << "Tree is empty\n";

    return -1;
}

void BSTree::print() {
    if (count > 0) {
        cout << "( ";
        root->printNode();
        cout << ")\n";
    } else cerr << "Tree is empty\n";
}

BSTNode *BSTree::find(int data) {
    if (count > 0) {
        BSTNode *ret;

        if (root->getData() == data)
            return root.get(); //Если корень совпадает, возвращаем его значение

        ret = root->findByValue(data);
        if (ret) return ret;
        else cerr << "Such element doesn't exist\n";
    } else cerr << "Tree is empty\n";

    return nullptr;
}

BSTNode *BSTree::find(int data, int shift) {
    if (count > 0) {
        BSTNode *ret;

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

int BSTree::getCount() const { return count; }

int BSTree::height() { return root->findDepth(root); }

void BSTree::swap(BSTree &otherTree) {
    root.swap(otherTree.root); //меняем местами объекты у умных указателей
    std::swap(count, otherTree.count);
}

void BSTree::exclude(int value) {
    if (count > 0) {
        if (root->getData() == value) {
            root.reset(nullptr);
            count = 0;

            return;
        }
        count = count - root->delByValue(value);
    } else cerr << "Tree is empty\n";
}

Vector BSTree::path(int value) {
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

void BSTree::treeBalance() {
    Vector array; // Массив для хранения дерева
    root->arrayConv(array, root);

    BSTree balancedTree; // Создание нового дерева
    arrayToBSTree(balancedTree, array, 0, array.size() - 1);

    swap(balancedTree); // заменяем дерево на созданное
}

void BSTree::arrayToBSTree(BSTree &store, Vector &array, int left, int right) {
    if (left > right) return;
    else {
        int middle = (left + right) / 2;
        store.push(array.at(middle));

        arrayToBSTree(store, array, left, middle - 1);
        arrayToBSTree(store, array, middle + 1, right);
    }
}

bool BSTree::operator==(const BSTree &otherTree) const { return (count == otherTree.count); }

bool BSTree::operator!=(const BSTree &otherTree) const { return (count != otherTree.count); }

bool BSTree::operator>(const BSTree &otherTree) const { return (count > otherTree.count); }

bool BSTree::operator>=(const BSTree &otherTree) const { return (count >= otherTree.count); }

bool BSTree::operator<(const BSTree &otherTree) const { return (count < otherTree.count); }

bool BSTree::operator<=(const BSTree &otherTree) const { return (count <= otherTree.count); }
