import java.util.ArrayList;
import java.util.Stack;

/**
 * 
 * This class performs a depth first search on a graph.
 * 
 * @author Joe Cuffney
 *
 */
public class DFS {

	public static boolean[] marked;
	public static int count;
	public static double dist;

	/**
	 * Constructs a DFS object which performs a depth first search on the passed
	 * in graph g upon creation.
	 * 
	 * @param g
	 */
	public static String path(Graph g) {
		marked = new boolean[g.V().length];
		Stack<Integer> stack = new Stack<Integer>();
		int[] result = new int[g.V().length + 1];
		int resIdx = g.V().length;
		stack.push(0);
		while (!stack.isEmpty()) {
			int v = stack.pop();
			result[resIdx] = v;
			resIdx--;
			if (marked[v] != true)
				marked[v] = true;
			ArrayList<Integer> adjs = g.getAdj(v);
			for (int a : adjs) {
				if (marked[a] != true) {
					stack.push(a);
				}
			}
		}
		result[0] = 0;
		String res = "";
		for (int i = 0; i < result.length; i++) {
			res += result[i] + " ";
		}
		return res;
	}

	/**
	 * Uses an iterative approach to DFS and prints the parents of each node
	 * when p is true. (FOR MST)
	 * 
	 * @param g
	 */
	public static int[] path(Graph g, boolean p) {
		marked = new boolean[g.V().length];
		Stack<DFSTuple> stack = new Stack<DFSTuple>();

		int[] result = new int[g.V().length + 1];
		int resIdx = 0;

		stack.push(new DFSTuple(0, -1));

		while (!stack.isEmpty()) {
			DFSTuple v = stack.pop();
			marked[v.v()] = true;
			if (p)
				System.out.println("Parent of " + v.v() + " is " + v.p());

			result[resIdx] = v.v();
			resIdx++;

			ArrayList<Integer> adjs = g.getAdj(v.v());
			for (int i = adjs.size(); i > 0; i--) {
				if (!marked[adjs.get(i - 1)]) {
					stack.push(new DFSTuple(adjs.get(i - 1), v.v()));
				}
			}
		}
		result[resIdx] = 0;
		return result;
	}

}
