package tree;

import java.util.ArrayDeque;
import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.ThreadLocalRandom;

import graph.Edge;
import graph.EdgeComparator;
import graph.Graph;
import graph.UnionFind;
import graph.Vertex;

public class Tree {

	public Node bigFather;
	public int maxDepth;
	
	public Node[] node;
	
	/// Summary: Creates a Minimum Spanning Tree from a Graph.
	/// The implementation uses a breadth-first search to add children starting from the root.
	public Tree(Graph G) {

		// We first apply the Minimum-spanning-tree algorithm to the Graph.
		Edge[] E = MST(G);
		
		// Next we transform the array of edges into vertices (containing their neighbours / weights) so we can easily process.
		// This is done in linear time.
		Vertex[] V = Graph.EdgesToVertices(E, G.n);
		
		
		// Finally we proceed to create the tree.
		
		node = new Node[V.length];
		
		for(int i = 0; i < V.length; i++)
			
			node[i] = new Node(i,null,0);
				
		// Sets a random node as the root of the tree
		int rand = ThreadLocalRandom.current().nextInt(node.length);
		bigFather = node[rand];
		
		maxDepth = 0;
		
		// Uses Breadth-First Search to create the tree with nodes at appropriate height, with root = bigFather.
		Queue<Vertex> BFS = new ArrayDeque<Vertex>();
		BFS.add(V[bigFather.id]);
		
		while( !BFS.isEmpty() ) {

			Vertex u = BFS.remove();
			
			Vertex[] Nu = u.GetNeighbours();
			Integer[] Wu = u.GetWeights();
			
			// We set all neighbours of u (except his own father) as children of u.
			for( int i = 0; i < Nu.length ; i++ ) {

				Vertex v = Nu[i];
				
				int w = Wu[i];
				
				if(node[v.id] != node[u.id].GetFather()) {

					node[u.id].children.add(node[v.id]);				
					node[v.id].SetFather(node[u.id],w);
					
					BFS.add(v);
					
					// we can safely set the maxDepth at each iteration since we are using BFS (depths are always increasing).
					maxDepth = node[v.id].height;
				}
				
			}
		}
		
	}
	
	//Kruskal's Algorithm to find a Minimum Spanning Tree from graph G.
	public static Edge[] MST(Graph G) {

		UnionFind u = new UnionFind(G.n);
		LinkedList<Edge> l = new LinkedList<Edge>();
		for(int j = 0; j < G.E.length; j++)
			l.add(G.E[j]);
		l.sort(new EdgeComparator());

		Edge[] F = new Edge[G.n - 1];
		int i =0;
		for(Edge r : l){
			int source = r.u;
			int target = r.v;
			if(u.find(source) != u.find(target)){
				F[i] = r;
				i++;
				u.union(source, target);
			}		
			
		}
		return F;
	}
	
	
	// Returns a string codifying the Tree by depth.
	public String toString() {
		
		String s = "";
		
		Queue<Node> BFS = new ArrayDeque<Node>();
		BFS.add(bigFather);
		s += bigFather.id + "\n";
		int height = 0;
		while(!BFS.isEmpty()) {
			
			Node nd = BFS.remove();
			if(nd.height > height)
				s+="\n";
			height = nd.height;
			
			for (Node child : nd.children) {
				BFS.add(child);
				s += child.id + " | ";

			}
			
		}
				
		return s;
		
	}
	
}
