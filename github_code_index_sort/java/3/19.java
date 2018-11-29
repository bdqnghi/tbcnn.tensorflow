/* Topological Sort
 * This is just the implementation of DFS
 * arrange the finish array in Descending order, it will give you the Topological Sort of Graph.
 */
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

class Graph {

	int V;

	public char color[];
	public LinkedList<Integer> AdjList[];
	public int discover[];
	public int finish[];
	public int Pi[];
	public LinkedList<Integer> Topological; 
	int t = 0;

	public Graph(int n) {
		this.V = n;
		AdjList = new LinkedList[n];
		Topological = new LinkedList<Integer>();
		color = new char[n];
		discover = new int[n];
		finish = new int[n];
		Pi = new int[n];

		for (int i = 0; i < n; i++) {
			AdjList[i] = new LinkedList<>();
		}
		Pi[0] = 0;
	}
}

public class Topologicalsort {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		Scanner s = new Scanner(System.in);

		System.out.println("Enter the number of nodes you have :");
		int n = s.nextInt();

		Graph vertex = new Graph(n);
		int u;
		int v;

		do {
			System.out.println("Enter the edges with start vertex u and end vertex v :");
			u = s.nextInt();
			v = s.nextInt();

			if (u == 0 && v == 0)
				break;

			addnode(vertex, u, v);

		} while (u != 0 || v != 0);

		printGraph(vertex);

		BFSTraversal(vertex, 0, vertex.color);

		System.out.println("Print various array : ");

		printArrays(vertex, n);

		System.out.println("Print DFS Traversal of Tree : ");
		printDFSTraversal(vertex, n);
		
		System.out.println("The Topological Sort of Graph : ");
		for(Integer i : vertex.Topological)
		{
			System.out.println(i);
		}
	}

	private static void printDFSTraversal(Graph vertex, int n) {
		System.out.println();
		int index = 0;
		System.out.print(index + " ");

		while (index < n) {
			index++;
			for (int i = 1; i < n; i++) {
				if (vertex.discover[i] == index) {
					System.out.print(i + " ");
				}
			}
		}
	}

	private static void printArrays(Graph vertex, int n) {

		System.out.println("The Pi tree of BFS is = ");

		for (int i = 0; i < n; i++) {
			System.out.print(vertex.Pi[i] + " ");
		}
		System.out.println();
		System.out.println("The color tree of BFS is = ");

		for (int i = 0; i < n; i++) {
			System.out.print(vertex.color[i] + " ");
		}
		System.out.println();
		System.out.println("The discovery tree of BFS is = ");

		for (int i = 0; i < n; i++) {
			System.out.print(vertex.discover[i] + " ");
		}
		System.out.println();
		System.out.println("The finish tree of BFS is = ");

		for (int i = 0; i < n; i++) {
			System.out.print(vertex.finish[i] + " ");
		}
	}

	private static void BFSTraversal(Graph v, Integer u, char[] color) {

		v.discover[u] = v.t++;
		v.color[u] = 'Y';

		if (!v.AdjList[u].isEmpty()) {
			for (Integer i : v.AdjList[u]) {
				if (v.color[i] == 'R') {
					v.Pi[i] = u;
					v.color[i] = 'Y';
					BFSTraversal(v, i, v.color);
				}
			}
		}

		v.color[u] = 'B';
		v.finish[u] = v.t++;
		//for topological sort insert in begining to get the correct order
		v.Topological.addFirst(u);
		
	}

	public static void addnode(Graph v, int start, int end) {
		v.AdjList[start].add(end);

		if (v.color[start] != 'R')
			v.color[start] = 'R';

		//v.AdjList[end].addFirst(start);

		if (v.color[end] != 'R')
			v.color[end] = 'R';

	}

	static void printGraph(Graph vertex) {
		for (int v = 0; v < vertex.V; v++) {
			System.out.println("Adjacency list of vertex " + v);
			System.out.print("head");
			System.out.print(vertex.color[v]);
			for (Integer pCrawl : vertex.AdjList[v]) {
				System.out.print(" -> " + pCrawl);
			}
			System.out.println("\n");
		}
	}
}
