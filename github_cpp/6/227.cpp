//bellman-ford for a directed graph using adjacency matrix
/*
5
10
1 2 6
1 5 7
2 3 5
2 5 8
2 4 -4
3 2 -2
4 3 7
4 1 2
5 4 9
5 3 -3
1
*/
#include <bits/stdc++.h>
#define MAX 1000
#define MOD 1000000007
#define INF 99999
#define for_each(i,n) for(i=0;i<n;++i)
#define for_each_dec(i,n) for(i=n-1;i>=0;--i)
typedef long long int LL;

using namespace std;

typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<LL> vll;
typedef vector<vll> vvll;


//fucntion to display a vector
template <typename T>
void displayVector(T v)
{
    for(typename T::iterator i=v.begin();i!=v.end();i++)
    {
        cout<<*i<<" ";
    }
    cout<<endl;
}

//fucntion to display a vector
template <typename T>
void displayVector(T v,int size)
{
    for(typename T::iterator i=v.begin();i!=v.begin()+size;i++)
    {
        cout<<*i<<" ";
    }
    cout<<endl;
}

//function to display a matrix
template <typename T>
void displayMatrix(T mat)
{
    for(typename T::iterator i=mat.begin();i!=mat.end();i++)
    {
            displayVector(*i);       
    }
    cout<<endl; 
}

//function to display a matrix
template <typename T>
void displayMatrix(T mat,int size)
{
    for(typename T::iterator i=mat.begin();i!=mat.begin()+size;i++)
    {
            displayVector(*i,size);       
    }
    cout<<endl; 
}


//fucntion to input a vector
template <typename T>
void inputVector(T &v)
{
    for(typename T::iterator i=v.begin();i!=v.end();i++)
    {
        cin>>*i;
    }
}

//function to input a matrix
template <typename T>
void inputMatrix(T &mat)
{
    for(typename T::iterator i=mat.begin();i!=mat.end();i++)
    {
            inputVector(*i);
    }
}
int dfs(vvi graph,vi vertexVal,vi &visited,int val,int totalVertices,int start=0)
{
    visited[start]=1;
    if(vertexVal[start]==val)
    {
        return start;
    }
    for (int i = 0; i < totalVertices; ++i)
    {
         if(graph[start][i]==1 && visited[i]==0)
         {
            return dfs(graph,vertexVal,visited,val,totalVertices,i);
         }
    }
    return -1;
}

int bfs(vvi graph,vi vertexVal,vi &visited,int val,int totalVertices,int start=0)
{
    queue<int> q;
    q.push(start);
    for(int i=0;i<totalVertices;++i)
    {
        start=q.front();
        q.pop();
        if(vertexVal[start]==val)
        {
            return start;
        }    
        for (int j = 0; j < totalVertices; ++j)
        {
            if(graph[start][j]==1)
            {
                q.push(j);
            }
        }
    }
    return -1;

}
//pathTable-consists predecessor nodes from which we get the shortest path
int bellman_ford(vvi graph,int totalVertices, vi &visited,int sourceNode,vi &distanceTable, vi &pathTable)
{
    //initializing the table with infinity(99999)
    for(int i=0;i<totalVertices;i++)
    {
        distanceTable[i]=INF;  
        pathTable[i]=i;
    }
    distanceTable[sourceNode]=0;
    int source=sourceNode;
    int k=totalVertices-1;

    while(k--)
    {
        for(int j=0;j<totalVertices;j++)
        {
            source=j;
            visited[source]=1;
            //updating distance table
            displayVector(distanceTable,totalVertices);
            for(int i=0;i<totalVertices;i++)
            {
                if(graph[source][i]!=0)
                {
                    //if we found a shorter path then that node goes in the pathTable
                    if(graph[source][i]+distanceTable[source]<distanceTable[i])
                    {
                        distanceTable[i]=graph[source][i]+distanceTable[source];
                        pathTable[i]=source;
                    }
                }
         
            }

        }
    }
    //for negative edge cycles
    int negativeCycle=0;
    for(int i=0;i<totalVertices;i++)
    {
        for(int j=0;j<totalVertices;j++)
        {
            if(graph[i][j]!=0)
            {
                if(graph[i][j]+distanceTable[i]<distanceTable[j])
                {
                    negativeCycle=1;
                    break;
                }
            }
        }
    }
    return negativeCycle;
}
int main()
{
    freopen("input.txt","r",stdin);
    //freopen("output.out","w",stdout);
    int V,E,v1,v2,val,w,source;
    
    vvi graph(1000,vi(1000,0));
    vi vertexVal(1000,0);
    vi visited(1000,0);
    vi distanceTable(1000,0);
    vi pathTable(1000,0);
    cout<<"Enter the number of vertices:"<<endl;
    cin>>V;
    
    cout<<"Enter the number of edges:"<<endl;
    cin>>E;
    cout<<"Enter the edges in the graph in the format (v1,v2,weight)"<<endl;
    for (int i = 0; i < E; ++i)
    {
        cin>>v1>>v2>>w;
        graph[v1-1][v2-1]=w;
    
    }
    cout<<"The graph matrix is:"<<endl;
    displayMatrix(graph,V);
    cout<<"Enter the source node of the graph:";
    cin>>source;
    source=source-1;
    cout<<endl;
    if(bellman_ford(graph,V,visited,source,distanceTable,pathTable)!=0)
    {
        cout<<"Negative weight cycles exist in the graph"<<endl;
        return 0;
    }
    cout<<"The shortest distance of the source node to all other nodes in the graph:"<<endl;
    for(int i=0;i<V;i++)
    {
        if(distanceTable[i]!=INF)
            cout<<"Node"<<i+1<<":"<<distanceTable[i]<<endl;
        else
            cout<<"Node"<<i+1<<":"<<"INF"<<endl;
    }
    
    return 0;

}