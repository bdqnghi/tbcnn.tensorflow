/*
	Java implementations of Ford-Fulkerson and Edmonds-Karp.
*/

	ArrayList<Edge>[] g;
	int n;

	class Edge
	{
		int j, c, f;
		Edge r;

		Edge(int j, int c)
		{
			this.j = j;
			this.c = c;
		}
	}

	void addEdge(int i, int j, int c)
	{
		Edge e = new Edge(j, c), f = new Edge(i, 0);
		e.r = f;
		f.r = e;
		g[i].add(e);
		g[j].add(f);
	}

	int maxFlow(int s, int t)
	{
		/*
		seen = new boolean[n];
		do Arrays.fill(seen, false);
		while(maxFlowDFS(s, t, INF) > 0);
		*/
		pre = new Edge[n];
		do Arrays.fill(pre, null);
		while(maxFlowBFS(s, t) > 0);
		int ans = 0;
		for(Edge e : g[s]) ans += e.f;
		return ans;
	}

	// Ford-Fulkerson
	boolean[] seen;

	int maxFlowDFS(int s, int t, int mf)
	{
		if(s == t) return mf;
		if(seen[s]) return 0;
		seen[s] = true;
		for(Edge e : g[s])
		{
			if(e.c == e.f) continue;
			int mf2 = Math.min(mf, e.c - e.f);
			mf2 = Math.min(mf2, maxFlowDFS(e.j, t, mf2));
			if(mf2 > 0)
			{
				e.f += mf2;
				e.r.f -= mf2;
				return mf2;
			}
		}
		return 0;
	}

	// Edmonds-Karp
	Edge[] pre;

	int maxFlowBFS(int s, int t)
	{
		LinkedList<Integer> q = new LinkedList<Integer>();
		q.add(s);
		while(!q.isEmpty())
		{
			int i = q.poll();
			for(Edge e : g[i]) if(e.c > e.f && e.j != s && pre[e.j] == null)
			{
				pre[e.j] = e;
				q.add(e.j);
			}
		}
		if(pre[t] == null) return 0;
		int f = INF;
		for(Edge e = pre[t]; e != null; e = pre[e.r.j])
			f = Math.min(f, e.c - e.f);
		for(Edge e = pre[t]; e != null; e = pre[e.r.j])
		{
			e.f += f;
			e.r.f -= f;
		}
		return f;
	}
