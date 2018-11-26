#include <climits>
#include <iostream>
using namespace std;

#define MAX_N 2000
int n;
int A[MAX_N][MAX_N];

class Node
{
    public:
        int cost = INT_MAX;;
        bool used = false;
};

int prim()
{
    int i, u, v, minv, sum = 0;
    Node *nodes = new Node[n];
    nodes[0].cost = 0;
    while (true) {
        u = -1; minv = INT_MAX;
        for (i = 0; i < n; i++) {
            if (nodes[i].cost < minv && !nodes[i].used) {
                u    = i;
                minv = nodes[i].cost;
            }
        }
        if (-1 == u) break;
        nodes[u].used = true;
        sum += nodes[u].cost;
        for (v = 0; v < n; v++) {
            if (!nodes[v].used && A[u][v] != -1) {
                nodes[v].cost = A[u][v] < nodes[v].cost ? A[u][v] : nodes[v].cost;
            }
        }
    }
    return sum;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    cout << prim() << endl;
    return 0;
}
