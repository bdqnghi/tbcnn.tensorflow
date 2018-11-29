package Graphs;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayDeque;
import java.util.Queue;
import java.util.Scanner;
 
//import linear.Queue;

public class BreadthFirstSearch {

	class Vertex{
		String name;
		Neighbour adjList;
		Vertex(String name, Neighbour neighs){
			this.name = name;
			this.adjList = neighs;
		}
	}
	
	class Neighbour{
		public int vertexNum;
		public Neighbour next;
		public Neighbour(int n, Neighbour neigh){
			vertexNum = n;
			next = neigh;
		}
	}
	
	class Graph{
		Vertex[] adjLists;
		
		public Graph(String file) throws FileNotFoundException{
		
			Scanner sc = new Scanner(new File(file));
			
			try{
				String graphType = sc.next();
				boolean undirected = true;
				if(graphType != "undirected"){
					undirected = false;
				}
				
				// Number of vertices
				adjLists = new Vertex[sc.nextInt()];
				
				//Read all vertices
				for(int i=0;i<adjLists.length;i++){
					adjLists[i] = new Vertex(sc.next(), null);
				}
				
				
				// Save all edges
				while(sc.hasNext()){
					int v1 = indexForName(sc.next());
					int v2 = indexForName(sc.next());
					
					// add v2 to front of v1's adjacency list and
		            // add v1 to front of v2's adjacency list
		            adjLists[v1].adjList = new Neighbour(v2, adjLists[v1].adjList);
		            if (undirected) {
		                adjLists[v2].adjList = new Neighbour(v1, adjLists[v2].adjList);
		            }
				}
				
				
			} finally {
				sc.close();
			}
			
			
			
		}
		
		public void bfs(){
			boolean[] visited = new boolean[adjLists.length];
			Queue<Integer> q = new ArrayDeque<>();
			for (int v=0; v < visited.length; v++) {
	            if (!visited[v]) {
	                System.out.println("STARTING AT " + adjLists[v].name);
	                q.clear();
	                implementBfs(v, visited, q);
	            }
	        }
		}
		
		public void implementBfs(int start, boolean[] visited, Queue q){
			visited[start] = true;
			System.out.println("visiting " + adjLists[start].name);
	        q.add(start);
	        
	        while(!q.isEmpty()){
	        		int v = (int)q.remove();
	        		
	        		for(Neighbour n = adjLists[v].adjList; n!=null; n=n.next){
	        			int vn = n.vertexNum;
	        			if(!visited[vn]){
	        				visited[vn] = true;
	        				q.add(vn);
	        			}
	        		}
	        }
		}
		
		int indexForName(String name) {
	        for (int v=0; v < adjLists.length; v++) {
	            if (adjLists[v].name.equals(name)) {
	                return v;
	            }
	        }
	        return -1;
	    }
	}
	
	
	
	public static void main(String[] args) throws FileNotFoundException{
		 
		        // TODO Auto-generated method stub
		        Scanner sc = new Scanner(System.in);
		        System.out.print("Enter graph input file name: ");
		        String file = sc.nextLine();
		        //Graph graph = new Graph(file);
		        //graph.bfs();
	}
}
