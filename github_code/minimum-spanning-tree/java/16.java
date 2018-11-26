package knmi.msolve.model.generate;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import knmi.msolve.model.maze.Node;

/**
 * <p> This algorithm is a randomized version of Kruskal's algorithm. </p>
 * 
 * <p>
 * Kruskal's algorithm is a minimum-spanning-tree algorithm which finds an edge of the least possible weight that connects any two trees in the forest. 
 * It is a greedy algorithm in graph theory as it finds a minimum spanning tree for a connected weighted graph adding increasing cost arcs at each step.
 * This means it finds a subset of the edges that forms a tree that includes every vertex, where the total weight of all the edges in the tree is minimized. 
 * If the graph is not connected, then it finds a minimum spanning forest (a minimum spanning tree for each connected component).
 * </p>
 * @author baasj
 *
 */
public class KruskalMazeGenerator extends MazeGenerator {

	public KruskalMazeGenerator(int width, int height, boolean polar) {
		super(width, height, polar);
	}

	@Override
	protected void generateMaze() {
		List<Wall> walls = new ArrayList<>();
		Map<Node, LinkedList<Node>> nodeMap = new HashMap<>();
		Set<Node> visited = new HashSet<>();
		
		for(Node node : nodes) {
			visited.add(node);

			LinkedList<Node> ll = new LinkedList<>();
			ll.add(node);
			nodeMap.put(node, ll);
			
			for(Node adj : node){
				if(!visited.contains(adj)){
					walls.add(new Wall(node, adj));
				}
			}
			// Set up walls around this cell
			node.clearNeighbors();
		}
		
		// For each wall, in some random order
		Collections.shuffle(walls);
		for(Wall wall : walls) {
			
			Node n1 = wall.n1;
			Node n2 = wall.n2;
			
			LinkedList<Node> disjointSet1 = nodeMap.get(n1);
			LinkedList<Node> disjointSet2 = nodeMap.get(n2);
			
			// If the cells divided by this wall belong to distinct sets
			if(disjointSet1 != disjointSet2) {
			    // Remove the current wall.
				Node.connect(n1, n2);
				
			    // Merge the sets of the formerly divided cells
				// Try adding the smaller set to the larger one
				LinkedList<Node> newSet;
				if(disjointSet1.size() < disjointSet2.size()) {
					disjointSet2.addAll(disjointSet1);
					newSet = disjointSet2;
				} else {
					disjointSet1.addAll(disjointSet2);
					newSet = disjointSet1;
				}
				
				// Update the reference for each node in the merged set
				for(Node n : newSet) {
					nodeMap.put(n, newSet);
				}
			}
			
		}
	}
	
	class Wall {
		private final Node n1,n2;

		public Wall(Node n1, Node n2) {
			this.n1 = n1;
			this.n2 = n2;
		}
	}
}
