package com.fbehrens.dsal.trees;

import com.fbehrens.dsal.Map;

/**
 * In an AVL treenode additional the height of the corresponding subtree is
 * stored. (If it would have to be computed then the comparing heights would be
 * too expensive).
 * 
 * @author Rossmanith
 *
 * @param <K>
 *            Type of the keys.
 * @param <D>
 *            Type of the data.
 */
class AVLtreenode<K extends Comparable<K>, D> extends Searchtreenode<K, D> {
	/**
	 * The height of the tree represented by this node.
	 */
	int h;

	/**
	 * Creates a new node with key k and data d.
	 * 
	 * @param k
	 *            The key for the new node.
	 * @param d
	 *            The data for the new node.
	 */
	public AVLtreenode(K k, D d) {
		super(k, d);
	}

	/**
	 * Returns the height of the given node (constant time).
	 * 
	 * @param n
	 *            The node which represents the tree of which the height should
	 *            be determined.
	 * @return 0, if n is null, and the height of the tree represented by the
	 *         node n, otherwise.
	 */
	static int height(Searchtreenode<?, ?> n) {
		return n == null ? 0 : ((AVLtreenode<?, ?>) n).h;
	}

	/*
	 * Note that after rotation the heights of nodes a,t,p and above p have to
	 * be updated. In this implementation, the height of p and its parents is
	 * not updated, but it is only done inside the rebalance method. Therefore,
	 * make sure that other methods which use rotate always make a call to
	 * rebalance afterwards!
	 * 
	 * Additionally as in Searchtreenode, the repair_root()-method should be
	 * used to recompute the new root of a tree. The same applies for
	 * rotateright.
	 */
	void rotateleft() {
		super.rotateleft();
		computeheight();
		((AVLtreenode<K, D>) parent).computeheight();
	}

	/*
	 * See comment of rotateleft about height-updates and root-repair.
	 */
	void rotateright() {
		super.rotateright();
		computeheight();
		((AVLtreenode<K, D>) parent).computeheight();
	}

	/**
	 * Recomputes the height of this node (constant time).
	 */
	void computeheight() {
		this.h = 1;
		int a = height(this.left) + 1;
		int b = height(this.right) + 1;
		if (a > this.h)
			this.h = a;
		if (b > this.h)
			this.h = b;
	}

	/**
	 * Restores the balances in all nodes above this node by doing rotations.
	 * 
	 * However, before this operation all nodes above this node must be
	 * unbalanced by at most 2 levels, otherwise balance will not necessarily be
	 * present after this call.
	 */
	void rebalance() {
		computeheight();
		if (height(left) > height(right) + 1) {
			if (height(left.left) < height(left.right))
				left.rotateleft();
			rotateright();
		} else if (height(right) > height(left) + 1) {
			if (height(right.right) < height(right.left))
				right.rotateright();
			rotateleft();
		}
		if (parent != null)
			((AVLtreenode<K, D>) parent).rebalance();
	}

	/**
	 * Deletes this node. Must not be called if this is the root and if the root
	 * is a leaf.
	 */
	/*
	 * Note that deletions involve rotations in the rebalance-routine, so
	 * afterwards a repair_root() is required.
	 */
	void delete() {
		if (left == null && right == null) {
			/*
			 * leaf case => this is not the root => parent is always non-null
			 */
			if (parent.left == this)
				parent.left = null;
			else
				parent.right = null;
			((AVLtreenode<K, D>) parent).rebalance();
		} else if (left == null) {
			/*
			 * copy data from right node into this, if there is no left subtree
			 */
			copy(right);
			if (right.left != null)
				right.left.parent = this;
			if (right.right != null)
				right.right.parent = this;
			left = right.left;
			right = right.right;
			rebalance();
		} else {
			/*
			 * if there is left subtree, find node "max" with largest value in
			 * left subtree. Then copy data from max into this, and finally
			 * delete max-node.
			 */
			Searchtreenode<K, D> max = left;
			while (max.right != null)
				max = max.right;
			copy(max);
			max.delete();
		}
	}

	/**
	 * Returns true iff the tree represented by this node satisfies the AVL
	 * property, i.e., heights of left- and right subtree differ at most by one.
	 */
	boolean check_balance() {
		int l = height(left);
		int r = height(right);
		if (l < r - 1 || r < l - 1)
			return false;
		return (left == null || ((AVLtreenode<K, D>) left).check_balance())
				&& (right == null || ((AVLtreenode<K, D>) right).check_balance());
	}

	/**
	 * Returns true iff the heights in the nodes have the right values.
	 */
	boolean check_heights() {
		if (left != null) {
			if (!((AVLtreenode<?, ?>) left).check_heights()) {
				return false;
			}
		}
		if (right != null) {
			if (!((AVLtreenode<?, ?>) right).check_heights()) {
				return false;
			}
		}
		int h = 1 + Math.max(height(left), height(right));
		return this.h == h;
	}
}

/**
 * An AVL-tree is an always balanced tree. To be more precise, for each node in
 * the tree the heights of the two subtrees differ by at most 1. Thus, the
 * height of an AVL-tree containing n elements is always about log(n). Thus, all
 * default operations like insertion ({@link #insert(Comparable, Object)}),
 * removal ({@link #delete(Comparable)}), lookup ({@link #find(Comparable)}),
 * ... have at most logarithmic costs.
 * 
 * @author Rossmanith
 *
 * @param <K>
 *            Type of the keys.
 * @param <D>
 *            Type of the data.
 * @see Map
 */
public class AVLtree<K extends Comparable<K>, D> extends Searchtree<K, D> {

	public void insert(K k, D d) {
		if (root == null)
			root = new AVLtreenode<K, D>(k, d);
		else
			root.insert(new AVLtreenode<K, D>(k, d));
		/*
		 * after (standard) insertion one just has to rebalance the
		 * corresponding node and all the nodes above.
		 */
		((AVLtreenode<K, D>) root.findsubtree(k)).rebalance();
		repair_root();
	}

	public void delete(K k) {
		if (root == null)
			return;
		AVLtreenode<K, D> n;
		n = (AVLtreenode<K, D>) root.findsubtree(k);
		if (n == null)
			return;
		/*
		 * special case for deleting the last element of a tree, see
		 * AVLtreenode.delete().
		 */
		if (n == root && n.left == null && n.right == null)
			root = null;
		else
			n.delete();
		/*
		 * as deleting involves rotations we have to call repair_root
		 */
		repair_root();
	}

}
