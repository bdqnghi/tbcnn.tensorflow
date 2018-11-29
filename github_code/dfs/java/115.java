/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.graph.algorithms;

import java.util.Stack;
import org.graph.directed.DefaultDirectedGraph;
import org.graph.directed.RootedTree;

/**
 *
 * @author rinke
 */
public final class DepthFirstSearch {

    private DepthFirstSearch() {
    }
    
    
    
    /**
     * Methode zum Erzeugen eines Tiefensuchbaums.
     *
     * @param root      Wurzel des Suchbaums
     * @return          {@link RootedTree} fuer den Knoten <code>root</code>
     */
    public static <V> RootedTree<V> computeDepthSearchTree(
                                            DefaultDirectedGraph<V> graph, V root) {
        RootedTree<V> tree = new RootedTree<V>(root);

        Stack<V> candidates = new Stack<V>();
        candidates.push(root);

        while (!candidates.isEmpty()) {
            V k = candidates.pop();
            for (V n : graph.getSuccessors(k)) {
                if (!tree.containsVertex(n)) {
                    candidates.push(n);
                    tree.addChild(n, k);
                }
            }
        }
        return tree;
    }
    
}
