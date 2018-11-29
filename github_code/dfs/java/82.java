package rmugattarov.crack;

import lombok.Data;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;

public class DepthFirstSearch {
    public static void main(String[] args) {
        DepthFirstSearch.Node root = new DepthFirstSearch.Node("root");
        DepthFirstSearch.Node l1_1 = new DepthFirstSearch.Node("l1_1");
        DepthFirstSearch.Node l1_2 = new DepthFirstSearch.Node("l1_2");
        DepthFirstSearch.Node l2_1 = new DepthFirstSearch.Node("l2_1");
        DepthFirstSearch.Node l2_2 = new DepthFirstSearch.Node("l2_2");
        root.children.add(l1_1);
        root.children.add(l1_2);
        l1_1.children.add(l2_1);
        l1_1.children.add(l2_2);

        ArrayDeque<DepthFirstSearch.Node> queue = new ArrayDeque<>();
        queue.add(root);
        System.out.println(contains(root, l2_2));
    }

    @Data
    private static class Node {
        private String name;
        private List<DepthFirstSearch.Node> children = new ArrayList<>();

        public Node(String name) {
            this.name = name;
        }
    }

    private static boolean contains(DepthFirstSearch.Node root, DepthFirstSearch.Node target) {
        System.out.println("Root : " + root);
        if (root == target) {
            return true;
        }
        for (Node n : root.children) {
            if (contains(n, target)) {
                return true;
            }
        }

        return false;
    }
}
