#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N,M,A,C,mod;
ll X,ans=0;

typedef struct node
{
    int u,v,w;
}node;

inline ll getnext()
{
    X= ((X * A)%mod + C )%mod;
    return X;
}

int *parent;

int find(int a)
{
    while(a!=parent[a])
    {
        a=parent[parent[a]];
        parent[a]=parent[parent[a]];
    }
    return a;
}

void unions(int a,int b)
{
    int x=find(a);
    int y=find(b);
    parent[x]=y;
}

struct comp
{
    bool operator()(const node &a, const node &b)
    {
        return a.w<b.w;
    }
};

vector<node> g;

void MST()
{
    ans=0;
    for(int i=0;i<N;i++)
    {
        parent[i]=i;
    }
    sort(g.begin(),g.end(),comp());
    vector<node>temp;
    int sz=g.size();
    for(int i=0;i<sz;i++)
    {
        int u=g[i].u;
        int v=g[i].v;
        if(u==v)
            continue;
        int w=g[i].w;
        if(find(u)!=find(v))
        {
            unions(u,v);
            ans+=w;
            temp.push_back(g[i]);
        }
    }
    g=temp;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>N>>M>>X>>A>>C>>mod;
    parent=new int[N];
    node temp;
    for(int i=0;i<M;i++)
    {
        int u,v,w;
        u=getnext()%N;
        v=getnext()%N;
        w=getnext();
        if(u==v)
            continue;
        temp.u=u;
        temp.v=v;
        temp.w=w;
        g.push_back(temp);
        if(g.size()>(unsigned)2*N)
            MST();
    }
    MST();
    cout<<ans<<endl;
    return 0;
}

