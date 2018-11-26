package com.satisdrms.code.treesAndGraphs;

import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;

//Minimum Spanning tree for an undirected graph

class MST {
	HashMap<Integer, GraphNodeMST> vertices;
	LinkedList<Edge> edges;
	HashMap<GraphNodeMST, LinkedList<Edge>> minspntree;

	public MST() {
		vertices = new HashMap<Integer, GraphNodeMST>();
		edges = new LinkedList<Edge>();
		minspntree = new HashMap<GraphNodeMST, LinkedList<Edge>>();
	}

	public void insert(GraphNodeMST node) {

	}

	public void createGraph(int[][] graph) {
		for (int i = 0; i < graph.length; i++) {
			for (int j = 0; j < graph[0].length; j++) {
				if (graph[i][j] != 0) {
					GraphNodeMST start, end;
					if (vertices.containsKey(i))
						start = vertices.get(i);
					else {
						start = new GraphNodeMST(i);
						vertices.put(i, start);
					}
					if (vertices.containsKey(j))
						end = vertices.get(j);
					else {
						end = new GraphNodeMST(j);
						vertices.put(j, end);
					}
					Edge e = new Edge(start, end, graph[i][j]);
					if (!edges.contains(e))
						edges.add(e);
					// else
					// System.out.println("edge between " + e.start.d+ " and " +
					// e.end.d + " exists");
					// tree.put(start, e);
				}
			}
		}
		// for (Edge e : edges) {
		// System.out.println(e.start.d + " is connected to edge with weight "
		// + e.weight + " to the node " + e.end.d);
		// }

	}

	public void printVertex(int v) {
		System.out.println(vertices.values().contains(new GraphNodeMST(v))
				+ " " + v);
		// for(vertices.values().
	}

	public void createMST() {
		Collections.sort(edges);
		// printObj(edges);printObj(sortEdges);

		for (Edge e : edges) {
			// System.out.println("edge is "+e.weight);
			resetNodesVisitStatus();
			addEdgeToGraph(minspntree, e);
			if (cycleExistsInMST(e)) {
				removeEdgeFromGraph(minspntree, e);
				// System.out.println(e.start.d+
				// " is connected to edge with weight " + e.weight+
				// " to the node " + e.end.d + " size is "+ minspntree.size());
			}
			// printMST(minspntree);
		}
		System.out.println("The MST is ");
		printMST(minspntree);
	}

	private void printObj(LinkedList<Edge> edges) {
		System.out.println("----------a Edge");
		Collections.sort(edges);
		for (Edge e : edges) {
			System.out.println(e);
		}

	}

	private void printMST(HashMap<GraphNodeMST, LinkedList<Edge>> tree) {
		resetNodesVisitStatus();
		//System.out.println("---------printing a tree  " + tree.size());
		LinkedList<String> sed = new LinkedList<String>();
		for (GraphNodeMST g : tree.keySet()) {
			// System.out.println("the node is " + g.d + " and the edges are ");
			for (Edge e : tree.get(g)) {
				String str = "nodes " + e.start.d + " and " + e.end.d
						+ " are connected with weight " + e.weight;
				if (!sed.contains(str)) {
					sed.add(str);
				}
			}
		}
		for (String s : sed) {
			System.out.println(s);
		}
	}

	/* Check whether a cycle will be formed by adding this node */
	private boolean cycleExistsInMST(Edge e) {

		// printMST(cyclemst);
		if (minspntree.size() == 0)
			return false;
		else {
			for (GraphNodeMST g : minspntree.keySet()) {
				if (!g.isVisited) {
					LinkedList<GraphNodeMST> connectedVertices = new LinkedList<GraphNodeMST>();
					connectedVertices.add(g);
					GraphNodeMST previous = null;
					while (!connectedVertices.isEmpty()) {
						GraphNodeMST vertex = connectedVertices.remove();
						vertex.isVisited = true;
						for (Edge ed : minspntree.get(vertex)) {
							GraphNodeMST otherEdge = ed.getOtherVertex(vertex);
							if (previous == null || !otherEdge.equals(previous)) {
								if (otherEdge.isVisited)
									return true;
								if (!connectedVertices.contains(otherEdge)) {
									connectedVertices.add(otherEdge);
								}
							}
						}
						previous = vertex;
					}
				}
			}
		}
		return false;
	}

	private void addEdgeToGraph(HashMap<GraphNodeMST, LinkedList<Edge>> graph,
			Edge e) {

		if (graph.containsKey(e.start)) {
			LinkedList<Edge> edgeList = graph.get(e.start);
			edgeList.add(e);
		} else {
			LinkedList<Edge> edgeList = new LinkedList<Edge>();
			edgeList.add(e);
			graph.put(e.start, edgeList);
		}

		if (graph.containsKey(e.end)) {
			LinkedList<Edge> edgeList = graph.get(e.end);
			edgeList.add(e);
		} else {
			LinkedList<Edge> edgeList = new LinkedList<Edge>();
			edgeList.add(e);
			graph.put(e.end, edgeList);
		}
		// printMST(graph);

	}

	private void removeEdgeFromGraph(
			HashMap<GraphNodeMST, LinkedList<Edge>> graph, Edge e) {
		GraphNodeMST start = e.start;
		GraphNodeMST end = e.end;

		if (graph.get(start).size() > 1)
			graph.get(start).remove(e);
		else
			graph.remove(start);

		if (graph.get(end).size() > 1)
			graph.get(end).remove(e);
		else
			graph.remove(end);
	}

	private void resetNodesVisitStatus() {
		for (GraphNodeMST g : vertices.values())
			g.isVisited = false;

	}
}

public class MinimumSpanningTree {
	static int graph[][] = new int[][] { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
			{ 4, 0, 8, 0, 0, 0, 0, 11, 0 }, { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
			{ 0, 0, 7, 0, 9, 14, 0, 0, 0 }, { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
			{ 0, 0, 4, 14, 10, 0, 2, 0, 0 }, { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
			{ 8, 11, 0, 0, 0, 0, 1, 0, 7 }, { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

	// { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
	// { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
	// { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
	// { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
	// { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
	// { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
	// { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
	// { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
	// { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

	public static void main(String[] args) {
		MST minspt = new MST();
		minspt.createGraph(graph);
		minspt.createMST();

		// LinkedList<Edge> test = new LinkedList<Edge>();
		// test.add(new Edge(null, null, 1));
		// test.add(new Edge(null, null, 13));
		// test.remove(new Edge(null, null, 13));
		// for (Edge e : test) {
		// System.out.println(e.weight);
		// }
		// minspt.printVertex(3);

	}
}
