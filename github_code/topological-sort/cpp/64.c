#include <bits/stdc++.h>

using namespace std;

struct Node {
    int val; // If we want to store the name of the node haha
    vector<Node*> children;
    
    Node(int val) : val{val}{
    
    }
};

vector<Node*> order; // Probably use deque later for speed lmao
unordered_set<Node*> visited;

void topological_sort(Node* cur) {
    // bool flag = true;
    visited.insert(cur);
    for (Node* child : cur->children) {
        if (visited.find(child) == visited.end()) {
            // Sort the children
            topological_sort(child);
        }
    }
    // Add me to the order
    order.push_back(cur);
}

int main() {
    int N, M;
    // scanf("%d", &T);
    
    scanf("%d%d", &N, &M);
    // Sample input from
    // https://www.hackerearth.com/practice/algorithms/graphs/topological-sort/tutorial/
    
    Node** arr = new Node*[N];
    
    for (int i = 0; i < N; ++i) {
        arr[i] = new Node(i);
    }
    
    for (int i = 0; i < M; ++i) {
        int source, sink;
        // arr[i]->val = i;
        scanf("%d%d", &source, &sink);
        arr[source-1]->children.push_back(arr[sink-1]);
    }
    for (int i = 0; i < N; ++i) {
        if (visited.find(arr[i]) == visited.end()) {
            topological_sort(arr[i]);
        }
    }
    
    for (int i = N-1; i >= 0; --i) {
        printf("%d ", order[i]->val+1);
    }
    
    for (int i = 0; i < N; ++i) {
        delete arr[i];
    }
    delete[] arr;
    
}
