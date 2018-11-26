//The bread-first-search algorithm starts at a vertex and visits, first the neighbours of it, then the neighbours of 
//the neighbours of it, and so on.
//A particularly useful application of the breadth-first-search algorithm is, therefore, in computing shortest paths.
//This algorithm is best suited to graphs represented using an adjacency list representation.

#include <iostream>
#include <vector>
#include <queue>

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

void bfs(Graph &g, int r){
  vector<bool> visited(g.vertices(),false);
  queue<int> toBeChecked;
  vector<int> edges;
  toBeChecked.push(r);
  visited[r] = true;
  cout<<r<<" ";
  while(!toBeChecked.empty()){
    int toCheck = toBeChecked.front();
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

  bfs(g,0);
  cout<<endl;
  return 0;
}

