package algorithms;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Set;

import components.Edge;
import components.Graph;
import components.Node;

/**
 * 
 * Breadth-First-Search Implementation
 * 
 * @author Antonios Georgiadis
 *
 */

public class BFS {

	public static void search(Graph graph, Node root, Node goal) {

		Queue<Node> queue = new LinkedList<Node>();
		Set<Node> visited = new HashSet<Node>();

		Node current;
		queue.add(root);
		visited.add(root);

		while (queue.size() > 0) {
			current = queue.poll();
			System.out.println(current.ID + " ");
			if (current.equals(goal)) break;

			for (Edge connection : current.getConnections()) {
				if (!visited.contains(connection.destination)) {
					queue.add(connection.destination);
					visited.add(connection.destination);
				}
			}
		}
	}
}
