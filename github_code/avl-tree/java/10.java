import java.util.*;
import java.lang.*;
import java.io.*;
import java.math.*;

class Ideone{

	public static Scanner scn = new Scanner(System.in);

	public static class AVL{

		private class Node{

			int key;
			int height;

			Node left, right;

			Node(int key){
				this.key = key;
				this.height = 1;
			}
		}

		private Node root;

		private int height(Node n){

			if(n == null) return 0;

			return n.height;
		}

		private int balanceFactor(Node n){

			if(n == null) return 0;

			return height(n.left) - height(n.right);
		}

		private void fixHeight(Node n){
			if(n == null) return;
			n.height = Math.max(height(n.left) , height(n.right)) + 1;
		}

		private Node rotateRight(Node z){
			
			/*		z                 y 
				   / \               / \
				  y   T2     -->   T1   z
				 / \                   / \
			   T1   x                 x   T2
 			*/

			Node y = z.left;
			Node x = y.right;

			//rotate
			y.right = z;
			z.left = x;

			//update height
			fixHeight(z);
			fixHeight(y);

			return y;
		}

		private Node rotateLeft(Node z){
			/*	   z		   		  y
				  / \     			 / \
				T1   y   	-->		z   T2
				    / \   	  	   / \     
			      x   T2  	     T1   x
 			*/

			Node y = z.right;
			Node x = y.left;

			//rotate
			y.left = z;
			z.right = x;

			//update height
			fixHeight(z);
			fixHeight(y);

			return y;
		}

		public void insert(int key){

			this.root = insert(root, key);
		}

		private Node insert(Node n, int key){

			if(n == null)
				return new Node(key);

			if(n.key == key){
				System.out.println("Duplicate keys not allowed");
				return n;
			}

			if(key < n.key)
				n.left = insert(n.left, key);
			else if(key > n.key)
				n.right = insert(n.right, key);

			//update height
			fixHeight(n);

			int balance = balanceFactor(n);

			//left heavy
			if(balance > 1){ 

				//left left
				if(key < n.left.key)
					return rotateRight(n);
				
				//left right
				if(key > n.left.key){
					n.left = rotateLeft(n.left);
					return rotateRight(n);
				}
			} 

			//right heavy
			if(balance < -1){ 

				//right right
				if(key > n.right.key)
					return rotateLeft(n);
				
				//right left
				if(key < n.right.key){
					n.right = rotateRight(n.right);
					return rotateLeft(n);
				}
			} 
		
			return n;
		}

		public void print(int type){

			if(type == 1){

				System.out.print("IN : ");
				inOrder(this.root);

			} else if(type == 2){

				System.out.print("PRE : ");
				preOrder(this.root);
			
			} else if(type == 3){

				System.out.print("POST : ");
				postOrder(this.root);
			}

			System.out.println();
		}

		private void inOrder(Node n){

			if(n == null) return;

			inOrder(n.left);

			System.out.print("" + n.key + " ");

			inOrder(n.right);
		}

		private void preOrder(Node n){

			if(n == null) return;

			System.out.print("" + n.key + " ");

			preOrder(n.left);
			preOrder(n.right);
		}

		private void postOrder(Node n){

			if(n == null) return;

			postOrder(n.left);
			postOrder(n.right);

			System.out.print("" + n.key + " ");
		}
	}

	public static void main (String[] args) throws java.lang.Exception{

		//int T = scn.nextInt();

		AVL tree = new AVL();

		//2, 1, 4, 5, 9, 3, 6, 7, 16, 0
		
		tree.insert(2);
		tree.insert(1);
		tree.insert(4);
		tree.insert(5);
		tree.insert(9);

		tree.insert(3);
		tree.insert(6);
		tree.insert(7);
		tree.insert(16);
		tree.insert(0);

		tree.print(1);
		tree.print(2);
		tree.print(3);
	}
}