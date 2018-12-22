
package algorithms;

import java.util.Hashtable;
import java.util.LinkedList;
import java.util.Queue;


import datastructures.adt.Graph;
import callbacks.BreadthFirstSearchCallback;
import exception.GraphException;


/*
 * Single-source shortest paths. Given a graph and a source vertex s, is
 * there a path to a target vertex v? And if so, what is the shortest path?
 */
public class BreadthFirstSearch<T>
{
    private Graph<T> graph;
    private T source;
    private Hashtable<T, T> parent;


    public BreadthFirstSearch(Graph<T> graph,
                              T source,
                              BreadthFirstSearchCallback<T> callback)
    {
        this.graph = graph;
        this.source = source;
        parent = new Hashtable<T, T>();

        bfs(callback);
    }

    public Iterable<T> pathTo(T v)
    {
        T u = parent.get(v);

        if (u == null) {
            return null;
        }

        LinkedList<T> stack = new LinkedList<T>();
        stack.add(0, v);

        while (u != source) {
            stack.add(0, u);
            u = parent.get(u);
        }

        stack.add(0, source);

        return stack;
    }

    private void bfs(BreadthFirstSearchCallback<T> callback)
    {
        Hashtable<T, Boolean> discovered = new Hashtable<T, Boolean>();
        Queue<T> queue = new LinkedList<T>();

        discovered.put(source, true);
        queue.add(source);

        while (!queue.isEmpty()) {
            T u = queue.remove();
            callback.call(graph, u);  // visit
            for (T v : graph.adjacent(u)) {
                Boolean discoveredFlag = discovered.get(v);
                if (discoveredFlag == null || !discoveredFlag) {
                    parent.put(v, u);
                    discovered.put(v, true);
                    queue.add(v);
                }
            }
        }
    }
}
