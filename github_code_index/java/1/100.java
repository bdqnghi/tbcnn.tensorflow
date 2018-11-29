package main;

import java.util.Scanner;

import breadthfirst.BreadthFirstSearch;
import depthfirst.DepthFirstSearch;

public class MainClass {

	public static void main(String[] args){

		DepthFirstSearch depthFirstSearch = new DepthFirstSearch();
		BreadthFirstSearch breadthFirstSearch = new BreadthFirstSearch();

		Scanner scanner = new Scanner(System.in);
		System.out.println("Enter the no of nodes: ");
		int nodes = scanner.nextInt();
		System.out.println("Enter the no of edges: ");
		int edges = scanner.nextInt();
		System.out.println("Enter the starting point: ");
		int n = scanner.nextInt();
		
		depthFirstSearch.dfs(n, edges, nodes);
		breadthFirstSearch.bfs(n, edges, nodes);
	}
}
