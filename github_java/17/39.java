/**
 * Creates a BST where no node has two red links connected to it. 
 * Every path from root to null has the same number of black links. 
 * Red links lean left.
 * Based off the Princeton Algorithms code: http://algs4.cs.princeton.edu/33balanced/RedBlackBST.java.html
 */
package redblacktree;

import java.util.NoSuchElementException;

public class RedBlackTree<Key extends Comparable<Key>, Value> {
	private static final boolean RED = true;
	private static final boolean BLACK = false;

	private Node root;

	// node properties
	private class Node {
		private Key key;
		private Value val;
		private Node left, right;
		private boolean color; // color of the link to parent node

		Node(Key key, Value val) {
			this.key = key;
			this.val = val;
			this.color = RED;
		}
	}

	/**
	 * check if tree is empty
	 * 
	 * @return true if tree is empty
	 */
	public boolean isEmpty() {
		return root == null;
	}

	/**
	 * check if node is red
	 * 
	 * @param node
	 * @return true if node is red
	 */
	private boolean isRed(Node node) {
		if (node == null) {
			return false;
		}
		return node.color == RED;
	}

	private Node rotateLeft(Node node) {
		Node x = node.right;
		node.right = x.left;
		x.left = node;
		x.color = node.color;
		node.color = RED;
		return x;
	}

	private Node rotateRight(Node node) {
		Node x = node.left;
		node.left = x.right;
		x.right = node;
		x.color = node.color;
		node.color = RED;
		return x;
	}

	/**
	 * flip parent, left, and right node colors
	 * 
	 * @param node
	 */
	private void colorFlip(Node node) {
		node.color = !node.color;
		node.left.color = !node.left.color;
		node.right.color = !node.right.color;
	}

	public Value search(Key key) {
		Node x = root;
		while (x != null) {
			int cmp = key.compareTo(x.key);
			if (cmp == 0) {
				return x.val;
			} else if (cmp < 0) {
				x = x.left;
			} else if (cmp > 0) {
				x = x.right;
			}
		}
		return null;
	}

	public void insert(Key key, Value value) {
		root = insert(root, key, value);
		root.color = BLACK;
	}

	private Node insert(Node node, Key key, Value value) {
		if (node == null)
			return new Node(key, value);
		// move this line to the end of method to get 2-3 trees
		if (isRed(node.left) && isRed(node.right))
			colorFlip(node);
		int cmp = key.compareTo(node.key);
		if (cmp == 0) {
			node.val = value;
		} else if (cmp < 0) {
			node.left = insert(node.left, key, value);
		} else {
			node.right = insert(node.right, key, value);
		}
		return node;
	}

	private Node moveRedLeft(Node node) {
		colorFlip(node);
		if (isRed(node.right.left)) {
			node.right = rotateRight(node.right);
			node = rotateLeft(node);
			colorFlip(node);
		}
		return node;
	}

	private Node moveRedRight(Node node) {
		colorFlip(node);
		if (isRed(node.left.left)) {
			node = rotateRight(node);
			colorFlip(node);
		}
		return node;
	}

	public void delete(Key key) {
		root = delete(root, key);
		root.color = BLACK;
	}

	private Node delete(Node node, Key key) {
		if (key.compareTo(node.key) < 0) {
			if (!isRed(node.left) && !isRed(node.left.left)) {
				node = moveRedLeft(node);
			}
			node.left = delete(node.left, key);
		} else {
			if (isRed(node.left))
				node = rotateRight(node);
			if (key.compareTo(node.key) == 0 && (node.right == null))
				return null;
			if (!isRed(node.right) && !isRed(node.right.left))
				node = moveRedRight(node);
			if (key.compareTo(node.key) == 0) {
				node.val = get(node.right, min(node.right).key);
				node.key = min(node.right).key;
				node.right = deleteMin(node.right);
			} else {
				node.right = delete(node.right, key);
			}
		}
		return fixUp(node);
	}

	public Value get(Key key) {
		if (key == null)
			throw new NullPointerException("argument to get() is null");
		return get(root, key);
	}

	private Value get(Node node, Key key) {
		while (node != null) {
			int cmp = key.compareTo(node.key);
			if (cmp < 0) {
				node = node.left;
			} else if (cmp > 0) {
				node = node.right;
			} else {
				return node.val;
			}
		}
		return null;
	}

	public Key min() {
		if (isEmpty())
			throw new NoSuchElementException("called min( with empty table");
		return min(root).key;
	}

	private Node min(Node node) {
		if (node.left == null) {
			return node;
		} else {
			return min(node.left);
		}
	}

	private Node deleteMin(Node node) {
		if (node.left == null) {
			return null;
		}
		if (!isRed(node.left) && !isRed(node.left.left))
			node = moveRedLeft(node);
		node.left = deleteMin(node.left);
		return balance(node);
	}

	private Node balance(Node node) {
		// assert (h != null);

		if (isRed(node.right))
			node = rotateLeft(node);
		if (isRed(node.left) && isRed(node.left.left))
			node = rotateRight(node);
		if (isRed(node.left) && isRed(node.right))
			colorFlip(node);

		node.size = size(node.left) + size(node.right) + 1;
		return node;
	}

	public int rank(Key key) {
		if (key == null)
			throw new NullPointerException("argument to rank() is null");
		return rank(key, root);
	}

	private int rank(Key key, Node node) {
		if (node == null)
			return 0;
		int cmp = key.compareTo(node.key);
		if (cmp < 0)
			return rank(key, node.left);
		else if (cmp > 0)
			return 1 + size(node.left) + rank(key, node.right);
		else
			return size(node.left);
	}

	public int size(Key lo, Key hi) {
		if (lo == null)
			throw new NullPointerException("first argument to size() is null");
		if (hi == null)
			throw new NullPointerException("second argument to size() is null");

		if (lo.compareTo(hi) > 0)
			return 0;
		if (contains(hi))
			return rank(hi) - rank(lo) + 1;
		else
			return rank(hi) - rank(lo);
	}

}