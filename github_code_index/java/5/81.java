package algoritms.graph;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class DepthFirstSearch {

    private static Set<Node> visited = new HashSet<>();

    public static boolean hasPath(Node from, Node to) {
        if (from == null) {
            return false;
        }

        if (from == to) {
            return true;
        }

        List<Node> adjacent = from.getAdjacent();

        for (Node node: adjacent) {
            if (!visited.contains(node)) {
                 if(hasPath(node, to)) {
                     visited.clear();
                     return true;
                 }
            }
            visited.add(node);
        }

        visited.clear();
        return false;
    }
}
