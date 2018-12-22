import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
/*
@author Keerthi Bala Sundram
This class does the BFS traversal and finds the shortest paths from the root to the other nodes.
* Date : 03/24/2016
*/
public class BFS {
	/*
	 * Procedure that computes the BFS of the given graph G.
	 * 
	 * @param g : The Directed graph for which the BFS traversal has to be made
	 * pre-condition : Graph is directed
	 * 
	 */
	public void BFS(Graph g) {

		for (Vertex u : g.verts) {
			u.parent = null;
			u.distance = 0;
			u.seen = false;
		}

		Queue<Vertex> queue = new LinkedList();
		// adding root
		Vertex root = g.verts.get(1);
		queue.add(root);

		root.distance = 0;
		root.seen = true;

		//BFS traversal
		while (!queue.isEmpty()) {
			Vertex u = queue.remove();

			for (Edge e : u.Adj) {
				Vertex v = e.otherEnd(u);

				if (!v.seen) {
					//distance of the node is the parents distance plus the selected edge's weight
					v.distance = u.distance + e.Weight;
					v.parent = u;
					v.seen = true;
					queue.add(v);
				}

			}

		}

		printBFS(g);

	}
	/*
	 * Procedure that prints the shortest path of all the nodes in the given graph g
	 * 
	 * @param g : The Directed graph for which the BFS shortest path has to be printed
	 * 
	 * pre-condition : Graph is directed
	 * 
	 */
	public void printBFS(Graph g) {
		
		
		
		int total = 0;

		for (Vertex u:g) {

			Vertex current = u;
		
			while (current.parent != null) {
				current = current.parent;
			}
			if (current.name != g.verts.get(1).name) {
				u.distance = -1;
			} else {
				total += u.distance;
			}

		}
		System.out.print("BFS "+" " + total);
		
		System.out.println();
		if (g.verts.size() <= 101) {
			for (Vertex u : g) {
				
				String shortPath = u.distance != -1 ? String.valueOf(u.distance) : "INF";
				String parent = u.parent == null ? "-" : u.parent.toString();
				System.out.print(u + " " + shortPath + " " + parent);
				System.out.println();
			}
		}
	}

	}
