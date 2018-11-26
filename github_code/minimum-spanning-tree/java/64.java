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
        // Write your code here
    }
}


/**
### Problem
minimum-spanning-tree
https://www.lintcode.com/problem/minimum-spanning-tree/description

### Description
Given a list of  Connections, which is the Connection class (the city name at both ends of the edge and a cost between them), find some edges, connect all the cities and spend the least amount.
Return the connects if can connect all the cities, otherwise return empty list.


### Notice
Return the connections sorted by the cost, or sorted city1 name if their cost is same, or sorted city2 if their city1 name is also same. 

### Example
Gievn the connections = `["Acity","Bcity",1], ["Acity","Ccity",2], ["Bcity","Ccity",3]`

Return `["Acity","Bcity",1], ["Acity","Ccity",2]`
*/