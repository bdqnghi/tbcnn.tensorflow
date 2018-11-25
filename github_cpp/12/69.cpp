#include <iostream>
using namespace std;
#define NIL -1
#define MAX 100
#define INF 2001

int n;
int G[MAX][MAX];
int done[MAX];
int d[MAX];

int getMinimumCost() {
    d[0] = 0;
    int min, u, i;
    while(1) {
        min = INF;
        for(i = 0; i < n; i++) {
            if(min > d[i] && done[i] != 1) {
                min = d[i];
                u = i;
            }
        }
        if(min == INF) break;

        done[u] = 1;

        for(i = 0; i < n; i++) {
            if(done[i] != 1 && G[u][i] < INF) {
                if(G[u][i] < d[i]) d[i] = G[u][i];
            }
        }
    }
    
    int sum = 0;
    for(i = 0; i < n; i++) {
        sum += d[i];
    }
    return sum;
}

int main() {
    int i, j, u;
    cin >> n;
    for(i = 0; i < n; i++ ) {
        done[i] = 0;
        d[i] = INF;
        for(j = 0; j < n; j++) {
            cin >> u;
            if(u == -1) G[i][j] = INF;
            else G[i][j] = u;
        }
    }
    cout << getMinimumCost() << endl;
    return 0;
}
