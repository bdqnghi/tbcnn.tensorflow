import java.util.Hashtable;

public class tcss543 {

	public static void main(String[] args) throws Exception {
		SimpleGraph G = new SimpleGraph();
		GraphInput.LoadSimpleGraph(G, args[0]);
		SimpleGraph newGraph = new SimpleGraph();
		Hashtable h = GraphInput.LoadSimpleGraph(newGraph, args[0]);
		SimpleGraph secondGraph = new SimpleGraph();
		Hashtable hSecond = GraphInput.LoadSimpleGraph(secondGraph, args[0]);
		FordFulkerson ff = new FordFulkerson();
		int b = ff.fordFulkerson(newGraph, secondGraph, h, hSecond);
		System.out.println("max flow for FordFulkerson " + b);

		SimpleGraph newGraph2 = new SimpleGraph();
		Hashtable hPre = GraphInput.LoadSimpleGraph(newGraph2, args[0]);
		PreFlowPush p = new PreFlowPush(hPre);
		int maxFlow = p.computeMaxFlow();
		System.out.printf("Flow for the graph using Preflow Push: %d\n", maxFlow);

		SimpleGraph graph = new SimpleGraph();
		Hashtable vertexEdgeMap = GraphInput.LoadSimpleGraph(graph, args[0]);

		FordFulkersonScaling fordFulkersonScaling = new FordFulkersonScaling();
		System.out.println("Maximum flow for FordFulkerson algorithm: " + b);
		System.out.println("Maximum flow for FordFulkerson Scaling algorithm: "
				+ fordFulkersonScaling.calculateMaxFlow(graph, vertexEdgeMap));
		System.out.printf("Flow for the graph using Preflow Push: %d\n", maxFlow);
	}
}
