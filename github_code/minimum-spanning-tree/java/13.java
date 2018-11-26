package net.shutingg.leetCode;

import java.util.*;

/**
 * http://www.lintcode.com/en/problem/minimum-spanning-tree/
 */
public class MinimumSpanningTree {
    class Connection {
        public String city1, city2;
        public int cost;
        public Connection(String city1, String city2, int cost) {
        this.city1 = city1;
        this.city2 = city2;
        this.cost = cost;
        }
     }
    /**
     * UnionFind - Greedy
     * Sort Connections first to greedily get minimum connection
     * Due to requirement, can only sort by Connection, not cost
     * UnionFind to ensure the graph is connected, and only connect when it is needed to
     *
     * String compare is slow. Map String to Int is faster.
     *
     * @param connections given a list of connections include two cities and cost
     * @return a list of connections from results
     */
    public List<Connection> lowestCost(List<Connection> connections) {
        List<Connection> res = new ArrayList<>();
        if (connections == null || connections.size() == 0) {
            return res;
        }

        Collections.sort(connections, (a, b) -> {
            if (a.cost != b.cost) {
                return a.cost - b.cost;
            }
            if (!a.city1.equals(b.city1)) {
                return a.city1.compareTo(b.city1);
            }
            return a.city2.compareTo(b.city2);
        });

        UnionFind uf = new UnionFind();
        Set<String> cities = new HashSet<>();
        for (Connection conn : connections) {
            if (uf.find(conn.city1).equals(uf.find(conn.city2))) {
                continue;
            }
            cities.add(conn.city1);
            cities.add(conn.city2);
            uf.union(conn.city1, conn.city2);
            res.add(conn);
        }
        if (cities.size() - 1 == res.size()) {
            return res;
        }

        return new ArrayList<>();
    }

    class UnionFind {
        Map<String, String> father;

        UnionFind () {
            father = new HashMap<>();
        }

        String find(String x) {
            if (father.get(x) == null) {
                father.put(x, x);
                return x;
            }
            if (x.equals(father.get(x))) {
                return x;
            }
            String root = find(father.get(x));
            father.put(x, root);
            return root;
        }

        void union(String a, String b) {
            String rootA = find(a);
            String rootB = find(b);
            if (a.equals(b)) {
                return;
            }
            father.put(rootA, rootB);
        }
    }
}
