/*
 * Copyright (c) 2008, SQL Power Group Inc.
 *
 * This file is part of SQL Power Library.
 *
 * SQL Power Library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * SQL Power Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */

package ca.sqlpower.graph;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;

/**
 * Class for performing a breadth-first search of a graph starting
 * from a given node.  Includes a callback (listener) mechanism for
 * clients to perform some custom action at each node along the way.
 * 
 * @param V the vertex type of the graph.  Doesn't really matter to
 * the algorithm implemented here, but it helps with type safety in
 * the listener.
 * @param E The edge type of the graph.  Doesn't really matter to
 * the algorithm implemented here, but it helps with type safety in
 * the listener.
 */
public class BreadthFirstSearch<V, E> {
    
    /**
     * The algorithm uses three states for each node, which we think
     * of as three colours.
     */
    private enum Colour {
        /**
         * The undiscovered state.
         */
        WHITE,
        
        /**
         * The discovered but not finished state.
         */
        GRAY,
        
        /**
         * The discovered and finished state.
         */
        BLACK
    }

    /**
     * The listeners who want to be notified of various aspects of the
     * search while it is in progress.
     */
    private final List<BreadthFirstSearchListener<V>> searchListeners =
        new ArrayList<BreadthFirstSearchListener<V>>();
    
    /**
     * A comparator used to order the adjacent nodes, ignored if null.
     */
    private Comparator<V> comparator;
    
    public BreadthFirstSearch() {
    }
    
    /**
     * Performs a breadth-first search of the given graph, starting
     * with the given node.  This algorithm is described in "Introduction
     * to Algorithms" by Cormen et al, Chapter 23.
     * 
     * @param model
     * @param startingNode
     * @return the list of nodes discovered, in the order they were discovered
     */
    public List<V> performSearch(GraphModel<V, E> model, V startingNode) {
        List<V> discoveredNodes = new ArrayList<V>();
        
        Map<V, Colour> colour = new HashMap<V, Colour>();
        Map<V, Integer> depth = new HashMap<V, Integer>();
        Map<V, V> predecessor = new HashMap<V, V>();
        
        for (V u : model.getNodes()) {
            colour.put(u, Colour.WHITE);
            depth.put(u, Integer.MAX_VALUE);
            predecessor.put(u, null);
        }
        
        colour.put(startingNode, Colour.GRAY);
        depth.put(startingNode, 0);
        predecessor.put(startingNode, null);
        fireNodeDiscovered(startingNode);
        discoveredNodes.add(startingNode);
        
        Queue<V> queue = new LinkedList<V>();
        queue.add(startingNode);
        while (!queue.isEmpty()) {
            V u = queue.element();
            Collection<V> adjacentNodes = model.getAdjacentNodes(u);
            if (comparator != null) {
            	adjacentNodes = new ArrayList<V>(adjacentNodes);
            	Collections.sort((List<V>) adjacentNodes, comparator);
            }
			for (V v : adjacentNodes) {
                if (colour.get(v) == Colour.WHITE) {
                    colour.put(v, Colour.GRAY);
                    depth.put(v, depth.get(u) + 1);
                    predecessor.put(v, u);
                    queue.add(v);
                    fireNodeDiscovered(v);
                    discoveredNodes.add(v);
                }
            }
            queue.remove();
            colour.put(u, Colour.BLACK);
        }
        
        return discoveredNodes;
    }
    
    /**
     * Notifies all search listeners that the given node was just discovered.
     */
    private void fireNodeDiscovered(V node) {
        for (int i = searchListeners.size()-1; i >= 0; i--) {
            BreadthFirstSearchListener<V> l = searchListeners.get(i);
            l.nodeDiscovered(node);
        }
    }
    
    /**
     * Adds the given listener to the list of clients interested in events
     * that occur during the breadth first search.
     * 
     * @param l The listener to add.  Must not be null.
     */
    public void addBreadthFirstSearchListener(BreadthFirstSearchListener<V> l) {
        if (l == null) throw new NullPointerException("Null listeners not allowed");
        searchListeners.add(l);
    }

    /**
     * Removes the given listener from this search object's listener list.
     * 
     * @param l The listener to remove.  If not present in the listener
     * list, the call to this method has no effect.
     */
    public void removeBreadthFirstSearchListener(BreadthFirstSearchListener<V> l) {
        searchListeners.remove(l);
    }

    /**
     * Returns the comparator used to order the adjacent nodes.
     */
	public Comparator<V> getComparator() {
		return comparator;
	}

	/**
	 * Sets a custom comparator to order the adjacent nodes. Setting a null
	 * comparator makes it not use one. 
	 */
	public void setComparator(Comparator<V> comparator) {
		this.comparator = comparator;
	}
}
