package com.artificial.pathfinding.algorithms;

public enum Pathfinder {
    ASTAR("A*", new AStar()),
    BEST_FIRST_SEARCH("Best-First-Search", new BestFirstSearch()),
    BREADTH_FIRST_SEARCH("Breadth-First-Search", new BreadthFirstSearch()),
    DIJKSTRA("Dijkstra", new Dijkstra()),
    DEPTH_FIRST_SEARCH("Depth-First-Search", new DepthFirstSearch()),
   // ITERATIVE_DEEPENING("IDA*", new IterativeDeepening()),
    ;
    private final String displayName;
    private final Algorithm algorithm;

    Pathfinder(final String displayName, final Algorithm algorithm) {
        this.displayName = displayName;
        this.algorithm = algorithm;
    }

    public Algorithm getAlgorithm() {
        return algorithm;
    }

    @Override
    public String toString() {
        return displayName;
    }
}
