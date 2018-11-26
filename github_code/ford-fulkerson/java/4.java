import java.util.*;
public class fordfulkerson
{
	static int fordFulkerson(int[][] cap, int[][] fnet, int n, int s, int t) {
		//ASSUMES: cap[u][v] stores capacity of edge (u,v). cap[u][v] = 0 for no edge.
		//Initialise the flow network so that fnet[u][v] = 0 for all u,v
		int flow = 0; //no flow yet

		while (true) {
			//Find an augmenting path using BFS
			int[] prev = new int[n];
			Arrays.fill(prev, -1);
			LinkedList<Integer> queue = new LinkedList<Integer>();
			prev[s] = -2;
			queue.add(s);
			while (!queue.isEmpty() && prev[t] == -1) {
				int u = queue.poll();
				for (int v = 0; v < n; v++) {
					if (prev[v] == -1) { //not seen yet
						if (fnet[v][u] > 0 || fnet[u][v] < cap[u][v]) {
							prev[v] = u;
							queue.add(v);
						}
					}
				}
			}
			//See if we couldn't find any path to t (t has no parents)
			if (prev[t] == -1) break;

			//Get the bottleneck capacity;
			int bot = Integer.MAX_VALUE;
			for (int v = t, u = prev[v]; u >= 0; v = u, u = prev[v]) {
				if (fnet[v][u] > 0)  //prefer a backward edge over a forward
					bot = bot < fnet[v][u] ? bot : fnet[v][u];
				else //must be a forward edge otherwise
					bot = bot < cap[u][v] - fnet[u][v]? bot: cap[u][v] - fnet[u][v];
			}

			//update the flow network
			for (int v = t, u = prev[v]; u >= 0; v = u, u = prev[v]) {
				if (fnet[v][u] > 0) //backward edge -> subtract
					fnet[v][u] -= bot;
				else //forward edge -> add
					fnet[u][v] += bot;
			}

			//Sent 'bot' amount of flow from s to v, so update the flow
			flow += bot;
		}
		return flow;
	}
}
