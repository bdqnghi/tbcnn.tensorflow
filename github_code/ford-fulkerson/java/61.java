package edu.uw.advalgm.networkflow;

import java.util.Hashtable;

import edu.uw.advalgm.graph.GraphInput;
import edu.uw.advalgm.graph.SimpleGraph;

/**
 * This is the main class that computes the max flow of the input graph for each of the following algorithms:
 * 
 * <ul>
 * <li>Ford-Fulkerson algorithm
 * <li>Ford-Fulkerson algorithm with scaling
 * <li>Preflow Push algorithm
 * <li>Large label push-relabel algorithm
 * </ul>
 * 
 * @author Chaitra, Saranya, Sayana, Tejaswi
 */
public class tcss543 {
    
    public static void main(String args[]) {
        // Compute max flow using Ford-Fulkerson Algorithm
        fordFulkersonAlgorithm(args[0]);
        
        // Compute max flow using Ford-Fulkerson with Scaling Algorithm
        scalingFordFulkersonAlgorithm(args[0]);
        
        // Compute max flow using Preflow-Push Algorithm
        preflowPushAlgorithm(args[0]);
        
        // Compute max flow using Large label push relabel algorithm
        largeLabelPushRelabel(args[0]);
    }
    
    private static void fordFulkersonAlgorithm(String inputFile) {
        SimpleGraph G = new SimpleGraph();
        GraphInput.LoadSimpleGraph(G, inputFile);
        FordFulkersonAlgorithm ffAlgm = new FordFulkersonAlgorithm();
        double maxFlow = ffAlgm.calculateMaxFlow(G);
        System.out.println("Max flow using Ford-Fulkerson Algorithm = " + maxFlow);
    }
    
    private static void scalingFordFulkersonAlgorithm(String inputFile) {
        SimpleGraph G = new SimpleGraph();
        Hashtable nodeEdges = GraphInput.LoadSimpleGraph(G, inputFile);
        double maxFlow = ScalingFordFulkerson.calculateMaxFlow(G, nodeEdges);
        System.out.println("Max flow using Scaling Ford-Fulkerson Algorithm = " + maxFlow);
    }
    
    private static void preflowPushAlgorithm(String inputFile) {
        SimpleGraph G = new SimpleGraph();
        GraphInput.LoadSimpleGraph(G, inputFile);
        double maxFlow = PreflowPush.findMaxFlow(G);
        System.out.println("Max flow using Preflow-Push Algorithm = " + maxFlow);
    }
    
    private static void largeLabelPushRelabel(String inputFile) {
        SimpleGraph G = new SimpleGraph();
        GraphInput.LoadSimpleGraph(G, inputFile);
        double maxFlow = LargeLabelPushRelabel.getMaxFlow(G);
        System.out.println("Max flow using Large label push relable algorithm = " + maxFlow);
    }
}
