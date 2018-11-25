#include <iostream>
#include <fstream>
#include <assert.h>
#include "data-structure/RedBlackTree.h"

using namespace std;

int main() {
    
    RedBlackTree redBlackTree;
    

    std::srand(time(0));
    for(int i = 0; i < 50; ++i){
        redBlackTree.redBlackInsert(new RedBlackTreeNode(std::rand()%1999));
        

        
    }
    ofstream tmpjsOut("/run/media/cfwloader/Documents/Project/C++/Data-Structure/Red-Black-Tree/GraphicTreeView/myJsData.js");
    if (tmpjsOut.is_open()) {
        redBlackTree.writeDataToFile_JSType(tmpjsOut);
    }else{
        cout << "write failed." << endl;
    }
    tmpjsOut.close();

    

    


    int searchKey;
    RedBlackTreeNode* ptrRecord;
    while(cin >> searchKey) {
        ptrRecord = redBlackTree.binarySearch(searchKey);
        ptrRecord = redBlackTree.redBlackDelete(ptrRecord);
        if(ptrRecord != nullptr)delete ptrRecord;
        
        ofstream jsOut("/run/media/cfwloader/Documents/Project/C++/Data-Structure/Red-Black-Tree/GraphicTreeView/myJsData.js");

        if (jsOut.is_open()) {
            redBlackTree.writeDataToFile_JSType(jsOut);
        }else{
            cout << "write failed." << endl;
        }
        jsOut.close();
    }



    

    
    return 0;
}