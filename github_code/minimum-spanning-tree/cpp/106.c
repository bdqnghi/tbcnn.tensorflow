/*

Written  by:- Hemant Kumar Mangwani on 03/08/17
references :-
 https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/tutorial/
 https://www.youtube.com/watch?v=oP2-8ysT3QQ&t=821s
 https://www.youtube.com/watch?v=cplfcGZmX7I&t=7s
*/http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1000001
#define pii pair<ll,ll>
vector<pii>a[MAX];
bool v[MAX]={false};

ll prims(ll x)
{
    priority_queue<pii,vector<pii>,greater<pii>>q;
    ll mc=0;
    pii p;
    q.push({0,x});

    while(!q.empty())
    {
        p=q.top();
        q.pop();
        x=p.second;
        if(v[x]==true) continue;
        v[x]=true;
        mc=mc+p.first;
        for(ll i=0;i<a[x].size();i++)
        {
            ll y=a[x][i].second;
            if(v[y]==false)
            {
                q.push(a[x][i]);
            }
        }
    }
    return mc;
}

int main()
{
  ll n,e;
  cout<<"Enter no of nodes and edges\n";
  cin>>n>>e;
  for(ll i=0;i<e;i++)
  {
      ll x,y,w;
      cin>>x>>y>>w;
      a[x].push_back({w,y});
      a[y].push_back({w,x});
  }
  cout<<prims(1)<<"\n";
    return 0;
}
