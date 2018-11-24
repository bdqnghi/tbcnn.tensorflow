#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX_node 100000

struct edg{
    int a,b,w;
    bool operator < (const edg &b) const{
        return w<b.w;
    }
}E[MAX_node+1];
 
int Prev[MAX_node+1];
int parent(int a){
    if(a==Prev[a]) return a;
    return Prev[a]=parent(Prev[a]);
}
 
int main(){
    int node,edge;
    while(scanf("%d%d",&node,&edge)){
         
        int TOTAL=0;
             
        for(int i=1;i<=node;i++) Prev[i]=i;
        for(int i=0;i<edge;i++) scanf("%d%d%d",&E[i].a,&E[i].b,&E[i].w);
         
        sort(E,E+edge);
         
        for(int i=0; i<edge; i++ ){
            int u=parent(E[i].a);
            int v=parent(E[i].b);
             
            if(u!=v){
                TOTAL+=E[i].w;
                Prev[u]=v;
            }
        }
         
        printf("%d\n",TOTAL);
    }
    return 0;
}
 
