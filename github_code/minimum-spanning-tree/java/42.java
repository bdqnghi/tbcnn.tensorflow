/*
@Copyright:LintCode
@Author:   yun16
@Problem:  http://www.lintcode.com/problem/minimum-spanning-tree
@Language: Java
@Datetime: 17-02-24 16:57
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
    //Kruskal + Union find
    public List<Connection> lowestCost(List<Connection> connections) {
        // Write your code here
        Collections.sort(connections, new Comparator<Connection>() {
            public int compare(Connection a, Connection b) {
                if (a.cost != b.cost) {
                    return a.cost - b.cost;
                } else if (!a.city1.equals(b.city1)) {
                    return a.city1.compareTo(b.city1);
                } else {
                    return a.city2.compareTo(b.city2);
                }
            }
        });
        
        /*
        HashMap<String, Integer> city = new HashMap<String, Integer>();
        int n = 1;
        for (Connection connection : connections) {
            if (!city.containsKey(connection.city1)) {
                city.put(connection.city1, n);
                n++;
            }
            if (!city.containsKey(connection.city2)) {
                city.put(connection.city2, n);
                n++;
            }
        }
        int[] father = new int[n];
        */
        
        HashMap<String, String> father = new HashMap<String, String>();
        //int n = 0;
        List<Connection> result = new ArrayList<Connection>();
        
        for (Connection connection : connections) {
            String root1 = connection.city1;
            String root2 = connection.city2;
            if (!father.containsKey(connection.city1)) {
                father.put(connection.city1, root1);
            } else {
                root1 = find(father, connection.city1);
            }
            if (!father.containsKey(connection.city2)) {
                father.put(connection.city2, root2);
            } else {
                root2 = find(father, connection.city2);
            }
            if (!root1.equals(root2)) {
                father.put(father.get(root1), root2);
                result.add(connection);
            }
        }
        if (result.size() != father.size() - 1) {
            return new ArrayList<Connection>();
        } else {
            return result;
        }
    }
    
    private String find(HashMap<String, String> father, String curt) {
        if (father.get(curt).equals(curt)) {
            return curt;
        }
        //father.put(father.get(curt), find(father, father.get(curt)));
        String fa = find(father, father.get(curt));
        father.put(father.get(curt), fa);
        return fa;
    }
    /*
    private int find(int[] father, int curt) {
        if (father[curt] == 0) {
            return curt;
        }
        father[curt] = find(father, father[curt]);
        return father[curt];
    }*/
    
}