package com.geoffslittle.datastructure.generalizedmap;


import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Queue;
import java.util.Set;
import java.util.function.Function;

public class BreadthFirstSearch<E> implements Iterator<E> {

    private final Queue<E> queue;
    // Seen contains both to-be-processed and already-processed darts (not just already-processed)
    private final Set<E> seen;
    private final Function<E, List<E>> neighborGenerator;

    private BreadthFirstSearch(Queue<E> queue, Set<E> seen, Function<E, List<E>> neighborGenerator) {
        this.queue = queue;
        this.seen = seen;
        this.neighborGenerator = neighborGenerator;
    }

    public static <E> BreadthFirstSearch<E> breadthFirstSearch(E source, Function<E, List<E>> neighborGenerator) {
        Queue<E> queue = new LinkedList<>();
        Set<E> seen = new HashSet<>();
        queue.add(source);
        seen.add(source);
        return new BreadthFirstSearch<E>(queue, seen, neighborGenerator);
    }

    @Override
    public boolean hasNext() {
        return !queue.isEmpty();
    }

    @Override
    public E next() {
        if (!hasNext()) {
            // Can't continue if there is no "next"
            throw new NoSuchElementException();
        }
        E current = queue.poll();
        // Get the orbit of the current dart as defined by the given list of alphas
        neighborGenerator.apply(current).stream()
                .filter(neighbor -> !seen.contains(neighbor))
                .forEach(neighbor -> {
                    queue.offer(neighbor);
                    seen.add(neighbor);
                });
        return current;
    }
}
