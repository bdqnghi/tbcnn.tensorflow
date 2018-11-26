package AVLTree;

import java.util.Scanner;

import BST.BST.Node;

public class AVLTree {
	
	private class Node{
		int value;
		int height;
		Node left, right;
		
		Node(int value){
			this.value = value;
			left = null;
			right = null;
			height = 0;
		}
	}
	Scanner in;
	int size;
	public Node head;
	
	public AVLTree(Scanner in){
		head = null;
		size = in.nextInt();
		for(int i = 0; i < size; i++)
			head = insert(head, in.nextInt());
	}
	
	public Node insert(Node h, int val){
		
		if(h == null){
			//System.out.println("The value being inserted is: " + val);
			//System.out.println("Case 1");
			return new Node(val);
		}
		
		//System.out.println("The value being inserted is: " + val);
		//System.out.println("h is: " + h.value);
		
		if(val < h.value){
			//System.out.println("Case 2");
			h.left = insert(h.left, val);
			if((Height(h.left) - Height(h.right)) == 2){
				if(val < h.left.value) h = rotateLL(h);
				else h = rotateLR(h);
			}
		}
		else{
			//System.out.println("Case 3");
			h.right = insert(h.right, val);
			if((Height(h.right) - Height(h.left)) == 2){
				if(val > h.right.value) h = rotateRR(h);
				else h = rotateRL(h);
			}
		}
		//System.out.println("h is: " + h.value);
		h.height = max(Height(h.right), Height(h.left)) + 1;
		return h;
	}
	
	private int max(int height, int height2) {
		return height > height2 ? height : height2;
	}

	private Node rotateRL(Node h) {
		h.right = rotateLL(h.right);
		h = rotateRR(h);
		//System.out.println("RL rotation complete");
		return h;
	}

	private Node rotateRR(Node h) {
		Node right = h.right;
		h.right = right.left;
		right.left = h;
		h.height = max(Height(h.left), Height(h.right)) + 1;
		right.height = max(Height(right.left), Height(right.right)) + 1;
		return right;
	}

	private Node rotateLR(Node h) {
		h.left = rotateRR(h.left);
		h = rotateLL(h);
		return h;
	}

	private Node rotateLL(Node h) {
		Node left = h.left;
		h.left = left.right;
		left.right = h;
		h.height = max(Height(h.left), Height(h.right)) + 1;
		left.height = max(Height(left.left), Height(left.right)) + 1;
		return left;
	}

	int Height(Node x){
		if(x == null) return -1; //VERY IMPORTANT CATCH
		return x.height;
	}

	public void printInOrder(Node h) {
		if(h == null) return;
		
		printInOrder(h.left);
		System.out.println(" " + h.value + " (height: " + h.height + ") ");
		printInOrder(h.right);
		
	}
	
	/*public Node remove(Node h, int value){
		if(h == null) {
			//System.out.println("Case 1");
			return h;
		}
		
		if(h.value == value){
			//System.out.println("Case 2");
			if(h.left == null && h.right == null) h = null;
			else if(h.left == null && h.right != null){
				int temp = h.value;
				h.value = h.right.value;
				h.right.value = temp;
				h.right = remove(h.right,h.right.value);
				
			}
			else if(h.left != null && h.right == null){
				int temp = h.value;
				h.value = h.left.value;
				h.left.value = temp;
				h.left = remove(h.left, h.left.value);
			}
			else{
				Node suc = findInOrderSuc(h);
				if(suc == null){
					System.out.println("Oops something went wrong");
					return null;
				}
				int temp = h.value;
				h.value = suc.value;
				suc.value = temp;
				//System.out.println("reached here. suc.value: " + suc.value);
				h.right = remove(h.right, suc.value);
			}
			return h;
		}
		
		if(value < h.value){
			//System.out.println("Case 3");
			h.left = remove(h.left, value);
		}
		else{
			//System.out.println("Case 4");
			h.right = remove(h.right, value);
		}
		
		return h;
	}
	
	private Node findInOrderSuc(Node h){
		if(h == null) return null;
		Node temp = h.right;
		while(temp.left != null) temp = temp.left;
		return temp;
	}*/
	
}
