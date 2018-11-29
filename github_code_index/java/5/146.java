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

public class Vertex {
	
	// Data types for the Vertex Class
	private String nodeName, parent;
	private LinkedList<Integer> children;
	private Boolean visited;
	private int start, finish;
		
	// Constructor for the Vertex Class
	public Vertex(String nodeName, LinkedList<Integer> children, Boolean visited, int start, int finish, String parent) {
		super();
		this.nodeName = nodeName;
		this.children = children;
		this.visited = visited;
		this.start = start;
		this.finish = finish;
		this.parent = parent;
	}	
	
	// Getters & Setters for the Vertex Class
	public String getParent() {
		return parent;
	}

	public void setParent(String parent) {
		this.parent = parent;
	}

	public int getStart() {
		return start;
	}

	public void setStart(int start) {
		this.start = start;
	}

	public int getFinish() {
		return finish;
	}

	public void setFinish(int finish) {
		this.finish = finish;
	}

	public void setNodeName(String n) {
		this.nodeName = n;
	}
	
	public void setChildren(LinkedList<Integer> children) {
		this.children = children;
	}
	
	public void setVisited(Boolean f) {
		this.visited = f;
	}
	
	public String getNodeName() {
		return nodeName;
	}
	
	public LinkedList<Integer> getChildren() {
		return children;
	}
	
	public Boolean getVisited() {
		return visited;
	}

}
