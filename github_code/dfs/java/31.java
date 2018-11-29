package com.xyx.nowcoder.class_6;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Stack;

/**
 * 图的深度优先搜索
 * @author huan
 * @date 2018年6月18日
 */
public class DFS {

	public static List<Node> dfs(Node node) {
		if (node == null)
			return null;
		Stack<Node> stack = new Stack<Node>();				//辅助栈
		stack.push(node);
		ArrayList<Node> result = new ArrayList<Node>();		//存放结果
		result.add(node);
		HashSet<Node> set = new HashSet<Node>();			//用来存放一个节点是否被遍历过
		
		while (!stack.isEmpty()) {
			//从栈中弹出一个节点，若是该节点的所有邻接点都已经被遍历过了，则不用管该节点了
			Node cur = stack.pop();
			for (Node next : cur.nexts) {
				if (!set.contains(next)) {
					//在添加至栈中的时候遍历
					stack.push(cur);
					stack.push(next);
					set.add(next);
					result.add(next);
					break;
				}
			}
		}
		return result;
	}
	
	//递归实现
	public static List<Node> dfs_recurse(Node node) {
		if (node == null)
			return null;
		HashSet<Node> set = new HashSet<Node>();
		ArrayList<Node> result = new ArrayList<Node>();
		dfsHelper(node, result, set);
		return result;
	}
	
	private static void dfsHelper(Node node, ArrayList<Node> result, HashSet<Node> set) {
		result.add(node);
		set.add(node);
		
		//遍历所有的邻接点
		for (Node next : node.nexts) {
			if (!set.contains(next)) {
				dfsHelper(next, result, set);
			}
		}
	}
	
	//test
	public static void main(String[] args) {
		int[][] rels = new int[][] {
			{1, 7, 1},
			{1, 2, 1},
			{2, 3, 1},
			{2, 4, 1},
			{3, 5, 1},
			{3, 4, 1},
			{4, 6, 1},
			{7, 4, 1},
			{7, 6, 1}
		};
		Graph graph = GraphicGenerator.generate(rels, true);
		List<Node> dfsResult = DFS.dfs(graph.getNode(1));
		System.out.println(dfsResult);
		List<Node> dfsResultR = DFS.dfs_recurse(graph.getNode(1));
		System.out.println(dfsResultR);
	}
}
