// Minimum Spanning Tree
// http://www.lintcode.com/en/problem/minimum-spanning-tree/

/*
Given a list of Connections, which is the Connection class (the city name at both ends of the edge and a cost between them), find some edges, connect all the cities and spend the least amount.
Return the connects if can connect all the cities, otherwise return empty list.

 Notice

Return the connections sorted by the cost, or sorted city1 name if their cost is same, or sorted city2 if their city1 name is also same.

Have you met this question in a real interview? Yes
Example
Gievn the connections = ["Acity","Bcity",1], ["Acity","Ccity",2], ["Bcity","Ccity",3]

Return ["Acity","Bcity",1], ["Acity","Ccity",2]
*/

/**
 * Definition for a Connection.
 * public class Connection {
 *   public String city1, city2;
 *   public int cost;
 *   public Connection(String city1, String city2, int cost) {
 *       this.city1 = city1;
 *       this.city2 = city2;
 *       this.cost = cost;
 *   }
 * }
 */
public class Solution {
	/**
	 * @param connections given a list of connections include two cities and cost
	 * @return a list of connections from results
	 */
	public List<Connection> lowestCost(List<Connection> connections) {
		if (connections == null || connections.size() <= 1) {
			return connections;
		}
		Collections.sort(connections, new Comp());
		int n = 0;
		HashMap<String, Integer> A = new HashMap<>();
		for (Connection i : connections) {
			if (!A.containsKey(i.city1)) {
				A.put(i.city1, n++);
			}
			if (!A.containsKey(i.city2)) {
				A.put(i.city2, n++);
			}
		}
		int[] B = new int[n];
		for (int i = 0; i < n; ++i) {
			B[i] = i;
		}
		List<Connection> result = new LinkedList<Connection>();
		for (Connection i : connections) {
			int id1 = A.get(i.city1), id2 = A.get(i.city2), root1 = f(B, id1), root2 = f(B, id2);
			if (root1 != root2) {
				--n;
				B[root1] = root2;
				result.add(i);
			}
		}
		return n == 1 ? result : new LinkedList<Connection>();
	}
	private class Comp implements Comparator<Connection> {
		public int compare(Connection a, Connection b) {
			if (a.cost == b.cost) {
				if (a.city1.equals(b.city1)) {
					return a.city2.compareTo(b.city2);
				}
				return a.city1.compareTo(b.city1);
			}
			return a.cost - b.cost;
		}
	};
	private int f(int[] A, int id) {
		if (A[id] == id) {
			return id;
		}
		int result = f(A, A[id]);
		A[id] = result;
		return result;
	}
}