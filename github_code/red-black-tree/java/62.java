package tree;

import java.awt.Color;

/**
 * Red Black Tree implementation with only positive integers and colors represented by sign
 * Red is positive and black is negative
 * @author timothy
 *
 */
public class RedBlackTree {
	/*
	 * Enum class to denote color of nodes
	 */
	enum Color{
		Black, Red
	}
	/*
	 * Inner Node class
	 */
	private class Node{
		Color nodeColor;
		int data;
		Node left, right, parent;
		
		public Node(int dat) {
			data=dat;
		}
	}
	
	private Node root; // Root node in the red black tree
	
	/*
	 * Red Black Tree Constructor when no root node is given
	 */
	public RedBlackTree() {
		root =null;
	}
	/*
	 * Red Black Tree constructor when no root node is given
	 */
	public RedBlackTree(int data) {
		root.data=data;
	}
	
	/**
	 * Red Black Tree insert method
	 * @param data
	 */
	public void add(int data) {
		//Insert like a normal binary search tree then call fixTree to properly insert
		Node toInsert = new Node(data);
		if(root ==null) {
			root = toInsert;
		}else {
			Node prev = null;
			Node temp = root;	
			while(temp!=null) {
				prev = temp;
				
				if(data < temp.data) {
					temp = temp.left;
				}else if(temp.data > data){
					temp = temp.right;
				}else {
					return;
				}
			}
			
			toInsert.parent = prev;
			if(prev==null) {
				root = toInsert;
			}else if(toInsert.data < prev.data) {
				prev.left = toInsert;
			}else {
				prev.right = toInsert;
			}
			toInsert.left =null;
			toInsert.right = null;
		}
		toInsert.nodeColor = Color.Red;
		fixInsert(toInsert);
	}
	
	/**
	 * Searches the Red Black Tree for the node
	 * @param data
	 * @return Node with value data
	 */
	public Node find(int data) {
		Node curr = root;
		while(curr!=null) {
			if(curr.data == data) {
				return curr;
			}else if(curr.data > data) {
				curr = curr.left;
			}else {
				curr = curr.right;
			}
		}
		return null;
	}
	
	/**
	 * Get predecessor node of any node in the RBT
	 * @param curr
	 * @return predecessor
	 */
	public Node getPred(Node curr) {

		if(curr.right != null) {
			curr = curr.right;
			while(curr.left!=null) {
				curr = curr.left;
			}
			return curr;
		}else {
			Node parent = curr.parent;
			while(parent!=null && curr == parent.right) {
				curr = parent;
				parent = curr.parent;
			}
			return parent;
		}
	}
	/**
	 * Red Black Tree remove method
	 * @param data
	 */
	public void remove(int data) {
		Node toRemove = find(data); 
		if(toRemove ==null) {
			return;
		}else if(toRemove.left != null && toRemove.right !=null) {
			//Node has two children
			Node pred = getPred(toRemove);
			toRemove.data = pred.data;
			toRemove = pred;
		}
		
		//Pred returns the min value of the right subtree which will have at most one child
		Node childPred = toRemove.left == null ? toRemove.right : toRemove.left;
		if(childPred !=null) {
			//splice the node and fix if double black
			if(toRemove == root) {
				//Addressing root case
				root = childPred;
			}else if(toRemove.parent.left == toRemove) {
				//if toRemove is a left child replace toRemove with the child
				toRemove.parent.left = childPred;
			}else {
				//Same for right child
				toRemove.parent.right = childPred;
			}
			//fix up on replacement node
			if(childPred.nodeColor == Color.Black) {
				fixRemove(childPred);
			}
		}else if(toRemove == root) {
			//no children and is the root so return an empty tree
			root = null; 
		}else {
			//no children so fixup on original node
			if(toRemove.nodeColor == Color.Black) {
				fixRemove(toRemove);
			}
		}
	}
	/**
	 * Method to fix any violations from the remove method
	 * @param toFix
	 */
	public void fixRemove(Node toFix) {
		while(toFix!= root && toFix.nodeColor == Color.Black) {
			if(toFix == toFix.parent.left) {
				//Left child
				Node sibling = toFix.parent.right;
				//If sibling of node toFix is red make proper adjustments
				if(sibling.nodeColor == Color.Red) {
					sibling.nodeColor = Color.Black;
					toFix.parent.nodeColor = Color.Red;
					rotateLeft(toFix.parent);
					sibling = toFix.parent.right;
				}
				
				if(sibling.left.nodeColor == Color.Black && sibling.right.nodeColor == Color.Black) {
					sibling.nodeColor = Color.Red;
					toFix = toFix.parent;
				}else {
					if(sibling.right.nodeColor == Color.Black) {
						sibling.left.nodeColor = Color.Black;
						sibling .nodeColor = Color.Red;
						rotateRight(sibling);
						sibling = toFix.parent.right;
					}
					
					sibling.nodeColor = toFix.parent.nodeColor;
					toFix.parent.nodeColor = Color.Black;
					sibling.right.nodeColor = Color.Black;
					rotateLeft(toFix.parent);
					toFix = root;
				}
			}else {
				//Right child
				Node sibling = toFix.parent.left;
				if(sibling.nodeColor == Color.Red) {
					sibling.nodeColor = Color.Black;
					toFix.parent.nodeColor = Color.Red;
					rotateRight(toFix.parent);
					sibling = toFix.parent.left;
				}
				
				if(sibling.left.nodeColor == Color.Black && sibling.right.nodeColor == Color.Black) {
					sibling.nodeColor = Color.Red;
					toFix = toFix.parent;
				}else {
					if(sibling.left.nodeColor == Color.Black) {
						sibling.right.nodeColor = Color.Black;
						sibling.nodeColor = Color.Red;
						rotateLeft(sibling);
						sibling = toFix.parent.left;
					}
					
					sibling.nodeColor = toFix.parent.nodeColor;
					toFix.parent.nodeColor = Color.Black;
					sibling.left.nodeColor = Color.Black;
					rotateRight(toFix.parent);
					toFix = root;
				}
			}
		}
		//When toFix becomes the root
		toFix.nodeColor = Color.Black;
	}
	/**
	 * Method to fix any violations the tree may make upon insertion
	 * @param toFix
	 */
	public void fixInsert(Node toFix) {
		//Will only need to fix if parent is red since node being inserted is red
		if(toFix !=null && toFix !=root && toFix.parent.nodeColor == Color.Red) {
			//Checking case where parent of node inserted is red and sibling of parent is also red
			if(getSibling(toFix.parent).nodeColor == Color.Red) {
				toFix.parent.nodeColor = Color.Black;
				getSibling(toFix.parent).nodeColor = Color.Black;
				grandParent(toFix).nodeColor = Color.Red;
				fixInsert(grandParent(toFix));
			}else if (grandParent(toFix) != null && toFix.parent ==grandParent(toFix).left ) {
				//If the parent is the left child of the grandparent
				if(toFix == toFix.parent.right) { 
					//if the node inserted is the right child of the parent you want to address the triangle case
					rotateLeft(toFix = toFix.parent); //Setting toFix to parent value because after rotation for triangle case
					//Line case must also be addressed
				}
				toFix.parent.nodeColor = Color.Black;
				grandParent(toFix).nodeColor = Color.Red;
				rotateRight(grandParent(toFix));
			}else if(grandParent(toFix) !=null && toFix.parent == grandParent(toFix).right) {
				if(toFix==toFix.parent.left) {
					//once again addressing triangle case
					rotateRight(toFix = toFix.parent);
				}
				toFix.parent.nodeColor = Color.Black;
				grandParent(toFix).nodeColor = Color.Red;
				rotateLeft(grandParent(toFix));
			}
		}
		root.nodeColor = Color.Black; //set root to black in case it is red
	}
	
	/**
	 * Rotate original node left on the tree
	 * @param originalNode
	 */
	public void rotateLeft(Node originalNode) {
		Node replaceNode = originalNode.right; //Node to take the place of the replacement node in left rotate
		originalNode.right = replaceNode.left; //Set left subtree of replacement node to be right subtree of original node
		if(replaceNode.left !=null) {
			replaceNode.left.parent = originalNode; //fix the parent linkage
		}
		replaceNode.parent = originalNode.parent; //Link the replacement node to the parent of the original node
		if(originalNode.parent ==null) { //if original node was root set new node to root
			root = replaceNode;
		}else if(originalNode == originalNode.parent.left) {
			originalNode.parent.left = replaceNode; //If left child then link parent left child to replacement node
		}else {
			originalNode.parent.right = replaceNode; //Otherwise right child so same thinking
		}
		replaceNode.left = originalNode;
		originalNode.parent = replaceNode; //Officially change the links of the original node to the replacement node		
	}
	
	/**
	 * Rotate original node right on the tree
	 * @param originalNode
	 */
	public void rotateRight(Node originalNode) {
		Node replaceNode = originalNode.left; //Node to replace original node should be left child
		originalNode.left = replaceNode.right;
		if(replaceNode.right!=null) {
			replaceNode.right.parent = originalNode;
		}
		replaceNode.parent = originalNode.parent;
		if(originalNode.parent == null) {
			root = replaceNode;
		}else if(originalNode == originalNode.parent.left) {
			originalNode.parent.left = replaceNode;
		}else {
			originalNode.parent.right = replaceNode;
		}
		
		replaceNode.right = originalNode;
		originalNode.parent = replaceNode;
	}
	/*
	 * Color getter
	 */
	public Color getColor(Node node) {
		return node == null ? Color.Black:Color.Red;
	}
	
	/*
	 * Sibling getter
	 */
	public Node getSibling(Node node) {
		return (node == null || node.parent == null) ? null:
			(node.parent.left == node ? node.parent.right:node.parent.left);
	}
	/*
	 * Returns grandparent if exists otherwise null
	 */
	public Node grandParent(Node node) {
		return node.parent == null ? null: node.parent.parent;
	}
	
}
