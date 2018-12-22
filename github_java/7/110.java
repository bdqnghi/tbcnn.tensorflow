/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/

//https://practice.geeksforgeeks.org/problems/topological-sort/1

/*Complete the function below*/
class TopologicalSort
{
	/*
		Here Array of ArrayList is given.
		This is bascially an Adjacency List.
		With the Index of Array as CurrentNode and List is the Neighbour

	*/
     public static int[] topoSort(ArrayList<Integer> graph[],int N) {
 		int[] sorted = new int[graph.length];
 		Set<Integer> processedNodes = new HashSet<>();
 		Stack<Integer> sortedVals  = new Stack<>();
 		Integer index = 0;
 		for (ArrayList<Integer> neighbours : graph) { 			
 			if (neighbours.isEmpty()) {
 				if (!processedNodes.contains(index)) {
 					sortedVals.push(index);
 				}
 				processedNodes.add(index);
 			} else {
 				processedNodes.add(index);
 				topoSortUtil(index, graph, graph[index], processedNodes, sortedVals);
 			}
 			index++; 			
 		}

 		int resultIndex = 0;
		while (!sortedVals.empty()) {			
			sorted[resultIndex] = sortedVals.pop();
			resultIndex++;
		}

 		return sorted;
     }

     public static void topoSortUtil(Integer currentNode, ArrayList<Integer> graph[], List<Integer> neighbours, 
     		Set<Integer> processedNodes, Stack<Integer> sortedVals) {

     	List<Integer> tempNeighbours = new ArrayList<>(neighbours);
     	for (Integer node : tempNeighbours) {
     		if (!processedNodes.contains(node)) {
     			processedNodes.add(node);
     			topoSortUtil(node, graph, graph[node], processedNodes, sortedVals);
     		}
     	}
     	if (!processedNodes.contains(currentNode)) {
 		    sortedVals.push(currentNode);
 		}
     	
     }
}