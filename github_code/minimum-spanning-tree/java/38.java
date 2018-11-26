/*
@Copyright:LintCode
@Author:   vadxin
@Problem:  http://www.lintcode.com/problem/minimum-spanning-tree
@Language: Java
@Datetime: 17-02-24 09:48
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
class Order implements Comparator<Connection> {
    public int compare(Connection a, Connection b) {
        if (a.cost != b.cost) {
            return a.cost - b.cost;
        }
        if (!a.city1.equals(b.city1)) {
            return a.city1.compareTo(b.city1);
        }
        return a.city2.compareTo(b.city2);
    }
}
public class Solution {
    /**
     * @param connections given a list of connections include two cities and cost
     * @return a list of connections from results
     */
    public List<Connection> lowestCost(List<Connection> connections) {
        // Write your code here
        List<Connection> mst = new ArrayList<Connection>();
        if (connections == null || connections.size() == 0) {
            return mst;
        }
        Collections.sort(connections, new Order());
        Map<String, Integer> map = new HashMap<String, Integer>();
        int n = 0;
        for (Connection connection: connections) {
            if (!map.containsKey(connection.city1)) {
                map.put(connection.city1, ++n);
            }
            if (!map.containsKey(connection.city2)) {
                map.put(connection.city2, ++n);
            }
        }
        int[] father = new int[n + 1];
        for (Connection connection: connections) {
            int num1 = map.get(connection.city1);
            int num2 = map.get(connection.city2);
            int root1 = find(num1, father);
            int root2 = find(num2, father);
            if (root1 != root2) {
                mst.add(connection);
                father[root1] = root2;
            }
        }
        if (mst.size() != n - 1) {
            return new ArrayList<Connection>();
        }
        return mst;
    }
    public int find(int num, int[] father) {
        if (father[num] == 0) {
            return num;
        }
        father[num] = find(father[num], father);
        return father[num];
    }
}