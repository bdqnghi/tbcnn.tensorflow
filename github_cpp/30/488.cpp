/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-04-04 20:26:36
* Filename     : dijkstra.cpp
* Description  :
 * 贪心+动态
 * www.programgo.com/article/4721147659
 * 能得到最优解，但是效率底
***********************************************************/
#include <iostream>
#include <malloc.h>

#include<stack>
using namespace std;
#define INT_MAX 9999
#define N 100
#define M 100
typedef struct node
{
    int matrix[N][M];      //邻接矩阵
    int n;                 //顶点数
    int e;                 //边数
}MGraph;

void DijkstraPath(MGraph g,int *dist,int *path,int v0)   //v0表示源顶点
{
    int i,j,k;
    bool *visited=(bool *)malloc(sizeof(bool)*g.n);
    for(i=0;i<g.n;i++)     //初始化
    {
        if(g.matrix[v0][i]>0&&i!=v0)
        {
            dist[i]=g.matrix[v0][i];
            path[i]=v0;     //path记录最短路径上从v0到i的前一个顶点
        }
        else
        {
            dist[i]=INT_MAX;    //若i不与v0直接相邻，则权值置为无穷大
            path[i]=-1;
        }
        visited[i]=false;
        path[v0]=v0;
        dist[v0]=0;
    }
    visited[v0]=true;
    for(i=1;i<g.n;i++)     //循环扩展n-1次
    {
        int min=INT_MAX;
        int u;
        for(j=0;j<g.n;j++)    //寻找未被扩展的权值最小的顶点
        {
            if(visited[j]==false&&dist[j]<min)
            {
                min=dist[j];
                u=j;
            }
        }
        visited[u]=true;
        for(k=0;k<g.n;k++)   //更新dist数组的值和路径的值
        {
            if(visited[k]==false&&g.matrix[u][k]>0&&min+g.matrix[u][k]<dist[k])
            {
                dist[k]=min+g.matrix[u][k];
                path[k]=u;
            }
        }
    }
}

//打印最短路径上的各个顶点
void showPath(int *path,int v,int v0)
{
    stack<int> s;
    int u=v;
    while(v!=v0)
    {
        s.push(v);
        v=path[v];
    }
    s.push(v);
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
}

int main()
{
    int n,e;     //表示输入的顶点数和边数
    while(cin>>n>>e&&e!=0)
    {
        int i,j;
        int s,t,w;      //表示存在一条边s->t,权值为w
        MGraph g;
        int v0;
        int *dist=(int *)malloc(sizeof(int)*n);
        int *path=(int *)malloc(sizeof(int)*n);
        for(i=0;i<N;i++)
            for(j=0;j<M;j++)
                g.matrix[i][j]=0;
        g.n=n;
        g.e=e;
        for(i=0;i<e;i++)
        {
            cin>>s>>t>>w;
            g.matrix[s][t]=w;
        }
        while(cin>>v0)
        {//输入源顶点
            DijkstraPath(g,dist,path,v0);
            for(i=0;i<n;i++)
            {
                if(i!=v0)
                {
                    showPath(path,i,v0);
                    cout<<dist[i]<<endl;
                }
            }
        }
    }
    return 0;
}

