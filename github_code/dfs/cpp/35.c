#include<iostream>
using namespace std;
int cost[10][10] , i , j, k , n , top , visit[10] , visited[10] , stk[10] , v;
int main()
{
	int m;
	cout<<"Enter number of vertices \n";
	cin>>n;
	cout<<"Enter number of edges \n";
	cin>>m;
	cout<<"\n Edges \n";
	for(k = 1;k<=m;k++)
	{
		cin>>i>>j;
		cost[i][j] = 1;
	}
	cout<<"Enter initital vertex \n";
	cin>>v;
	cout<<"Order of visited vertices \n";
	cout<<v;
	k = 1;
	visited[v] = 1;
	while(k<n)
	{
		for(j = n;j>=1;j--)
		{
			if(cost[v][j]!=0&&visit[j]!=1&&visited[j]!=1)
			{
				visit[j] = 1;
				stk[top] = j;
				top++;
			}
		}
		v = stk[--top];
		cout<<v<< " ";
		k++;
		visit[v] = 0;
		visited[v] = 1;
	}
	return 0;
}
