package tour;

import search.*;

public class Tour {

    public static void main(String[] args) {

        Cities romania = SetUpRomania.getRomaniaMapSmall();
        City startCity = romania.getState("Bucharest");

        GoalTest goalTest = new TourGoalTest(romania.getAllCities(), startCity);
//        NodeFunction aStarFunction = new AStarFunction(new TourHeuristicFunction());
//        Frontier bestFirstFrontier = new BestFirstFrontier(aStarFunction);
//        generateSearch(new TourState(startCity), "A* TREE SEARCH", bestFirstFrontier, new TreeSearch(bestFirstFrontier), goalTest);



//      Here I initialize frontiers and generate searches
        Frontier breadthFirstFrontier = new BreadthFirstFrontier();
//        Should be 75972, 44217
        generateSearch(new TourState(startCity), "Breadth First TREE Search", breadthFirstFrontier, new TreeSearch(breadthFirstFrontier), goalTest);

//        breadthFirstFrontier = new BreadthFirstFrontier();
//        should be 946, 186
//        generateSearch(new TourState(startCity), "Breadth First GRAPH Search", breadthFirstFrontier, new GraphSearch(breadthFirstFrontier), goalTest);

//        Frontier depthFirstFrontier = new DepthFirstFrontier();
//        should be 30 steps, 61, 19
//        generateSearch(new TourState(startCity), "Depth First GRAPH Search", depthFirstFrontier, new GraphSearch(depthFirstFrontier), goalTest);

//        The depth first tree search runs infinitely and does not find a solution
//        depthFirstFrontier = new DepthFirstFrontier();
//        generateSearch(initialConfiguration, "Depth First TREE Search", depthFirstFrontier, new TreeSearch(depthFirstFrontier), new TilesGoalTest());


    }

    /**
     * Utility function for generating searches, finding solutions and printing them
     * @param initialConfiguration Initial state of the Romanian Tour
     * @param title String for printing the title
     * @param frontier Breadth first or depth first search frontier
     * @param search Tree search or Graph search
     * @param goalTest am I at the goal?
     */
    private static void generateSearch(TourState initialConfiguration, String title, Frontier frontier, Search search, GoalTest goalTest) {
        System.out.println("------------------" + title + "----------------------");
        System.out.println();

        Node solution = search.findSolution(new Node(null, null, initialConfiguration, 0), goalTest);
        new TourPrinting().printSolution(solution);
        System.out.println("Total number of nodes: " + search.numberOfNodes());
        System.out.println("Maximum number of nodes on the frontier: " + frontier.max());
        System.out.println();
    }

}
