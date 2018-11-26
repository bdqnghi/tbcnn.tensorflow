#include<bits/stdc++.h>
using namespace std;
int visited[21]={0};
stack<int>st;
void topologiclsort(int edge[11][11],int s,int x)
{
  visited[s]=1;
  for(int j=1;j<=x;j++)
  {
  	if(!visited[j] && edge[s][j])
  		topologiclsort(edge,j,x);
  }
  	st.push(s);
 
  return;
}
int main()
{
	int x,y,u,v;
	cin>>x>>y;
	int edge[11][11]={0};
	for(int i=0;i<y;i++)
	{
		cin>>u>>v;
      edge[u][v]=1;
	}
	/*for(int i=0;i<x;i++)
	{
		for(int j=0;j<x;j++)
			cout<<edge[i][j]<<" ";
		cout<<"\n";
	}*/
	for(int i=1;i<=x;i++)
	{
      if(!visited[i])
      {
      	topologiclsort(edge,i,x);
      }
	}
	while(!st.empty())
	{
		int top1=st.top();
		cout<<top1<<" ";
		st.pop();
	}



}