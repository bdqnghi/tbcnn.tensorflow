/**
 * Jimmy C Lu jcl2182
 * HW2
 * 
 * This class uses a breadth first search to find
 * a solution to a sokoban game.
 */

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Stack;

public class BreadthFirstSearch {
	private GameMap gameMap;

	public BreadthFirstSearch(GameMap m) {
		gameMap = m;
	}
	
	/*
	 * The search uses a linked list and simply adds nodes 
	 * that are unexplored and pops the node from previous
	 * depth.  This ensures that every possible move is
	 * explored.
	 * 
	 * Directional changes dx and dy are based on two arrays to determine
	 * where to add to subtract.
	 */

	private int[] dx = { 0, 0, 1, -1 };
	private int[] dy = { 1, -1, 0, 0 };
	private final int DIRSIZE = 4;
	private long nodesGenerated, nodesRevisited;
	private ArrayList<GameMap> exploredList;

	public Node search() {
		Node curNode = new Node(gameMap);

		nodesGenerated = 0;
		nodesRevisited = 0;
		LinkedList<Node> ll = new LinkedList<Node>();
		exploredList = new ArrayList<GameMap>();
		ll.add(curNode);

		if (curNode.isSolved())
			return curNode;

		while (!ll.isEmpty()) {
			curNode = ll.pop();
			exploredList.add(curNode.gameMap);
			curNode.isVisited = true;
			for (int i = 0; i < DIRSIZE; i++) {
				Node n = new Node(curNode.gameMap);
				nodesGenerated++;
				if (n.move(dx[i], dy[i]) && !isExplored(n.gameMap)) {
					n.prev = curNode;
					setBranches(n, curNode, dx[i], dy[i]);
					if (n.isSolved())
						return n;
					ll.add(n);
				}
			}
		}
		return null;
	}
	
	/*
	 * Set branches connects all the nodes together for fringe search
	 */

	private void setBranches(Node n, Node curNode, int x, int y) {
		if (x == 1) {
			n.right = curNode;
		} else if (x == -1)
			n.left = curNode;
		else if (y == 1)
			n.down = curNode;
		else if (y == -1)
			n.up = curNode;
	}

	/*
	 * Compares the maps to see if it's an explored node.  If the
	 * map is exactly the same then it's a move that's definitely 
	 * been explored.
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
	 * 
	 * Fringe nodes is not used by method is still there to
	 * to count any unvisited nodes.  Since this nodes doesn't
	 * visit explored nodes, there are none.
	 */
	private long fringeNodes;

	public void printResult() {
		fringeNodes = 0;
		long time = System.nanoTime();
		Node n = search();
		if (n == null) {
			System.out.println("Solution not found");
			return;
		}
		time = System.nanoTime() - time;
		time /= 1000;
		String result = "Solution: ";
		Stack<Character> s = new Stack<Character>();
		s.push(n.trans);
		while ((n = n.prev) != null) {
			s.push(n.trans);
		}

		while (!s.isEmpty()) {
			result += s.pop() + " ";
		}

		result += "\n" + "Nodes Generated: " + nodesGenerated + "\n";
		result += "Nodes revisited: " + nodesRevisited + "\n";
		result += "Explored nodes list: " + exploredList.size() + "\n";
		result += "Time: " + time + " milliseconds \n";
		System.out.println(result);
	}

	/*
	 * Does a depth traversal to find fringe nodes.
	 * Not used.
	 */
	private void setFringeNodes(Node n) {
		if (!n.isVisited)
			fringeNodes++;
		if (n.up != null)
			setFringeNodes(n.up);
		if (n.left != null)
			setFringeNodes(n.left);
		if (n.down != null)
			setFringeNodes(n.down);
		if (n.right != null)
			setFringeNodes(n.right);
	}
}
