package Examples;


import Graphs.BreadthFirstSearch;
import Graphs.SymbolGraph;
import Graphs.UndirectedGraph;

import java.util.HashMap;

public class SixDegreesKevinBacon {

    private BreadthFirstSearch breadthFirstSearch;
    private SymbolGraph graph;

    public SixDegreesKevinBacon(String pathToFile, String delimiter, String source) {

        graph = new SymbolGraph(pathToFile, delimiter);

        if (!graph.contains(source)) {
            throw new Error("The from is not in the list.");
        }

        UndirectedGraph tempGraph = graph.graph();

        BreadthFirstSearch breadthFirstSearch = new BreadthFirstSearch(tempGraph, graph.index(source));


        HashMap m = new HashMap();
    }


    /**
     * Given the path to the file, returns the degree
     * between Kevin Bacon and the given actor/actress.
     * We recommend using the file provided at
     * http://algs4.cs.princeton.edu/41undirected/movies.txt,
     * otherwise modifications are needed.
     *
     * @param pathToFile, the path to the file
     */
    public SixDegreesKevinBacon(String pathToFile, String delimiter) {
        this(pathToFile, delimiter, "Kevin Bacon");
    }

    /**
     * Returns the degree of separation between the source
     * and the given name.
     *
     * @param name, the name
     */
    public int separation(String name) {
        return breadthFirstSearch.distTo(graph.index(name));
    }

    /**
     * Print the chain from the source to the given name
     *
     * @param name
     */
    public void printChain(String name) {

        if (!graph.contains(name)) {
            System.out.println("The list doesn't contain " + name);
        }

        if (!breadthFirstSearch.hasPathTo(graph.index(name))) {
            System.out.println("No path to " + name);
        }

        if (breadthFirstSearch.hasPathTo(graph.index(name))) {
            for (Integer vertex : breadthFirstSearch.pathTo(graph.index(name))) {
                System.out.println(graph.name(vertex));
            }
        }

    }

}
