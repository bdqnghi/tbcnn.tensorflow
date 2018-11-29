/**
 * Jimmy C Lu jcl2182
 * HW2
 * 
 * This class uses a depth first search to find
 * a solution to a sokoban game.
 */

import java.util.ArrayList;
import java.util.Stack;

public class DepthFirstSearch {
	private GameMap gameMap;

	public DepthFirstSearch(GameMap m) {
		gameMap = m;
	}

	/*
	 * Uses a stack to place all unexplored nodes in one branch.
	 * It then pops it when it finds a node that has an explored
	 * node from each branch.
	 * 
	 * Explored list checks all nodes.
	 */
	private long nodesGenerated, nodesRevisited;
	private ArrayList<GameMap> exploredList;
	private Stack<Node> stack;

	public Node search() {
		Node curNode = new Node(gameMap);
		stack = new Stack<Node>();
		exploredList = new ArrayList<GameMap>();
		stack.push(curNode);
		exploredList.add(curNode.gameMap);
		return dfs(curNode);
	}

	/*
	 * Recursively explores everything.  So if left is not null
	 * then add to stack and keep traversing left.
	 */
	private Node dfs(Node curNode) {
		if (curNode.isSolved())
			return curNode;
		Node n = new Node(curNode.gameMap);
		try {
			if (n.move(1, 0) && !isExplored(n.gameMap)) {
				nodesGenerated++;
				stack.push(n);
				n.prev = curNode;
				exploredList.add(n.gameMap);
				dfs(n);
			}
			n = new Node(curNode.gameMap);
			if (n.move(-1, 0) && !isExplored(n.gameMap)) {
				stack.push(n);
				nodesGenerated++;
				n.prev = curNode;
				exploredList.add(n.gameMap);
				dfs(n);
			}
			n = new Node(curNode.gameMap);
			if (n.move(0, 1) && !isExplored(n.gameMap)) {
				stack.push(n);
				n.prev = curNode;
				nodesGenerated++;
				exploredList.add(n.gameMap);
				dfs(n);
			}
			n = new Node(curNode.gameMap);
			if (n.move(0, -1) && !isExplored(n.gameMap)) {
				stack.push(n);
				n.prev = curNode;
				nodesGenerated++;
				exploredList.add(n.gameMap);
				dfs(n);
			}
		} catch (StackOverflowError e) {
		}

		if (!stack.isEmpty()) {
			curNode = stack.pop();
			if (curNode.isSolved())
				return n;
			dfs(curNode);
		}

		return null;
	}

	/*
	 * Compares the maps to determine if it's a move
	 * that's definitely been explored.
	 * 
	 * Increments nodes revisited int.
	 */
	private boolean isExplored(GameMap m) {
		if (exploredList == null)
			return false;

		for (GameMap compare : exploredList) {
			if (m.isEquals(compare)) {
				nodesRevisited++;
				return true;
			}
		}

		return false;
	}
	/*
	 * Main function that is called to run the algorithm and 
	 * prints out the result.
	 * 
	 * Keeps track of time with system nano time and converts 
	 * it to milliseconds.
	 */
	public void printResult() {
		long time = System.nanoTime();
		String result = "";
		Node n = search();
		if (n == null) {
			result += "Solution not found";
		} else {
			result += "Solution: ";
			Stack<Character> s = new Stack<Character>();
			s.push(n.trans);
			while ((n = n.prev) != null) {
				s.push(n.trans);
			}

			while (!s.isEmpty()) {
				result += s.pop() + " ";
			}
		}
		time = System.nanoTime() - time;
		time /= 1000;
		result += "\n" + "Nodes Generated: " + nodesGenerated + "\n";
		result += "Nodes revisited: " + nodesRevisited + "\n";
		result += "Explored nodes list: " + exploredList.size() + "\n";
		result += "Time: " + time + " milliseconds \n";

		System.out.println(result);
	}
}
