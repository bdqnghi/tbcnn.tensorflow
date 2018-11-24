#include<bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f

int maze[101][101]; //记录各个路的距离
int vis[101];//判断是否被纳入集合
int d[101];//源点到各个点的最短距离
int n;//点的个数


void Dijkstra(int s) //s即为源点
{
    d[s]=0;//源点到源点距离为0
    for(int i=1;i<=n;i++) //i并不是定位作用，而是计数
    {
        int u=-1;  //下一个挪入的点的索引
        for(int j=1;j<=n;j++)
            if(!vis[j])
            {
                if(u==-1||d[u]>d[j]) u=j;//找T到S的最短距离
            }
        vis[u]=1;//把最短距离的T端的点挪入S集合

        for(int j=1; j<=n; ++j)
        {
            if(!vis[j])
	    {
		d[j]=min(d[j],d[u]+maze[u][j]);
	    }
           
           //用d[x]记录 在S集合内 从源点到x的最短距离
           //正是因为每挪动一个就要计算一次 所以引入i变量
	}
    }
    
}
int main()
{
    int m;
    while(cin>>n>>m&&n)
    {
        memset(maze,INF,sizeof(maze));
        memset(vis,0,sizeof(vis));
        memset(d,INF,sizeof(d));
        while(m--)
        {
            int a,b,c;
            cin>>a>>b>>c;
            maze[a][b]=maze[b][a]=c;
        }
        Dijkstra(1);
        cout<<d[n]<<endl;
    }
    return 0;
}
