package org.pang.learning.ds;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class AVL {
	public static void main(String[] args) {
		Tree tree = newTree(2,1,2,5,6,8,9,2,3,12,7,9);
		tree.print();
	}
	
	public static Tree newTree(int ...datas){
		if(datas==null||datas.length<1)
			return null;
		Node root=new Node(datas[0]);
		Tree tree=new Tree(root);
		
		for(int i=1;i<datas.length;i++){
			tree.add(datas[i]);
		}
		
		return tree;
	}

	static class Tree{
		Node root;
		public Tree(Node root){
			this.root=root;
		}
		
		public void add(int data){
			Node node=root;
			do{
				if(node.data==data)
					break;
				if(node.data>data){
					if(node.left==null){
						node.left=new Node(data);
						node.left.parent=node;
						break;
					}else
						node=node.left;
				}else{
					if(node.right==null){
						node.right=new Node(data);
						node.right.parent=node;
						break;
					}else
						node=node.right;
				}
			}while(true);
		}
		
		public int height(){
			return height(root);
		}
		
		private int height(Node node){
			if(node==null)
				return 0;
			else{
				return 1+Math.max(height(node.left), height(node.right));
			}
		}
		
		public void print(Node node){
//			if(node)
		}
		
		public void print(){
			int height=height();
//			System.out.println("height of tree: "+height);
//			System.out.println();
			if(height==0)
				return;
			int distance=2;
			int offset=distance*height;
			LinkedList<Node> nodeList=new LinkedList<Node>();
			nodeList.addLast(root);
			int hIdx=0;
			while(!nodeList.isEmpty()){
				int size=nodeList.size();
				int innerOffset=offset;
				for(Node node : nodeList){
					System.out.printf("%"+innerOffset+"s",node.data);
					innerOffset+=distance*hIdx;
				}
				System.out.println();
				hIdx++;
				offset=offset-distance;
				for(int i=0;i<size;i++){
					Node node = nodeList.poll();
					if(node.left!=null)
						nodeList.addLast(node.left);
					if(node.right!=null)
						nodeList.addLast(node.right);
					
				}
			}
		}
	}
	
	static class Node{
		int data;
		Node left;
		Node right;
		Node parent;
		public Node(int data){
			this.data=data;
		}
	}
}
