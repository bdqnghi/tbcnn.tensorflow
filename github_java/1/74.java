package src;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;

import java.util.Scanner;
import java.util.Set;

public class breadthfirstsearch {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		Scanner scan = new Scanner(System.in);
		int N = scan.nextInt();
		
		// int M = scan.nextInt();

		int[][] edges = new int[N - 1][2];

		for (int i = 0; i < N - 1; i++) {

			edges[i][0] = scan.nextInt();
			edges[i][1] = scan.nextInt();

		}
		int x=scan.nextInt();

		graph g = new graph(N, edges);
		BFS(g, 1,x);
	}

	public static void BFS(graph g, int s,int x) {

		Set<Integer> visited = new HashSet<Integer>();
		LinkedList<Integer> level = new LinkedList<Integer>();

		visited.add(s);
		level.add(s);

		while (level.size() != 0) {

			s = level.poll();

			ArrayList<Integer> adjArrayList = g.getMap().get(s);
		
			Iterator<Integer> itr = adjArrayList.listIterator();
			while (itr.hasNext()) {
				int n = itr.next();

				if (!visited.contains(n)) {
					visited.add(n);

					level.add(n);

				}

			}
		}
	}

}

