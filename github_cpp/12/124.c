#include <iostream>
#include <cstring>

using namespace std;



void prim(size_t n, int** costs, int* result) {
    bool flag[n];
    int lowest[n];
    memset(flag,0,sizeof(flag));
    memset(lowest,0,sizeof(lowest));
    memset(result,0,sizeof(result));
    int cur = 0;                  
    bool done = 0,cnt = 0;
    int m,mindex; 
    memcpy(lowest,costs[cur],n);
    while (!done) {
        m=costs[cur][0]; mindex=0; 
        result[cnt++]=cur;         
        flag[cur]=1;               
        done = 1;                  
        for (size_t i = 1; i < n; i++) {
            if (!flag[i]) done=0;   
            if (costs[cur][i]<m && !flag[i]) {
                mindex=i;
                m=costs[cur][i];
            }
        }
        if (done) break;
        cur=mindex;
        for (size_t i = 0; i < n; i++) {
            lowest[i]=(lowest[i]<costs[cur][i])?lowest[i]:costs[cur][i];
        }
    }
}



void kruskal(size_t n, int** costs, int* result) {

}

int main(void) {

}
