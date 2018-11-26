/*
Problem statement link https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/practice-problems/algorithm/monk-and-tree-1/

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct node {
    ll wt;
    pair<ll, ll> edge;
};
struct node2 {
    ll val;
    ll size;
};
bool comparator(const node& a, const node& b) {
    return a.wt > b.wt;
}
vector<node2> arr;

void initialize(ll n) {
    arr.resize(n);
    for(ll i = 0; i < n; ++i) {
        arr.at(i) = {i, 1};
    }
}
ll root(ll i) {
    while(arr.at(i).val != i) {
        arr.at(i).val = arr.at(arr.at(i).val).val;
        i = arr.at(i).val;
    }
    return i;
}
void Union(ll a, ll b) {
    ll r_a = root(a);
    ll r_b = root(b);
    if(r_a == r_b) 
        return;
    if(arr.at(r_a).size < arr.at(r_b).size) {
        arr.at(r_a).val = arr.at(r_b).val;
        arr.at(r_b).size +=  arr.at(r_a).size;
    }
    else {
        arr.at(r_b).val = arr.at(r_a).val;
        arr.at(r_a).size +=  arr.at(r_b).size;
    }
    
}
ll find(ll a, ll b) {
    return root(a) == root(b);
}
ll minCost(vector<node>& graph) {
    ll mincost = 0;
    for(ll j =1; j < graph.size(); ++j) {
        const node& i = graph.at(j);
        if(!find(i.edge.first, i.edge.second)) {
            Union(i.edge.first, i.edge.second);
        } 
        else 
            mincost += i.wt;   
    }
    for(int i = 1; i < arr.size(); ++i) {
        if(i == arr.at(i).val)
           ++mincost;
    }
    return mincost - 1;
}
int main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    cin>>t;
    while(t--) {
        ll n, m;
        cin>>n>>m;
        initialize(n+1);
        vector<node> graph(m+1);
        for(ll i = 1; i <= m; ++i) {
            ll x, y;
            cin>>x>>y;
            graph.at(i).wt = abs(x-y);
            graph.at(i).edge = make_pair(x, y);
        }
        sort(graph.begin()+1, graph.end(), comparator);
    
        cout<<minCost(graph)<<endl;
    }
    
    return 0;
}