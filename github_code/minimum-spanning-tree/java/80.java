package greedy.graph;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

public class MinimumSpanningTree {

	/**
	 * 
	 */
	EdgeWeightedGraph graph;
	List<Edge> edges;
	public List<Edge> getEdges() {
		return edges;
	}
	public MinimumSpanningTree(EdgeWeightedGraph graph) {
		this.graph = graph;
		edges = new ArrayList<>(graph.V -1);
	}
	double weight() {
		return 0;
	}
	public void kruskal() {
		List<Edge> edges2 = graph.getEdges();
		Iterator<Edge> iterator = edges2.iterator();
		int [] parent = new int [graph.V];
		for(int i=0;i<graph.V; i++) {
			parent[i] = -1;
		}
		while(edges.size() <graph.V -1) {
			if(iterator.hasNext()) {
				Edge edge = iterator.next();
				if(!isCycleFormed(parent, edge.u, edge.v))
					edges.add(edge);
			}
		}
		
	}
	
	boolean isCycleFormed(int parent[], int u, int v) {
		int ps = parent(parent, u);
		int pd = parent(parent, v);
		if(ps == pd)
			return true;
		else
			union(parent, u, pd);
	return false;

}
private void union(int[] parent, int u, int pd) {
	// TODO Auto-generated method stub
	if(parent[u] == -1)
	{
		parent[u] = pd;
	}
	else{
		union(parent, parent[u], pd);
	}
}
	

/**
 * @param parent
 * @param s
 * @return
 */
private int parent(int[] parent, int s) {
	if(parent[s] == -1)
		return s;
	else
		return(parent(parent, parent[s]));
}

	
	
}
