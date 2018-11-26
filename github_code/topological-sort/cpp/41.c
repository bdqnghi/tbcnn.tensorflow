//Problem Link https://practice.geeksforgeeks.org/problems/topological-sort/1
#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define fi first
#define se second
#define fu(i,a,n) for(i=a;i<=n;i++)
#define fd(i,a,n) for(i=a;i>=n;i--)
#define rep(i,n)  for(i=0;i<n;i++)
#define si(i)  scanf("%d",&i)
#define ss(s)  scanf("%s",s)
#define sl(i)  scanf("%lld",&i)
#define pi(i)  printf("%d",i)
#define pl(i)  printf("%lld",i);
#define ps()   printf(" ");
#define pn()   printf("\n");
#define all(v)  v.begin(),v.end()
#define vi vector <int>
#define vl vector <ll>
#define N 100005
vector <ll> adj[N];
ll vis[N];
stack <ll> st;
void topo_sort(ll u)
{
    vis[u]=1;
    ll i;
    rep(i,adj[u].size())
    {
        if(!vis[adj[u][i]])
        {
            topo_sort(adj[u][i]);
        }
    }
    //cout<<u<<endl;
    st.push(u);
}
int main()
{
    ll n,m,u,v,i;
    sl(n);
    sl(m);
    fu(i,1,m)
    {
        sl(u);
        sl(v);
        adj[u].pb(v);
    }
    fu(i,1,n)
    {
        if(!vis[i])
        {
            topo_sort(i);
        }
    }
    while(!st.empty())
    {
        pl(st.top());
        ps();
        st.pop();
    }
    pn();
    return 0;
}