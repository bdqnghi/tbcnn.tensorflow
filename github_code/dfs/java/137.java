/**
 * Program Name: ProgramC: heuristic depth-first-search (hDFS)
 * @author Jack Hysell
 * @date 7/16/2017
 * @description	This program performs a heuristic depth-first-search (hDFS) on a 
 * directed weighted graph that is imported as an adjacency matrix in .txt format. 
 * After the operation has been performed, results detailing the grpahs traversal 
 * order, vertices start and finish times, edge classification, topological sort, 
 * and strongly connected components are printed to and output file also in .txt 
 * format containing the original files name appended with "_out.txt."
 * 
 * This program contains four classes:
 * 	FileManagement: Allows user to select a .txt file to import, then formats that 
 * 					file and sends it off to the DFS class.
 *  
 * 	DFS: 			Performs the heuristic depth-first-search on the graph provided.
 * 
 * 	Vertex:			Allows us to create a unique object for each vertex in the graph
 * 					containing all of the vital information needed to perform hDFS.
 * 
 * Edge:			Allows us to create a unique object for each edge in the graph 
 * 					containing vital information needed to get the edge classification.	
 * 
 * @sources
 * 	This is the one source I used to get some inspiration for how I may go about designing
 * 	this program. In the end, I'm happy to say that the  code here was actually not copy 
 * 	pasted from anywhere. 
 * 	https://www.dropbox.com/s/3dzueevdm87yso2/Graph.java									
 */

package hDFS;

import java.util.LinkedList;

public class Edge {
	
	// Data types for the Edge class
	private String startingEdge;
	private LinkedList<Integer> children;
	
	// Constructor for the Edge Class
	public Edge(String startingEdge, LinkedList<Integer> children) {
		super();
		this.startingEdge = startingEdge;
		this.children = children;
	}
	
	// Getters & Setters for the Edge Class
	public String getStartingEdge() {
		return startingEdge;
	}
	
	public void setStartingEdge(String startingEdge) {
		this.startingEdge = startingEdge;
	}
	
	public LinkedList<Integer> getChildren() {
		return children;
	}
	
	public void setChildren(LinkedList<Integer> children) {
		this.children = children;
	}
}
