#include <iostream>
#include <vector>
#include <list>
#include <stack>
using namespace std;
class Graph{
   int V;
   vector<list<int> > adjlist;
  public:
   Graph(int nov);
   void addedge(int u,int v);
   void topologicalsort();
   void topologicalsortutil(int v,vector<bool>&visited,stack<int>&st);

};
Graph::Graph(int nov)
{
   V=nov;
   for(int i=0;i<=V;i++)
     adjlist.push_back(list<int>());
}
void Graph::addedge(int u,int v)
{
  adjlist[u].push_back(v);
}
void Graph::topologicalsortutil(int v,vector<bool>&visited,stack<int>&st)
{
  visited[v]=true;
//  cout<<v<<" "<<visited[v]<<"\n";
  list<int>::iterator i;
  for(i=adjlist[v].begin();i!=adjlist[v].end();i++)
  {
    if(!visited[*i])
    {
//      cout<<*i<<"\n";
      topologicalsortutil(*i,visited,st);
    }
  }
  st.push(v);
}
void Graph::topologicalsort()
{
  stack<int> st;
  vector<bool>visited(V+1,false);

  for(int i=0;i<V;i++)
      if(!visited[i])
          topologicalsortutil(i,visited,st);
  while(!st.empty())
  {
    cout<<st.top()<<" ";
    st.pop();
  }
  cout<<"\n";
}
int main()
{
  Graph g(6);
  g.addedge(5, 2);
  g.addedge(5, 0);
  g.addedge(4, 0);
  g.addedge(4, 1);
  g.addedge(2, 3);
  g.addedge(3, 1);
                           
  cout << "Following is a Topological Sort of the given graph \n";
  g.topologicalsort();
  return 0;
}
