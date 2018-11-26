package ford_fulkerson;


import given_code.Edge;
import given_code.GraphInput;
import given_code.SimpleGraph;
import given_code.Vertex;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Set;

import test.NumberUtility;



/**
 * This class implements the Ford Fulkerson Algorithm. The general outline
 * follows the implementation by Keith Schwarz and modified to work with the 
 * provided code for the project
 * 
 * @author Keith Schwarz(http://www.keithschwarz.com/interesting/code/ford-fulkerson/) 
 * modified by Justin Wong
 * 
 *
 */
public class FordFulkerson {
	/**
	 * SimpleGraph object
	 */
	private SimpleGraph my_graph;
	/**
	 * Starting Vertex
	 */
	private Vertex start;
	/**
	 * Destination Vertex(sink)
	 */
	private Vertex dest;
	
	/**
	 * Constructor for Ford Fulkerson Algorithm 
	 * @param filepath file path to generate graph
	 */
	/*This assumes the source and sink are labeled s and t*/
	public FordFulkerson(String filepath){
		my_graph = new SimpleGraph();
		Hashtable table = GraphInput.LoadSimpleGraph(my_graph, filepath);
		start = (Vertex)table.get("s");
		dest = (Vertex)table.get("t");
		
	}
	
	/**
	 * Constructor to create Ford Fulkerson object. 
	 * @param graph The SimpleGraph
	 * @param the_start Starting Vertex
	 * @param the_dest Destion Vertex
	 */
	public FordFulkerson(SimpleGraph graph, Vertex the_start, Vertex the_dest){
		my_graph = graph;
		start = the_start;
		dest = the_dest;
	}
	
	/**
	 * Starts the Ford Fulkerson algorithm 
	 * @return max flow
	 */
	public int run(){
		/*ensur these aren't equal*/
		if(isEqual(start, dest)){
			return 0;
		}
		
		return sumFlow(0);
	}
	
	protected int sumFlow(int min_cap){
		int flow = 0;
		
		/*continuously search for an augumenting path until it can't find one*/
		while(true){
			Deque<Edge> path = findPath(start, dest, my_graph, min_cap);
			
			if(path == null){
				break;
			}
			/*finds bottleneck and augments the paths*/
			int bottleneck = findBottleneck(path);
			augumentPath(path,bottleneck);
			flow += bottleneck;
		}
		
		return flow;
	}
	
	/**
	 * Recursively look for a path in the SimpleGraph
	 * @param start Starting vertex 
	 * @param dest sink vertex
	 * @param graph The simple graph
	 * @param min_cap minimum capcity to look for in the path
	 * @return the Deque of edges in the graph
	 */
	protected Deque<Edge> findPath(Vertex start, Vertex dest, SimpleGraph graph, int min_cap){
		/*min_cap is used mainly in the Scaling FF algorithm but to prevent 
		 * repeated code, add another parameter to determine what is the min
		 * capacity on each edge we need to look at*/
		return findPathRec(start, dest, graph, new HashSet<Vertex>(), min_cap);
	}
	
	/**
	 * Recursively look for a path in the SimpleGraph
	 * @param start Starting vertex 
	 * @param dest sink vertex
	 * @param graph The simple graph
	 * @param visited nodes that are visited
	 * @param min_cap minimum capacity to look for in the path
	 * @return the Deque of edges in the graph
	 */
	private Deque<Edge> findPathRec(Vertex start, Vertex dest, SimpleGraph graph, Set<Vertex> visited, int min_cap){
		/*if we've already seen this node*/
		if(visited.contains(start)){
			return null;
		}
		/*marking this node since we've been here*/
		visited.add(start);
		
		/*hit the dest*/
		if(isEqual(start, dest)){
			return new ArrayDeque<Edge>();
		}
		
		/*finds the path*/
		Iterator edges = graph.incidentEdges(start);
		while(edges.hasNext()){
			Edge e = (Edge) edges.next();
			
			/*looks for edge with capacity at least*/
			if(NumberUtility.getInt(e.getData()) > 0){
				Deque<Edge> result = findPathRec(e.getSecondEndpoint(), dest, graph, visited, min_cap);
				
				if(result != null){
					result.addFirst(e);
					return result;
				}
			}
		}
		return null;
	}
	
	/**
	 * Auguments the flow on the given paths. 
	 * @param path the path to augument flow
	 * @param bottleneck bottleneck of the path
	 */
	protected void augumentPath(Deque<Edge> path,int bottleneck){
		Iterator i = path.iterator();
		
		/*This continues to add flow along each path and also adds a 
		 * backward edge if one doesn't exist*/
		while(i.hasNext()){
			Edge e = (Edge) i.next();
			
			if(NumberUtility.getInt(e.getData()) < bottleneck){
				throw new IllegalArgumentException("bottleneck is larger than capacity");
			}
			
			Vertex v1 = e.getFirstEndpoint();
			Vertex v2 = e.getSecondEndpoint();
			
			Iterator j = my_graph.incidentEdges(v2);
			boolean back_edge = false;
			
			/*determines if there is a backward edge from v2 to v1 (v1 <- v2) */
			while(j.hasNext()){
				Edge e_2 = (Edge)j.next();
				
				/*
				 * Not the best equality checker, but for now it should do
				 */
				if(e_2.getFirstEndpoint().equals(v2) && e_2.getSecondEndpoint().equals(v1)){
					back_edge = true;
					e_2.setData(NumberUtility.getInt(e_2.getData()) + bottleneck);
					break;
				}
			}
			/*if there isn't a backward edge*/
			if(!back_edge){
				my_graph.insertEdge(v2, v1, bottleneck, null);
			}
			e.setData(NumberUtility.getInt(e.getData()) - bottleneck);	
		}	
	}
	
	/**
	 * Finds the bottle neck in the path
	 * @param path The Edge list paths 
	 * @return the minimum capacity of all the edges
	 */
	protected int findBottleneck(Deque path){
		int min = Integer.MAX_VALUE;
		Iterator i = path.iterator();
		
		while(i.hasNext()){
			Edge e = (Edge) i.next();
			min = Math.min(min, NumberUtility.getInt(e.getData()));
		}
		
		return min;
	}
	
	/**
	 * Determines if two vertexs are the same
	 * @param v1 vertex 1
	 * @param v2 vertex 2
	 * @return boolean value if v1 and v2 are equal
	 */
	private boolean isEqual(Vertex v1, Vertex v2){
		/*
		 * Might need to override equals and hashcode in vertex, right now
		 * just checking memory locations
		 */
		return v1.equals(v2);
	}
	
//	public static void main(String[] args){
//		//cap: 30
////		SimpleGraph g = new SimpleGraph();
////		Vertex v1 = g.insertVertex(null, "v1");
////		Vertex v2 = g.insertVertex(null, "v2");
////		Vertex v3 = g.insertVertex(null, "v3");
////		Vertex v4 = g.insertVertex(null, "v4");
////		
////		g.insertEdge(v1, v2, 20, null);
////		g.insertEdge(v1, v3, 10, null);
////		g.insertEdge(v2, v4, 10, null);
////		g.insertEdge(v2, v3, 30, null);
////		g.insertEdge(v3, v4, 20, null);
////		
////		FordFulkerson f = new FordFulkerson(g);
////		System.out.println(f.normalMaxFlow(g, v1, v4));
//		
//		//cap: 28
//		SimpleGraph g = new SimpleGraph();
//		Vertex v1 = g.insertVertex(null, "1");
//		Vertex v2 = g.insertVertex(null, "2");
//		Vertex v3 = g.insertVertex(null, "3");
//		Vertex v4 = g.insertVertex(null, "4");
//		Vertex v5 = g.insertVertex(null, "5");
//		Vertex v6 = g.insertVertex(null, "6");
//		Vertex v7 = g.insertVertex(null, "7");
//		Vertex v8 = g.insertVertex(null, "8");
//		
//		g.insertEdge(v7, v8, 10, null);
//		g.insertEdge(v3, v6, 8,  null);
//		g.insertEdge(v1, v2,10, null);
//		g.insertEdge(v5, v8, 10, null);
//		g.insertEdge(v1, v4, 15, null);
//		g.insertEdge(v2, v3, 6, null);
//		g.insertEdge(v7, v3, 6, null);
//		g.insertEdge(v2, v5, 9, null);
//		g.insertEdge(v2, v6, 15, null);
//		g.insertEdge(v6, v8, 10, null);
//		g.insertEdge(v4, v7, 30, null);
//		g.insertEdge(v5, v6, 15, null);
//		g.insertEdge(v3, v4, 4, null);
//		g.insertEdge(v1, v3, 5, null);
//		g.insertEdge(v6, v7, 15, null);
//		//normal order cap: 28
////		g.insertEdge(v1, v2, 10, null);
////		g.insertEdge(v1, v3, 5, null);
////		g.insertEdge(v1, v4, 15, null);
////		g.insertEdge(v2, v5, 9, null);
////		g.insertEdge(v2, v6, 15, null);
////		g.insertEdge(v2, v3, 4, null);
////		g.insertEdge(v3, v4, 4, null);
////		g.insertEdge(v3, v6, 8, null);
////		g.insertEdge(v4, v7, 30, null);
////		g.insertEdge(v5, v8, 10, null);
////		g.insertEdge(v5, v6, 15, null);
////		g.insertEdge(v6, v8, 10, null);
////		g.insertEdge(v6, v7, 15, null);
////		g.insertEdge(v7, v3, 6, null);
////		g.insertEdge(v7, v8, 10, null);
//		
//		FordFulkerson f = new FordFulkerson(g, v1, v8);
//		System.out.println(f.run());
//
//		SimpleGraph G = new SimpleGraph();
//        Vertex s, a, b, c, d, t;
//        Edge e, k, l, m, n;
//        //Correct Max Flow: 120
////        s = G.insertVertex(null, "s");
////        a = G.insertVertex(null, "a");
////        G.insertEdge(s, a, 90, "s-a");
////        b = G.insertVertex(null, "b");
////        G.insertEdge(a, b, 60, "a-b");
////        c = G.insertVertex(null, "c");
////        G.insertEdge(s, c, 110, "K");
////        d = G.insertVertex(null, "d");
////        G.insertEdge(c, d, 30, "c-d");
////        t = G.insertVertex(null, "t");
////        G.insertEdge(b, t, 50, "b-t");
////        G.insertEdge(c, a, 10, "c-a");
////        G.insertEdge(d, t, 100, "d-t");
////        G.insertEdge(a, d, 30, "a-d");
////        G.insertEdge(b, d, 40, "b-d");
////        FordFulkerson f1 = new FordFulkerson(G);
////        System.out.println(f1.normalMaxFlow(G, s, t));
      
//        //Correct Max Flow: 6
////        s = G.insertVertex(null, "s");
////        a = G.insertVertex(null, "a");
////        G.insertEdge(s, a, 4, "E");
////        b = G.insertVertex(null, "b");
////        G.insertEdge(s, b, 2, "K");
////        t = G.insertVertex(null, "t");
////        G.insertEdge(a, t, 5, "I");
////        G.insertEdge(b, t, 1, "M");
////        G.insertEdge(b, a, 3, "L");
////      FordFulkerson f1 = new FordFulkerson(G, s, t);
////      System.out.println(f1.run());
//		
//	}

}
