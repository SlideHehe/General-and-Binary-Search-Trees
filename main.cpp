#include "Tree.h"

int main() {

    Tree tree1;
    tree1.push(1);

    TNode *root = tree1.find(1);

    tree1.push(2, root);
    cout << tree1.height() << endl;
    tree1.push(3, root);
    tree1.push(4, tree1.find(1));
    tree1.print();

    TNode *node1 = tree1.find(3);
    for (int i = 0; i < 3; i++)
        tree1.push(i, node1);
    tree1.print();

    TNode *node2 = tree1.find(2);
    for (int i = 0; i < 3; i++)
        tree1.push(i, node2);
    tree1.print();

    cout << tree1.pop(1) << endl;

    TNode *shiftTest = tree1.find(1, 2);
    tree1.push(99, shiftTest);
    tree1.print();

    Vector testPaths = tree1.path(2);
    for (int i: testPaths)
        cout << i << " ";
    cout << endl;

    tree1.exclude(2);
    tree1.print();

    cout << tree1.pop() << endl;
    cout << tree1.getCount() << endl;
    tree1.print();

    cout << tree1.height() << endl;

    cout << "\n\n";
    tree1.print();

    Tree tree2;
    tree2.push(9);

    TNode *root2 = tree2.find(9);
    tree2.push(7, root2);
    tree2.push(8, root2);
    tree2.push(4, tree2.find(9));
    tree2.print();

    cout << "\n";
    tree1.swap(tree2);
    tree1.print();
    tree2.print();

    return 0;
}
