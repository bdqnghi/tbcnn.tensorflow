/*
	Simple implementation of Prim's MST algorithm
	(Should be rewritten to handle conditions like overflow, etc...)
*/

// g[v] is a vector of (len, u) pairs

vector<pii> g[N];

int minimum_spanning_tree()
{
	set<int> seen;
	set<pii> q;
	q.insert({0, 0});
	int len = 0;
	while(!q.empty())
	{
		auto p = q.begin();
		len += p->first;
		int v = p->second;
		q.erase(p);
		if(!seen.count(v))
		{
			seen.insert(v);
			for(auto e : g[v])
				q.insert(e);
		}
	}
	return len;
}



/*
	Implementation of Chu-Liu-Edmonds algorithm for computing the MST on directed graphs
*/

struct edge { int u, v, c; };
vector<edge> es;
edge * pre[N];
int n, id[N], pass[N];

int directed_minimum_spanning_tree(int root)
{
	int ans = 0, m = n;
	while(true)
	{
		clr0(pre), clr1(id), clr1(pass);
		for(auto & e : es) if(!pre[e.v] || e.c < pre[e.v]->c)
			pre[e.v] = &e;
		rep(v, m) if(v != root && !pre[v])
			return -1;
		int k = 0;
		rep(v, m) if(v != root)
		{
			ans += pre[v]->c;
			int u = v;
			while(u != root && pass[u] == -1)
			{
				pass[u] = v;
				u = pre[u]->u;
			}
			if(pass[u] == v)
			{
				while(id[u] == -1)
					id[u] = k, u = pre[u]->u;
				k++;
			}
		}
		if(k == 0) break;
		rep(v, m) if(id[v] == -1)
			id[v] = k++;
		vector<edge> fs;
		for(auto & e : es) if(id[e.u] != id[e.v])
			fs.emplace_back(id[e.u], id[e.v], e.c - pre[e.v]->c);
		root = id[root], m = k, es = move(fs);
	}
	return ans;
}
