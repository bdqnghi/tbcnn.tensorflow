/**
 * @author Manasi Bharde 
 * @author Paridhi Srivastava
 * This is application of ford-fulkerson algorithm to maximize network flow.
 * Source and sink is added to original graph. All edges from source to students
 *  are given weight 3 which is maximum number of courses student can take. 
 *  Edges from courses to sink are given weight equal to course capacity.
 *  Edges from student to course are given weight 1. And flow from source to sink is maximized.  
 */

import java.util.Scanner;

public class Register {

	private static int s, c;
	private static int maxSum;
	private static int[][] adjMatrix;
	private static boolean seen[];
	private static int[] parent;
	private static int path;

	
	/*
	 * this method adds edges between students and courses and connects the 
	 * students vertices to the source and the course vertices to the sink
	 * and builds an adjacency matrix for the graph formed. it then prints 
	 * the maximum number of students that can be registered
	 */
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		s = sc.nextInt();
		c = sc.nextInt();
		seen = new boolean[s + c + 2];
		parent = new int[s + c + 2];

		adjMatrix = new int[s + c + 2][s + c + 2];

		sc.nextLine();
		for (int i = 0; i < s; i++) {
			String[] line = sc.nextLine().split("\\s+");
			for (String ind : line) {
				int id = Integer.parseInt(ind);
				adjMatrix[i + 1][s + id] = 1;
			}
			adjMatrix[0][i + 1] = 3;
		}

		for (int i = 0; i < c; i++) {
			adjMatrix[s + 1 + i][s + c + 1] = sc.nextInt();
		}
		regStudents();
	}

	/*
	 * displays any given matrix
	 */
	public static void displayMatrix(int[][] matrix) {
		for (int i = 0; i < s + c + 2; i++) {
			for (int j = 0; j < s + c + 2; j++) {
				System.out.print(matrix[i][j] + " ");
			}
			System.out.println();
		}
	}

	/*
	 * performs Ford-Fulkerson algorithm on the given graph and prints the 
	 * maximum flow through the graph 
	 */
	public static void regStudents() {
		for (int i = 0; i < (s); i++) {
			while (adjMatrix[0][i] >= 1) {
				dfssearch(i);
				parent[i] = 0;
				if (path > -1) {
					while (path > -1 && path != 0) {
						adjMatrix[parent[path]][path]--;
						adjMatrix[path][parent[path]]++;
						path = parent[path];
					}
					maxSum++;
					init();
					path = -1;
				} else {
					path = -1;
					break;
				}
			}
		}
		System.out.println(maxSum);
	}

	/* performs a recursive depth-first search to find a path to the sink
	 * if there is no path, it returns -1
	 */
	private static int dfssearch(int vertex) {
		seen[vertex] = true;
		for (int i = 0; i < s + c + 2; i++) {
			if (!seen[i]) {
				if (adjMatrix[vertex][i] >= 1 && i == s + c + 1) {
					parent[i] = vertex;
					path = i;
				} else if (!seen[i] && adjMatrix[vertex][i] >= 1) {
					parent[i] = vertex;
					dfssearch(i);
				}
			}
		}
		return -1;
	}

	/*
	 * initializes parent and seen arrays for every vertex in the graph
	 */
	private static void init() {
		for (int i = 0; i < s + c + 2; i++) {
			parent[i] = i;
			seen[i] = false;
		}
	}
}

