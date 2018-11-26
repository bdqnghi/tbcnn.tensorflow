import java.util.Hashtable;

import graphCode.GraphInput;
import graphCode.SimpleGraph;

public class tcss543 {

	public static void main(String[] args) throws Exception {

		SimpleGraph newGraph = new SimpleGraph();
		Hashtable h = GraphInput.LoadSimpleGraph(newGraph, args[0]);
		SimpleGraph secondGraph = new SimpleGraph();
		Hashtable hSecond = GraphInput.LoadSimpleGraph(secondGraph, args[0]);
		FordFulkerson ff = new FordFulkerson();
		int b = ff.fordFulker(newGraph, secondGraph, h, hSecond);
		System.out.println("max flow for FordFulkerson " + b);

		PreFlowPush p = new PreFlowPush(h);
		int maxFlow = p.computeMaxFlow();
		System.out.printf("Flow for the graph using Preflow Push: %d\n", maxFlow);

		SimpleGraph G = new SimpleGraph();
		Hashtable vertexEdgeMap = GraphInput.LoadSimpleGraph(G, args[0]);

		FordFulkersonScaling fordFulkersonScaling = new FordFulkersonScaling();
		System.out.println("\nMax flow for FordFulkerson Scaling algorithm: " + fordFulkersonScaling.calculateMaxFlow(G, vertexEdgeMap));

		System.out.println("Max flow for FordFulkerson " + b);

		System.out.printf("Flow for the graph using Preflow Push: %d\n", maxFlow);

	}
}
