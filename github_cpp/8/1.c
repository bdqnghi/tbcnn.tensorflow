




#include <iostream>
#include <stack>
#include <vector>

using std::vector;

void dfs(vector<vector<int>>& g, int v,
         bool *visited, int *labels, int *currentLabel) {
    visited[v] = true;
    for (auto i = g[v].begin(); i != g[v].end(); i++) {
        if (visited[*i] == false) {
            visited[*i] = true;
            dfs(g, *i, visited, labels, currentLabel);
        }
    }
    labels[*currentLabel] = v; 
    (*currentLabel)--;
}


void topological_sort(vector<vector<int>>& g) {
    int labels[g.size()];
    bool visited[g.size()];
    int currentLabel = (int)g.size()-1; 

    for(int i = 0; i < g.size(); i++) {
        visited[i] = false;
    }

    for (int i = 0; i < g.size(); i++) {
        if (visited[i] == false) {
            dfs(g, i, visited, labels, &currentLabel);
        }
    }
    
    for (int i = 0; i < g.size(); i++) {
        printf("%d ", labels[i]);
    }
    printf("\n");
}

int main() {
    vector<vector<int>> graph(4);
    graph[0].push_back(2);
    graph[3].push_back(0);
    graph[3].push_back(1);
    graph[3].push_back(2);
    graph[1].push_back(0);

    
    topological_sort(graph);
    return 0;
}
