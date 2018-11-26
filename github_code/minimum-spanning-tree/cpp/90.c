//Problem Statement -- https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/practice-problems/algorithm/panda-and-destruction/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct node {
    ll outdegree = 0;
    ll value = 0;
    vector<ll> l;
};

bool comp(const node& a, const node& b) {
    if(a.outdegree == b.outdegree)
        return a.value < b.value;
    
    return a.outdegree > b.outdegree;
}

int main() {
    ll n, m;
    cin>>n>>m;

    vector<node> v(n+1), v1(n+1);

    while(m--) {
        ll x, y;
        cin>>x>>y;

        v.at(x).value = x;
        ++v.at(x).outdegree;
        v1.at(x).l.push_back(y);
        v1.at(x).value = x;
        ++v1.at(x).outdegree;

        v.at(y).value = y;
        ++v.at(y).outdegree;
        v1.at(y).l.push_back(x);
        v1.at(y).value = y;
        ++v1.at(y).outdegree;
    }

    sort(v.begin()+1, v.end(), comp);

    ll cnt = 0, desc = 0;

    for(ll i = 1; i < v.size(); ++i) {
        if(v1.at(v.at(i).value).outdegree <= 0) {
            ++cnt;
            if(cnt >= v.size()-1) {
                cout<<desc;
                break;
            }
            continue;
        }

        else {
            v1.at(v.at(i).value).outdegree = 0;
            ++desc;
            ++cnt;
        }

        if(cnt >= v.size()-1) {
            cout<<desc;
            break;
        }

        for(const ll& j : v1.at(v.at(i).value).l) {
            if(v1.at(j).outdegree > 0)
                --v1.at(j).outdegree;
        }
    }

    return 0;
}