







#ifndef Heap_h
#define Heap_h

#define MINSORT 0
#define MAXSORT 1


#include "BCRHelper.h"
#include "Node.h"

class IntegerHeap {
private:
    static void buildHeap(std::vector<int> &A, int n, int o);
    static void heapify(std::vector<int> &A, int n, int i, int o);
    static void heapSort(std::vector<int> &A, int n, int o);
public:
    static void heapSort(std::vector<int> &A) { heapSort(A, (int)A.size(), MAXSORT); }
    static void heapSort(std::vector<int> &A, int o) { heapSort(A, (int)A.size(), o); }
}; 


class NodeHeap {
private:
    static void buildHeap(Node::NodeList &A, int n, int o);
    static void heapify(Node::NodeList &A, int n, int i, int o);
    static void heapSort(Node::NodeList &A, int n, int o);
public:
    static void heapSort(Node::NodeList &A) { heapSort(A, (int)A.size(), MAXSORT); }
    static void heapSort(Node::NodeList &A, int o) { heapSort(A, (int)A.size(), o); }
}; 










#endif 
