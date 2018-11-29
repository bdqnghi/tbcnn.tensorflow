package com.timepass.graphtheory.revised;

public class DepthFirstSearch {
	private boolean [] marked;
	private int count;
	
	public DepthFirstSearch(Graph graph, int source){
		marked = new boolean[graph.V()];	
		
		dfs(graph, source);
	}	
	
	private void dfs(Graph graph, int vertex){
		System.out.println("Visiting: " + vertex);
		marked[vertex] = true;
		count++;
		for (int v: graph.adj(vertex)) {
			if(!marked[v]){
				dfs(graph, v);
			}
		}
	}
	
	public int count(){
		return count;
	}
	
    public static void main(String[] args) {
        Graph graph = new Graph(10);
        
        graph.addEdge(0, 9);
        graph.addEdge(9, 3);
        graph.addEdge(3, 6);
        graph.addEdge(6, 2);
        
        DepthFirstSearch depthFirstSearch = new DepthFirstSearch(graph, 0);
        if(depthFirstSearch.count() == graph.V()){
        	System.out.println("Connected");
        } else{
        	System.out.println("Not Connected");
        }
    }
}
