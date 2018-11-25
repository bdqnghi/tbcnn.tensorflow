#include <bits/stdc++.h>

using namespace std;

struct Node {
    int val; 
    vector<Node*> children;
    
    Node(int val) : val{val}{
    
    }
};

vector<Node*> order; 
unordered_set<Node*> visited;

void topological_sort(Node* cur) {
    
    visited.insert(cur);
    for (Node* child : cur->children) {
        if (visited.find(child) == visited.end()) {
            
            topological_sort(child);
        }
    }
    
    order.push_back(cur);
}

int main() {
    int N, M;
    
    
    scanf("%d%d", &N, &M);
    
    
    
    Node** arr = new Node*[N];
    
    for (int i = 0; i < N; ++i) {
        arr[i] = new Node(i);
    }
    
    for (int i = 0; i < M; ++i) {
        int source, sink;
        
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
