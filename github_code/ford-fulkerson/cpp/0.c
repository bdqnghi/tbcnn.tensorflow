const int NN = 1024;

int cap[NN][NN], prev[NN];

vector<int> g[NN];

/*
 * If the graph is un-directed remember to also set 
 * cap[v][u] = cap[u][v] = c
 */

inline void link(int u, int v, int c){
	cap[u][v] = c;
	g[u].push_back(v);
	g[v].push_back(u);
}

int res[NN][NN];
int fordFulkerson(int n, int s, int t){
	memcpy(res, cap, sizeof cap);
	
	int ans = 0;
	while(true){
		fill_n(prev,n,-1);
		queue<int> q;
		q.push(s);
		while(!q.empty() && prev[t] == -1){
			int u = q.front();
			q.pop();
			vector<int> &out = g[u];
			for(int k=0, m = out.size(); k<m; ++k){
				int v = out[k];
				if(v != s && prev[v] == -1 && res[u][v] > 0)
					prev[v] = u, q.push(v);
			}
		}
		if(prev[t] == -1) break;
		int bottleneck = 1<<30;
		for(int v = t, u = prev[v]; u != -1; v = u, u = prev[v])
			bottleneck = min(bottleneck, res[u][v]);
		for(int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
			res[u][v] -= bottleneck;
			res[v][u] += bottleneck;
		}
		ans += bottleneck;
	}
	return ans;
}
