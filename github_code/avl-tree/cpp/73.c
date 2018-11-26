/* 
 * File:   main.cpp
 * Author: richard
 *
 * Created on October 30, 2012, 5:16 PM
 */

#include <cstdlib>
#include <iostream>
#include "AvlTree.h"
#include "Btree.h"

using namespace std;

/*
 * Main method for program execution.
 * @return 0 if no error occurred.
 */
int main() {
    AvlTree avltree;
    Btree btree;

    for (unsigned n = 10000; n < (10000 * 5); n += 10000) {
        for (unsigned i = 0; i < n; i++) {
            double r = rand();
            avltree.insert(r);
            btree.insert(r);
        }
        cout << "AVL-Tree height for n = " << n << " => " << avltree.height() << endl;
        cout << "B-Tree height for n = " << n << " => " << btree.height() << endl;
    }
    cout << "Finally finished =)" << endl;

    return 0;
}