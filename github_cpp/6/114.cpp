#include <iostream>
#include <vector>
using namespace std;

#define MAX 100
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NIL -1

class Graph{
	int v,e; 		
	vector<int>Adj[MAX];	
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
				
				Adj[s-1].push_back(d-1);
				
				
			}
		}
		void dfs(){
			
			for(int i=0;i<v;i++)
				predecessor[i] = NIL;
			
			for(int i=0;i<v;i++)
				color[i] = WHITE;
			for(int i=0;i<v;i++){
				if(color[i]==WHITE){
					
					cout << "Root: " << i+1 << endl;
					dfs_visit(i);
				}
			}
		}
		void dfs_visit(int s){
			
			color[s] = GRAY;
			for(int i=0;i<Adj[s].size();i++){
				
				if(color[Adj[s][i]]==WHITE){
					predecessor[Adj[s][i]] = s;
					dfs_visit(Adj[s][i]);
				}
			}
			
			color[s] = BLACK;
		}
};

int main(){
	Graph g;
	
	g.dfs();
	return 0;
}
