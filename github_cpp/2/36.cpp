#include <iostream>
#include <queue>
#include <cstddef>
using namespace std;
/*
Huffman coding assigns variable length codewords to fixed length input characters based on their frequencies. More frequent characters are assigned shorter codewords and less frequent characters are assigned longer codewords. A Huffman tree is made for the input string and characters are decoded based on their position in the tree. We add a '0' to the codeword when we move left in the binary tree and a '1' when we move right in the binary tree. We assign codes to the leaf nodes which represent the input characters.

For example :

        {ϕ,5}
     0 /     \ 1
    {ϕ,2}   {A,3}
   0/   \1
{B,1}  {C,1}  
Input characters are only present on the leaves. Internal nodes have a character value of ϕ. Codewords:

A - 1
B - 00
C - 01
No codeword appears as a prefix of any other codeword. Huffman encoding is a prefix free encoding technique.

Encoded String "1001011" represents the string "ABACA"

You have to decode an encoded string using the Huffman tree.

You are given pointer to the root of the Huffman tree and a binary coded string. You need to print the actual string.

Sample Input

         {ϕ,5}
      0 /     \ 1
     {ϕ,2}   {A,3}
    0/   \1
{B,1}  {C,1}  

S="1001011"

Sample Output
ABACA

*/

typedef struct node
{
    int freq;
    char data;
    node * left;
    node * right;
    
}node;

class Solution {
    public:
  		node* createNode(int freq, char data) {
            node* newNode = new node();
            newNode->freq = freq;
            newNode->data = data;
            newNode->left = NULL;
            newNode->right = NULL;
            return newNode;
        }

        void decode_huff(node * root, string s)
        {
            node* tmp = root;
            for (char& c: s){
                tmp = c == '0' ? tmp->left : tmp->right;
                if (tmp->data != '\0'){
                    cout << tmp->data;
                    tmp = root;
                }
            }
        }

}; //End of Solution



int main() {
    Solution myTree;
    node* root = myTree.createNode(5,'\0');
    node* n1 = myTree.createNode(2, '\0');
    n1->left = myTree.createNode(1, 'B');
    n1->right = myTree.createNode(1, 'C');
    root->left = n1;
    root->right = myTree.createNode(3, 'A');
    myTree.decode_huff(root, "1001011");
 
    //cout << "height:" << height;

    return 0;
}

