/*
 * AVLTree.java
 *
 * AVL-Tree implementation.
 *
 * F.Moon   -   Oct.5, 2016
 */

/*
 * TODO:
 *	1) helper methods.
 *	2) rotate methods.
 *	3) insert method.
 *	4) tree traversal.
 */

public class AVLTree {

	/* --- DATA FIELD --- */
	AVLNode root;

	/* Constructor */
	public AVLTREE () {
		this.root = null;
	}

	/**
	 * insert (int key)
	 * insert key into AVL-Tree.
	 */
	public void insert (int key) {
		AVLNode newNode = new AVLNode(key);
		insert(root, newNode);
	}
	
	private void insert (AVLNode root, AVLNode newNode) {
		
		/* empty tree */
		if (root == null) {
			this.root = newNode;
		} else {
			if (root.key > newNode.key) {
				/* go left */
				if (root.left == null) {
					/* insertion point found
					 * insert, set parent
					 * then restructure on the way way of stack */
					root.left = newNode;
					newNode.parent = root;
					restructure(root);
				} else {
					insert(root.left, newNode);
				}
			} else if (root.key < newNode.key) {
				/* go right */
				if (root.right == null) {
					/* insertion point found 
					 * insert, set parent
					 * then restructure */
					root.right = newNode;
					newNode.parent = root;
					restructure(root);
				} else {
					insert(root.right, newNode);
				}
			} else { /* nothing root.key == newNode.key */ }
		}
	}

	/** TODO
	 * restructure (AVLNode node)
	 * as we work way out of the recursive insertion track, we will constantly
	 * update, and check the balance factor of each nodes.
	 * depending on the balance factor computed, it determines 4 cases of rotations
	 */
	public void restructure (AVLNode node) {
		/* compute BF of current Node */
		compute_BF(node);
	
		/* 4 cases: */
		/* -2 or +2 indicates first imbalnced node. Check left/right 
		 * child's balance_factor 
		 */
		if (node.balance_factor == -2) {
			/* case A : left subtree is longer */
			if (node.left.balance_factor < 0) {
				/* case A-1 : straight */
				node = rotateRight(node);
			} else {
				/* case A-2 : crooked */
				node = rotateLeftRight(node);
			}
		} else if (node.balance_factor == 2) {
			/* case B : right subtree is longer */
			if (node.right.balance_factor > 0) {
				/* case B-1 : straight */
				node = rotateLeft(node);
			} else {
				/* case B-2 : crooked */
				node = rotateRightLeft(node);
			}
		}

		/* Confirm whether the node returned after rotation is root of the AVL-Tree */
		if (node.parent == null) {
			this.root = node;
		}
	}

	/**
	 * height (AVLNode node)
	 * compute the height of current node 
	 */
	public int height (AVLNode node) {
		if (node == null) return 0;
		return Math.max(height(node.left), height(node.right)) + 1;
	}

	/**
	 * compute_bf (AVLNode node)
	 * compute the node's current balance_factor.
	 * balance_factor = (height of right subtree - height of left subtree)
	 */
	private void compute_bf (AVLNode node) {
		node.balanced_factor = height(node.right) - height(node.left);
	}

	/* --- Rotation Methods --- */
	/* Should return new root to be checked whether it is the root of the
	 * entire AVL-Tree.
	 */

	/** TODO
	 * rotateRight (AVLNode node)
	 * rotateRight.
	 */
	public AVLNode rotateRight (AVLNode node) { return node; }

	/** TODO
	 * rotateLeft (AVLNode node)
	 * rotateLeft.
	 */
	public AVLNode rotateLeft (AVLNode node) { return node; }

	/** TODO
	 * rotateLeftRight (AVLNode node)
	 * rotateLeft; then rotateRight.
	 */
	public AVLNode rotateLeftRight (AVLNode node) { return node; }

	/** TODO
	 * rotateRightLeft (AVLNode node)
	 * rotateRight; then rotateLeft.
	 */
	public AVLNode rotateRightLeft (AVLNode node) { return node; }

	/* --- Traversal Methods --- */

	/**
	 * preorder ()
	 */
	public void preorder () { preorder(root); }
	private void preoder (AVLNode node) {
		if (node != null) {
			System.out.print(node.key + " ");
			preorder(node.left);
			preorder(node.right);
		}
	}

	/**
	 * inorder ()
	 */
	public void inorder () { inorder(root); }
	private void inoder (AVLNode node) {
		if (node != null) {
			inorder(node.left);
			System.out.print(node.key + " ");
			inorder(node.right);
		}
	}

	/**
	 * postorder ()
	 */
	public void postorder () { postorder(root); }
	private void postoder (AVLNode node) {
		if (node != null) {
			postorder(node.left);
			postorder(node.right);
			System.out.print(node.key + " ");
		}
	}

	/** 
	 * main()
	 * internal testing purposes only.
	 */
	public static void main (String[] args) {}
}
