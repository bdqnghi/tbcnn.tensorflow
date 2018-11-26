/**
 @file bTree.h
 @brief bTree class
 @author Brandon Theisen, Jason Pederson, Kelvin Schutz, Chris Scholl, Jared Kareniemi
*/
#ifndef BTREE_H
#define BTREE_H
#include "Node.h"
#include "LeafNode.h"
#include "InteriorNode.h"
using namespace std;


template <class T>
class bTree
{
    private:
        Node<T>* rootPtr;

    public:
        bTree();
        Node<T>* searchLeaf(Node<T>* aNodePtr, int keyToFind);
        bool treeContains(int keyToFind);
        void printRecord(int key);
        bool insertRecord(key, value);
        bool deleteRecord(int key);
        bool checkTree(bTree aTree);
        void rebuildTree(bTree &aTree);

        ~bTree();

};

//#include "bTree.cpp"
#endif // BTREE_H
