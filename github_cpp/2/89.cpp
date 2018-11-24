#include "../h_files/HuffmanCoding.h"
#include <iostream>
#include <utility>
using namespace std;


///////////////////////////////////////////////////////////////
////     Constructor to be initially called from Main
////     This function essentially starts the program
///////////////////////////////////////////////////////////////

HuffmanCoding::HuffmanCoding(string src){
    sourceData = src;
    compressedString = "";
    //worst case scenario, all unique characters
    //must accomodate
    heap = new Heap(sourceData.length());
    buildTable();
    buildHeap();
}

HuffmanCoding::~HuffmanCoding(){
    if(heap != NULL) delete heap;
}

///////////////////////////////////////////////////////////////
////    This function is used to build the table that 
////    stores the frequency of each character
///////////////////////////////////////////////////////////////
void HuffmanCoding::buildTable(){
    for(size_t i = 0; i < sourceData.length(); i++){
        char c = sourceData.at(i);
        if (frequencyTable.find(sourceData.at(i)) == frequencyTable.end()){
            frequencyTable.insert(pair<char, int>(c, 1));
        }
        else{
            frequencyTable[c]++;
        }
    }
}

///////////////////////////////////////////////////////////////
////    Builds the heap that is used to determine smallest
////    node to assemble huffman code strings
///////////////////////////////////////////////////////////////
void HuffmanCoding::buildHeap(){
    //fill heap
    for(map<char,int>::iterator it = frequencyTable.begin();
        it != frequencyTable.end(); ++it){
        heap->insert(new HuffNode(it->first, it->second));
    }
    //pop off two at a time until you get one left
    while(!heap->isEmpty()){
        if(heap->getSizeOfHeap() == 1) break;
        HuffNode* left = heap->removeSmallest();
        HuffNode* right = heap->removeSmallest();
        heap->insert(new HuffNode(left, right));
    }
    //final one is the root of your encoding tree
    string code = "";
    getHuffmanEncoding(heap->getRoot(), code);
    encode();
}


///////////////////////////////////////////////////////////////
////    Builds the huffman code string of 0s and 1s for each
////    character in the message
///////////////////////////////////////////////////////////////
void HuffmanCoding::getHuffmanEncoding(HuffNode* root, string code){
    if(root->getLeft() == NULL){
        root->setHuffmanCode(code);
        huffmanTable.insert(pair<char, string>(root->getLetter(), code));
        return;
    }
    else{
        getHuffmanEncoding(root->getLeft(), code+"0");
        getHuffmanEncoding(root->getRight(), code+"1");
    }
}

///////////////////////////////////////////////////////////////
////    Print to standard output the frequency table
///////////////////////////////////////////////////////////////
void HuffmanCoding::displayTable(){
    cout << "\tFrequency Table:\t" << endl;
    cout << " ------------------------------------------" << endl;
    for(map<char,int>::iterator it = frequencyTable.begin();
        it != frequencyTable.end(); ++it){
        cout << "" << it->first << "\t\t|\t" << it->second << "\t\t" << endl;
\
    }
    cout << endl << endl;
}

///////////////////////////////////////////////////////////////
////    Print huffman values for each character to 
////    standard output
///////////////////////////////////////////////////////////////
void HuffmanCoding::displayHuffmanTable(){
    cout << "\tHuffman Table:\t" << endl;
    cout << " ------------------------------------------" << endl;
    for(map<char,string>::iterator it = huffmanTable.begin();
        it != huffmanTable.end(); ++it){
        cout << "" << it->first << "\t\t|\t" << it->second << "\t\t" << endl;

    }
    cout << endl << endl;
}

///////////////////////////////////////////////////////////////
////    appends source string onto the compressed string
///////////////////////////////////////////////////////////////
void HuffmanCoding::encode(){
    for(size_t i = 0; i < sourceData.length(); i++){
        compressedString.append(huffmanTable[sourceData.at(i)]);
        //compressedString.append(" ");
        
    }
}

///////////////////////////////////////////////////////////////
////    This function is currently unused but it decodes
////    the encoded message.
////    
////    In order to make it work, uncomment the following 
////    line in the HuffmanCoding::encode() function
////        compressedString.append(" ");
///////////////////////////////////////////////////////////////
string HuffmanCoding::decodeString(string src){
    string info = "";
    size_t lastBlock = 0;
    for(size_t i = 0; i < src.length(); i++){
        if (src.at(i) == ' '){
            string temp = src.substr(lastBlock, i-lastBlock);
            lastBlock = i+1;
            for(map<char,string>::iterator it = huffmanTable.begin();
                it != huffmanTable.end(); ++it){
                if (it->second == temp){
                    info += (it->first);
                    break;
                }
            }
        }
    }
    return info;
}



