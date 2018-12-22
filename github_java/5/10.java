package com.dima.algorithms.tree;

public class Tree {
	
	Node root;	
	
	public void addNode(int key, String value) {
		Node newNode = new Node(key, value);
		if(root == null) {
			root = newNode;
		} else {
			Node focusNode = root;			
			while(true) {				
				if(key < focusNode.key) {
					// left branch
					if(focusNode.leftChild == null){
						focusNode.leftChild = newNode;						
						return;
					}
					focusNode = focusNode.leftChild;
				} else {
					// right branch					
					if(focusNode.rightChild == null) {
						focusNode.rightChild = newNode;						
						return;
					}
					focusNode = focusNode.rightChild;
				}
			}
		}		
	}
	
	/**
	 * DFS depth-first-search in-order-traverse method
	 * 
	 * @param focuseNode
	 */
	public void dfsInOrderTraverse(Node focuseNode){
		if(focuseNode != null) {
			dfsInOrderTraverse(focuseNode.leftChild);
			System.out.println(focuseNode.toString());
			dfsInOrderTraverse(focuseNode.rightChild);
		}		
	}
	
	
	/**
	 * DFS depth-first-search pre-order-traverse method
	 * 
	 * @param focuseNode
	 */
	public void dfsPreOrderTraverse(Node focuseNode){
		if(focuseNode != null) {
			System.out.println(focuseNode.toString());
			dfsPreOrderTraverse(focuseNode.leftChild);
			dfsPreOrderTraverse(focuseNode.rightChild);
		}		
	}

	
	/**
	 * DFS depth-first-search post-order-traverse method
	 * 
	 * @param focuseNode
	 */
	public void dfsPostOrderTraverse(Node focuseNode){
		if(focuseNode != null) {			
			dfsPostOrderTraverse(focuseNode.leftChild);
			dfsPostOrderTraverse(focuseNode.rightChild);
			System.out.println(focuseNode.toString());
		}		
	}
	
	
	
	public Node findNode(int key) {
		Node focusNode = root;
		while (true) {
			if (key < focusNode.key) {
				// left branch
				if (focusNode.leftChild.key == key) {
					return focusNode.leftChild;
				}
				focusNode = focusNode.leftChild;
			} else {
				// right branch
				if (focusNode.rightChild.key == key) {
					return focusNode.rightChild;
				}
				focusNode = focusNode.rightChild;
			}
			// very important to quit the loop
			if(focusNode == null) {
				return null;
			}
		}
	}
	

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Tree tree = new Tree();
		System.out.println("Start");
		
		tree.addNode(200, "root");
		tree.addNode(100, "left_100_of_root");
		tree.addNode(50, "left_50_of_left_100");
		tree.addNode(120, "right_120_of_left_100");
		tree.addNode(250, "right_250_of_root");
		tree.addNode(240, "left_240_of_right_250");
		tree.addNode(260, "right_260_of_right_250");
		
		System.out.println("in order traverse");
		tree.dfsInOrderTraverse(tree.root);
		
		
		System.out.println("pre order traverse");
		tree.dfsPreOrderTraverse(tree.root);
		
		System.out.println("pre order traverse");
		tree.dfsPostOrderTraverse(tree.root);
		
		
		Node n = tree.findNode(100);
		
		System.out.println("Node was found: " + n);
		
		
		System.out.println("Stop");

	}

}
