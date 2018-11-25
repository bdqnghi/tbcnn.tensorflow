


#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<utility>
#include"FibonacciHeap.h"


#define MAX	0x7fffffff

using namespace std;


struct edgeNode
{
	size_t adjvertex;
	size_t weight;
	edgeNode *nextEdge;
	edgeNode(size_t adj, size_t w) :adjvertex(adj), weight(w), nextEdge(nullptr){}
};

struct edge
{
	size_t u, v;
	size_t weight;
	edge(size_t u_, size_t v_, size_t w) :u(u_), v(v_), weight(w){}
};


class AGraph
{
private:
	vector<edgeNode*> graph;
	size_t nodenum;
	void transformGraph(vector<edge>&);

	AGraph& operator=(const AGraph&);
	AGraph(const AGraph&);
public:
	AGraph(size_t n = 0){editGraph(n); }
	void editGraph(size_t n)
	{
		nodenum = n;
		graph.resize(n + 1);
	}
	size_t size()const { return nodenum; }
	void initGraph();
	edgeNode* search(size_t, size_t);
	void add1Edge(size_t, size_t, size_t);
	void add2Edges(size_t, size_t, size_t);
	void delete1Edge(size_t, size_t);
	void delete2Edges(size_t, size_t);
	size_t kruskal(AGraph*);
	size_t prim(AGraph*,size_t);
	void print();
	void destroy();
	~AGraph(){ destroy(); }
};

void AGraph::initGraph()
{
	size_t start, end;
	size_t w;
	ifstream infile("F:\\testdata\\mst.txt");
	while (infile >> start >> end >> w)
		add1Edge(start, end, w);
}

void AGraph::transformGraph(vector<edge> &E)
{
	for (size_t i = 1; i != graph.size(); ++i)
	{
		edgeNode *curr = graph[i];
		while (curr != nullptr)
		{
			if (i < curr->adjvertex)
			{
				edge e(i, curr->adjvertex, curr->weight);
				E.push_back(e);
			}
			curr = curr->nextEdge;
		}
	}
}

edgeNode* AGraph::search(size_t start, size_t end)
{
	edgeNode *curr = graph[start];
	while (curr != nullptr && curr->adjvertex != end)
		curr = curr->nextEdge;
	return curr;
}

void AGraph::add1Edge(size_t start, size_t end, size_t weight)
{
	edgeNode *curr = search(start, end);
	if (curr == nullptr)
	{
		edgeNode *p = new edgeNode(end, weight);
		p->nextEdge = graph[start];
		graph[start] = p;
	}
}

inline void AGraph::add2Edges(size_t start, size_t end, size_t weight)
{
	add1Edge(start, end, weight);
	add1Edge(end, start, weight);
}

void AGraph::delete1Edge(size_t start, size_t end)
{
	edgeNode *curr = search(start, end);
	if (curr != nullptr)
	{
		if (curr->adjvertex == end)
		{
			graph[start] = curr->nextEdge;
			delete curr;
		}
		else
		{
			edgeNode *pre = graph[start];
			while (pre->nextEdge->adjvertex != end)
				pre = pre->nextEdge;
			pre->nextEdge = curr->nextEdge;
			delete curr;
		}
	}
}

inline void AGraph::delete2Edges(size_t start, size_t end)
{
	delete1Edge(start, end);
	delete1Edge(end, start);
}

size_t AGraph::kruskal(AGraph *mst)
{
	struct findRoot:public binary_function<vector<size_t>,size_t,size_t>
	{
		size_t operator()(vector<size_t> &UFS, size_t v)const
		{
			if (v == UFS[v]) return v;
			UFS[v] = findRoot()(UFS, UFS[v]);
			return UFS[v];
		}
	};
	struct edgeCompare:public binary_function<edge,edge,bool>
	{
		bool operator()(const edge &left, const edge &right)const
		{
			return left.weight < right.weight;
		}
	};
	vector<edge> E;
	transformGraph(E);
	vector<size_t> UFS(nodenum + 1);
	size_t sum = 0, cnt = 0;
	for (size_t i = 1; i <= nodenum; ++i)
		UFS[i] = i;
	sort(E.begin(), E.end(), edgeCompare());
	for (size_t i = 0; i != E.size(); ++i)
	{
		size_t u_root = findRoot()(UFS, E[i].u), v_root = findRoot()(UFS, E[i].v);
		if (u_root != v_root)
		{
			sum += E[i].weight;
			mst->add2Edges(E[i].u, E[i].v, E[i].weight);
			UFS[u_root] = v_root;
			++cnt;
		}
		if (cnt == nodenum - 1) break;
	}
	return sum;
}

size_t AGraph::prim(AGraph *mst,size_t u)
{
	vector<size_t> parent(nodenum + 1);
	
	vector<fibonacci_heap_node<size_t,size_t>*> V(nodenum + 1);
	fibonacci_heap<size_t, size_t> Q;
	for (size_t i = 1; i <= nodenum; ++i)
	{
		parent[i] = i;
		if (i == u) V[i] = Q.insert(0, i);
		else V[i] = Q.insert(MAX, i);
	}
	size_t sum = 0;
	while (!Q.empty())
	{
		pair<size_t, size_t> min = Q.extractMin();
		V[min.second] = nullptr;
		sum += min.first;
		for (edgeNode *curr = graph[min.second]; curr; curr = curr->nextEdge)
		{
			if (V[curr->adjvertex] != nullptr && curr->weight < V[curr->adjvertex]->key)
			{
				Q.decreaseKey(V[curr->adjvertex], curr->weight);
				parent[curr->adjvertex] = min.second;
			}
		}
		if (min.second != u) mst->add2Edges(parent[min.second], min.second,min.first);
	}
	return sum;
}

inline void AGraph::print()
{
	for (size_t i = 1; i != graph.size(); ++i)
	{
		edgeNode *curr = graph[i];
		cout << i;
		if (curr == nullptr) cout << " --> null";
		else
			while (curr != nullptr)
			{
				cout << " --<" << curr->weight << ">--> " << curr->adjvertex;
				curr = curr->nextEdge;
			}
		cout << endl;
	}
}

void AGraph::destroy()
{
	for (size_t i = 1; i != graph.size(); ++i)
	{
		edgeNode *curr = graph[i], *pre;
		while (curr != nullptr)
		{
			pre = curr;
			curr = curr->nextEdge;
			delete pre;
		}
		graph[i] = curr;
	}
}

const size_t nodenum = 9;

size_t main()
{
	AGraph graph(nodenum), mst(nodenum);
	graph.initGraph();
	graph.print();
	cout << endl;
	cout << graph.kruskal(&mst) << endl;
	mst.print();
	getchar();
	return 0;
}