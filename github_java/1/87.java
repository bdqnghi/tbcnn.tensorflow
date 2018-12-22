package edu.wisc.cs.will.stdAIsearch;

import java.util.List;

/**
 * Implements a breath-first search.
 * 
 * @author shavlik
 */
public class BreadthFirstSearch extends SearchStrategy {
    /**
     * Default constructor. Does nothing.
     */
    public BreadthFirstSearch() {
    }

    /**
     * Adds the given node to the end of the open list so that the nearest
     * (oldest) nodes are examined first.
     * 
     * @see edu.wisc.cs.will.stdAIsearch.SearchStrategy#addChildrenToOpenList(edu.wisc.cs.will.stdAIsearch.OpenList,
     *      java.util.List)
     */
    public <T extends SearchNode> void addChildrenToOpenList(OpenList<T> open, List<T> children) {
        for (T node : children) {
            open.addToEndOfOpenList(node); // For breadth-first search, add new nodes to END of list.
        }
    }

    /**
     * Returns "breadth-first search".
     * 
     * @see java.lang.Object#toString()
     */
    public String toString() {
        return "breadth-first search";
    }
}
