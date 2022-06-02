#include "Tests.h"

/*
   а)	push - вставка элемента в структуру(БД – упорядоченно, обычное - с указанием узла);
   б)	pop - выталкивание элемента из структуры(Выталкивает лист);
   в)	find - поиск элемента в структуре;
   г)	count - возврат количества элементов в структуре;
   д)	height - возврат высоты дерева;
   е)	path - подсчёт длины пути от корня до указанного узла.Если узлов с указанным элементом более одного, вернуть множество длин до каждого из узлов.Т.е.если в дереве несколько узлов с элементом 5, и длина до каждого из них равна 3, 5, 8, то метод path вернёт{ 3, 5, 8 }.
   ж)	print - вывод дерева в консоль(В preorder порядке);
   з)	балансировка - привести дерево к виду, в котором для каждого узла, высота в его левом и правом поддеревьях отличается не более чем на 1. Реализуется только для двоичного дерева.
   и)	динамический размер - размер структуры должен увеличиваться при необходимости;
   к)	операторы сравнения(> , < , != , etc) - объекты структур должны поддерживать операции лексикографического сравнения;*/
   /*реализация обмена деревьями
   исключение узлов с указанным значением*/

   /*
   Временные тесты:
       1.Формирование дерева формата form высотой N
       2.Вывод высоты и количества элементов
       3.Выталкивание листьев до высоты 4
       4.Вывод дерева
  */


void TestTree()
{
    Tree t1, t2;

    t1.push(1);
    TNode* root = t1.find(1);
    t1.push(2, root);
    t1.push(3, root);
    root = t1.find(3);
    t1.push(4, root);
    t1.push(5, root);
    root = t1.find(4);
    t1.push(6, root);
    t1.print();
    cout << "Tree height: " << t1.height() << ", Number of Tree nodes: " << t1.getCount() << endl;

    Vector vpath = t1.path(6);//прямой порядок обхода функции
    cout << "Path to node 6: ";
    for (int i = 0; i < vpath.size(); i++) {
        cout << vpath.at(i) << " ";
    }
    cout << endl;

    cout << "Pop list: " << t1.pop() << endl;
    t1.print();
    cout << "Pop list: " << t1.pop(1) << endl;
    t1.print();

    t1.exclude(3);
    t1.print();

    t2.push(1);
    TNode* root2 = t2.find(1);
    t2.push(2, root2);
    t2.push(3, root2);
    t2.print();


    t1.swap(t2);
    t1.print();
    t2.print();

    cout << "Number of Tree1 nodes <= Number of Tree2 nodes: " << (t1 <= t2) << endl;
}

void TestTimeTree()
{
    cout << "\n----------------------------------\n";
    auto written_Tree_start = std::chrono::high_resolution_clock::now();

    Tree t;
    if (N > 0) {
        t.push(ii);
        if (form == 0) {
            for (int i = 1; i < N; i++) {
                for (int j = 0; j < pow(3, i - 1); j++) {
                    TNode* ptr = t.find(ii * i, j);
                    t.push(ii * (i + 1), ptr);
                    t.push(ii * (i + 1), ptr);
                    t.push(ii * (i + 1), ptr);
                }
            }
        }
        if (form == 1 && N > 1) {
            TNode* ptr = t.find(ii);
            t.push(ii + 1, ptr);
            t.push(ii + 1, ptr);
            for (int i = 2; i < N; i++) {
                ptr = t.find(ii + i - 1, 1);
                t.push(ii + i, ptr);
                t.push(ii + i, ptr);
            }
        }
    }

    cout << t.getCount() << " " << t.height() << endl;

    while (t.getCount() > 4) {
        t.pop();
    }

    t.print();

    auto written_Tree_end = std::chrono::high_resolution_clock::now();
    auto written_Tree_res = std::chrono::duration_cast<ms>(written_Tree_end - written_Tree_start).count();
    cout << "----------------------------------\nExecution time of the written Tree: " << written_Tree_res << " ms" << endl << endl;
}

void TestBSTree() {

    BSTree t1, t2;

    t1.push(10);
    t1.push(2);
    t1.push(3);
    t1.print();
    t1.push(1);
    t1.push(5);
    t1.push(2);
    t1.print();
    cout << "Tree height: " << t1.height() << ", Number of Tree nodes: " << t1.getCount() << endl;

    Vector vpath = t1.path(2);//прямой порядок обхода функции
    cout << "Path to node 2: ";
    for (int i = 0; i < vpath.size(); i++) {
        cout << vpath.at(i) << " ";
    }
    cout << endl;
    
    cout << "Pop list: " << t1.pop() << endl;
    t1.print();
    cout << "Pop list: " << t1.pop(1) << endl;
    t1.print();

    t1.exclude(2);
    t1.print();

    t2.push(2);
    t2.push(1);
    t2.push(3);
    t2.print();


    t1.swap(t2);
    t1.print();
    t2.print();

    cout << "Number of Tree1 nodes <= Number of Tree2 nodes: " << (t1 <= t2) << endl;

    t2.push(1);
    t2.push(2);
    t2.push(3);
    t2.push(4);
    t2.push(5);
    t2.print();
    t2.treeBalance();//error--балансировка - привести дерево к виду, в котором для каждого!!! узла, высота в его левом и правом поддеревьях отличается не более чем на 1.
    //+повторение узла 4
    t2.print();

}

void TestTimeBSTree() {
    cout << "\n----------------------------------\n";
    auto written_BSTree_start = std::chrono::high_resolution_clock::now();

    BSTree t;
    if (N > 0) {
        t.push((1000+ii)/2);
        if (form == 0) {
            for (int i = 1; i < N; i++) {
                    t.push((1000 + ii) / 2 - i);
                    t.push((1000 + ii) / 2 + i);
            }
        }
        if (form == 1 && N > 1) {
            t.push(ii + 1);
            t.push(ii + 1);
            for (int i = 2; i < N; i++) {
                t.push(ii + i);
                t.push(ii + i);
            }
        }
    }

    cout << t.getCount() << " " << t.height() << endl;

    while (t.getCount() > 4) {
        t.pop();
    }

    t.print();

    auto written_BSTree_end = std::chrono::high_resolution_clock::now();
    auto written_BSTree_res = std::chrono::duration_cast<ms>(written_BSTree_end - written_BSTree_start).count();
    cout << "----------------------------------\nExecution time of the written Binary Tree: " << written_BSTree_res << " ms" << endl << endl;
}
