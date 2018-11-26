package amazon;

import java.util.*;

/**
 * Created by billjyc on 2016/10/4.
 */
public class MinimumSpanningTree {

    public ArrayList<Connection> getLowCost(ArrayList<Connection> connections) {
        // write your code here
        if(connections == null || connections.isEmpty()) {
            return null;
        }

        //Set<String> connectedSet = new HashSet<>();
        Set<String> set = new HashSet<>();
        ArrayList<Connection> res = new ArrayList<>();

        Comparator<Connection> costCmp = (c1, c2) -> (c1.cost - c2.cost);
        Comparator<Connection> nameCmp = new Comparator<Connection>() {
            @Override
            public int compare(Connection o1, Connection o2) {
                if(o1.node1.equals(o2.node1)) {
                    return o1.node2.compareTo(o2.node2);
                }
                return o1.node1.compareTo(o2.node1);
            }
        };

        for(Connection conn : connections) {
            set.add(conn.node1);
            set.add(conn.node2);
        }

        UnionFind uf = new UnionFind(set);
        Collections.sort(connections, costCmp);
        for(Connection conn : connections) {
            if(uf.union(conn.node1, conn.node2)) {
                res.add(conn);
            }

            if(res.size() == set.size() - 1) {
                break;
            }
        }

        if(res.size() != set.size() - 1) {
            return null;
        }

        Collections.sort(res, nameCmp);
        return res;
    }

    class UnionFind {
        Map<String, String> father;
        //ArrayList<Connection> list;

        public UnionFind(Set<String> set) {
            father = new HashMap<>();
            //list = new ArrayList<>();
            for(String s : set) {
                father.put(s, s);
            }
        }

        public String find(String s) {
            String pa = father.get(s);
            while(!pa.equals(father.get(pa))) {
                pa = father.get(pa);
            }
            return pa;
        }

        public boolean union(String a, String b) {
            String fa_a = find(a);
            String fa_b = find(b);
            if(!fa_a.equals(fa_b)) {
                father.put(fa_a, fa_b);
                return true;
            }
            return false;
        }
    }

    public static void main(String[] args) {
        MinimumSpanningTree solution = new MinimumSpanningTree();

        // test case 1
        ArrayList<Connection> connections = new ArrayList<>();
        connections.add(new Connection("A", "B", 1));
        connections.add(new Connection("B", "C", 3));
        connections.add(new Connection("B", "E", 2));
        connections.add(new Connection("C", "E", 7));
        connections.add(new Connection("E", "A", 6));
        connections.add(new Connection("D", "E", 5));
        ArrayList<Connection> res = solution.getLowCost(connections);
        System.out.println("test case 1: ");
        for (Connection c : res){
            System.out.println(c.node1 + " -> " + c.node2 + " " + c.cost);
        }

        // test case 2
        connections = new ArrayList<>();
        connections.add(new Connection("A", "B", 2));
        connections.add(new Connection("B", "C", 2));
        connections.add(new Connection("B", "D", 2));
        connections.add(new Connection("C", "D", 2));
        connections.add(new Connection("D", "A", 2));
        connections.add(new Connection("A", "C", 2));
        res = solution.getLowCost(connections);
        System.out.println("test case 2: ");
        for (Connection c : res){
            System.out.println(c.node1 + " -> " + c.node2 + " " + c.cost);
        }

        // test case 3
        connections = new ArrayList<>();
        connections.add(new Connection("A", "B", 2));
        connections.add(new Connection("B", "C", 2));
        connections.add(new Connection("C", "D", 2));
        connections.add(new Connection("D", "E", 2));
        connections.add(new Connection("E", "F", 2));
        connections.add(new Connection("G", "F", 1));
        connections.add(new Connection("G", "E", 1));
        connections.add(new Connection("G", "E", 1));
        connections.add(new Connection("G", "D", 1));
        connections.add(new Connection("G", "C", 1));
        connections.add(new Connection("G", "B", 1));
        connections.add(new Connection("G", "A", 1));
        connections.add(new Connection("A", "F", 2));
        res = solution.getLowCost(connections);
        System.out.println("test case 3: ");
        for (Connection c : res){
            System.out.println(c.node1 + " -> " + c.node2 + " " + c.cost);
        }

        // test case 4
        res = solution.getLowCost(null);
        if(res == null) {
            System.out.println("test case 4 correct!");
        } else {
            System.out.println("test case 4 fail!");
        }

        // test case 5
        res = solution.getLowCost(new ArrayList<Connection>());
        if(res == null) {
            System.out.println("test case 5 correct!");
        } else {
            System.out.println("test case 5 fail!");
        }

        // test case 6
        connections = new ArrayList<>();
        connections.add(new Connection("A", "B", 1));
        connections.add(new Connection("A", "C", 9));
        connections.add(new Connection("A", "D", 4));
        connections.add(new Connection("A", "E", 6));
        connections.add(new Connection("B", "C", 1));
        connections.add(new Connection("B", "D", 2));
        connections.add(new Connection("B", "E", 8));
        connections.add(new Connection("C", "D", 5));
        connections.add(new Connection("D", "C", 7));
        connections.add(new Connection("C", "E", 2));
        connections.add(new Connection("D", "E", 3));
        connections.add(new Connection("D", "F", 97));

        res = solution.getLowCost(connections);
        System.out.println("test case 6: ");
        for (Connection c : res){
            System.out.println(c.node1 + " -> " + c.node2 + " " + c.cost);
        }

        // test case 7
        connections = new ArrayList<>();
        connections.add(new Connection("A", "B", 1));
        connections.add(new Connection("A", "C", 2));
        connections.add(new Connection("C", "B", 7));
        connections.add(new Connection("D", "E", 1));
        connections.add(new Connection("F", "E", 8));
        res = solution.getLowCost(connections);
        if(res == null) {
            System.out.println("test case 7 correct!");
        } else {
            System.out.println("test case 7 fail!");
        }

        // test case 8
        connections = new ArrayList<>();
        connections.add(new Connection("C", "E", 1));
        connections.add(new Connection("F", "B", 2));
        connections.add(new Connection("C", "A", 3));
        connections.add(new Connection("C", "D", 4));
        connections.add(new Connection("D", "E", 5));
        connections.add(new Connection("G", "E", 6));
        connections.add(new Connection("D" ,"I", 7));
        connections.add(new Connection("I" ,"E", 8));
        connections.add(new Connection("A", "K", 9));
        connections.add(new Connection("A", "B", 10));
        connections.add(new Connection("A", "H", 11));
        connections.add(new Connection("K", "J", 12));
        connections.add(new Connection("I", "G", 13));
        connections.add(new Connection("F", "G", 14));
        connections.add(new Connection("A", "J", 15));
        connections.add(new Connection("J", "B", 16));
        connections.add(new Connection("E", "H", 17));
        res = solution.getLowCost(connections);
        System.out.println("test case 8: ");
        for (Connection c : res){
            System.out.println(c.node1 + " -> " + c.node2 + " " + c.cost);
        }
    }
}

class Connection {
    String node1;
    String node2;
    int cost;
    Connection (String node1, String node2, int cost) {
        this.node1 = node1;
        this.node2 = node2;
        this.cost = cost;
    }
}
