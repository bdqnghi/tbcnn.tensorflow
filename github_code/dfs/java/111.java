package npuzzle;

import search.*;

public class nPuzzle {
    public static void main(String[] args) {

        System.out.println("---------------------nPuzzle--------------------------");
        System.out.println();

        Tiles initialConfiguration = new Tiles(new int[][] {
                { 7, 4, 2 },
                { 8, 1, 3 },
                { 5, 0, 6 }
        });

        NodeFunction aStarFunction = new AStarFunction(new MisplacedTilesHeuristicFunction());
        Frontier bestFirstFrontier = new BestFirstFrontier(aStarFunction);
        generateSearch(initialConfiguration, "A* TREE SEARCH", bestFirstFrontier, new TreeSearch(bestFirstFrontier), new TilesGoalTest());

        bestFirstFrontier = new BestFirstFrontier(aStarFunction);
        generateSearch(initialConfiguration, "A* GRAPH SEARCH", bestFirstFrontier, new GraphSearch(bestFirstFrontier), new TilesGoalTest());

//      Here I initialize frontiers and generate searches
//        Frontier breadthFirstFrontier = new BreadthFirstFrontier();
//        generateSearch(initialConfiguration, "Breadth First TREE Search", breadthFirstFrontier, new TreeSearch(breadthFirstFrontier), new TilesGoalTest());

//        breadthFirstFrontier = new BreadthFirstFrontier();
//        generateSearch(initialConfiguration, "Breadth First GRAPH Search", breadthFirstFrontier, new GraphSearch(breadthFirstFrontier), new TilesGoalTest());

//        Frontier depthFirstFrontier = new DepthFirstFrontier();
//        generateSearch(initialConfiguration, "Depth First GRAPH Search", depthFirstFrontier, new GraphSearch(depthFirstFrontier), new TilesGoalTest());

//        The depth first tree search runs infinitely and does not find a solution
//        depthFirstFrontier = new DepthFirstFrontier();
//        generateSearch(initialConfiguration, "Depth First TREE Search", depthFirstFrontier, new TreeSearch(depthFirstFrontier), new TilesGoalTest());
    }


    /**
     * Utility function for generating searches, finding solutions and printing them
     * @param initialConfiguration Initial state of the nPuzzle
     * @param title String for printing the title
     * @param frontier Breadth first or depth first search frontier
     * @param search Tree search or Graph search
     * @param goalTest am I at the goal?
     */
    private static void generateSearch(Tiles initialConfiguration, String title, Frontier frontier, Search search, GoalTest goalTest) {
        System.out.println("------------------" + title + "----------------------");
        System.out.println();

        Node solution = search.findSolution(new Node(null, null, initialConfiguration, 0), goalTest);
        new NPuzzlePrinting().printSolution(solution);
        System.out.println("Total number of nodes: " + search.numberOfNodes());
        System.out.println("Maximum number of nodes on the frontier: " + frontier.max());
        System.out.println();
    }
}
