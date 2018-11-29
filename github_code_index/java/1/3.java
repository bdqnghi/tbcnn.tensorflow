package com.practice.stanford.graphs;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

public class BFS {

	public static void bfs(int start, Map<Integer, List<Integer>> adjancylist) {

		Set<Integer> vertices = adjancylist.keySet();
		Set<Integer> visited = new HashSet<Integer>();

		Queue<Integer> queue = new LinkedList<>();
		queue.add(start);
		visited.add(start);
		while (!queue.isEmpty()) {

			int v = queue.poll();

			List<Integer> connected = adjancylist.get(v);
			for (Integer w : connected) {

				if (!visited.contains(w)) {
					visited.add(w);
					queue.add(w);
				}

			}

		}

	}

}
