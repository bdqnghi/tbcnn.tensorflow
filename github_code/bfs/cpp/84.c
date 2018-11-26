#include <bits/stdc++.h>
using namespace std;

#define WHITE false
#define BLACK true

void BFS(int s, vector< vector<int> > &adj, vector<int> &parent, vector<int> &distance)
{
    queue<int> Q;
    vector<bool> color(parent.size());
    for (int u = 0; u < parent.size(); u++)
    {
        parent[u] = u;
        color[u] = WHITE;
        distance[u] = -1;
    }

    color[s] = BLACK;
    distance[s] = 0;
    Q.push(s);
    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (vector<int>::iterator v = adj[u].begin(); v != adj[u].end(); v++)
        {
            if(color[*v] == WHITE)
            {
                parent[*v] = u; 
                distance[*v] = distance[u] + 1;
                color[*v] = BLACK;
                Q.push(*v);
            }
        }
        color[u] = BLACK;
    }
}

int main()
{
    int q;
    cin >> q;
    while(q--)
    {
        int n, m;
        cin >> n >> m;
        vector< vector<int> > adj(n);
        vector<int> distance(n);
        vector<int> parent(n);
        while(m--)
        {
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int s;
        cin >> s;
        s--;
        BFS(s, adj, parent, distance);
        for (int i = 0; i < n; i++)
        {
            if (i == s)
                continue;
            if (distance[i] == -1)
                cout << -1 << " ";
            else cout << distance[i]*6 << " ";
        }
        cout << endl;
    }
    return 0;
}