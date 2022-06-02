#ifndef TESTS_H
#define TESTS_H

#include <chrono>
using ms = std::chrono::milliseconds;

#include "Tree.h"
#include "BSTree.h"

//#include 

#define N 8//3290
#define ii 1
#define form 0
		   //Формат 0 для : дерева: (ii ( ii*2 ( ii*3(...)) (ii*3(...)) (ii*3(...)) )  ( ii*2 ( ii*3(...)) (ii*3(...)) (ii*3(...)) ) ( ii*2 ( ii*3(...)) (ii*3(...)) (ii*3(...)) )) - для бинарного по два поддерева
		   //               бинарного дерева:  (1000+ii/2 ( 1000+ii/2-1 ( 1000+ii/2-2 (...) ) ) (1000+ii/2+1 ( 1000+ii/2+2 (...) ) ) )
		   //Формат 1 для : дерева: (ii ( ii+1 ) ( ii+1 ( ii+2) ( ii+2 ( ii+3 ) ( ii+3 (...) (...) ) ) ) )
		   //				бинарного дерева:	(ii (ii+1 ( ii+1 )( ii+2 ( ii+2 ) ( ii+3 ( ii+3 ) (...) ) ) ) )

void TestTree();
void TestTimeTree();

void TestBSTree();
void TestTimeBSTree();


#endif //TESTS_H
