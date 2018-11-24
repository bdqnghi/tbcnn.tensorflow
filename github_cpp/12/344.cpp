#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m, v1, v2, l;
    vector<vector<int>> graph;
    cin >> n >> m;
    graph.resize(n);
    for (int i = 0; i < n; i++){
        graph[i].resize(n);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = INT_MAX;
    for (int i = 0; i < m; i++) {
        cin >> v1 >> v2 >> l;
        graph[v1-1][v2-1] = l;
    }
    for (int i = 0; i < n; i++){
        graph[i][i] = 0;
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if ((graph[i][k] < INT_MAX) && (graph[k][j] < INT_MAX))
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (graph[i][j] != INT_MAX)
                cout << graph[i][j] << ' ';
            else
                cout << ' ' << ' ';
        cout << "\n";
    }
}