package org.IhorLitvinov.graph.search;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.function.BiConsumer;
import java.util.function.Function;
import java.util.function.Predicate;

/**
 * Breadth-first search (BFS) is an algorithm for traversing
 * or searching tree or graph data structures.
 * It starts at the tree root
 * (or some arbitrary node of a graph,
 * sometimes referred to as a 'search key')
 * and explores the neighbor nodes first,
 * before moving to the next level neighbors.
 */
public class BreadthFirstSearch {
    /**
     * @param markFunction      used to mark node as visited,
     *                          mark distance from start node or
     *                          mark sequence number of the connected component.
     *                          First parameter is current nodeId,
     *                          second is previous nodeId
     *                          (used for path marking, etc).
     *                          Should work fine when
     *                          previous node is current (initial case)
     * @param isVisited      used to check if current node was visited.
     *                          Connected to markFunction
     * @param isDestinationNode used to check if current node is destination node
     * @param neighborsFunction used to get neighbors of current node.
     *                          Argument is nodeId
     * @return true if destination node has been reached
     */
    public boolean search(
            Integer startNodeId,
            BiConsumer<Integer, Integer> markFunction,
            Predicate<Integer> isVisited,
            Predicate<Integer> isDestinationNode,
            Function<Integer, List<Integer>> neighborsFunction
    ) {
        markFunction.accept(startNodeId, startNodeId);

        if (isDestinationNode.test(startNodeId)) {
            return true;
        }

        Queue<Integer> nodeQueue = new LinkedList<>();
        nodeQueue.add(startNodeId);

        while (!nodeQueue.isEmpty()) {
            Integer nodeId = nodeQueue.poll();
            List<Integer> neighbors = neighborsFunction.apply(nodeId);

            for (Integer neighborNodeId : neighbors) {
                if (!isVisited.test(neighborNodeId)) {
                    markFunction.accept(neighborNodeId, nodeId);
                    if (isDestinationNode.test(neighborNodeId)) {
                        return true;
                    }
                    nodeQueue.add(neighborNodeId);
                }
            }
        }
        return false;
    }
}
