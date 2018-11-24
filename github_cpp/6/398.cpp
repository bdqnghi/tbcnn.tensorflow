bool bellman-ford(V, E){
	int cost[V];
	cost[0] = 0;
	for(int i = 1; i < V; i++){
		cost[i] = INT_MAX;
	}
	for(int i = 0; i < V-1; i++){
		for(int i = 0; i < E; i++){
			int u = E[i].u;
			int v = E[i].v;
			cost[v] = min(cost[v], cost[u]+E[i].cost);
		}
	}
	int min_cost = 0 ;
	//calculating total cost 
	for (int i = 0; i < V; ++i)
	{
		min_cost += cost[i];
	}
	for(int i = 0; i < E; i++){
		int u = E[i].u;
		int v = E[i].v;
		cost[v] = min(cost[v], cost[u]+E[i].cost);
	}
	int costnew = 0;
	for (int i = 0; i < V; ++i)
	{
		costnew += cost[i];
	}
	if(costnew < min_cost){
		return true;
	} else {
		return false;
	}

}