#include <iostream>
#include <vector>
using namespace std;

#define MAX 100
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NIL -1

class Graph{
	int v,e; 		// Vertices and edges
	vector<int>Adj[MAX];	// Adjacency List
	int predecessor[MAX];	
	int color[MAX];		 
	public:
		Graph(){
			cout << "Number of vertices and edges: ";
			cin >> v >> e;
			cout << "Enter the edges:\n";
			int E = e;
			while(E--){
				int s, d;
				cin >> s >> d;
				// Directed graph
				Adj[s-1].push_back(d-1);
				// Uncomment this for undirected graph
				//Adj[d-1].push_back(s-1);
			}
		}
		void dfs(){
			// Initialising the predecessor array
			for(int i=0;i<v;i++)
				predecessor[i] = NIL;
			// All not visited
			for(int i=0;i<v;i++)
				color[i] = WHITE;
			for(int i=0;i<v;i++){
				if(color[i]==WHITE){
					// Root of differnet predecessor subgraph
					cout << "Root: " << i+1 << endl;
					dfs_visit(i);
				}
			}
		}
		void dfs_visit(int s){
			// Processing the vertex s
			color[s] = GRAY;
			for(int i=0;i<Adj[s].size();i++){
				// Check whether the other end point is not visited
				if(color[Adj[s][i]]==WHITE){
					predecessor[Adj[s][i]] = s;
					dfs_visit(Adj[s][i]);
				}
			}
			// Processed the vertex s
			color[s] = BLACK;
		}
};

int main(){
	Graph g;
	// Run the depth first search
	g.dfs();
	return 0;
}
