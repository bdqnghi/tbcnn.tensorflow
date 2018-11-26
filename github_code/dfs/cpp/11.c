#ifndef DEPTH_FIRST_SEARCH_CPP_S9MUPCGW
#define DEPTH_FIRST_SEARCH_CPP_S9MUPCGW

#include "graph.h"
#include <vector>
using std::vector;


#include <stack>
using std::stack;


enum class node_color{WHITE,GRAY, BLACK};


class depth_first_search
{
public:
  depth_first_search (Graph & G):G{G}{

    auto n =G.num_vertices();
    colors = vector<node_color>(n,node_color::WHITE);
    start = vector<int>(n,-1);
    finish= vector<int> (n,-1);
    parent = vector<int> (n,-1);
    comp = vector<int> (n,-1);
    time=0;
    c=0;
  }

  virtual ~depth_first_search ()
  {
    colors.clear();
    start.clear();
    finish.clear();
    parent.clear();
  };

 void DFS(int s)
 {
    assert(s>=0);
    assert(s<colors.size());
    
    if(colors[s]!=node_color::WHITE)
      return;
    // state value for source
    colors[s]=node_color::GRAY;
    start[s]=time++;
    comp[s]=c;

    for(auto v : G.neighbors(s))
      if(colors[v]==node_color::WHITE)
      {
        parent[v]=s;
        DFS(v);
      }
    finish[s]=time++;
 }

void DFS()
{

  for(int i=0;i<G.num_vertices();i++)
    if(colors[i]==node_color::WHITE)
      DFS(i);
}

void DFS(vector<int> order)
{
  for(auto v:order)
  {
    DFS(v);
    c++;
    }
}
public:
  Graph &G;
  vector<node_color> colors;
  vector<int> start;
  vector<int> finish;
  vector<int> parent;
  vector<int> comp;
  int time;
  int c;
};

#endif /* end of include guard: DEPTH_FIRST_SEARCH_CPP_S9MUPCGW */
