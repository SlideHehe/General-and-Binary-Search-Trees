#include "Tests.h"

void TestTree()
{
    Tree t1, t2;

    t1.push(1);
    TNode *root = t1.find(1);
    t1.push(2, root);
    t1.push(3, root);
    root = t1.find(3);
    t1.push(4, root);
    t1.push(5, root);
    root = t1.find(4);
    t1.push(6,root);
    t1.print();
    cout << t1.height()<< " "<<t1.getCount()<<endl;

    //Vector vpath = t1.path(6);//прямой порядок обхода функции
    //for (int i = 0; i < vpath.size(); i++) {
    //    cout << vpath.at(i);
    //}
   

    /*cout<<t1.pop(3); t1.print();
    cout<<t1.pop(1);
    t1.print();*/


    /*t2.push(1);
    TNode* root2 = t2.find(1);
    t2.push(2, root2);
    t2.push(3, root2);
    t2.print();*/

    /*t1.swap(t2);
    t1.print();
    t2.print();*/

    /*t1.exclude(3);
    t1.print();*/

    //cout << (t2 <= t1) << endl;

    /*а)	push - вставка элемента в структуру(БД – упорядоченно, обычное - с указанием узла);
    б)	pop - выталкивание элемента из структуры(Выталкивает лист);--смещение работает некорректно: работает только по одному уровню, иначе знчение не удаляет
    в)	find - поиск элемента в структуре;
    г)	count - возврат количества элементов в структуре;
    д)	height - возврат высоты дерева;
    е)	path - подсчёт длины пути от корня до указанного узла.Если узлов с указанным элементом более одного, вернуть множество длин до каждого из узлов.Т.е.если в дереве несколько узлов с элементом 5, и длина до каждого из них равна 3, 5, 8, то метод path вернёт{ 3, 5, 8 }.
        ж)	print - вывод дерева в консоль(В preorder порядке);
    з)	балансировка - привести дерево к виду, в котором для каждого узла, высота в его левом и правом поддеревьях отличается не более чем на 1. Реализуется только для двоичного дерева.
    и)	динамический размер - размер структуры должен увеличиваться при необходимости;
    к)	операторы сравнения(> , < , != , etc) - объекты структур должны поддерживать операции лексикографического сравнения;*/
    //changeRoot();--для чего?
    /*реализация обмена деревьями	
    исключение узлов с указанным значением--не работает: некоторые узлы с поддеревьями и листья не обрабатываются: для рассматриваемой структуры 3,5,6*/


    /*Tree tree1;
    tree1.push(1);

    TNode* root = tree1.find(1);

    tree1.push(2, root);
    cout << tree1.height() << endl;
    tree1.push(3, root);
    tree1.push(4, tree1.find(1));
    tree1.print();

    TNode* node1 = tree1.find(3);
    for (int i = 0; i < 3; i++)
        tree1.push(i, node1);
    tree1.print();

    TNode* node2 = tree1.find(2);
    for (int i = 0; i < 3; i++)
        tree1.push(i, node2);
    tree1.print();

    cout << tree1.pop(1) << endl;

    TNode* shiftTest = tree1.find(1, 2);
    tree1.push(99, shiftTest);
    tree1.print();

    Vector testPaths = tree1.path(2);
    for (int i : testPaths)
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

    TNode* root2 = tree2.find(9);
    tree2.push(7, root2);
    tree2.push(8, root2);
    tree2.push(4, tree2.find(9));
    tree2.print();

    cout << "\n";
    tree1.swap(tree2);
    tree1.print();
    tree2.print();*/
}

void TestTimeTree()
{
    /*
    1.Формирование дерева формата form высотой N
    2.Вывод высоты и количества элементов
    3.Выталкивание листьев до высоты 4
    4.Вывод дерева
    */
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
                t.push(ii+i, ptr);
                t.push(ii+i, ptr);
           }
        }
    }

    cout << t.getCount() << " " << t.height() << endl;

    /*while (t.height() > 4) {
        t.pop();
    }*/

    t.print();

    auto written_Tree_end = std::chrono::high_resolution_clock::now();
    auto written_Tree_res = std::chrono::duration_cast<ms>(written_Tree_end - written_Tree_start).count();
    cout << "----------------------------------\nExecution time of the written Tree: " << written_Tree_res << " ms" << endl << endl;
}
