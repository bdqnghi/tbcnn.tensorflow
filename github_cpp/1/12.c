#include<bits/stdc++.h>
using namespace std;
template<typename T>
class Graph
{
    map<T,list<T>>l;
    public:
    void addEdge(T u,T v,bool bidir=true)
    {
        l[u].push_back(v);
        if(bidir)
        {
            l[v].push_back(u);
        }
    }
    void bfs(T src)
    {
        queue<T>q;
        map<T,bool>visited;
        q.push(src);
        visited[src]=true;
        while(!q.empty())
        {
            T node =q.front();
            cout<<node<<" ";
            q.pop();

        for(int neighbour:l[node])
        {
            if(!visited[neighbour])
            {
                q.push(neighbour);
                visited[neighbour]=true;
            }
        }
        }
    }
};
int main()
{
    Graph<int>g;
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(0,4);
    g.addEdge(2,4);
    g.addEdge(2,3);
    g.addEdge(3,5);
    g.addEdge(3,5);
    g.addEdge(3,4);
    g.bfs(0);
    return 0;
}
