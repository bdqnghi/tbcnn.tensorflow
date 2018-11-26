package graphos;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.PriorityQueue;

/*
 * Prim's Algorithms 
 * MST - Minimum-Spanning-Tree
 */

public class P1774 {

	public static void main(String[] args) throws IOException {

		BufferedReader scan = new BufferedReader(new InputStreamReader(System.in));

		String[] split = scan.readLine().split(" ");
		Integer vertexes = Integer.parseInt(split[0]);
		Integer count = Integer.parseInt(split[1]);
		PriorityQueue<Router> queue = new PriorityQueue<>();
		ArrayList<LinkedList<Router>> adjList = new ArrayList<LinkedList<Router>>();

		int totalCost = 0, index = 1;

		boolean[] checks = new boolean[vertexes + 1];

		for (int i = 1; i <= vertexes + 1; i++) {
			adjList.add(new LinkedList<Router>());
		}

		while (count-- > 0) {

			String[] split2 = scan.readLine().split(" ");

			int origin = Integer.parseInt(split2[0]);
			int destin = Integer.parseInt(split2[1]);
			int cost = Integer.parseInt(split2[2]);

			Router router = new Router();
			router.cost = cost;
			router.destin = destin;

			Router router2 = new Router();
			router2.cost = cost;
			router2.destin = origin;

			adjList.get(origin).add(router);
			adjList.get(destin).add(router2);

		}

		while (vertexes-- > 0) {

			checks[index] = true;
			LinkedList<Router> currentRouter = adjList.get(index);

			for (int i = 0; i < currentRouter.size(); i++) {
				queue.add(currentRouter.get(i));
			}
			Router router;
			while (true) {
				router = queue.poll();

				if (router == null)
					break;

				if (!checks[router.destin]) {
					totalCost += router.cost;
					index = router.destin;
					break;
				}
			}

		}

		System.out.println(totalCost);

	}

}

class Router implements Comparable<Router> {
	Integer destin;
	Integer cost;

	@Override
	public int compareTo(Router router2) {
		// TODO Auto-generated method stub
		return cost.compareTo(router2.cost);
	}

}