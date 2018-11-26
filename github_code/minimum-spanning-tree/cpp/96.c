/*
 
Written  by:- Hemant Kumar Mangwani on 03/08/17
references :-
 https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/tutorial/
https://www.youtube.com/watch?v=fAuF0EuZVCk&t=423s
https://www.youtube.com/watch?v=tKwnms5iRBU&t=2054s
https://www.youtube.com/watch?v=71UQH7Pr9kU
http://www.geeksforgeeks.org/greedy-algorithms-set-2-kruskals-minimum-spanning-tree-mst/
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[100000001];
vector<pair<ll,pair<ll,ll>>> v;

ll root(ll i)
{
    while(a[i]!=i)
    {
        a[i]=a[a[i]];
        i=a[i];
    }
    return i;
}

void unions(ll x,ll y)
{
    a[root(x)]=a[root(y)];
}


ll kruskals(ll e)
{
    ll x,y,w,mc=0,i;
    for(i=0;i<e;i++)
    {
     x=v[i].second.first;
     y=v[i].second.second;
     w=v[i].first;
     if(root(x)!=root(y))
     {
         unions(x,y);
         mc+=w;
     }
   }
    return mc;
}




//driver
int main()
{
    ll n,e,i;
    cout<<"Enter no of nodes and edges\n";
    cin>>n>>e;
    //Initilaization
    for(i=0;i<n;i++) a[i]=i;
    for(i=0;i<e;i++)
    {
        ll x,y,w;
        cin>>x>>y>>w;
        v.push_back(make_pair(w,make_pair(x,y)));
    }
    sort(v.begin(),v.end());
    cout<<kruskals(e)<<"\n";
    return 0;
}
