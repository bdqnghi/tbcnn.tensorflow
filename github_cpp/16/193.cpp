// Problem Statemnt -- https://www.geeksforgeeks.org/topological-sorting/

#include <bits/stdc++.h>

using namespace std;

struct node {
    int visited = 0;
    list<int> l;
};

void addEdge(vector<node>& graph, int u, int v) {
    graph.at(u).l.push_back(v);
}

void doDFS(vector<node>& Graph, int v, stack<int>& s) {
    Graph.at(v).visited = true;

    for(int& i : Graph.at(v).l) {
        if(!Graph.at(i).visited) 
            doDFS(Graph, i, s);
    }

    s.push(v+1);
}

void printTopo(vector<node>& Graph) {
    stack<int> s;

    for(int i = 0; i < Graph.size(); ++i) {
        if(!Graph.at(i).visited)
            doDFS(Graph, i, s);
    }

    while(!s.empty()) {
        cout<<s.top()<<" ";
        s.pop();
    }
}

int main() {
    int n, m;
    cin>>n>>m;

    vector<node> Graph(n);

    while(m--) {
        int u, v;
        cin>>u>>v;

        addEdge(Graph, --u, --v);
    }

    printTopo(Graph);

    return 0;
}
