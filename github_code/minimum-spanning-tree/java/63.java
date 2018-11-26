package com.ab.obj;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.PriorityQueue;

import edu.uci.ics.jung.graph.DirectedSparseGraph;

public class MinimumSpanningTree {
	
	static String START = "jeff.dasovich@enron.com";
	public static DirectedSparseGraph<Person, Edge> mst = new DirectedSparseGraph<>();
	
	public MinimumSpanningTree(Graph graph){

		build(graph);
		
	}
	
	static void build(Graph g){
		
		ArrayList<Person> used = new ArrayList<>();
		Person start = g.getPerson(START);
		used.add(start);
		
		PriorityQueue<Edge> openEdges = new PriorityQueue<>(g.graph.getOutEdges(start));
		mst.addVertex(start);
		while(!openEdges.isEmpty()){
			
			Edge current = openEdges.poll();
			if (used.contains(current.getTo()))
				continue;
			
			mst.addVertex(current.getTo());
			mst.addEdge(current, current.getFrom(), current.getTo());
			used.add(current.getTo());
			
			for(Edge e : g.graph.getOutEdges(current.getTo())){
				if (used.contains(e.getTo()))
					continue;
				openEdges.add(e);
			}
			
		}
		
	}
}