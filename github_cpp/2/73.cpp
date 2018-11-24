/*
Lossless Data Compression Technique
*/
#include <bits/stdc++.h>
using namespace std;
 
// A Huffman tree node
class MinHeapNode
{
public:
    char data;                // One of the input characters
    unsigned freq;             // Frequency of the character
    MinHeapNode *left, *right; // Left and right child
 
    MinHeapNode(char data, unsigned freq) : data(data), freq(freq), left(NULL), right(NULL) {}
};
 
// For comparison of two heap nodes (needed in min heap)
class compare
{
public:
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};
 
// Prints huffman codes from the root of Huffman Tree.
void printCodes(struct MinHeapNode* root, string str)
{
    if (!root)	// fail safe
    	return;
 
    if (root->data != '$') // If we reached leaf node
        cout << root->data << ": " << str << "\n";
 
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}
 
// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size)
{
    MinHeapNode *left, *right, *top;
 
    // Create a min heap & inserts all characters of data[]
    // Passing compare would override the () operator here..
    // compare(a,b) where a<b for priority queue storing elements in descending order...
    // we apply l->freq > r->freq (opposite) logic to get ascending ordering to pop
    // and generate tree from bottom
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));
 
    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1)
    {
        // Extract the two minimum freq items from min heap
        left = minHeap.top();
        cout<<"left = minHeap.top() => "<<minHeap.top()->freq<<endl;
        minHeap.pop();
        cout<<"minHeap.pop()\n";
        right = minHeap.top();
        cout<<"right = minHeap.top() => "<<minHeap.top()->freq<<endl;
        minHeap.pop();
 
        // Create a new internal node with frequency equal to the
        // sum of the two nodes frequencies. Make the two extracted
        // node as left and right children of this new node. Add
        // this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = new MinHeapNode('$', left->freq + right->freq);
        cout<<"top = "<<top->freq<<endl;
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
 
    // Print Huffman codes using the Huffman tree built above
    printCodes(minHeap.top(), "");
}
 
// Driver program to test above functions
int main()
{
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(arr) / sizeof(arr[0]);
 
    HuffmanCodes(arr, freq, size);
 
    return 0;
}

/*
OUTPUT:

left = minHeap.top() => 5
minHeap.pop()
right = minHeap.top() => 9
top = 14
left = minHeap.top() => 12
minHeap.pop()
right = minHeap.top() => 13
top = 25
left = minHeap.top() => 14
minHeap.pop()
right = minHeap.top() => 16
top = 30
left = minHeap.top() => 25
minHeap.pop()
right = minHeap.top() => 30
top = 55
left = minHeap.top() => 45
minHeap.pop()
right = minHeap.top() => 55
top = 100
f: 0
c: 100
d: 101
a: 1100
b: 1101
e: 111

*/