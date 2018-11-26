/**
 *
 * The Maximum Flow Problem:
 * 			Given a directed weighted graph, source vertex 's',
 * 			target vertex 't', find the maximum flow that can go from s to s,
 * 			given that each edge has a positive capacity.
 * 
 * Ford-Fulkerson's Method:
 * 	mxf = 0
 * 	while(there exists an augmenting path from s to t)
 * 		1- find the flow 'f' along the path
 *  	2- decrease capacities of forward edges along the path by f
 *  	3- increase capacities of backward edges along the path by f
 *  	4- mxf += f
 * 	return mxf
 * 
 * Time Complexity: O(mxf*|E|)
 * 
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;
import java.util.TreeMap;

public class FordFulkerson {

	static Scanner in;
	
	static int[][] cap;
	static int[][] flow;
	
	static boolean[] vis;
	
	static int n, m, s, t;
	
	public static void main(String[] args) throws FileNotFoundException {
		in = new Scanner(new File("Maximum Flow.txt"));
		n = in.nextInt();
		m = in.nextInt();
		cap = new int[n][n];
		TreeMap<String, Integer> val = new TreeMap<>();
		String from, to;
		int w, dfrom, dto;
		int idx = 0;
		while(m-- > 0) { // Building the initial Graph
			from = in.next();
			to = in.next();
			w = in.nextInt();
			if(val.containsKey(from)) dfrom = val.get(from);
			else {
				dfrom = idx++;
				if(from.charAt(0) == 's') s = dfrom;
				val.put(from, dfrom);
			}
			if(val.containsKey(to)) dto = val.get(to);
			else {
				dto = idx++;
				if(to.charAt(0) == 't') t = dto;
				val.put(to, dto);
			}
			cap[dfrom][dto] = w;
		}
		System.out.println("Maximum Flow from s to t = " + maxFlow());
	}
	
	static int maxFlow() {
		int mxf = 0;
		vis = new boolean[n];
		flow = new int[n][n];
		while(true) {
			Arrays.fill(vis, false);
			int f = dfs(s, t, Integer.MAX_VALUE);
			if(f == 0) break;
			mxf += f;
		}
		return mxf;
	}
	
	static int dfs(int s, int t, int f) {
		if(vis[s]) return 0;
		if(s == t) return f;
		vis[s] = true;
		for(int i = 0 ; i < n ; ++i)
			if(cap[s][i] - flow[s][i] > 0) {
				int temp = dfs(i, t, Math.min(f, cap[s][i] - flow[s][i]));
				if(temp > 0) {
					flow[s][i] += temp;
					flow[i][s] -= temp;
					return temp;
				}
			}
		return 0;
	}
	
}
