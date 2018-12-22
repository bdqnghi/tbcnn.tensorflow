package nonlinear.graph.client;

import java.util.ArrayDeque;
import java.util.Deque;

import nonlinear.graph.api.DepthFirstSearch;
import nonlinear.graph.api.Graph;
import nonlinear.graph.api.GraphUsingAdjacencyList;

public class Paths {

	private DepthFirstSearch depthFirstSearch;

	public Paths(Graph G, int source) {
		depthFirstSearch = new DepthFirstSearch(G, source);
	}

	/***
	 * 
	 * @param v
	 *            source vertex
	 * @param w
	 *            destination vertex
	 * @return This method returns a List of vertices connecting vertex v and vertex
	 *         w
	 */
//	public List<Integer> getPath(int v, int w) {
//
//		return null;
//	}

	public boolean hasPathTo(int vertex) {
		if(vertex >= this.depthFirstSearch.getDepthFirstSearchHelperArr().length) return false;
		return this.depthFirstSearch.getDepthFirstSearchHelperArr()[vertex] != null;
	}

	/***
	 * 
	 * @param v
	 * @return a stack of vertices connecting vertex v to the source vertex s
	 */
	public Deque<Integer> getPathFromSource(int v) {
		Deque<Integer> stackOfVertices = new ArrayDeque<>();
		if (this.hasPathTo(v)) {
			System.out.println("[getPathFromSource] : has path...");
			System.out.println( "...edgeTo.......... " + this.depthFirstSearch.getDepthFirstSearchHelperArr()[v].getEdgeTo());
			System.out.println( "...edgeTo.......... " + this.depthFirstSearch.getDepthFirstSearchHelperArr()[this.depthFirstSearch.getDepthFirstSearchHelperArr()[v].getEdgeTo()].getEdgeTo());
			for (int x = v; x != this.depthFirstSearch
					.getSource(); x = this.depthFirstSearch.getDepthFirstSearchHelperArr()[x].getEdgeTo()) {
				System.out.println("[getPathFromSource] : path : " + x);
				stackOfVertices.push(x);
			}
			stackOfVertices.push(this.depthFirstSearch.getSource());
		}
		return stackOfVertices;
	}
	
	
	public static void main(String[] args) {
		Graph G = new GraphUsingAdjacencyList(7);
		G.addEdge(0, 1);
		G.addEdge(0, 3);
		G.addEdge(1, 6);
		G.addEdge(1, 0);
		G.addEdge(1, 2);
		G.addEdge(1, 6);
		G.addEdge(2, 1);
		G.addEdge(3, 6);
		G.addEdge(3, 5);
		G.addEdge(4, 6);
		G.addEdge(4, 0);
		G.addEdge(5, 3);
		G.addEdge(5, 6);
		G.addEdge(6, 1);
		G.addEdge(6, 5);
		G.addEdge(6, 4);
		
		Paths paths = new Paths(G, 0);
		System.out.println("has path to 6 : " + paths.hasPathTo(6));

		paths.getPathFromSource(22).forEach(e->{
			System.out.println("eeeeeeeeeee--" + e);
		});;
		
		
		
	}
}
