package pl.edu.mimuw.wikiontology.kp347208.wikiontology;

import java.util.*;
import java.util.function.Predicate;

/**
 * Class able to do a breadth-first-search on an entities graph.
 *
 * @author Krzysztof Pszeniczny
 */
public class GraphSearch {
    private final HashMap<String, Entity> map = new HashMap<>();

    /**
     * Default constructor
     *
     * @param entities A collection of entities representing the vertices of the graph
     */
    public GraphSearch(Collection<Entity> entities) {
        entities.forEach(x -> map.put(x.getTitle().toLowerCase(), x));
    }

    /**
     * Performs a breadth-first-search on the given graph
     * <p>
     * Calls {@link pl.edu.mimuw.wikiontology.kp347208.wikiontology.GraphSearch#getPath(String, String, java.util.function.Predicate)}
     * with predicate always satisfied.
     */
    public ArrayList<String> getPath(String from, String to) {
        return getPath(from, to, whatever -> true);
    }

    /**
     * Performs a breadth-first-search on the given graph
     *
     * @param from Name of the starting vertex (not-null)
     * @param to   Name of the target vertex (not-null)
     * @param pred Additional predicate that must be satisfied by every vertex on the path (not-null)
     * @return A list of vertices forming the path from the source (incl.) to the target (incl.).
     * If no path was found, returns null.
     */
    public ArrayList<String> getPath(String from, String to, Predicate<Entity> pred) {
        Objects.requireNonNull(from, "Source vertex must not be null");
        Objects.requireNonNull(to, "Target vertex must not be null");
        Objects.requireNonNull(pred, "Predicate must not be null");

        HashMap<String, String> parent = new HashMap<>();
        Queue<String> queue = new ArrayDeque<>();

        if (!map.containsKey(from.toLowerCase()) ||
                !pred.test(map.get(from.toLowerCase())))
            return null;

        parent.put(from.toLowerCase(), null);
        queue.add(from);

        while (!queue.isEmpty()) {
            final String node = queue.poll();
            map.get(node.toLowerCase()).linksStream()
                    .filter(x -> map.containsKey(x.toLowerCase()) // vertex is in graph
                            && !parent.containsKey(x.toLowerCase()) // but was not already visited
                            && pred.test(map.get(x.toLowerCase()))) // and it satisfies the predicate
                    .forEach(x -> {
                        parent.put(x.toLowerCase(), node);
                        queue.add(x);
                    });
        }

        if (!parent.containsKey(to.toLowerCase()))
            return null;

        ArrayDeque<String> result = new ArrayDeque<>();
        for (String name = to; name != null; name = parent.get(name.toLowerCase()))
            result.addFirst(name);

        return new ArrayList<>(result);
    }
}
