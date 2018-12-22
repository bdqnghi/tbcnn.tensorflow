import java.util.*;
class Main {
  public static void main(String[] args) {
    System.out.println("hello world");
    
   
    // Tushar's test case
    /*
    Graph g = new Graph(8);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 4);
    g.addEdge(4, 7);
    g.addEdge(4, 5);
    g.addEdge(1, 3);
    g.addEdge(3, 5);
    g.addEdge(5, 6);
    */

    //https://www.hackerearth.com/practice/algorithms/graphs/topological-sort/tutorial/

	http://www.geeksforgeeks.org/topological-sorting/
	from 3:00

    Graph g = new Graph(6);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    Deque<Integer> result = g.topologicalSort();
    
    while(!result.isEmpty())
    	System.out.print(result.pop() + " ");
  }
}

class Graph{
	private int V;
	private LinkedList<Integer> adjacencyList[];
	
	public Graph(int size){
		this.V = size;
		adjacencyList = new LinkedList[V];
		for (int i = 0; i < V; i++)
			adjacencyList[i] = new LinkedList();
			
	}
	
	public void addEdge(int v, int w){
		adjacencyList[v].add(w);
	}
	
	public Deque<Integer> topologicalSort(){
		return topologicalSort(this);
	}
	
	public Deque<Integer> topologicalSort(Graph graph){
		Deque<Integer> stack = new LinkedList<>();
		Set<Integer> visited = new HashSet<>();
		for (int vertex = 0; vertex < V; vertex++){
			// if node has no outgoing edges, ignore it.
			if (adjacencyList[vertex].size() < 1)
				continue;
			if (visited.contains(vertex))
				continue;
			
			topologicalSortHelper(vertex, stack, visited);
		}
		return stack;
	}
	
	public void topologicalSortHelper(Integer vertex, Deque<Integer> stack, Set<Integer> visited){
		visited.add(vertex);
		
		for (Integer neighbor: adjacencyList[vertex]){
			if (visited.contains(neighbor))
				continue;
			topologicalSortHelper(neighbor, stack, visited);
		}
		stack.push(vertex);
	}
}

