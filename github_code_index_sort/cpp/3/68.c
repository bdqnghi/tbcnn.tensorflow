#include<iostream>
#include<stack>
#include<list>
#include<vector>

using namespace std;

class Graph{
	//number of vertices
	int V;
	//pointer to an array containing adjacency lists
	list<int> *adj;
	vector<int> indegree;

	void topological_sort_utils(int v, bool visited[], stack<int> &stack);
	void all_topological_sort_utils(vector<int> &res, bool visited[]);
public:
	//constructor
	Graph(int V);
	//function to add edge to graph
	void add_edge(int u, int v);
	//print topological sort of Graph(DAG)
	void topological_sort();
	void all_topological_sort();
};

Graph::Graph(int V){
	this->V=V;
	adj= new list<int>[V];
	for(int i=0;i<V;++i){
		indegree.push_back(0);
	}
}

void Graph::add_edge(int u, int v){
	//add 'v' to adjacency list of u
	adj[u].push_back(v);
	indegree[v]++;
}

void Graph::all_topological_sort_utils(vector<int> &res, bool visited[]){
	bool flag=false;

	for(int i=0;i<V;++i){
		if(indegree[i]==0 && !visited[i]){
			list<int>::iterator j;
			for(j=adj[i].begin();j!=adj[i].end();++j){
				indegree[*j]--;
			}

			res.push_back(i);
			visited[i]=true;
			all_topological_sort_utils(res, visited);

			//resetting visited, res and indegree for backtracking
			visited[i]=false;
			res.erase(res.end()-1);
			for(j=adj[i].begin();j!=adj[i].end();++j){
				indegree[*j]++;
			}
			flag=true;
		}
	}	

	if(!flag){
		for(int i=0;i<res.size();++i){
			cout<<res[i]<<" ";
		}cout<<endl;
	}

}

void Graph::topological_sort_utils(int v, bool visited[], stack<int> &stack){
	visited[v]=true;

	list<int>::iterator i;
	for(i=adj[v].begin();i!=adj[v].end();++i){
		if(!visited[*i]){
			topological_sort_utils(*i, visited, stack);
		}
	}

	stack.push(v);
}

void Graph::all_topological_sort(){
	bool *visited = new bool[V];
	for(int i=0;i<V;++i){
		visited[i]=false;
	}

	vector<int> res;
	all_topological_sort_utils(res, visited);
}

void Graph::topological_sort(){
	stack<int> stack;

	//mark all vertices as not visited
	bool *visited= new bool[V];
	for(int i=0;i<V;++i){
		visited[i]=false;
	}

	for(int i=0;i<V;++i){
		if(visited[i]==false){
			topological_sort_utils(i, visited, stack);
		}
	}

	while(stack.empty()==false){
		cout<<stack.top()<<" ";
		stack.pop();
	}cout<<endl;
}



int main(){

	Graph g(6);
	g.add_edge(5, 2);
    g.add_edge(5, 0);
    g.add_edge(4, 0);
    g.add_edge(4, 1);
    g.add_edge(2, 3);
    g.add_edge(3, 1);
    
    cout<<"Topological Sort: ";
    g.topological_sort();

    cout<<"All Topological Sorts: \n";
    g.all_topological_sort();

	return 0;
}