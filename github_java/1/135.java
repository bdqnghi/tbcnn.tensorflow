package Crack6.Graphs;

import com.sun.org.apache.xml.internal.security.algorithms.implementations.IntegrityHmac;

import java.util.*;

public class BFS {

    public boolean withGraph(Graph graph, int val) {

        for(Node<Integer> node:graph.nodes) {
            Queue<Node<Integer>> queue = new LinkedList<>();
            Set<Node> set = new HashSet<>();
            queue.add(node);
            while(!queue.isEmpty()) {
                Node<Integer> parent = queue.remove();
                set.add(parent);
                if(parent.value.equals(val)) {
                    return true;
                }
                for(Node<Integer> temp:parent.children) {
                    if(!set.contains(temp)) {
                        queue.add(temp);
                    }

                }
            }
        }
        return false;
    }

    public boolean withAdjacencyList(List<ArrayList<Integer>> graph, int val, int dest) {
        System.out.println("BFS with adjacency List");
        Set<Integer> set = new HashSet<>();
        Queue<Integer> queue = new LinkedList<>();
        int size = graph.size();
        if (val >= size  || dest >=graph.size()) {
            return false;
        }

        queue.add(val);
        set.add(val);
        while (!queue.isEmpty()) {
            int temp = queue.remove();
            System.out.println(temp);
            if (temp == dest) {
                return true;
            }
            List<Integer> children = graph.get(temp);
            for (int i : children) {
                if (!set.contains(i)) {
                    queue.add(i);
                }
            }
        }

        return true;
    }
    public boolean withAdjacencyMatrix(int[][] graph, int val, int dest) {
        System.out.println("BFS with adjacency Matrix");
        Set<Integer> set = new HashSet<>();
        Queue<Integer> queue = new LinkedList<>();
        int size = graph.length;
        if (val >= size || dest >=graph.length) {
            return false;
        }

        queue.add(val);
        set.add(val);
        while(!queue.isEmpty()) {
            int temp = queue.remove();
            System.out.println(temp);
            if (temp == dest) {
                return true;
            }
            for(int i = 0;i<graph[temp].length;i++) {
                int kid = graph[temp][i];
                if(kid != 0) {
                    if(!set.contains(i)) {
                        set.add(i);
                        queue.add(i);
                    }
                }
            }
        }

        return false;

    }
}
