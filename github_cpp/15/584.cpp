//Implemented as min-heap
//TODO: pop implmentation is almost there, but does not delete popped nodes
//and leaves '0' as empty placeholders
#include <vector>
#include <iostream>
#include <climits>
struct Node {
    int val;
    Node* left, *right;

    Node(int val) : val(val), left(nullptr), right(nullptr){}
};
class Heap {
    std::vector<Node> vec;

    public:
    Heap() {}

    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
    void insert(int val) {
        vec.push_back(Node(val));
        int currIndex = vec.size() - 1;
        int parentIndex = (vec.size() - 1) / 2;
        while (vec[currIndex].val < vec[parentIndex].val) {
            swap(vec[currIndex].val, vec[parentIndex].val);

            currIndex = parentIndex;
            parentIndex = (currIndex - 1) / 2;
        }
    }
    int pop() {
        int currValue = vec[0].val;

        return currValue;
    }
    int peek() {return vec[0].val;}
    //Prints breadth-first
    void print() {
        for (Node node : vec)
            std::cout << node.val << ' ';
        std::cout << '\n';
    }
};

int main() {
    Heap heap;
    heap.insert(3);
    heap.insert(1);
    heap.insert(2);
    heap.insert(4);
    heap.insert(10);
    heap.insert(9);
    heap.insert(7);
    heap.insert(23);
    for (int i = 0; i < 5; i++){
        std::cout << heap.pop() << '\n';
        heap.print();
    }
}
