#include<iostream>
using namespace std;

#include "graph/graph.hpp"
#include "../DataStructures/FibonacciHeap.hpp"
#include<limits.h>
class NodeMST : public Node {
    private:
        bool in_tree;
        int distance;
        NodeMST* parent;

    public:
        NodeMST(){
            in_tree = false;
            distance = INT_MAX;
            parent = NULL;
        }
        NodeMST(int value) : Node(value) {
            in_tree = false;
            distance = INT_MAX;
            parent = NULL;
        }
        NodeMST(string label): Node(label) {
            in_tree = false;
            distance = INT_MAX;
            parent = NULL;
        }
        NodeMST(int value, string label) : Node(value, label) {
            in_tree = false;
            distance = INT_MAX;
            parent = NULL;
        }
        void addToTree() {in_tree = true;}
        bool isInTree() {return in_tree;}
        void setDistance(int distance) {this->distance = distance;}
        int getDistance() {return distance;}
        void setParent(NodeMST* parent) {this->parent = parent;}
        NodeMST* getParent() {return parent;}
        void reset() {
            in_tree = false;
            distance = INT_MAX;
            parent = NULL;
        }
};
class MinQueueWrapper {
    public:
        virtual void init(Graph<NodeMST>* G) = 0;
        virtual void insertNode(NodeMST* node) = 0;
        virtual NodeMST* getMinWeightNode() = 0;
        virtual void decreaseKey(NodeMST* node, int weight) = 0;
};

class SimpleMinQueueWrapper : public MinQueueWrapper {
    private:
        Graph<NodeMST> *g;
    public:
        void init(Graph<NodeMST> *G) {
            g = G;
        }
        void insertNode(NodeMST* node) {
            // do nothing
        }
        void decreaseKey(NodeMST* node, int weight);
        NodeMST* getMinWeightNode();
};
class FHeapQueueWrapper : public MinQueueWrapper {
    private:
        FibonacciHeap<NodeMST> heap;
    public:
        FHeapQueueWrapper() {
            heap = FibonacciHeap<NodeMST>();
        }
        void init(Graph<NodeMST> *G);
        void insertNode(NodeMST* node);
        void decreaseKey(NodeMST* node, int weight);
        NodeMST* getMinWeightNode();
};

enum Algo {PRIM, KRUSKAL};
enum Scheme {SIMPLE, FHEAP};
class MinimumSpanningTree {
    private:
        MinQueueWrapper* mQ;
        Algo algo;
        Scheme scheme;
        MinimumSpanningTree(){
            algo = PRIM;
            scheme = SIMPLE;
            mQ = new SimpleMinQueueWrapper();
        };
        MinimumSpanningTree(MinimumSpanningTree const& copy);
        MinimumSpanningTree& operator =(MinimumSpanningTree const& copy);
        NodeMST* getVertexWithSmallestWeight(Graph<NodeMST>* G);
        NodeMST* simpleMinQueue(Graph<NodeMST>* G);
        int PRIMS(Graph<NodeMST> *G, NodeMST* source);
        int KRUSKAL(Graph<NodeMST> *G, NodeMST* source);
    public:
        static MinimumSpanningTree* getInstance() {
            static MinimumSpanningTree instance;
            return &instance;
        }

        int spanMinimumTree(Graph<NodeMST> *G, NodeMST* source) {
            if (algo == PRIM)
                PRIMS(G, source);
        }
        void setAlgo(Algo algo) {
            this->algo = algo;
        }

        void setScheme(Scheme scheme) {
            if (scheme == SIMPLE)
                mQ = new SimpleMinQueueWrapper();
            else if(scheme == FHEAP)
                mQ = new FHeapQueueWrapper();
        }

        void printMSTEdges(Graph<NodeMST>* G);
};


