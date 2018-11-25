


#include <bits/stdc++.h>
using namespace std;

const int INF = 1 << 25;
const int NMAX = 1005;
int c[NMAX][NMAX];          
int f[NMAX][NMAX];          
int parent[NMAX];


int ford_fulkerson(int n, int s, int t) {
    
    
    int max_flow = 0;
    
    
    
    for (int i=0; i<n; i++) {
        for (int k=0; k<n; k++) {
            f[i][k] = 0;
        }
    } 
    
    
    while (true) {
        
        for (int i=0; i<n; i++) { parent[i] = -1; }  
        parent[s] = -2;                             
        queue<int> q;
        q.push(s);
        
        while (!q.empty() && parent[t] == -1) {
            int u = q.front(); q.pop();
            for (int v=0; v<n; v++) {
                int cf = c[u][v] - f[u][v];
                if (cf > 0 && parent[v] == -1) {
                    q.push(v);
                    parent[v] = u;
                }
            }
        }
                    
        if (parent[t] == -1) break;   
            
        
        int u, v, delta, cf;
        
        v = t;
        delta = INF;
        while (true) {
            u = parent[v];
            cf = c[u][v] - f[u][v];
            delta = min(delta, cf);
            v = u;
            if (v == s) break;
        }
                
        v = t;
        while (true) {
            u = parent[v];
            f[u][v] += delta;
            f[v][u] -= delta;
            v = u;
            if (v == s) break;
        }
            
        max_flow += delta;
    }
    return max_flow;
}
    





int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    
    for (int i=0; i<n; i++) {
        for (int k=0; k<n; k++) {
            c[i][k] = 0;
        }
    } 
    
    int u, v, capacity;    
    for (int i=0; i<m; i++) {
        cin >> u >> v >> capacity;
        c[u-1][v-1] = capacity;
    }   
     
    int res = ford_fulkerson(n, s-1, t-1);
    cout << "Maximum flow: " << res << '\n';
    
    return 0;
}
