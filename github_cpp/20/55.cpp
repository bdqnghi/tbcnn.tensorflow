

#include <iostream>
#include "RedBlackTree.h"
using namespace std;


int main(int argc, char* argv[])
{
    cout << "Creating a new Red-Black-Tree ... ";
    RedBlackTree<int> test;
    cout << "done." << endl;
    cout << "Inserting some values ... ";
    test.insert(7);
    test.insert(8);
    test.insert(6);
    test.insert(12);
    test.insert(0);
    test.insert(9);
    test.insert(10);
    test.insert(-7);
    test.insert(999);
    cout << "done." << endl;
    cout << "Tree now: " << test << endl;
    cout << "Deleting a few values ... ";
    test.remove(12);
    test.remove(0);
    test.remove(9);
    test.remove(7);
    test.remove(8);
    test.remove(10);
    test.remove(-7);
    test.remove(6);
    cout << "done." << endl;
    cout << "Tree now: " << test << endl;
    
    cout << "Clearing tree now ... ";
    test.clear();
    cout << "done." << endl;
    cout << "Tree now: " << test << endl;
    return 0;
}
