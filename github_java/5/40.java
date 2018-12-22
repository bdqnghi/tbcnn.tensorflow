package com.algorithms;
import java.io.IOException;

public class ConnectedComponents {

	int componenetCount = 0;
	int [] connectedComponentsList;
	boolean [] discovered;
	Graph graph;
	public ConnectedComponents(Graph graph) {
		// TODO Auto-generated constructor stub
		this.graph = graph;
	}

	public int countNumberOfConnectedGraph(){
		DepthFirstSearch depthFirstSearch = new DepthFirstSearch(this.graph);
		depthFirstSearch.dfs_stack(0);
		++componenetCount;
		for (int i =0;i<depthFirstSearch.discovered.length;++i) {
			if(!depthFirstSearch.discovered[i]){
				++componenetCount;
				depthFirstSearch.dfs_stack(i);
			}
		}
		return componenetCount;
	}
	
	public static void main(String[] args) throws IOException {
		final Graph graph = Graph.readGraph();
		ConnectedComponents cc = new ConnectedComponents(graph);
		int countNumberOfConnectedGraph = cc.countNumberOfConnectedGraph();
		System.out.println(countNumberOfConnectedGraph);
	}
}
