package datastructure.graph;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class GraphQuestions {
	
	//Given a directed graph, design an algorithm to find out whether there is a route between two nodes.
	
	//implement a depth-first-search non-recursively
	public static boolean dfs(MyDirectedGraphNode<Integer> node, int value){
		
		//time cost= O(N)
		//time cost= O(0)
		
		if(node == null)
			return false;
	
		Stack<MyDirectedGraphNode<Integer>> stack = new Stack<MyDirectedGraphNode<Integer>>();
			
		stack.push(node);
		
		while(!stack.isEmpty()){
			MyDirectedGraphNode<Integer> currentNode = stack.pop();
			
			if(currentNode.getValue() == value)
				return true;
			
			for (MyDirectedGraphNode<Integer> adjacentNode : currentNode.adjacentNodes) {
				if(!adjacentNode.isVisited())
					stack.push(adjacentNode);
			}
				
		}
		return false;
	}
	//implement a depth-first-search recursively
	public static boolean dfsRecursive(MyDirectedGraphNode<Integer> node, int value){
		
		//time cost= O(N)
		//time cost= O(0)
		
		if(node == null || node.isVisited())
			return false;
	
		if(node.getValue() == value){
			return true;
		}else{
			for (MyDirectedGraphNode<Integer> adjacentNode : node.adjacentNodes) {
				if(dfsRecursive(adjacentNode, value))
					return true;
			}
		}
		return false;
	}
	
	//implement a depth-first-search non-recursively
	public static boolean bfs(MyDirectedGraphNode<Integer> node, int value){
		
		//time cost= O(N)
		//time cost= O(0)
		
		if(node == null)
			return false;
	
		Queue<MyDirectedGraphNode<Integer>> queue = new LinkedList<MyDirectedGraphNode<Integer>>();
			
		queue.add(node);
		
		while(!queue.isEmpty()){
			
			MyDirectedGraphNode<Integer> currentNode = queue.poll();
			
			if(currentNode.getValue() == value)
				return true;
			
			for (MyDirectedGraphNode<Integer> adjacentNode : currentNode.adjacentNodes) {
				if(!adjacentNode.isVisited())
					queue.add(adjacentNode);
			}	
		}
		return false;
	}
}