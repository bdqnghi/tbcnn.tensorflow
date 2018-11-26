//PROJECT DEVELOPER'S NAME: Saran Sai Movva
//COURSE NUMBER: CMSC270
//DATE: 3/5/2017
//PROJECTNAME: Minimum Spanning Tree 
//DESCRIPTION: Implement both Prim's and Kruskal's minimum spanning tree algorithms using the algorithms
//found in the Chapter 14 Graphs PowerPoint. Test your program with the attached graphs, G1 through G6.
//For graphs G2, G4, & G5, the vertex letters are converted to integers where A=1, B=2, etc. For graph G6
//the vertices were assigned vertex numbers randomly
//FILES: DisjointSet.java, NodeType.java, Edge.java, MinimumSpanningTree.java
//BUGS: None that i have noticed
//problems existing in your project.
//UNIMPLEMENTED FEATURES: A better visual representation to display the minimum spanning tree
//RESULTS AND CONCLUSIONS: Result is that Prim's and Kruskal's Algorithms are fundamental concepts that allow
//for people to find the minimum spanning tree in a graph. They both end up finding the minimum spanning tree 
//and the minimum weight despite having very different implementation. 
package cs.ben.edu.Lab3;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * MinimumSpanningTree
 * 
 * @author Saran
 *
 */
public class MinimumSpanningTree {
	/**
	 * Main method
	 * 
	 * @param args
	 *            -String array args
	 */
	public static void main(String args[]) {
		Scanner input = new Scanner(System.in);
		boolean bool = true;
		while (bool) {

			System.out.print("Enter file name(0 to quit): ");
			String fileName = input.next();
			if (fileName.equals("0")) {
				bool = false;
				break;
			}
			int[][] graph = null;

			try {
				Scanner file = new Scanner(new File(fileName));
				Scanner file2 = new Scanner(new File(fileName));
				int size = file.nextInt();
				// Create adjacency matrix
				graph = new int[size + 1][size + 1];
				for (int i = 1; i < size + 1; i++) {
					for (int j = 1; j < size + 1; j++) {
						if (i == j) {
							graph[i][j] = 0;
						} else {
							graph[i][j] = Integer.MAX_VALUE;
						}
					}
				}
				// Read through file
				int edgeCount = 0;
				while (file.hasNextInt()) {
					int first = file.nextInt();
					int second = file.nextInt();
					int third = file.nextInt();
					graph[first][second] = third;
					graph[second][first] = third;
					edgeCount++;
				}
				primsAlgorithm(size, graph);

				Edge[] edgeArray = new Edge[edgeCount];
				edgeCount = 0;
				file2.nextInt();
				// Parse through file
				while (file2.hasNextInt()) {
					int first = file2.nextInt();
					int second = file2.nextInt();
					int weight = file2.nextInt();

					Edge edge = new Edge(weight, first, second);
					edgeArray[edgeCount] = edge;
					edgeCount++;
				}
				kruskalsAlgorithm(size, edgeCount, edgeArray);

			} catch (FileNotFoundException e) {
				System.out.println("Not a valid file.");
			}
		}
		input.close();
	}

	/**
	 * Method that sorts through a edge array
	 * 
	 * @param sort
	 *            -Array of Edge
	 * @return Array of Edge
	 */
	public static Edge[] sortEdgeArray(Edge[] sort) {
		Edge temp;
		for (int i = 1; i < sort.length; i++) {
			for (int j = i; j > 0; j--) {
				if (sort[j].getWeight() < sort[j - 1].getWeight()) {
					temp = sort[j];
					sort[j] = sort[j - 1];
					sort[j - 1] = temp;
				}
			}
		}
		return sort;
	}

	/**
	 * Prims Algorithm implementation
	 * 
	 * @param numOfVerticies
	 *            -int value of number of vertices
	 * @param weight
	 *            -2 dimensional int array of weights
	 */
	public static void primsAlgorithm(int numOfVerticies, int[][] weight) {
		Edge[] edges = new Edge[numOfVerticies];
		int[] nearest = new int[numOfVerticies + 1];
		int[] distance = new int[numOfVerticies + 1];
		int edgeCount = 0;
		int total = 0;
		int min = 0;

		for (int i = 2; i <= numOfVerticies; i++) {
			nearest[i] = 1;
			distance[i] = weight[1][i];
		}

		for (int n = 0; n < numOfVerticies - 1; n++) {
			min = Integer.MAX_VALUE;
			int next = 0;
			for (int i = 2; i <= numOfVerticies; i++) {
				if (distance[i] >= 0 && distance[i] < min) {
					min = distance[i];
					next = i;
				}
			}
			edges[edgeCount] = new Edge(next, nearest[next]);
			total += weight[nearest[next]][next];
			edgeCount++;

			distance[next] = -1;
			for (int i = 2; i <= numOfVerticies; i++) {
				if (weight[i][next] < distance[i]) {
					distance[i] = weight[i][next];
					nearest[i] = next;
				}
			}
		}
		printPrims(edges, total);
	}

	/**
	 * Implementation of Kruskals Algorithm
	 * 
	 * @param nodeNum
	 *            -int value of number of nodes
	 * @param edgeNum
	 *            - int value of number of edges
	 * @param edges
	 *            -int array of sorted edges
	 */
	public static void kruskalsAlgorithm(int nodeNum, int edgeNum, Edge[] edges) {
		Edge[] f = new Edge[edgeNum];
		DisjointSet ds = new DisjointSet(nodeNum);
		int fCount = 0;
		int p = 0;
		int q = 0;
		int i = 0;
		int j = 0;
		int weightTotal = 0;
		int edgeECount = 0;
		edges = sortEdgeArray(edges);

		while (fCount < nodeNum - 1) {
			Edge e = edges[edgeECount];
			edgeECount++;
			i = e.getFirst();
			j = e.getSecond();

			p = ds.find(i);
			q = ds.find(j);

			if (!ds.sameSet(p, q)) {
				ds.merge(p, q);
				f[fCount] = e;
				fCount++;
				weightTotal += e.getWeight();
			}
		}
		printKruskal(f, weightTotal);
	}

	/**
	 * Method that prints the results of Prim's Algorithm
	 * 
	 * @param edges
	 *            -int array values of edges in order
	 * @param total
	 *            -int value of minimum weight
	 */
	public static void printPrims(Edge[] edges, int total) {

		System.out.println("Prim's Algorithm");
		System.out.println("Weight: " + total);
		for (int i = 0; i < edges.length - 1; i++) {
			System.out.println("Edges: (" + edges[i].getFirst() + ", " + edges[i].getSecond() + ")");
		}
	}

	/**
	 * Method that prints the results of Kruskal's Algorithm
	 * 
	 * @param edges
	 *            -int array values of edges in order
	 * @param total
	 *            -int value of minimum weight
	 */
	public static void printKruskal(Edge[] edges, int total) {
		System.out.println();
		System.out.println("Kruskal's Algorithm");
		System.out.println("Weight: " + total);
		for (int i = 0; i < edges.length - 1; i++) {
			try {
				System.out.println("Edges: (" + edges[i].getFirst() + ", " + edges[i].getSecond() + ")");
			} catch (NullPointerException e) {
				continue;
			}
		}
		System.out.println();

	}

}
