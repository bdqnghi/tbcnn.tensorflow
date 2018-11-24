#include <iostream>
using namespace std;
#define NUM 10000000

int n;
int a[105][105];

int prim(){
    int u,minv;
    int sum = 0;
    int d[105],p[105],state[105];
    for(int i=0;i<n;i++){
        d[i] = NUM;
        p[i] = -1;
        state[i] = 0;
    }
    d[0] = 0;
    while(1){
        minv = NUM;
        u = -1;
        for(int i=0;i<n;i++){
            if(minv > d[i] && state[i] != 2){
                u = i;
                minv = d[i];
            }
        }
        if(u == -1) break;
        state[u] = 2;
        for(int v=0;v<n;v++){
            if(state[v] != 2 && a[u][v] != NUM){
                if(d[v] > a[u][v]){
                    d[v] = a[u][v];
                    p[v] = u;
                    state[v] = 1;
                }
            }
        }
        sum = 0;
        for(int i=0;i<n;i++){
            if(p[i] != -1) sum += a[i][p[i]];
        }
    }
    return sum;
}

int main(){
    int e;
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          cin >> e;
          if(e == -1){
              a[i][j] = NUM;
          }else{
              a[i][j] = e;
          }
        }
    }
    cout << prim() << endl;
}