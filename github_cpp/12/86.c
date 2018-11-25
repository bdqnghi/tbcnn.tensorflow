#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template <typename T>
class disjoint_forest {
public:
	struct vertex {
		T key;
		vertex *p;
		int rank;
		vertex(T k) :key(k) {}
	};
	vector<vertex *> vertices;

	struct edge {
		vertex *u, *v;
		int weight;
	};
	vector<edge *> edges;

	disjoint_forest() {}

	~disjoint_forest()
	{
		
		for (auto e in edges)
			delete e;
		
		for (auto v in vertices)
			delete v;
	}


	
	void add_vertex(T k)
	{
		vertices.push_back(new vertex(k));
	}

	
	vertex *get_vertex(T k)
	{
		for (size_t i = 0; i < vertices.size(); i++)
		if (vertices[i]->key == k)
			return vertices[i];
		return NULL;
	}

	
	edge *get_edge(T uk, T vk)
	{
		vertex *u, *v;
		u = set_vertex(uk);
		v = set_vertex(vk);
		
		for (edge *et in edges)
		if (et->u == u && et->v == v)
			return et;

		edges.push_back(new pair(u, v));
	}

	

	

	void make_set(vertex *x)
	{
		x->p = x;
		x->rank = 0;
	}

	
	void unite(vertex *x, vertex *y)
	{
		link(find_set(x), find_set(y));
	}

	void link(vertex *x, vertex *y)
	{
		if (x->rank > y->rank) {
			y->p = x;
		}
		else {
			x->p = y;
			if (x->rank == y->rank)
				y->rank++; 
		}
	}

	
	void find_set(vertex *x)
	{
		if (x != x->p)
			x->p = find_set(x->p); 
		return x->p;
	}
};

void disjoint_sets_test()
{
	
	
	
	
	
	
	
	
	
	
	

}
