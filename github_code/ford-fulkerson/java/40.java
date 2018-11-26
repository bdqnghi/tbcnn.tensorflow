import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

public class FordFulkerson {

	public int maxFlow(int source, int sink, int cap[][]) {

		int result = 0;
		Map<Integer, Integer> parent = new HashMap<>();
		while (BFS(cap, source, sink, parent)) {
			int flow = Integer.MAX_VALUE;
			int v = sink;
			while (v != source) {
				int u = parent.get(v);
				flow = Math.min(flow, cap[u][v]);
				v = u;
			}
			result += flow;
			v=sink;
			while (v != source) {
				int u = parent.get(v);
				cap[u][v] -= flow;
				cap[v][u] += flow;
				v = u;
			}
		}
		return result;
	}

	public boolean BFS(int cap[][], int source, int sink, Map<Integer, Integer> parent) {

		Set<Integer> visited = new HashSet<>();
		Queue<Integer> queue = new LinkedList<>();
		visited.add(source);
		queue.add(source);
		boolean find = false;
		while (!queue.isEmpty()) {
			int u = queue.poll();
			for (int v = 0; v < cap.length; v++) {
				if (!visited.contains(v) && cap[u][v] > 0) {
					parent.put(v, u);
					visited.add(v);
					queue.add(v);
					if (v == sink) {
						find = true;
						break;
					}
				}
			}
		}
		return find;
	}

	public FordFulkerson() {
		int[][] capacity = { { 0, 3, 0, 3, 0, 0, 0 }, { 0, 0, 4, 0, 0, 0, 0 }, { 3, 0, 0, 1, 2, 0, 0 },
				{ 0, 0, 0, 0, 2, 6, 0 }, { 0, 1, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0, 0, 9 }, { 0, 0, 0, 0, 0, 0, 0 } };
		System.out.println(maxFlow(0, 6, capacity));
	}

	public static void main(String[] args) {
		new FordFulkerson();
	}
}
