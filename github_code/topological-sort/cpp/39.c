//dfs for directed graph
#include<iostream>
#include<vector>
#include<stack>

using namespace std;

stack <int> Stack;

void dfsvisit(int u,vector <int> adj[],vector <bool> &visited){
visited[u]=true;
for(int i=0;i<adj[u].size();i++){
if( visited[adj[u][i]] == false)
dfsvisit(adj[u][i],adj,visited);
}
Stack.push(u);

}

void dfs(vector <int> adj[],int v){
	vector <bool> visited(v,false);
	for(int u=0;u<v;u++)
          if(visited[u]==false)
		  dfsvisit(u,adj,visited);
}

int main(){
	int i,e,v,x,y;
	cout<<"enter the number of vertices and edges";
	cin>>v>>e;
        
	vector <int> adj[v];
	for(i=0;i<e;i++){
        cin>>x>>y;
	adj[x].push_back(y);
	}

	dfs(adj,v);
	while( Stack.empty()==false)
	{
		cout<<Stack.top()<<" ";
		Stack.pop();
	}
	return 0;}
     
	
