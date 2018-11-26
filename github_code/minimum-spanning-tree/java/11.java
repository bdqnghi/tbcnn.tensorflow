package lint.Amazon;

import common.datastructure.Connection;

import java.util.*;

/**
 * Created by xuanlin on 2/21/17.
 * 629
 *
 * http://www.jiuzhang.com/solutions/minimum-spanning-tree/
 */
public class MinimumSpanningTree {
    /**
     * @param connections given a list of connections include two cities and cost
     * @return a list of connections from results
     */
    public List<Connection> lowestCost(List<Connection> connections) {
        //sort connections
        Collections.sort(connections, new Comparator<Connection>() {
            @Override
            public int compare(Connection o1, Connection o2) {
                if (o1.cost != o2.cost) {
                    return o1.cost - o2.cost;
                }
                if (o1.city1.equals(o2.city1)) {
                    return o1.city2.compareTo(o2.city2);
                }
                return o1.city1.compareTo(o2.city1);
            }
        });

        //calculate how many cities we have, we need n-1 edges.
        HashMap<String, Integer> hash = new HashMap<>();
        int n = 0;
        for (Connection connection: connections) {
            if (!hash.containsKey(connection.city1)) {
                hash.put(connection.city1, ++n);
            }
            if (!hash.containsKey(connection.city2)) {
                hash.put(connection.city2, ++n);
            }
        }

        int [] father = new int [n+1];

        List<Connection> rst = new ArrayList<>();
        for (Connection connection: connections) {
            int num1 = hash.get(connection.city1);
            int num2 = hash.get(connection.city2);

            int root1 = find(num1, father);
            int root2 = find(num2, father);

            if (root1 != root2) {
                father[root1] = root2;
                rst.add(connection);
            }

        }

        if (rst.size() !=n-1)
            return new ArrayList<Connection>();
        return rst;
    }



    // union find
    public int find(int num, int[] father) {
        if (father[num] == 0) {
            return num;
        }
        return father[num] = find(father[num], father);
    }


}

/*
题目内容是这样的，给十几个城市供电，连接不同城市的花费不同，让花费最小同时连到所有的边。给出一系列connection类，里面是edge两端的城市名和它们之间的一个cost，找出要你挑一些边，把所有城市连接起来并且总花费最小。不能有环，最后所以城市要连成一个连通块。
不能的话输出空表，最后还要按城市名字排序输出，按照node1来排序,如果一样的话再排node2。
输入:
{"Acity","Bcity",1}
("Acity","Ccity",2}
("Bcity","Ccity",3}
输出：
("Acity","Bcity",1}
("Acity","Ccity",2}


答案： http://www.jiuzhang.com/solutions/minimum-spanning-tree/
 */

