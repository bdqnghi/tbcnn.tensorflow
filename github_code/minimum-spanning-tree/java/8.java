package algorithms;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

/**
 * Credits: http://apps.topcoder.com/wiki/display/tc/SRM+531
 * @author sasik
 *
 */
public class MinimumSpanningTree {
	int[][] adjList;
	final int numNodes = 5;
	public static final int MAX_WEIGHT = 10;
	
	public void init() {
		Random r = new Random(MinimumSpanningTree.class.hashCode());
		adjList = new int[numNodes][numNodes];
			
		for(int i=0; i<numNodes; ++i) {			
			for(int j=0; j<numNodes; ++j) {
				if(i!=j) {
					adjList[i][j] = r.nextInt(MAX_WEIGHT);
					if(adjList[i][j] != 0)
						System.out.println(i + " -> " + j + " [label=\"" + adjList[i][j] + "\"]");
				}				
			}
		}
	}
	
	private class Edge implements Comparable<Edge>{
		int startNodeId;
		int endNodeId;
		int weight;
		boolean chosen = false;
		
		@Override
		public int compareTo(Edge e) {
			return weight - e.weight;
		}
		
		public Edge(int start, int end, int weight) {
			startNodeId = start;
			endNodeId = end;
			this.weight = weight;			
		}
		
		@Override
		public String toString() {
			return "StartNode: " + startNodeId + " endNode: " + endNodeId + " weight: " + weight;
		}
	}
	
	public void minSpanningTree() {
		int[] color = new int[numNodes];
		for(int i=0; i<numNodes; ++i) {
			color[i] = i;
		}
		
		ArrayList<Edge> edges = new ArrayList<Edge>();
		for(int i=0; i<numNodes-1; ++i) {			
			for(int j=i+1; j<numNodes; ++j) {
				if(adjList[i][j] > 0) {
					edges.add(new Edge(i, j, adjList[i][j]));
				}
			}
		}
		
		Collections.sort(edges);
		int mstCost = 0;
		for(int i=0; i<edges.size(); ++i) {
			Edge e = edges.get(i);
			
			if(color[e.startNodeId] != color[e.endNodeId]) {
				mstCost += e.weight;
				e.chosen = true;
			}
			
			// Merge component with endNodeId to component with startNodeIds
			int endColor = color[e.endNodeId], startColor = color[e.startNodeId];
			for(int nodeId = 0; nodeId < numNodes; ++nodeId) {
				if(color[nodeId] == endColor) {
					color[nodeId] = startColor;
				}
			}			
		}
		
		for(Edge e: edges) {
			if(e.chosen) {
				System.out.println(e);
			}
		}
		System.out.println("MSTCost: " + mstCost);
	}
	
	
	public static void main(String[] args) {
		MinimumSpanningTree m = new MinimumSpanningTree();
		m.init();
		m.minSpanningTree();
	}
}
