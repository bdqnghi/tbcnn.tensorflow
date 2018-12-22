package com.test;

import java.util.Scanner;
import java.util.Stack;

public class DepthFirstSearch {
	private Stack<Integer> stack;

	public DepthFirstSearch() {
		stack = new Stack<Integer>();
	}

	public void searchTree(int dfsTree[][], int searchValue) {
		int nodeCount = dfsTree[searchValue].length - 1;

		int visited[] = new int[nodeCount + 1];
		int element = searchValue;
		int i = searchValue;
		System.out.print(element + "\t");
		visited[searchValue] = 1;
		stack.push(searchValue);

		while (!stack.isEmpty()) {
			element = stack.peek();
			i = element;
			while (i <= nodeCount) {
				if (dfsTree[element][i] == 1 && visited[i] == 0) {
					stack.push(i);
					visited[i] = 1;
					element = i;
					i = 1;
					System.out.print(element + "\t");
					continue;
				}
				i++;
			}
			stack.pop();
		}
	}

	public int[][] createTree(Scanner scanner) {
		int number_of_nodes;
		System.out.println("Enter the number of nodes in the graph");
		number_of_nodes = scanner.nextInt();

		int adjacency_matrix[][] = new int[number_of_nodes + 1][number_of_nodes + 1];
		System.out.println("Enter the adjacency matrix");
		for (int i = 1; i <= number_of_nodes; i++)
			for (int j = 1; j <= number_of_nodes; j++)
				adjacency_matrix[i][j] = scanner.nextInt();
		return adjacency_matrix;
	}

}
