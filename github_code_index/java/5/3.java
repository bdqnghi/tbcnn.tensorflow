package graphtheory;

import java.util.Iterator;
import java.util.LinkedList;

class Graph2 {
	int V;
	LinkedList<Integer> adj[];
	@SuppressWarnings({ "unchecked", "rawtypes" })
	Graph2(int v){
		V = v;
		adj = new LinkedList[v];
		for(int i=0;i<v;i++) {
			adj[i] = new LinkedList();
		}
	}
	void addEdge(int v, int u) {
		adj[v].add(u);
	}
	void dfsUtil(int v, boolean visit[]) {
		visit[v] = true;
		System.out.println(v+" ");
		Iterator<Integer> i = adj[v].listIterator();
		while(i.hasNext()) {
			int n = i.next();
			if(!visit[n])
				dfsUtil(n,visit);
		}
	}
	void dfs() {
		boolean visit[] = new boolean[V];
		for(int i=0; i<V; i++) {
			if(visit[i] == false)
				dfsUtil(i,visit);
		}
	}
}
public class Dfs {

	public static void main(String[] args) {
		Graph2 g = new Graph2(4);
 
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 2);
        g.addEdge(2, 0);
        g.addEdge(2, 3);
        g.addEdge(3, 3);
 
        System.out.println("Following is Depth First Traversal");
 
        g.dfs();
	}
}
