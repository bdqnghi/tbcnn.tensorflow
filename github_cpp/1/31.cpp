#include<iostream>
using namespace std;
int cost[10][10] , i , j , k, n , qu[10] , front , rare , v , visited[10] , visit[10];
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
	cout<<"Enter initial vertex \n";
	cin>>v;
	cout<<"Visisted vertices \n";
	cout<<v;
	visited[v] = 1;
	k = 1;
	while(k<n)
	{
		for(j = 1;j<=n;j++)
		{
			if(cost[v][j]!=0&&visited[j]!=1&&visit[j]!=1)
			{
				visit[j]  =1;
				qu[rare++] = j;
			}
		}
		v = qu[front++];
		cout<<v<<" ";
		k++;
		visit[v] = 0;
		visited[v] = 1;
	}
	return 0;
}
