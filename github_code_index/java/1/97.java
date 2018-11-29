/* An exercise in DepthFirstSearch and BreadthFirstSearch
 * author: 	Kevin Richardson <kevin@magically.us>
 * date:	16-Apr-2011
 */

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class GraphSearchAlgorithms {
	
	static Scanner scan;
	
	static ArrayList<String> nodeList = new ArrayList<String>();
	static int[] visitedNodes;
	static int[][] connections;
	
	static int numConnections;
	static String firstNode, secondNode;
	static int firstNodeIndex, secondNodeIndex;	
	
	// creates a graph based on stdin then performs depth-first-search and breadth-first-search starting at node "A"
	public static void main(String[] args) {
		generateGraph();
				
		// depth-first-search
		System.out.println("DEPTH-FIRST SEARCH:");
		DFS(connections, "A");
		
		System.out.println("-----");
		// reset visitedNodes
		for(int i = 0; i < visitedNodes.length; i++){
			visitedNodes[i] = 0;
		}
		
		// breadth-first-search
		System.out.println("BREADTH-FIRST SEARCH:");
		BFS(connections, "A");
	}


	// reads in the connections of a graph via stdin and stores the graph in nodeList and connections.
	// format:
	// numConnections (ex 15)
	// node1 node2 (ex A B)
	static void generateGraph() {
		scan = new Scanner(System.in);
		
		numConnections = scan.nextInt();
		connections = new int[numConnections][numConnections];
		
		while(numConnections > 0) {
			firstNode = scan.next();
			secondNode = scan.next();
			
			// establish a relationship like 0 -> "A", 1 -> "B", etc.
			if(!nodeList.contains(firstNode)){ 	nodeList.add(firstNode); }
			if(!nodeList.contains(secondNode)){ nodeList.add(secondNode); }
			
			// get the index of "A", "B", etc...
			firstNodeIndex = nodeList.indexOf(firstNode);
			secondNodeIndex = nodeList.indexOf(secondNode);
			
			// connect the firstNode to the secondNode
			connections[firstNodeIndex][secondNodeIndex] = 1;
			
			numConnections --;
		}
		
		visitedNodes = new int[nodeList.size()];
	}
	
	// examines connections for any values with 1 to determine which connections exist
	static void showConnections() {
		for(int i = 0; i < connections.length; i++) {
			for(int j = 0; j < connections[i].length; j++) {
				if(connections[i][j] == 1){
					System.out.println(nodeList.get(i) + " connects to " + nodeList.get(j));
				}
			}
		}
	}
	
	// runs depth-first-search on adjacency matrix "connections" starting at String "node"
	static void DFS(int[][] connections, String node) {
		int nodeIndex = nodeList.indexOf(node);
		
		// mark the node as being visited
		visitedNodes[nodeIndex] = 1;
		
		System.out.println("Examining node " + node + ".");
		
		// for each node this one connects to, examine it (if it has not already been visited)
		//TODOmake sure it is not also looking into the same node (ex: A->A)
		for(int i = 0; i < connections[nodeIndex].length; i++){
			if(i != nodeIndex) {
				if(connections[nodeIndex][i] == 1 && visitedNodes[i] != 1){
					DFS(connections, nodeList.get(i));
				}
			}
		}
	}
	
	// runs breadth-first-search on adjacency matrix "connections" starting at String "node"
	static void BFS(int[][] connections, String node) {
		Queue<String> queue = new LinkedList<String>();
		
		// add initial node to the queue and mark it as visited
		queue.add(node);
		visitedNodes[nodeList.indexOf(node)] = 1;
				
		// find new connections to examine based on the item in the front of the queue.
		// do this as long as the queue is not empty.
		while(!queue.isEmpty()){
			node = (String) queue.remove();
			int nodeIndex = nodeList.indexOf(node);	
			
			System.out.println("Examining node " + node + ".");

			for(int i = 0; i < connections[nodeIndex].length; i++) {
				if(connections[nodeIndex][i] == 1 && visitedNodes[i] != 1){
					// add each node to the queue and mark them as visited
					queue.add(nodeList.get(i));
					visitedNodes[i] = 1;
				}
			}
			

		}
	}
}
