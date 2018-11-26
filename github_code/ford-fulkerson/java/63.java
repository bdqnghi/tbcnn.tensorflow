import java.util.*;

// Test cases available at http://www.cs.ust.hk/mjg_lib/Classes/COMP572_Fall07/Project/maxflow_test.txt
public class FordFulkerson {
	private int[] parent;
	private Queue<Integer> queue;
	private int numV;
	private boolean[] visited;

	public FordFulkerson(int numV) {
		this.numV = numV;
		this.queue = new LinkedList<Integer>();
		parent = new int[numV + 1];
		visited = new boolean[numV + 1];		
	}

	public boolean bfs(int s, int goal, int graph[][]) {
		boolean pathFound = false;
		int d, element;

		for(int v = 1; v <= numV; v++) {
			parent[v] = -1;
			visited[v] = false;
		}
		queue.add(s);
		parent[s] = -1;
		visited[s] = true;

		while (!queue.isEmpty()) { 
			element = queue.remove();
			d = 1;

			while (d <= numV) {
				if (graph[element][d] > 0 &&  !visited[d]) {
					parent[d] = element;
					queue.add(d);
					visited[d] = true;
				}
				d++;
			}
		}
		if(visited[goal]) {
			pathFound = true;
		}
		return pathFound;
	}

	public int fordFulkerson(int graph[][], int s, int d) {
		int u, v;
		int maxFlow = 0;
		int pathFlow;

		int[][] residualGraph = new int[numV + 1][numV + 1];
		for (int sVertex = 1; sVertex <= numV; sVertex++) {
			for (int dVertex = 1; dVertex <= numV; dVertex++) {
				residualGraph[sVertex][dVertex] = graph[sVertex][dVertex];
			}
		}

		while (bfs(s ,d, residualGraph)) {
			pathFlow = Integer.MAX_VALUE;
			for (v = d; v != s; v = parent[v]) {
				u = parent[v];
				pathFlow = Math.min(pathFlow, residualGraph[u][v]);
			}
			for (v = d; v != s; v = parent[v]) {
				u = parent[v];
				residualGraph[u][v] -= pathFlow;
				residualGraph[v][u] += pathFlow;
			}
			maxFlow += pathFlow;	
		}
		return maxFlow;
	}

	public static void main(String...arg) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter the number of nodes");
		int numV = sc.nextInt();
		int[][] graph = new int[numV + 1][numV + 1];

		System.out.println("Enter the graph matrix");
		for (int s = 1; s <= numV; s++) {
			for (int d = 1; d <= numV; d++) {
				graph[s][d] = sc.nextInt();
			}
		}

		System.out.println("Source:");
		int source= sc.nextInt();
		System.out.println("Sink:");
		int sink = sc.nextInt();
		FordFulkerson fordFulkerson = new FordFulkerson(numV);
		int maxFlow = fordFulkerson.fordFulkerson(graph, source, sink);
		System.out.println("The Max Flow is " + maxFlow);
		sc.close();
	}
}