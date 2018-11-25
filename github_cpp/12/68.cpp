#include<bits/stdc++.h>
using namespace std;
const int MAX = 1e4 + 5;
int spanningTree(vector <pair<int,int> > g[], int n);
int main()
{
	int t ;
	cin>>t;
	while(t--)
	{
	vector <pair<int,int> > adj[MAX];
    int n,e;
    int w, mC;
    cin >> n>> e;
    for(int i = 0;i < e;++i)
    {
    	int x,y;
        cin >> x >> y >> w;
        adj[x].push_back({w, y});
        adj[y].push_back({w, x});
    }
  
    mC= spanningTree(adj, MAX);
    cout << mC << endl;
	}
    return 0;
}



int spanningTree(vector <pair<int,int> > g[], int MAX)
{
	
	unordered_map<int,bool> MST;
	map<int,int> Keys;
	for(int i=0;i<MAX;i++){
	    if(g[i].size()>0){
	        Keys[i]=INT_MAX;
	    }
	}
	int sum=0,v;
	auto it=Keys.begin();
    v=it->first;
    for(int i=0;i<g[v].size();i++){
        Keys[g[v][i].first]=g[v][i].first;
    }
    MST[v]=true;
	while(!Keys.empty()){
	    it=Keys.begin();
	    v=it->first;
	    for(int i=0;i<g[v].size();i++){
	        if(MST[g[v][i].second]==false)
	            Keys[g[v][i].second]=g[v][i].first;
	    }
	    MST[v]=true;
	    sum+=it->second;
	    Keys.erase(v);
	}
	return sum;
}