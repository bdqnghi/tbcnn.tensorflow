package bfs;

import java.util.LinkedList;
import java.util.Queue;

public class BreadthFirstSearch {

	public static void main(String[] args) {
		int[][] graph = { 
			{1},
			{0, 4, 5},
			{3, 4, 5},
			{2, 6},
			{1, 2},
			{1, 2, 6},
			{3, 5},
			{}
		};
		
		BFSInfo[] bfsInfo = doBFS(graph, 3);
		for (int i = 0; i < graph.length; i++) {
			System.out.println("vertex " + i + " : distance = " + bfsInfo[i].distance + ", predecessor = " + bfsInfo[i].predecessor);
		}
		
		assert bfsInfo[0].distance == 4;
		assert bfsInfo[0].predecessor == 1;
		
		assert bfsInfo[1].distance == 3;
		assert bfsInfo[1].predecessor == 4;
		
		assert bfsInfo[2].distance == 1;
		assert bfsInfo[2].predecessor == 3;
		
		assert bfsInfo[3].distance == 0;
		assert bfsInfo[3].predecessor == null;
		
		assert bfsInfo[4].distance == 2;
		assert bfsInfo[4].predecessor == 2;
		
		assert bfsInfo[5].distance == 2;
		assert bfsInfo[5].predecessor == 2;
		
		assert bfsInfo[6].distance == 1;
		assert bfsInfo[6].predecessor == 3;
		
		assert bfsInfo[7].distance == null;
		assert bfsInfo[7].predecessor == null;
	}
	
	/**
	 * Performs a breadth-first search on a graph 
	 * @param graph Graph represented as adjacency list
	 * @param source the index of the source vertex
	 * @return array of BFSInfo objects describing each vertex [{ distance, predecessor}, ...]
	 */
	static BFSInfo[] doBFS(int[][] graph, int source) {

		// this structure will be used for distances and predecessors
		BFSInfo[] bfsInfo = new BFSInfo[graph.length];
		for (int i = 0; i < graph.length; i++) {
			bfsInfo[i] = new BFSInfo();
			bfsInfo[i].distance = null;
			bfsInfo[i].predecessor = null;
		}

		// distance from source to source is ZERO
		bfsInfo[source].distance = 0; 
		
		// put the source in the queue 
		Queue<Integer> queue = new LinkedList<Integer>();
		queue.add(source);
		
		// Traverse the graph
		
	    // As long as the queue is not empty:
		while (!queue.isEmpty()) {
			
	        //  Repeatedly dequeue a vertex u from the queue.
	        int u = queue.remove();
	        
	        for (int i = 0; i < graph[u].length; i++) {
	        	int v = graph[u][i];
	            if (bfsInfo[v].distance == null) {
		        	// Set distance to 1 greater than u's distance
		            bfsInfo[v].distance = (bfsInfo[u].distance == null) ? 1 : bfsInfo[u].distance + 1;
		            
		            // Set predecessor to u
		            bfsInfo[v].predecessor = u;
	            
		            // Enqueue v
		            queue.add(v);
	            }
	        }
		}
		return bfsInfo;
	}
	
	
	public static class BFSInfo {
		Integer distance;
		Integer predecessor;
	}
}
