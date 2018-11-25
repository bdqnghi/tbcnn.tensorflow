#include <bits/stdc++.h>

using namespace std;

class Edge {
    public:
        int to;
        int cap;
        int rev;

        Edge(int too, int capp, int revv) {
            to = too;
            cap = capp;
            rev = revv;
        }
};


class FordFulkerson {
    private:
        static const int MAXN = 1010;
        static const int MAXX = 1e9;
        int n,s,t;
        int cap[MAXN][MAXN];
        vector<Edge> adj[MAXN];
        bool vis[MAXN];
        
        int findPath(int u, int f) {
            if (u == t) return f;
            vis[u] = 1;
            for (int i=0; i<adj[u].size(); i++) {
                int v = adj[u][i].to;
                if (!vis[v] && adj[u][i].cap > 0) {
                    int df = findPath(v, min(f, adj[u][i].cap));
                    if (df > 0) {
                        adj[u][i].cap -= df;
                        adj[v][adj[u][i].rev].cap += df;
                        return df;
                    }
                }
            }
            return 0;
        }
    public:
        FordFulkerson(int N) {
            n = N;
            memset(cap, 0, sizeof cap);
        }
        void addCap(int x, int y, int val) {
            cap[x][y] += val;
        }
        void buildEdge() {
            int a,b;
            for (int i=0; i<n; i++) {
                for (int j=i+1; j<n; j++) {
                    if (cap[i][j] + cap[j][i] > 0) {
                        a = adj[i].size();
                        b = adj[j].size();
                        Edge edge1(j, cap[i][j], b);
                        adj[i].push_back(edge1);
                        Edge edge2(i, cap[j][i], a);
                        adj[j].push_back(edge2);
                    }
                }
            }
        }
        int getMaxFlow(int S, int T) {
            s = S;
            t = T;
            for (int flow = 0;;) {
                memset(vis, 0, sizeof vis);
                int df = findPath(s, MAXX);
                if (df == 0) return flow;
                flow += df;
            }
        }
};

int n,m,tc;
int a,b,c;
FordFulkerson *ff;

int main() {
    cin >> tc;
    while (tc--) {
        cin >> n >> m;
        ff = new FordFulkerson(n+2);
        while (m--) {
            cin >> a >> b >> c;
            ff->addCap(a, b, c);
            ff->addCap(b, a, c);
        }
        ff->buildEdge();
        cout << ff->getMaxFlow(1, n) << endl;
    }
    return 0;
}
