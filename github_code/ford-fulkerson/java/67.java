package com.trial;
import java.util.ArrayList;
import java.util.List;

public class App {
	public static void main(String[] args) {
		

		Vertex vertex0 = new Vertex("s",0);
		Vertex vertex1 = new Vertex("A",1);
		Vertex vertex2 = new Vertex("B",2);
		Vertex vertex3 = new Vertex("t",3);
		
		vertex0.addEdge(new Edge(vertex0, vertex1, 4));
		vertex0.addEdge(new Edge(vertex0, vertex2, 5));

		vertex1 .addEdge(new Edge(vertex1, vertex3, 7));

		vertex2.addEdge(new Edge(vertex2, vertex1, 4));
		vertex2.addEdge(new Edge(vertex2, vertex3, 1));
		

		List<Vertex> vertexList = new ArrayList<>();
		vertexList.add(vertex0);
		vertexList.add(vertex1);
		vertexList.add(vertex2);
		vertexList.add(vertex3);
		
		FlowNetwork flowNetwork = new FlowNetwork(vertexList,0,3);




		FordFulkerson fordFulkerson = new FordFulkerson(flowNetwork);
		
		fordFulkerson.runAlgorithm();
		
		fordFulkerson.verticesInMinCut();
		
		System.out.println("Maximum flow is: " + fordFulkerson.getMaxFlow());
		
		
	}
}
