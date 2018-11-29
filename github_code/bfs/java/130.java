package atg;

import java.util.Iterator;
import java.util.LinkedList;

public class BreadthFirstSearch {

	public static void main(String[] args) {
		 Graph g = new Graph(4);
		 
	        g.addEdge(0, 1);
	        g.addEdge(0, 2);
	        g.addEdge(1, 2);
	        g.addEdge(2, 0);
	        g.addEdge(2, 3);
	        g.addEdge(3, 3);
	        
	        System.out.println("Following is Breadth First Traversal "+
                    "(starting from vertex 2)");

	        	g.BFS(2);
	        	g.DepthFirstSearch(2);
	        	
	        	
	      int v1 = 1;
	      int v2 = 3;
	      if(g.hasPath(v1, v2)) {
	    	  System.out.println("Theres is a path from " + v1 + " to " + v2);
	      }
	      else {
	    	  System.out.println("Theres is not path from " + v1 + " to " + v2);
	      }

	}
	
	
	
}


class Graph
{
	private int V;   // No. of vertices
	private LinkedList<Integer> adj[]; //Adjacency Lists
	
	// Constructor
	Graph(int v)
	{
		V = v;
		adj = new LinkedList[v];
		for (int i=0; i<v; ++i)
			adj[i] = new LinkedList();
	}
	
	public void BFS(int vertex) {
		// TODO Auto-generated method stub
		boolean[] visited = new boolean[V];
		LinkedList<Integer> queue = new LinkedList<>();
		
		visited[vertex] = true;
		queue.add(vertex);
		
		while(queue.size() != 0) {
			vertex = queue.poll();
			System.out.println(vertex +  " ");
			
			Iterator<Integer> iterator =  adj[vertex].listIterator();
			
			while(iterator.hasNext()) {
				int neighboor = iterator.next();
				if(!visited[neighboor]) {
					visited[neighboor] = true;
					queue.add(neighboor);
				}
			}
		}
	}
	
	void DepthFirstSearch(int v) {
		boolean[] visited = new boolean[V];
		DFSUtil(v,visited);
	}

	private void DFSUtil(int v, boolean[] visited) {
		// TODO Auto-generated method stub
		visited[v] = true;
		System.out.println("DFS UTIL " + v);
		Iterator<Integer> iterator = adj[v].listIterator();
		
		while(iterator.hasNext()) {
			int neighboor = iterator.next();
			if(!visited[neighboor]) {
				DFSUtil(neighboor,visited);
			}
		}
	}
	
	
	boolean hasPath(int v1, int v2) {
		
		boolean[] visited = new boolean[V];
		LinkedList<Integer> queue = new LinkedList<>();
		
		visited[v1] = true;
		queue.add(v1);
		
		Iterator<Integer> iterator;
		
		while(queue.size() != 0) {
			v1 = queue.poll();
			
			int neighboor;
			
			iterator = adj[v1].listIterator();
			
			while(iterator.hasNext()) {
				
				neighboor = iterator.next();
				
				if(neighboor == v2) {
					return true;
				}
				else {
					if(!visited[neighboor]) {
						visited[neighboor] = true;
						queue.add(neighboor);
					}
				}
				
			}
		}
		return false;
	}
	// Function to add an edge into the graph
	void addEdge(int v,int w)
	{
		adj[v].add(w);
	}	
}