//The depth-first-search algorithm is similar to the standard algorithm for traversing binary trees; it first 
//fully explores one subtree before returning to the current node and then exploring the other subtree. 
//Another way to think of depth-first-search is by saying that it is similar to breadth-first search except that it 
//uses a stack instead of a queue.
//Although depth-first-search may best be thought of as a recursive algorithm, recursion is not the best way to implement it.
//The depth-first-search algorithm can be used to detect cycles in the graph.
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph{
protected:
  int numOfVertices;
  vector<vector<int>> adjLists;
public:
  Graph(int n){
    numOfVertices = n;
    for(int i=0; i<numOfVertices; i++){
      adjLists.push_back({});
    }
  }
  ~Graph(){
    
  }
  void addEdge(int i, int j){
    adjLists[i].push_back(j);
  }
  void removeEdge(int i, int j){
    for(int k=0; k<adjLists[i].size(); k++){
      if(adjLists[i][k] == j){
	adjLists[i].erase(adjLists[i].begin()+k);
      }
    }
  }
  bool hasEdge(int i, int j){
    for(int k=0; k<adjLists[i].size(); k++){
      if(adjLists[i][k] == j){
	return true;
      }
    }
    return false;
  }
  void outEdges(int i, vector<int> &edges){
    edges = adjLists[i];
  }
  void inEdges(int i, vector<int> &edges){
    for(int j=0; j<numOfVertices; j++){
      for(int k=0; k<adjLists[j].size(); k++){
	  if(adjLists[j][k]==i){
	    edges.push_back(j);
	  }
      }
    }
  }
  int vertices(){
    return numOfVertices;
  }
};

enum State{
  Unvisited,
  Visiting,
  Visited
};
//Recursive implementation.
void dfs(Graph &g, int i, vector<int> &stateArray){
  stateArray[i] = Visiting;
  vector<int> edges;
  g.outEdges(i,edges);
  cout<<i<<" ";
  for(int edge:edges){
    if(stateArray[edge]==Unvisited){
      stateArray[edge] = Visiting;
      dfs(g,edge,stateArray);
    }
  }
  stateArray[i] = Visited;
}
void rdfs(Graph &g, int r){
  vector<int> stateArray(g.vertices(),Unvisited);
  dfs(g,r,stateArray);
}


//Non-recursive implementation 1
void nrdfs1(Graph &g, int r){
  vector<int> stateArray(g.vertices(),Unvisited);
  stack<int> toBeChecked;
  vector<int> edges;
  toBeChecked.push(r);
  cout<<r<<" ";
  while(!toBeChecked.empty()){
    int toCheck = toBeChecked.top();
    stateArray[toCheck] = Visiting;
    toBeChecked.pop();
    g.outEdges(toCheck,edges);
    for(int edge:edges){
      if(stateArray[edge]==Unvisited){
	toBeChecked.push(edge);
	cout<<edge<<" ";
      }
    }
    stateArray[toCheck] = Visited;
  }
}


//Non-recursive implementation 2
void nrdfs2(Graph &g, int r){
  vector<bool> visited(g.vertices(),false);
  stack<int> toBeChecked;
  vector<int> edges;
  toBeChecked.push(r);
  visited[r] = true;
  cout<<r<<" ";
  while(!toBeChecked.empty()){
    int toCheck = toBeChecked.top();
    toBeChecked.pop();
    g.outEdges(toCheck,edges);
    for(int edge:edges){
      if(!visited[edge]){
	toBeChecked.push(edge);
	visited[edge] = true;
	cout<<edge<<" ";
      }
    }
  }
}
int main(){
  Graph g(4);
  g.addEdge(0,0);
  g.addEdge(0,1);
  g.addEdge(1,2);
  g.addEdge(1,3);
  g.addEdge(2,2);
  g.addEdge(2,3);

  rdfs(g,0);
  cout<<endl;
  nrdfs1(g,0);
  cout<<endl;
  nrdfs2(g,0);
  cout<<endl;
  return 0;
}

