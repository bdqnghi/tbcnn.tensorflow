import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.LinkedHashMap;
import java.util.Set;
import java.util.Stack;
import java.util.Queue;
import java.util.LinkedList;
import java.util.function.Function;

/**
 * TA Questions...
 * 1. What is count for in the searches?
 * 2. Closed set is just read from and inserted into?
 * 3. Queue for open set in BFS, Stack in IDFS?
 * 4. If we expect search to already be done, why ask for vj in retrievePath?
 */

/**
 * @author Ryan Linden and Brandon Ngo .
 * Extra Credit Options Implemented, if any:  (mention them here.)
 *
 * Solution to Assignment 5 in CSE 373, Autumn 2016
 * University of Washington.
 *
 * (Based on starter code v1.3. By Steve Tanimoto.)
 *
 * Java version 8 or higher is recommended.
 *
 */

// Here is the main application class:
public class ExploredGraph {
	Set<Vertex> Ve; // collection of explored vertices
	Set<Edge> Ee;   // collection of explored edges
	LinkedHashMap<String, Vertex> pred; // predecessors of explored vertices, i.e. <vertex, vertexPred>
	Set<Operator> pegMoves;
	int numPegs;

	/**
	 * Explored graph constructor. Sets up edge/vertex sets and possible moves using Operator class.
	 * You can specify number of pegs using this constructor
	 * @param pegs The number of pegs in Tower-Of-Hanoi
	 */
	public ExploredGraph(int pegs) {
		Ve = new LinkedHashSet<Vertex>();
		Ee = new LinkedHashSet<Edge>();
		pred = new LinkedHashMap<String, Vertex>();
		pegMoves = new LinkedHashSet<Operator>();
		numPegs = pegs;
		// Construct possible moves
		for (int i = 0; i < numPegs; i++) {
			for (int j = 0; j < numPegs; j++) {
				if (i != j) { pegMoves.add(new Operator(i, j)); }
			}
		}
	}

	/**
	 * Explored graph constructor. Sets up edge/vertex sets and possible moves using Operator class.
	 * Uses the default of 3 pegs.
	 */
	public ExploredGraph() {
		this(3);
	}

	/**
	 * Adds the starting point to the graph.
	 * @param v The starting vertex.
	 */
	public void initialize(Vertex v) {
		// TODO Check for valid # of pegs?
		Ve.add(v);
	}

	/**
	 * Gets the number of vertices currently in explored graph.
	 * @return The total number of vertices in the graph.
	 */
	public int nvertices() {
		return Ve.size();
	}

	/**
	 * Gets the number of edges currently in explored graph.
	 * @return The total number of vertices in the graph.
	 */
	public int nedges() {
		return Ee.size();
	}

	/**
	 * Find path from vi to vj using Iterative Depth-First Search.
	 * Adds explored edges/vertices to graph as we progress.
	 * @param vi The start vertex.
	 * @param vj The end vertex.
	 */
	public void idfs(Vertex vi, Vertex vj) {
		boolean endSearch = false; // true when we find vj.
		// Set Count = 0
		// int count = 0;
		// Let OPEN = [v0]; Let CLOSED = []
		Stack<Vertex> openVe = new Stack<Vertex>();
		LinkedHashSet<Vertex> closedVe = new LinkedHashSet<Vertex>();
		// Set Pred(v0) = null;
		pred.clear();
		pred.put(vi.toString(), null);
		// Add Start vertex to open set
		openVe.push(vi);
		// While OPEN is not empty:
		while (!openVe.empty() && !endSearch) {
			// v = OPEN.removeFirst()
			Vertex currentVe = openVe.pop();
			// Set Label(v) = count; count += 1
			// count++;
			// S = successors(v);
			// For s in S:
			for (Operator move : pegMoves) {
				// if s in OPEN or s in CLOSED, continue
				// else insert s into OPEN at the front.
				Vertex childVe = move.transition(currentVe);
				if (childVe.hashCode() != currentVe.hashCode()
//						&& !openVe.contains(childVe)
//						&& !closedVe.contains(childVe)) {
						&& !stackContains(openVe, childVe)
						&& !setContains(closedVe, childVe)) {
					openVe.push(childVe);
					// Set Pred(s) = v.
					pred.put(childVe.toString(), currentVe);
					// Add to explored graph?
					Ve.add(childVe);
					Ee.add(new Edge(currentVe, childVe));
				}
				if (childVe.toString() == vj.toString()) {
					endSearch = true;
				}
			}
			// Insert v into CLOSED
			closedVe.add(currentVe);
		}
	}

	/**
	 * Check if vertex is in the Set.
	 * Used since contains does not work for the vertices...
	 * @param setVe
	 * @param vi
	 * @return
	 */
	private boolean setContains(Set<Vertex> setVe, Vertex vi) {
		Iterator<Vertex> it = setVe.iterator();
		while (it.hasNext()) {
			if (it.next().toString().equals(vi.toString())) {
				return true;
			}
		}
		return false;
	}

	private boolean stackContains(Stack<Vertex> stackVe, Vertex vi) {
		Iterator<Vertex> it = stackVe.iterator();
		while (it.hasNext()) {
			if (it.next().toString().equals(vi.toString())) {
				return true;
			}
		}
		return false;
	}

	private boolean queueContains(Queue<Vertex> queueVe, Vertex vi) {
		Iterator<Vertex> it = queueVe.iterator();
		while (it.hasNext()) {
			if (it.next().toString().equals(vi.toString())) {
				return true;
			}
		}
		return false;
	}

	/**
	 * Find path from vi to vj using Breadth-First search.
	 * Adds explored edges/vertices to graph as we progress.
	 * @param vi The start vertex.
	 * @param vj The end vertex.
	 */
	public void bfs(Vertex vi, Vertex vj) {
		boolean endSearch = false;

		// Set count = 0
		int count = 0;

		// use stack for open set
		Queue<Vertex> openVe = new LinkedList<Vertex>();
		Queue<Vertex> closedVe = new LinkedList<Vertex>();

		// Set Pred(v0) = null;
		pred.clear();
		pred.put(vi.toString(), null);

		// Add Start vertex to open set
		openVe.add(vi);
		Vertex currentVe;

		// While open set not empty:
		while (!openVe.isEmpty() && !endSearch) {
			// pop node from open set
			currentVe = openVe.remove();

			for (Operator move : pegMoves) {
				// if s in OPEN or s in CLOSED, continue.
				// else insert s into OPEN at the front.
				Vertex childVe = move.transition(currentVe);
//				if (childVe != currentVe && !closedVe.contains(childVe) && !openVe.contains(childVe)) {
				if (childVe.hashCode() != currentVe.hashCode()
						&& !openVe.contains(childVe)
						&& !closedVe.contains(childVe)) {
//						&& !queueContains(openVe, childVe)
//						&& !queueContains(closedVe, childVe)) {
					openVe.add(childVe);
					// Set Pred(s) = v.
					pred.put(childVe.toString(), currentVe);
					// Add to explored graph?
					Ve.add(childVe);
					Ee.add(new Edge(currentVe, childVe));
				}
				if (childVe.toString() == vj.toString()) {
					endSearch = true;
				}
			}
			// Insert v into CLOSED
			closedVe.add(currentVe);
		}
	}

	/**
	 * Retrieve a path to a vertex using the last tried search method.
	 * If no search method used, before, we must throw an exception.
	 * @param vi The vertex to retrieve a path to.
	 * @return The path to the specified vertex.
	 * @throws IllegalArgumentException If no search has been performed yet.
	 */
	public ArrayList<Vertex> retrievePath(Vertex vi) {

		Stack<Vertex> revPath = new Stack<Vertex>();
		ArrayList<Vertex> path = new ArrayList<Vertex>();

		if (pred.containsKey(vi.toString())) {
			// Build the path in reverse order.
			Vertex currentPred = vi;
			while (pred.get(currentPred.toString()) != null) {
				revPath.push(currentPred);
				currentPred = pred.get(currentPred.toString());
			}
			revPath.push(currentPred);
			// Reverse list to get proper order.
			while (!revPath.isEmpty()) {
				path.add(revPath.pop());
			}
		} else {
			// Vertex not in last searched path.
			throw new IllegalArgumentException();
		}

		return path;
	}

	/**
	 * Find the shortest path for two vertices using Breadth-First Search.
	 * @param vi The start vertex.
	 * @param vj The end vertex.
	 * @return The shortest path from the start to the end vertex.
	 */
	public ArrayList<Vertex> shortestPath(Vertex vi, Vertex vj) {
		// Breadth-First gives us the shortest path.
		bfs(vi, vj);
		ArrayList<Vertex> path = retrievePath(vj);
		return path;
	}

	/**
	 * Get the vertices in the explored graph.
	 * @return The vertices currently in the explored graph.
	 */
	public Set<Vertex> getVertices() {return Ve;}

	/**
	 * Get the edges in the explored graph.
	 * @return The edges currently in the explored graph.
	 */
	public Set<Edge> getEdges() {return Ee;}


	/**
	 * Vertex class, where each vertex holds a Towers-of-Hanoi state.
	 */
	class Vertex {
		ArrayList<Stack<Integer>> pegs; // Each vertex will hold a Towers-of-Hanoi state.
		// There will be 3 pegs in the standard version, but more if you do extra credit option A5E1.
		// Constructor that takes a string such as "[[4,3,2,1],[],[]]":
		public Vertex(String vString) {
			String[] parts = vString.split("\\],\\[");
			pegs = new ArrayList<Stack<Integer>>(numPegs);
			for (int i=0; i<numPegs;i++) {
				pegs.add(new Stack<Integer>());
				try {
					parts[i]=parts[i].replaceAll("\\[","");
					parts[i]=parts[i].replaceAll("\\]","");
					List<String> al = new ArrayList<String>(Arrays.asList(parts[i].split(",")));
//					System.out.println("ArrayList al is: "+al);
					Iterator<String> it = al.iterator();
					while (it.hasNext()) {
						String item = it.next();
                        if (!item.equals("")) {
//                                System.out.println("item is: "+item);
                                pegs.get(i).push(Integer.parseInt(item));
                        }
					}
				}
				catch(NumberFormatException nfe) { nfe.printStackTrace(); }
			}
		}
		public String toString() {
			String ans = "[";
			for (int i=0; i<numPegs; i++) {
			    ans += pegs.get(i).toString().replace(" ", "");
				if (i<numPegs-1) { ans += ","; }
			}
			ans += "]";
			return ans;
		}
	}

	/**
	 * Edges contain two vertices to show that it is the edge between them
	 */
	class Edge {
		private Vertex vi, vj;

		/**
		 * Construct an edge using two vertices
		 * @param vi The first vertex used in creating the edge.
		 * @param vj The second vertex used in creating the edge.
		 */
		public Edge(Vertex vi, Vertex vj) {
			this.vi = vi;
			this.vj = vj;
		}

		/**
		 * Return a string representation of an edge
		 * @return The string representation of the edge.
		 */
		public String toString() {
			String ans = "Edge from ";
			ans += vi.toString();
			ans += " to ";
			ans += vj.toString();
			return ans;
		}

		/**
		 * Get the first vertex end point.
		 * @return The first vertex end point.
		 */
		public Vertex getEndPoint1(){
			return vi;
		}

		// Return the second vertex end point

		/**
		 * Get the second vertex end point.
		 * @return The second vertex end point.
		 */
		public Vertex getEndPoint2(){
			return vj;
		}
	}

	/**
	 * Operator class is the operation to move a disk from one peg to another.
	 */
	class Operator {
		private int i, j;

		public Operator(int i, int j) { // Constructor for operators.
			this.i = i;
			this.j = j;
		}

		// Will determine whether or not this
		// operator is applicable to this vertex.
		// Only one disk may be moved at a time. Only a disk that is topmost in its stack of disks may be moved.
		// It must then be moved either to a peg containing no disks or to a peg
		// where the topmost disk is of a larger diameter than its own
		public boolean precondition(Vertex v) {
			if(v.pegs.get(i).empty()){ // Checks if peg i is empty
				return false;
			} else if (v.pegs.get(j).empty()){ // Checks if peg j is empty
				return true;
			} else if (v.pegs.get(i).peek() > v.pegs.get(j).peek()){ // Checks if top disk at peg i is larger than top disk at peg j
				return false;
			} else { // Top disk at peg is smaller than the top disk at peg j
				return true;
			}

		}

		public Vertex transition(Vertex v) {
			if(precondition(v)){
				Vertex newState = new Vertex(v.toString());
				newState.pegs.get(j).push(newState.pegs.get(i).pop());
				return newState;
			} else {
			return v; // Should return null or original input Vertex v since insertion into set of same vertex will not do anything?
			}
		}


		//Code to return a string good enough
		// to distinguish different operators
		public String toString() {
			return "Move a disk from peg " + i + " to peg " + j;

		}
	}

//	/**
//	 * Used for testing purposes
//	 * @param args
//	 */
//	public static void main(String[] args) {
//		ExploredGraph eg = new ExploredGraph(4);
//		// Test the vertex constructor:
//		Vertex v0 = eg.new Vertex("[[5,4,3,2,1],[],[],[]]");
//		Vertex v1 = eg.new Vertex("[[],[],[],[5,4,3,2,1]]");
//		System.out.println(v0);
//		// Add your own tests here.
//		eg.initialize(v0);
//		eg.idfs(v0, v1);
//		ArrayList<Vertex> idfsPath = eg.retrievePath(v1);
//		Iterator<Vertex> it = idfsPath.iterator();
//		System.out.println(idfsPath.size());
//		for (Vertex v : idfsPath) {
//			System.out.println(v.toString());
//		}
//		// The autograder code will be used to test your basic functionality later.
////		eg.Ve.add(v0); // Adds v0 to the Set of Vertexes in the ExploredGraph
////		eg.Ve.add(v1); // Adds 1 to the Set of Vertexes in the ExploredGraph
////		System.out.println(eg.nvertices()); // Size should be equal to 2
//	}

//	/**
//	 * Used for testing purposes
//	 * @param args
//	 */
//	public static void main(String[] args) {
//		ExploredGraph eg = new ExploredGraph();
//		// Test the vertex constructor:
//		Vertex v0 = eg.new Vertex("[[4,3,2,1],[],[]]");
//		Vertex v1 = eg.new Vertex("[[],[],[4,3,2,1]]");
//		System.out.println(v0);
//		// Add your own tests here.
//		eg.initialize(v0);
//		eg.idfs(v0, v1);
//		ArrayList<Vertex> path = eg.retrievePath(v1);
//		Iterator<Vertex> it = path.iterator();
//		System.out.println(path.size());
//		for (Vertex v : path) {
//			System.out.println(v.toString());
//		}
//		// The autograder code will be used to test your basic functionality later.
////		eg.Ve.add(v0); // Adds v0 to the Set of Vertexes in the ExploredGraph
////		eg.Ve.add(v1); // Adds 1 to the Set of Vertexes in the ExploredGraph
////		System.out.println(eg.nvertices()); // Size should be equal to 2
//	}

	/**
	 * Used for testing purposes
	 * @param args
	 */
	public static void main(String[] args) {
		ExploredGraph eg = new ExploredGraph();
		// Test the vertex constructor:
		Vertex v0 = eg.new Vertex("[[4,3,2,1],[],[]]");
		Vertex v1 = eg.new Vertex("[[],[],[4,3,2,1]]");
		System.out.println(v0);
		// Add your own tests here.
		eg.initialize(v0);
		ArrayList<Vertex> path = eg.shortestPath(v0, v1);
		Iterator<Vertex> it = path.iterator();
		System.out.println(path.size());
		for (Vertex v : path) {
			System.out.println(v.toString());
		}
		// The autograder code will be used to test your basic functionality later.
//		eg.Ve.add(v0); // Adds v0 to the Set of Vertexes in the ExploredGraph
//		eg.Ve.add(v1); // Adds 1 to the Set of Vertexes in the ExploredGraph
//		System.out.println(eg.nvertices()); // Size should be equal to 2
	}

}
