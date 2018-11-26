package com.ram.home.datastructures;

public class Graph {
	
	private final int MAX_VERTS = 20;
	private Vertex[] vertexList;
	private int[][] adjMat;
	private int nVerts;
	private StackXX stack;
	private Queue theQueue;
	
	public Graph() {
		vertexList =  new Vertex[MAX_VERTS];
		adjMat = new int[MAX_VERTS][MAX_VERTS];
		nVerts = 0;
		stack = new StackXX(MAX_VERTS);
		theQueue = new Queue();
		
		for (int i=0;i<MAX_VERTS;i++) {
			for (int j=0;j<MAX_VERTS;j++) {
				adjMat[i][j] = 0;
			}
		}
	}
	
	public void addVertex(char label) {
		vertexList[nVerts++] = new Vertex(label);
	}
	
	public void addEdge(int start, int end) {
		adjMat[start][end] = 1;
		adjMat[end][start] = 1;
	}
	
	public void displayVertex(int v) {
		System.out.print(vertexList[v].label);
	}
	
	public int getAdjUnVisitedVertex(int v) {
		
		for (int i=0;i<nVerts;i++) {
			if (adjMat[v][i] == 1 && vertexList[i].wasVisited == false) {
				return i;
			}
		}
		return -1;
	}
	
	//Depth-First-Search
	public void dfs() {
		vertexList[0].wasVisited = true;
		displayVertex(0);
		stack.push(0);
		
		while (!stack.isEmpty()) {
			
			int v = getAdjUnVisitedVertex((int) stack.peek());
			if (v == -1) {
				stack.pop();
				
			} else {
				vertexList[v].wasVisited = true;
				displayVertex(v);
				stack.push(v);
			}
		}
		
		//reset flags
		
		for (int j=0;j<nVerts;j++) {
			vertexList[j].wasVisited =  false;
		}
	}
	
	//Breadth-First-Search
	public void bfs() {
		vertexList[0].wasVisited = true;
		displayVertex(0);
		theQueue.insert(0);
		int v2;
		
		while (!theQueue.isEmpty()) {
			
			int v1 = theQueue.remove();
			
			while ( (v2 = getAdjUnVisitedVertex(v1)) != -1) {
				
				vertexList[v2].wasVisited = true;
				displayVertex(v2);
				theQueue.insert(v2);
			}
			
		}
		
		//reset flags
		
		for (int j=0;j<nVerts;j++) {
			vertexList[j].wasVisited =  false;
		}	
	}
	
	//Minimum-Spanning-Tree
	public void mst() {
		
		vertexList[0].wasVisited = true;
		stack.push(0);
		
		while (!stack.isEmpty()) {
			
			int currentVertex = (int) stack.peek();
			int v = getAdjUnVisitedVertex(currentVertex);
			
			if (v == -1) {
				stack.pop();
				
			} else {
				vertexList[v].wasVisited = true;
				stack.push(v);
				
				displayVertex(currentVertex);
				displayVertex(v);
				System.out.print(" ");
			}
		}
		
		//reset flags
		
		for (int j=0;j<nVerts;j++) {
			vertexList[j].wasVisited =  false;
		}
		
	}
	

}
