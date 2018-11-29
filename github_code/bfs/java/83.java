package global.structures.trieclustercat;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

import edu.stanford.nlp.ling.IndexedWord;

public class BreadthFirstSearch {

	public BreadthFirstSearch() {

	}

	public boolean compute(GraphNode startGraphNode, GraphNode goalGraphNode) {

		if (startGraphNode.equals(goalGraphNode)) {
			System.out.println("startGraphNode=" + startGraphNode + " == " + goalGraphNode);
			System.out.println(startGraphNode.getNodeValue());
		}

		Queue<GraphNode> queue = new LinkedList<>();
		ArrayList<GraphNode> explored = new ArrayList<>();
		queue.add(startGraphNode);

		while (!queue.isEmpty()) {

			GraphNode current = queue.remove();
			if (current != null && !explored.contains(current)) {

				System.out.println("add " + current.toString());
				explored.add(current);

				if (current.getNodeValue().equals(goalGraphNode.getNodeValue())) {

					for (GraphNode gn : explored)
						System.out.println("->explored!" + gn.getNodeValue());
					return true;

				} else {
					if (current.getChildren().isEmpty())
						return false;
					else {
						// System.out.println("add >>" + current.getChildren());
						queue.addAll(current.getChildren());
					}
				}

			}
		}

		System.out.println("No path found at this point.");
		return false;

	}

	public void exploreBfs(GraphNode startGraphNode, int maxDepth) {

		Queue<GraphNode> queue = new LinkedList<>();

		Map<Integer, Set<GraphNode>> results = new LinkedHashMap<>();
		Set<GraphNode> explored = new LinkedHashSet<>();
		int level = 0, elementsToDepthIncrease = 1, nextElementsToDepthIncrease = 0;
		queue.add(startGraphNode);

		while (!queue.isEmpty()) {

			GraphNode node = queue.remove();

			if (node != null && !explored.contains(node)) {

				explored.add(node);
				// System.out.println("add " + level + " :: " + current.toString());

				Set<GraphNode> soFar = results.get(level);
				if (soFar == null)
					soFar = new HashSet<>();
				soFar.add(node);
				results.put(level, soFar);

				nextElementsToDepthIncrease += node.getChildren().size();

				if (--elementsToDepthIncrease == 0) {
					if (++level > maxDepth)
						break;
					elementsToDepthIncrease = nextElementsToDepthIncrease;
					nextElementsToDepthIncrease = 0;
				}

				if (!node.getChildren().isEmpty()) {
					queue.addAll(node.getChildren());
				}
			}
		}

		System.out.println("explored" + explored);
		for (Integer l : results.keySet()) {
			Set<GraphNode> gns = results.get(l);
			for (GraphNode gn : gns) {
				// if (!gn.getChildren().isEmpty())
				System.out.println(l + "->" + gn.getNodeValue() + ", children=" + gn.getChildren());
			}
		}
	}

	public static void main(String args[]) {
		IndexedWord westminster = new IndexedWord();
		westminster.setValue("Westminster");

		IndexedWord waterloo = new IndexedWord();
		waterloo.setValue("Waterloo");

		IndexedWord londonBridge = new IndexedWord();
		londonBridge.setValue("London Bridge");

		IndexedWord trafalgarSquare = new IndexedWord();
		trafalgarSquare.setValue("Trafalgar Square");
		// System.out.println("trafalgarSquare" + trafalgarSquare);

		GraphNode westminsters = new GraphNode(westminster);
		GraphNode waterloos = new GraphNode(waterloo);
		GraphNode trafalgarSquares = new GraphNode(trafalgarSquare);
		GraphNode londonBridges = new GraphNode(londonBridge);

		westminsters.addNeighbor(trafalgarSquares);
		westminsters.addNeighbor(waterloos);
		trafalgarSquares.addNeighbor(londonBridges);
		waterloos.addNeighbor(trafalgarSquares);
		waterloos.addNeighbor(westminsters);
		londonBridges.addNeighbor(trafalgarSquares);
		londonBridges.addNeighbor(waterloos);

		BreadthFirstSearch bfs = new BreadthFirstSearch();

		// if (bfs.compute(waterloos, londonBridges))
		// System.out.print("Path Found!");

		bfs.exploreBfs(waterloos, 5);
	}

}