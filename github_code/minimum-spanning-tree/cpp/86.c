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
		// free edges
		for (auto e in edges)
			delete e;
		// free vertices
		for (auto v in vertices)
			delete v;
	}


	// 
	void add_vertex(T k)
	{
		vertices.push_back(new vertex(k));
	}

	// get vertex by key
	vertex *get_vertex(T k)
	{
		for (size_t i = 0; i < vertices.size(); i++)
		if (vertices[i]->key == k)
			return vertices[i];
		return NULL;
	}

	// get edge by keys
	edge *get_edge(T uk, T vk)
	{
		vertex *u, *v;
		u = set_vertex(uk);
		v = set_vertex(vk);
		//edge *e = NULL;
		for (edge *et in edges)
		if (et->u == u && et->v == v)
			return et;

		edges.push_back(new pair(u, v));
	}

	/* minimum-spanning-tree Kruskal algorithm.
	MST-KRUSKAL(G, w)
	1 A = {}
	2 for each vertex v in G.V
	3     MAKE-SET(v)
	4 sort the edges of G.E into nondecreasing order by weight w
	5 for each edge (u, v) in G.E, taken in nondecreasing order by weight
	6     if FIND-SET(u) != FIND-SET(v)
	7         A = A + {(u, v)}
	8         UNION(u, v)
	9 return A
	*/

	// disjoint sets operations

	void make_set(vertex *x)
	{
		x->p = x;
		x->rank = 0;
	}

	// union by rank
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
				y->rank++; // 0 -> 1
		}
	}

	// path compression: two pass method.
	void find_set(vertex *x)
	{
		if (x != x->p)
			x->p = find_set(x->p); // all nodes will point to root vertex directly.
		return x->p;
	}
};

void disjoint_sets_test()
{
	// input:
	// vertices:
	// a,b,c,d,e,f,g,h,i,j
	// edges:
	// b,d
	// e,g
	// a,c
	// h,i
	// a,b
	// e,f
	// b,c

}
