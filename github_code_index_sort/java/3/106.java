//Topologically Sort the given graph


import java.util.*;

public class Topologicalsort{

	class Vertex{
		int data;
		ArrayList<Vertex> edges;
		
		public Vertex(int data){
			this.data = data;
			this.edges = new ArrayList<Vertex>();
		}

		public void addEdge(Vertex edge){
			this.edges.add(edge);
		}

	}


	class Graph{
		ArrayList<Vertex> v;
		
		public Graph(){
			this.v = new ArrayList<Vertex>();
		}

		public void add(int data){
			v.add(new Vertex(data));
		}

	}

	public static void topologicalSearch(HashMap<Integer, HashSet<Integer>> graph, ArrayList<Integer> visited, Stack<Integer> st, ArrayList<Integer> result, int vertex){
		for (int key : graph.get(vertex)){
			if(!visited.contains(key)){
				
				visited.add(key);
				st.push(key);
				System.out.println(key);
				topologicalSearch(graph, visited, st, result, key);
			}
		}
		result.add(st.pop());

	}


	public static ArrayList<Integer> topologicalSort(HashMap<Integer, HashSet<Integer>> graph){
		Stack<Integer> st = new Stack<Integer>();
		ArrayList<Integer> visited = new ArrayList<Integer>();
		ArrayList<Integer> result = new ArrayList<Integer>();
		for (int key : graph.keySet()){
			if(!visited.contains(key)){
				visited.add(key);
				st.push(key);
				topologicalSearch(graph, visited, st,result, key);
			}
		}

		if(!st.isEmpty())
			result.add(st.pop());
	
		return result;
	}


	public static void main(String[] args){
		HashMap<Integer, HashSet<Integer>> graph = new HashMap<Integer, HashSet<Integer>>();

		graph.put(1, new HashSet<Integer>(Arrays.asList(2,3)));
		graph.put(2, new HashSet<Integer>());
		graph.put(3, new HashSet<Integer>());
		graph.put(4, new HashSet<Integer>(Arrays.asList(1,3)));
		System.out.println(graph);
		System.out.println(topologicalSort(graph));
		
	}


}



