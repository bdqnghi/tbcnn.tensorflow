/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.graph.algorithms;


import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;
import org.graph.directed.DirectedGraph;
import org.graph.directed.RootedTree;
import org.graph.undirected.UnDirected;
import org.graph.undirected.Tree;

/**
 *
 * @author rinke
 */
public final class BreadthFirstSearch {

    private BreadthFirstSearch() {
    }
    
    
    /**
     * Methode zum Erzeugen eines Breitensuchbaums.
     *
     * @param root      Wurzel des Suchbaums
     * @return          {@link RootedTree} fuer den Knoten <code>root</code>
     */
    public static <V> RootedTree<V> computeBreadthSearchTree(
                                            DirectedGraph<V> graph, V root) {
        //Suchbaum, der am Ende zurueckgegeben wird.
        RootedTree<V> tree = new RootedTree<V>(root);

        Queue<V> candidates = new ConcurrentLinkedQueue<V>();
        candidates.offer(root);

        while (!candidates.isEmpty()) {
            V k = candidates.poll();
            for (V n : graph.getSuccessors(k)) {
                if (!tree.containsVertex(n)) {
                    candidates.offer(n);
                    tree.addChild(n, k);
                }
            }
        }
        return tree;
    }

    public static <V> RootedTree<V> computeBreadthSearchTree(
                                            DirectedGraph<V> graph, V root, int K) {
        //Suchbaum, der am Ende zurueckgegeben wird.
        RootedTree<V> tree = new RootedTree<V>(root);

        Queue<V> candidates = new ConcurrentLinkedQueue<V>();
        candidates.offer(root);

        while (!candidates.isEmpty()) {
            V k = candidates.poll();
            for (V n : graph.getSuccessors(k)) {
                if (!tree.containsVertex(n)) {
                    candidates.offer(n);
                    tree.addChild(n, k);
                    if(tree.numberOfVertices()==K)
                        return tree;
                }
            }
        }
        return tree;
    }


    /**
     * Methode zum Erzeugen eines Breitensuchbaums.
     *
     * @param root      Wurzel des Suchbaums
     * @return          {@link RootedTree} fuer den Knoten <code>root</code>
     */
    public static <V> Tree<V> computeBreadthSearchTree(
                                            UnDirected<V> graph, V root) {
        //Suchbaum, der am Ende zurueckgegeben wird.
        Tree<V> tree = new Tree<V>(root);

        Queue<V> candidates = new ConcurrentLinkedQueue<V>();
        candidates.offer(root);

        while (!candidates.isEmpty()) {
            V k = candidates.poll();
            for (V n : graph.getNeighbours(k)) {
                if (!tree.containsVertex(n)) {
                    candidates.offer(n);
                    tree.addConnection(n, k);
                }
            }
        }
        return tree;
    }

}
