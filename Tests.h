#ifndef TESTS_H
#define TESTS_H

#include <cmath>
#include <chrono>
using ms = std::chrono::milliseconds;

#include "Tree.h"

//#include 
#define N 5
#define ii 1
#define form 0//Формат дерева 0: (ii ( ii*2 ( ii*3(...)) (ii*3(...)) (ii*3(...)) )  ( ii*2 ( ii*3(...)) (ii*3(...)) (ii*3(...)) ) ( ii*2 ( ii*3(...)) (ii*3(...)) (ii*3(...)) )) - для бинарного по два поддерева
		   //Формат дерева 1: (ii ( ii+1 ) ( ii+1 ( ii+2) ( ii+2 ( ii+3 ) ( ii+3 (...) (...) ) ) ) )

void TestTree();
void TestTimeTree();



#endif //TESTS_H
