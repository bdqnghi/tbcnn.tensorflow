class graph {
    int V;
    list<int> *adjs;

    graph(int V, list<int> *adjs);
    void _topological_sort(int v, bool visited[], stack<int> &stack);
    void topological_sort();
};

graph::graph(int V, list<int> *adjs) {

    this->V = V;
    this->adjs = adjs;
}
void graph::_topological_sort(int v, bool visited[], stack<int> &stack) {

    visited[v] = 1;
    for(auto it=adjs[v].begin(); it!=adjs[v].end(); it++)
        if(!visited[*it])
            _topological_sort(*it, visited, stack);

    stack.push(v);
}
void graph::topological_sort() {

    stack<int> stack;

    bool *visited = new bool[V];
    for(int i=0; i<V; i++) visited[i] = 0;

    for(int i=0; i<V; i++)
        if(!visited[i])
            _topological_sort(i, visited, stack);

    while(!stack.empty()) {
        cout << stack.top() << " ";
        stack.pop();
    }
}