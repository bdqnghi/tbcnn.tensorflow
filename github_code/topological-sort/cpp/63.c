/*
    Topological sorting: Maintain a set of visited nodes. Start with a random node. Put it and its child in set recursively.
    if no more unvisited children put in stack. In the end stack gives topological sort order
    Multiple topological orders might exist for the same graph. Depends on the order in which we consider the nodes.
*/

#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <map>
#include <stdlib.h>
#include <string>
#include <queue>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <climits>
#include <set>
#include <stack>
using namespace std;

vector<int> adj[20];    //considering 20 nodes
bool vis[20];
stack<int> st;

void recurse(int n){
    vis[n] = 1;
    for(int i=0; i<adj[n].size(); i++)
        if(!vis[ adj[n][i] ])recurse(adj[n][i]);
    st.push(n);
}

int main(){
    int n,e,n1,n2;    //no of nodes and edges
    cout<<"Enter no of nodes nad edges:";
    cin>>n>>e;
    cout<<"Node1 Node2\n";
    for(int i=0; i<e; i++){
        cin>>n1>>n2;
        adj[n1].push_back(n2);
    }

    for(int i=0; i<n; i++)
        if(!vis[i]) recurse(i);

    while(!st.empty()){
        cout<<st.top();
        st.pop();
    }
    return 0;
}
