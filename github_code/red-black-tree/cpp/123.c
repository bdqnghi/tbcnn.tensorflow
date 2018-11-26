#include <iostream>
#include <fstream>
#include <assert.h>
#include "data-structure/RedBlackTree.h"

using namespace std;

int main() {
    //cout << "Hello, World!" << endl;
    RedBlackTree redBlackTree;
    //ofstream jsOut("/run/media/cfwloader/Documents/Project/C++/Data-Structure/Red-Black-Tree/GraphicTreeView/myJsData.js");

    std::srand(time(0));
    for(int i = 0; i < 50; ++i){
        redBlackTree.redBlackInsert(new RedBlackTreeNode(std::rand()%1999));
        /*
        ofstream jsOut("/run/media/cfwloader/Documents/Project/C++/Data-Structure/Red-Black-Tree/GraphicTreeView/myJsData.js");

        if (jsOut.is_open()) {
            redBlackTree.writeDataToFile_JSType(jsOut);
        }else{
            cout << "write failed." << endl;
        }
        jsOut.close();

        cout << i << endl;
        getchar();
         */

        /*
        redBlackTree.showTree(cout);
        getchar();
         */
    }
    ofstream tmpjsOut("/run/media/cfwloader/Documents/Project/C++/Data-Structure/Red-Black-Tree/GraphicTreeView/myJsData.js");
    if (tmpjsOut.is_open()) {
        redBlackTree.writeDataToFile_JSType(tmpjsOut);
    }else{
        cout << "write failed." << endl;
    }
    tmpjsOut.close();

    /*
    redBlackTree.redBlackInsert(new RedBlackTreeNode(1));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(2));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(3));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(4));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(5));
     */

    //redBlackTree.showTree(cout);


    int searchKey;
    RedBlackTreeNode* ptrRecord;
    while(cin >> searchKey) {
        ptrRecord = redBlackTree.binarySearch(searchKey);
        ptrRecord = redBlackTree.redBlackDelete(ptrRecord);
        if(ptrRecord != nullptr)delete ptrRecord;
        //redBlackTree.showTree(cout);
        ofstream jsOut("/run/media/cfwloader/Documents/Project/C++/Data-Structure/Red-Black-Tree/GraphicTreeView/myJsData.js");

        if (jsOut.is_open()) {
            redBlackTree.writeDataToFile_JSType(jsOut);
        }else{
            cout << "write failed." << endl;
        }
        jsOut.close();
    }



    /*
    if (jsOut.is_open()) {
        redBlackTree.writeDataToFile_JSType(jsOut);
    }else{
        cout << "write failed." << endl;
    }
    jsOut.close();
     */

    /*
    for(int i = 0; i < 20; ++i){
        redBlackTree.redBlackInsert(new RedBlackTreeNode(i));
    }

    redBlackTree.redBlackInsert(new RedBlackTreeNode(1));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(2));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(3));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(4));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(5));

    redBlackTree.showTree(cout);
    int searchKey;
    RedBlackTreeNode* ptrRecord;
    while(cin >> searchKey){
        ptrRecord = redBlackTree.binarySearch(searchKey);
        redBlackTree.redBlackDelete(ptrRecord);
        redBlackTree.showTree(cout);
    }
    */
    return 0;
}