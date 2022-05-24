#include "Tree.h"

int main() {

    Tree tree1;
    tree1.push(1, nullptr); //Корень можно создать либо так, передавая нулевой указатель

//    TNodePtr root_temp = std::make_unique<TNode>(1); //Либо вручную создавать узел
//    tree1.changeRoot(std::move(root_temp)); //и ставить за позицию корня

    TNode *root = tree1.find(1);

    tree1.push(2, root);
    tree1.push(3, root);
    tree1.push(4, root);
    tree1.print();

    TNode *node1 = tree1.find(3);
    for (int i = 0; i < 3; i++)
        tree1.push(i, node1);
    tree1.print();

    TNode *node2 = tree1.find(2);
    for (int i = 0; i < 3; i++)
        tree1.push(i, node2);
    tree1.print();

    return 0;
}
