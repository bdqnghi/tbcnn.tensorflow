package com.jcnlp.simrank.util;

import java.util.ArrayList;
import java.util.List;

import com.jcnlp.simrank.core.GenerateSim.NodeVal;

/**
 * This class is the complete and tested implementation of an AVL-tree.
 */
public class AvlTree {
	public int x_idx; // the index of the node on which treewand is performed
	public AvlNode root; // the root node

	/***************************** Core Functions ************************************/
	
	public AvlNode locatePivot(double theta){
		AvlNode curNode = root;
		AvlNode pivotNode = null;
//		int pivotDim = -1;
		while (curNode != null){
			if (curNode.leftSum + curNode.ub > theta){
//				pivotDim = curNode.dim;
				pivotNode = curNode;
				curNode = curNode.left;
			}
			else{
				theta = theta - curNode.leftSum - curNode.ub;
				curNode = curNode.right;
			}
		}
		return pivotNode;
	}

	
	/**
	 * Add a new element with key "k" into the tree.
	 * 
	 * @param k
	 *            The key of the new node.
	 */
	public void insert(List<NodeVal> inv_list, int dim, double ub_i)
	{
		if (inv_list.get(0).idx == x_idx){
			inv_list.remove(0);
		}
		if (inv_list.size() == 0){
			return;
		}
		int x = inv_list.get(0).idx; // x = top element's index
		
		AvlNode n = new AvlNode(x); // create new node
		n.inv_list = inv_list;
		n.dim = dim;
		n.ub = ub_i;
		n.nextNode = -1;
		if (inv_list.size() > 1){
			n.nextNode = inv_list.get(1).idx;
		}
		// start recursive procedure for inserting the node
		insertAVL(this.root, n);
	}

	/**
	 * Recursive method to insert a node into a tree.
	 * 
	 * @param p
	 *            The node currently compared, usually you start with the root.
	 * @param q
	 *            The node to be inserted.
	 */
	public void insertAVL(AvlNode p, AvlNode q) {
		// If node to compare is null, the node is inserted. If the root is
		// null, it is the root of the tree.
		if (p == null) {
			this.root = q;
		} else {

			// If compare node is smaller, continue with the left node
			if (q.topNode < p.topNode) {
				if (p.left == null) {
					p.left = q;
					q.parent = p;
					p.leftSum += q.ub;
					// Node is inserted now, continue checking the balance
					recursiveBalance(p);
				} else {
					p.leftSum += q.ub;
					insertAVL(p.left, q);
				}

			} else if (q.topNode > p.topNode) {
				if (p.right == null) {
					p.right = q;
					q.parent = p;

					// Node is inserted now, continue checking the balance
					recursiveBalance(p);
				} else {
					insertAVL(p.right, q);
				}
			} else{// p.topNode == q.topNode
				if (q.nextNode > p.nextNode) // the invList with largest second element goes to left
				{
					if (p.left == null) {
						p.left = q;
						q.parent = p;
						p.leftSum += q.ub;
						// Node is inserted now, continue checking the balance
						recursiveBalance(p);
					} else {
						p.leftSum += q.ub;
						insertAVL(p.left, q);
					}

			}
				else // otherwise, it goes right
				{
					if (p.right == null) {
						p.right = q;
						q.parent = p;
						// Node is inserted now, continue checking the balance
						recursiveBalance(p);
					} else {
						insertAVL(p.right, q);
					}
				}
			}
		}
	}

	/**
	 * Check the balance for each node recursivly and call required methods for
	 * balancing the tree until the root is reached.
	 * 
	 * @param cur
	 *            : The node to check the balance for, usually you start with
	 *            the parent of a leaf.
	 */
	public void recursiveBalance(AvlNode cur) {

		// we do not use the balance in this class, but the store it anyway
		int balance = getBalance(cur);

		// check the balance
		if (balance == -2) {

			if (getHeight(cur.left.left) >= getHeight(cur.left.right)) {
				cur = rotateRight(cur);
			} else {
				cur = doubleRotateLeftRight(cur);
			}
		} else if (balance == 2) {
			if (getHeight(cur.right.right) >= getHeight(cur.right.left)) {
				cur = rotateLeft(cur);
			} else {
				cur = doubleRotateRightLeft(cur);
			}
		}
		cur.setHeight();
		// we did not reach the root yet
		if (cur.parent != null) {
			recursiveBalance(cur.parent);
		} else {
			this.root = cur;
//			System.out
//					.println("------------ Balancing finished ----------------");
		}
	}
	
	public void recursiveBalance(AvlNode cur, double subtrahend) {
		if (cur.parent != null){
			cur.parent.leftSum -= subtrahend;
			if (cur != cur.parent.left){
				System.out
				.println("------------ Unexpected right child ----------------");
			}
		}
		// we do not use the balance in this class, but the store it anyway
		int balance = getBalance(cur);

		// check the balance
		if (balance == -2) {

			if (getHeight(cur.left.left) >= getHeight(cur.left.right)) {
				cur = rotateRight(cur);
			} else {
				cur = doubleRotateLeftRight(cur);
			}
		} else if (balance == 2) {
			if (getHeight(cur.right.right) >= getHeight(cur.right.left)) {
				cur = rotateLeft(cur);
			} else {
				cur = doubleRotateRightLeft(cur);
			}
		}
		cur.setHeight();
		// we did not reach the root yet
		if (cur.parent != null) {
			recursiveBalance(cur.parent, subtrahend);
		} else {
			this.root = cur;
		}
	}


	public AvlNode removeToSkip(){
		AvlNode LMnode = leftMost();
		if (LMnode != root){
			LMnode.parent.left = null; // delete leftmost node
			if (LMnode.right != null){ // Leftmost node can only have either a right child or none
				LMnode.right.parent = LMnode.parent; // change right child's parent
				LMnode.parent.left = LMnode.right; // change parent's left child
			}
			LMnode.parent.leftSum -= LMnode.ub;
			recursiveBalance(LMnode.parent, LMnode.ub);
		}
		else{
			if (LMnode.right != null){ // Leftmost node can only have either a right child or none
				LMnode.right.parent = null; // change right child's parent
				root = LMnode.right; // change parent's left child
			}
			else{
				root = null;
			}
		}
		return LMnode; // return the deleted leaf node
	}
	public AvlNode leftMost(){
		if (root == null){
			return null;
		}
		AvlNode cur_node = root;
		while (cur_node.left != null){
			cur_node = cur_node.left;
		}
		return cur_node;
	}

	/***************************** Helper Functions ************************************/
	/***********************************************************************************/
	/***********************************************************************************/
	/***********************************************************************************/
	/***********************************************************************************/
	/**
	 * Left rotation using the given node.
	 * 
	 * 
	 * @param n
	 *            The node for the rotation.
	 * 
	 * @return The root of the rotated tree.
	 */
	public AvlNode rotateLeft(AvlNode n) {

		AvlNode v = n.right;
		v.parent = n.parent;

		n.right = v.left;

		if (n.right != null) {
			n.right.parent = n;
		}

		v.left = n;
		n.parent = v;

		if (v.parent != null) {
			if (v.parent.right == n) {
				v.parent.right = v;
			} else if (v.parent.left == n) {
				v.parent.left = v;
			}
		}

		n.setHeight();
		v.setHeight();
		v.leftSum += n.leftSum + n.ub;
		return v;
	}

	/**
	 * Right rotation using the given node.
	 * 
	 * @param n
	 *            The node for the rotation
	 * 
	 * @return The root of the new rotated tree.
	 */
	public AvlNode rotateRight(AvlNode n) {

		AvlNode v = n.left;
		v.parent = n.parent;

		n.left = v.right;

		if (n.left != null) {
			n.left.parent = n;
		}

		v.right = n;
		n.parent = v;

		if (v.parent != null) {
			if (v.parent.right == n) {
				v.parent.right = v;
			} else if (v.parent.left == n) {
				v.parent.left = v;
			}
		}

		n.setHeight();
		v.setHeight();
		n.leftSum -= v.leftSum + v.ub; 
		return v;
	}

	/**
	 * 
	 * @param u
	 *            The node for the rotation.
	 * @return The root after the double rotation.
	 */
	public AvlNode doubleRotateLeftRight(AvlNode u) {
		u.left = rotateLeft(u.left);
		return rotateRight(u);
	}

	/**
	 * 
	 * @param u
	 *            The node for the rotation.
	 * @return The root after the double rotation.
	 */
	public AvlNode doubleRotateRightLeft(AvlNode u) {
		u.right = rotateRight(u.right);
		return rotateLeft(u);
	}



	/**
	 * Returns the successor of a given node in the tree (search recursivly).
	 * 
	 * @param q
	 *            The predecessor.
	 * @return The successor of node q.
	 */
	public AvlNode successor(AvlNode q) {
		if (q.right != null) {
			AvlNode r = q.right;
			while (r.left != null) {
				r = r.left;
			}
			return r;
		} else {
			AvlNode p = q.parent;
			while (p != null && q == p.right) {
				q = p;
				p = q.parent;
			}
			return p;
		}
	}

	
	


	private int getBalance(AvlNode cur) {
		return getHeight(cur.right) - getHeight(cur.left);
	}
	
	public int getHeight(AvlNode cur){
		if (cur == null){
			return -1;
		}
		else{
			return cur.height;
		}
	}
	/**
	 * Calculates the Inorder traversal of this tree.
	 * 
	 * @return A Array-List of the tree in inorder traversal.
	 */
	final protected ArrayList<AvlNode> inorder() {
		ArrayList<AvlNode> ret = new ArrayList<AvlNode>();
		inorder(root, ret);
		return ret;
	}

	/**
	 * Function to calculate inorder recursivly.
	 * 
	 * @param n
	 *            The current node.
	 * @param io
	 *            The list to save the inorder traversal.
	 */
	final protected void inorder(AvlNode n, ArrayList<AvlNode> io) {
		if (n == null) {
			return;
		}
		inorder(n.left, io);
		io.add(n);
		inorder(n.right, io);
	}
}
/**
 * Removes a node from the tree, if it is existent.
 */
//public void remove(int k) {
//	// First we must find the node, after this we can delete it.
//	removeAVL(this.root, k);
//}

/**
 * Finds a node and calls a method to remove the node.
 * 
 * @param p
 *            The node to start the search.
 * @param q
 *            The KEY of node to remove.
 */
//public void removeAVL(AvlNode p, int q) {
//	if (p == null) {
//		System.out.println("Node not found");
//		return;
//	} else {
//		if (p.topNode > q) {
//			removeAVL(p.left, q);
//		} else if (p.topNode < q) {
//			removeAVL(p.right, q);
//		} else if (p.topNode == q) {
//			// we found the node in the tree.. now lets go on!
//			removeFoundNode(p);
//		}
//	}
//}

/**
 * Removes a node from a AVL-Tree, while balancing will be done if
 * necessary.
 * 
 * @param q
 *            The node to be removed.
 */
//public void removeFoundNode(AvlNode q) {
//	AvlNode r;
//	// at least one child of q, q will be removed directly
//	if (q.left == null || q.right == null) {
//		// the root is deleted
//		if (q.parent == null) {
//			this.root = null;
//			q = null;
//			return;
//		}
//		r = q;
//	} else {
//		// q has two children --> will be replaced by successor
//		r = successor(q);
//		q.key = r.key;
//	}
//
//	AvlNode p;
//	if (r.left != null) {
//		p = r.left;
//	} else {
//		p = r.right;
//	}
//
//	if (p != null) {
//		p.parent = r.parent;
//	}
//
//	if (r.parent == null) {
//		this.root = p;
//	} else {
//		if (r == r.parent.left) {
//			r.parent.left = p;
//		} else {
//			r.parent.right = p;
//		}
//		// balancing must be done until the root is reached.
//		recursiveBalance(r.parent);
//	}
//	r = null;
//}

//
///**
// * Only for debugging purposes. Gives all information about a node.
// * 
// * @param n
// *            The node to write information about.
// */
//public void debug(AvlNode n) {
//	int l = 0;
//	int r = 0;
//	int p = 0;
//	if (n.left != null) {
//		l = n.left.key;
//	}
//	if (n.right != null) {
//		r = n.right.key;
//	}
//	if (n.parent != null) {
//		p = n.parent.key;
//	}
//
//	System.out.println("Left: " + l + " Key: " + n + " Right: " + r
//			+ " Parent: " + p + " Balance: " + getBalance(n));
//
//	if (n.left != null) {
//		debug(n.left);
//	}
//	if (n.right != null) {
//		debug(n.right);
//	}
//}
