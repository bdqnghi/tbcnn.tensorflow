/**
 * CS 146 Project 2
 * @author Harkamal Grewal
 * @author Gurpreet Singh
 */
public class AVLTree<T extends Comparable<Integer>> extends
		BinarySearchTree<Integer> {

	private static final int ALLOWED_IMBALANCE = 1; // Maximum allowed difference between the height of the left and right sub-tree.

	/**
	 * Constructs an AVL tree with the given root.
	 */
	public AVLTree() {
		super.root = null;
	}

	/**
	 * Calculates the Height of the given node
	 * @return Returns the height of node t, or -1 if null.
	 */
	protected int height(BinaryNode<Integer> t) {
		return t == null ? -1 : t.height;
	}

	/**
	 * Inserts the integer into the tree
	 * @param x the integer to be inserted in the tree
	 */
	public void insert(Integer x) {
		super.root = balance(insert(x, super.root)); // Recursive call to the helper method
	}
	
	/**
	 * Helper method for insert method.
	 * @param x the integer to be inserted 
	 * @param t the node to insert the value in.
	 * @return the node with value inserted
	 */
	protected BinaryNode<Integer> insert(Integer x, BinaryNode<Integer> t) {
		if (t == null)
			return new BinaryNode<Integer>(x, null, null);

		int compareResult = x.compareTo(t.element);

		if (compareResult < 0) {
			t.left = insert(x, t.left);
		} else if (compareResult > 0) {
			t.right = insert(x, t.right);
		} else {
			;
		}
		return balance(t);

	}
 
	/**
	 * Removes the given value from the tree
	 * @param x  the value to be removed
	 */
	public void remove(Integer x) {
		super.root = balance(super.remove(x, super.root)); // Calls the super class remove method
	}

	/**
	 * Checks if the tree is unbalanced and then balances it
	 * @param t the node to check
	 * @return the balanced node of the tree
	 */
	private BinaryNode<Integer> balance(BinaryNode<Integer> t) {
		if (t == null) {
			return t;
		}
		if (height(t.left) - height(t.right) > ALLOWED_IMBALANCE) {
			if (height(t.left.left) >= height(t.left.right)) {
				t = singleRightRotation(t);
			} else {
				t = doubleLeftRightRotation(t);
			}
		} else {
			if (height(t.right) - height(t.left) > ALLOWED_IMBALANCE) {
				if (height(t.right.right) >= height(t.right.left)) {
					t = singleLeftRotation(t);
				} else {
					t = doubleRightLeftRotation(t);
				}
			}
			t.height = Math.max(height(t.left), height(t.right)) + 1;
		}
		return t;
	}
    
	/**
	 * Rotates the binary node with right child.
	 * Single rotation for case 2. updates height and then returns it.
	 * @param k2 the node to be rotated
	 * @return the rotated tree
	 */
	private BinaryNode<Integer> singleRightRotation(BinaryNode<Integer> k2) {
		BinaryNode<Integer> k1 = k2.getLeft();
		k2.setLeft(k1.getRight());
		k1.setRight(k2);
		k2.setHeight(Math.max(height(k2.getLeft()), height(k2.getRight())) + 1);
		k1.setHeight(Math.max(height(k1.getLeft()), k2.getHeight()) + 1);
		System.out.println("Single Right Rotation : " + k2.element);
		return k1;
	}
	
	/**
	 * Performs the left-right rotation. Case 3.
	 * @param k3 the node to be rotated
	 * @return the balanced node
	 */

	private BinaryNode<Integer> doubleLeftRightRotation(BinaryNode<Integer> k3) {
		k3.setLeft(singleLeftRotation(k3.getLeft()));
		System.out.println("Double Left-Right Rotation : " + k3.element);
		return singleRightRotation(k3);
	}
     
	/**
	 * Performs the single left rotation. Case 1
	 * @param k1 the node to be rotated 
	 * @return the balanced node
	 */
	private BinaryNode<Integer> singleLeftRotation(BinaryNode<Integer> k1) {
		BinaryNode<Integer> k2 = k1.getRight();
		k1.setRight(k2.getLeft());
		k2.setLeft(k1);
		k1.setHeight(Math.max(height(k1.getLeft()), height(k1.getRight())) + 1);
		k2.setHeight(Math.max(height(k2.getRight()), k1.getHeight()) + 1);
		System.out.println("Single Left Rotation : " + k1.element);
		return k2;
	}
	
    /**
     * Performs the right-left rotation of the given node
     * @param k1 the node to be rotated 
     * @return the balanced node
     */
	private BinaryNode<Integer> doubleRightLeftRotation(BinaryNode<Integer> k1) {
		k1.setRight(singleRightRotation(k1.getRight()));
		System.out.println("Double Right-Left Rotation : " + k1.element);
		return singleLeftRotation(k1);
	}

	/**
     * Checks for a given value in the tree
     * @param x the value to look up for in the tree
     * @return true if the value is in the tree
     */
	public boolean contains(Integer x) {
		return contains(x, root);
	}
    
	/**
	 * Recursive helper method for contains method
	 * @param x the value to find
	 * @param t the node to find the value in
	 * @return true or false
	 */ 
	private boolean contains(Integer x, BinaryNode<Integer> t) {
		if (t == null) {
			return false;
		}
		int compareResult = x.compareTo(t.element);
		if (compareResult < 0) {
			return contains(x, t.left);
		} else if (compareResult > 0) {
			return contains(x, t.right);
		} else {
			return true; // Match
		}
	}
}