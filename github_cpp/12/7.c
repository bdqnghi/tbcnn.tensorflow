#include<bits/stdc++.h>

using namespace std;
typedef pair<int,int> ii;

const int MX_N = 20002;
const int MX_M = 30003;

int p[MX_N],M,N;

int find(int i){ return p[i] = (i==p[i] ? i : find(p[i]));}
void join(int a, int b){
    int pa = find(a);
    int pb = find(b);
    if(pa!=pb)
        p[pa]=pb;
}
bool connected(int a, int b){ return find(a)==find(b);}

struct edge {
    int x,y,w;
    edge(int _x, int _y, int _w) : x(_x), y(_y), w(_w) {}
    bool operator < (edge e) const {
        return w < e.w;
    }
};

int main(){
    while(scanf("%d %d",&N,&M),N||M){
        for(int i = 0; i < N; i++)
            p[i]=i;
        vector<edge> eList;
        vector<ii> treeList;
        int u,v,w;
        for(int i = 0; i < M; i++){
            scanf("%d %d %d",&u,&v,&w);
            eList.push_back(edge(u,v,w));
        }
        sort(eList.begin(),eList.end());
        int cost = 0;
        int sz=N;
        for(auto i = eList.begin(); i != eList.end(); i++){
            v=(*i).x; u=(*i).y; w=(*i).w;
            if(!connected(u,v)){
                join(u,v);
                treeList.push_back(make_pair(min(u,v),max(u,v)));
                sz--;
                cost+=w;
            }
        }
        if(sz!=1)
            puts("Impossible");
        else {
            printf("%d\n",cost);
            sort(treeList.begin(), treeList.end());
            for(int i = 0; i < treeList.size(); i++){
                printf("%d %d\n",treeList[i].first,treeList[i].second);
            }
        }
    }
    return 0;
}
