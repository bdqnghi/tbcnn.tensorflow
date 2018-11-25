#include <iostream>
#include <list>
#include <stack>

using namespace std;

class graph
{
	private:
		list<int>* adj;
		int V;
		void topologicalSortUtil(int s,bool visited[],stack<int>& S)
		{
			visited[s] = true;
			list<int>::iterator itr;
			for(itr = adj[s].begin(); itr != adj[s].end();itr++)
			{
				if(visited[*itr] == false)
				{
					topologicalSortUtil(*itr, visited, S);
				}
			}
			S.push(s);
		}
	public:
		graph(int V)
		{
			this->V = V;
			adj = new list<int>[V];
		}
		void addEdge(int u,int v)
		{
			adj[u].push_back(v);
		}
		void topologicalSort()
		{
			stack<int> S;
			bool *visited = new bool[V];
			for (int i = 0; i < V; ++i)
			{
				visited[i] = false;
			}
			
			for (int i = 0; i < V; ++i)
			{
				if(visited[i] == false)
				{
					topologicalSortUtil(i,visited, S);
				}
			}
			while(S.empty() == false){
				cout<<S.top()<<" ";
				S.pop();
			}
		}

};
int main(){
	graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    g.topologicalSort();
	return 0;
}