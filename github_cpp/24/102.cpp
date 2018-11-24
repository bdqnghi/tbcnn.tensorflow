#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int,int> II;

const int mx=1e4+5;
vector<vector<int> > g(mx),c(mx);

void clr(){
    for(int i=0; i<mx; ++i) g[i].clear(), c[i].clear();
}

LL prims(){
    bitset<mx> taken;
    LL ans=0;

    priority_queue<II, vector<II>, greater<II> > pq;
    pq.push(make_pair(0,1));

    while(!pq.empty()){
        int node=pq.top().second;
        int cost=pq.top().first;

        pq.pop();

        if(!taken[node]){
            ans+=cost;
            taken[node]=1;
        }

        vector<int> v=g[node];
        vector<int> w=c[node];

        for(int i=0; i<v.size(); ++i){
            if(!taken[v[i]]){
                pq.push(make_pair(w[i],v[i]));
            }
        }
    }

    return ans;
}

int main()
{
    int n,m;

    while(cin>>n>>m){
        //clear graph
        clr();

        //scanning graph
        for(int i=0; i<m; ++i){
            int u,v,w;
            cin>>u>>v>>w;

            g[u].push_back(v);
            g[v].push_back(u);

            c[u].push_back(w);
            c[v].push_back(w);
        }

        //process
        LL ans=prims();

        cout<<ans<<endl;
    }

    return 0;
}
