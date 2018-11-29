package algoritms.graph;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Set;

public class BreadthFirstSearch {

    public static boolean hasPath(Node from, Node to) {
        if (from == to) {
            return true;
        }

        Set<Node> visited = new HashSet<>();
        Queue<Node> queue = new LinkedList<>();

        queue.offer(from);

        while (!queue.isEmpty()) {
            Node node = queue.poll();
            if (node == to) {
                return true;
            }
            visited.add(node);
            List<Node> adjacent = node.getAdjacent();
            for (Node n: adjacent) {
                if (!visited.contains(n)) {
                    queue.offer(n);
                }
            }
        }

        return false;
    }
}
