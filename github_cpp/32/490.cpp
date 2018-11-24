#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <climits>
#include <ctime>
#include <algorithm>
#include <stack>
#include <queue>
#include <list>
#include <sys/time.h>
#include <iomanip>
//#define NDEBUG    //when all assert statements have to be disabled
#include <cassert>
#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++) 
#define present(c,x) ((c).find(x) != (c).end()) 
#define ARRAY_SIZE(arr) (1[&arr]-arr)      
#define lld long long int
#define MOD 1000000007
using namespace std;

typedef struct{
	int key;
	int index;
}node;


typedef struct n{
	struct n *parent;
	int u,v,weight;
	int rank;        //if node is the parent, it keeps track of number of its children. if not, it is -1.
}node;


node* MAKE(int u, int v, int weight)
{
	node *n=(node*)malloc(sizeof(node));
	n->parent=n;
	n->u=u;
	n->v=v;
	n->weight=weight;
	n->rank=0;
}

node *FIND(node *n)
{
	if(n->parent==n)
		return n;
	n->parent=FIND(n->parent);
	return n->parent;
}

void MERGE(node *n1, node *n2)     //merge n1 and n2 and store in n1.
{
	assert(n1->rank!=-1);
	assert(n2->rank!=-1);
	if(n1->rank<n2->rank)
	{
		MERGE(n2,n1);
		return ;
	}
	n2->parent=n1;
	n1->rank=n1->rank+n2->rank+1;
	n2->rank=-1;
}



class Graph          //undirected graphs, change addEdge function for directed graphs
{
private:
	int V;    //number of edges
	vector<node> *adj;    //pointer to array of vectors for storing in adjacency list format
	void find_vertice(int u, int v, vector<node>::iterator &it);
public:
	Graph(int V);
	void addEdge(int u, int v,int weight,bool directed); //join u to v
	void dijkstra(int start);
};

Graph::Graph(int V)
{
	this->V=V;
	adj = new vector<node>[V+1];
}

void Graph::find_vertice(int u, int v, vector<node>::iterator &it)
{

	while(it!=adj[u].end())
	{
		if((*it).index==v)
			return;
	}
}

void Graph::deleteEdge(int u, int v)       //generic function for both directed and undirected
{
	vector<node>::iterator it;
	this->find_vertice(u,v,it);
	int uv=0;           //0->not present, 1-> uv present, 2-> uv and vu present
	if(it!=adj[v].end())
	{
		this->adj[u].erase(it);
		uv=1;
	}
		
	this->find_vertice(v,u,it);
	if(it!=adj[v].end())
	{
		this->adj[v].erase(it);
		uv=2;
	}
	if(uv==0)
		cout<<"no such edge\n";

}

void Graph::addEdge(int u, int v,int weight,bool directed)
{
	node n;
	n.index=v;
	n.key=weight;
	adj[u].push_back(n);
	if(!directed)
	{
		n.index=u;
		adj[v].push_back(n);     //for undirected graph
	}
}



void Graph::dijkstra(int start)
{
	long long int distance[V+1],i;
	node array[V+1];
	for(i=1;i<=V;i++)
		distance[i]=INT_MAX;
	distance[start]=0;
	long long int temp;
	for(i=1;i<=V;i++)
	{
		array[i].key=distance[i];
		array[i].index=i;
	}
	minHeap mh(array,V);
    //bool visited[V+1];
	//memset(visited, false, sizeof visited);
	while(!mh.isEmpty())
	{
		node n=mh.top();
		mh.delete_top();
		if(n.key==INT_MAX)
			break;            //remaining nodes are inaccessible from the given start node
		for(vector<node>::iterator it=adj[n.index].begin();it!=adj[n.index].end();it++)
		{
			temp=distance[n.index]+(*it).key;
			if(distance[(*it).index]>temp)
			{
				distance[(*it).index]=temp;
				mh.decreaseKey((*it).index, temp);
			}
		}
	}
	cout<<"distances from "<<start<<endl;
	for(i=1;i<=V;i++)
		cout<<distance[i]<<endl;
	
}

int main()
{
	node n1(1,2,10);
	node n1(1,3,25);
	node n1(2,3,30);
	node n1(3,4,50);
	Graph g(4);
	g.addEdge();
}
