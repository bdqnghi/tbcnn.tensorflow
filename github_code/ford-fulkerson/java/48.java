package ford_fulkerson;

import java.util.Iterator;

import given_code.Edge;
import given_code.SimpleGraph;
import given_code.Vertex;

/**
 * Runs the Scaling Ford Fulkerson Algorithm 
 * @author Justin wong
 *
 */
public class ScalingFordFulkerson extends FordFulkerson{
	/**
	 * Constructor to start ScalingFordFulkerson
	 * 
	 * @param graph the SimpleGraph object
	 * @param start Starting Vertex
	 * @param dest Ending Vertex
	 */
	public ScalingFordFulkerson(SimpleGraph graph, Vertex start, Vertex dest) {
		super(graph, start, dest);
	}
	
	/**
	 * Second constructor accepting file path
	 * @param filepath
	 */
	public ScalingFordFulkerson(String filepath){
		super(filepath);
	}
	
	/**
	 * Sets the initial conditions of the scaling Ford Fulkerson algorithm 
	 * @param start Starting vertex
	 * @param graph SimpleGraph object
	 * @return
	 */
	private int setScalingPhase(Vertex start, SimpleGraph graph){
		int max = Integer.MIN_VALUE;
		Iterator edges = graph.incidentEdges(start);
		
		while(edges.hasNext()){
			Edge e = (Edge)edges.next();
			max = Math.max(max, (int)e.getData());
		}
		
		return (int)(Math.log(max)/Math.log(2));
	}
	
	/**
	 * Calculates the max flow of using Scaling Ford Fulkerosn algorithm 
	 * @param graph
	 * @param start
	 * @param dest
	 * @return
	 */
	public int scalingMaxFlow(SimpleGraph graph, Vertex start, Vertex dest){
		/*sets the initial scaling*/
		int scaling = setScalingPhase(start, graph);
		int flow = 0;
		
		while(scaling >= 1){
			
			flow += sumFlow(scaling);
			
			scaling = scaling/2;
		}
		
		return flow;
	}
//	public static void main(String[] args){
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
////		ScalingFordFulkerson f = new ScalingFordFulkerson(g, v1, v4);
////		System.out.println(f.scalingMaxFlow(g, v1, v4));
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
//		
//		g.insertEdge(v1, v2, 10, null);
//		g.insertEdge(v1, v3, 5, null);
//		g.insertEdge(v1, v4, 15, null);
//		g.insertEdge(v2, v5, 9, null);
//		g.insertEdge(v2, v6, 15, null);
//		g.insertEdge(v2, v3, 4, null);
//		g.insertEdge(v3, v4, 4, null);
//		g.insertEdge(v3, v6, 8, null);
//		g.insertEdge(v4, v7, 30, null);
//		g.insertEdge(v5, v8, 10, null);
//		g.insertEdge(v5, v6, 15, null);
//		g.insertEdge(v6, v8, 10, null);
//		g.insertEdge(v6, v7, 15, null);
//		g.insertEdge(v7, v3, 6, null);
//		g.insertEdge(v7, v8, 10, null);
//		
//		ScalingFordFulkerson f = new ScalingFordFulkerson(g, v1, v8);
//		System.out.println(f.scalingMaxFlow(g, v1, v8));
//	}

}
