package pucrs.alpro3.rbt;

import pucrs.alpro3.exceptions.DuplicateItemException;
import pucrs.alpro3.exceptions.ItemNotFoundException;

/**
* Implements a red black tree. Note that all "matching" is based on the
* compares method.
* 
* @author Mark Allen Weiss
*/
public class RedBlackTree {

	private static class BinaryNode {
		BinaryNode left;
		int color;
		BinaryNode right;
		Comparable element;

		BinaryNode(Comparable newData) {
			left = right = nullNode;
			element = newData;
			color = 1;
		}
	}

	static final class Rotations
	{
	    /**
	     * Rotate binary tree node with left child.
	     * For AVL trees, this is a single rotation for case 1.
	     */
	    static BinaryNode withLeftChild( BinaryNode k2 )
	    {
	        BinaryNode k1 = k2.left;
	        k2.left = k1.right;
	        k1.right = k2;
	        return k1;
	    }

	    /**
	     * Rotate binary tree node with right child.
	     * For AVL trees, this is a single rotation for case 4.
	     */
	    static BinaryNode withRightChild( BinaryNode k1 )
	    {
	        BinaryNode k2 = k1.right;
	        k1.right = k2.left;
	        k2.left = k1;
	        return k2;
	    }

	    /**
	     * Double rotate binary tree node: first left child
	     * with its right child; then node k3 with new left child.
	     * For AVL trees, this is a double rotation for case 2.
	     */
	    static BinaryNode doubleWithLeftChild( BinaryNode k3 )
	    {
	        k3.left = withRightChild( k3.left );
	        return withLeftChild( k3 );
	    }

	    /**
	     * Double rotate binary tree node: first right child
	     * with its left child; then node k1 with new right child.
	     * For AVL trees, this is a double rotation for case 3.
	     */
	    static BinaryNode doubleWithRightChild( BinaryNode k1 )
	    {
	        k1.right = withLeftChild( k1.right );
	        return withRightChild( k1 );
	    }
	}	
	
	/**
	 * Construct the tree.
	 * 
	 * @param negInf
	 *            a value less than or equal to all others.
	 */
	public RedBlackTree(Comparable negInf) {
		header = new BinaryNode(negInf);
	}

	/**
	 * Insert into the tree.
	 * 
	 * @param x
	 *            the item to insert.
	 * @exception DuplicateItem
	 *                if an item that matches x is already in the tree.
	 */
	public void insert(Comparable x) throws DuplicateItemException {
		current = parent = grand = header;
		nullNode.element = x;

		while (current.element.compareTo(x) != 0) {
			great = grand;
			grand = parent;
			parent = current;
			current = x.compareTo(current.element) < 0 ? current.left
					: current.right;

			// Check if two red children; fix if so
			if (current.left.color == RED && current.right.color == RED)
				handleReorient(x);
		}

		// Insertion fails if already present
		if (current != nullNode)
			throw new DuplicateItemException("RedBlackTree insert");
		current = new BinaryNode(x);

		// Attach to parent
		if (x.compareTo(parent.element) < 0)
			parent.left = current;
		else
			parent.right = current;
		handleReorient(x);
	}

	/**
	 * Remove from the tree. Not implemented in this version.
	 * 
	 * @param x
	 *            the item to remove.
	 * @exception ItemNotFound
	 *                if no item that matches x can be found in the tree.
	 */
	public void remove(Comparable x) throws ItemNotFoundException {
		System.out.println("Remove is not implemented");
	}

	/**
	 * Remove the smallest item from the tree. Not implemented in this version.
	 * 
	 * @exception ItemNotFound
	 *                if the tree is empty.
	 */
	public void removeMin() throws ItemNotFoundException {
		System.out.println("RemoveMin is not implemented");
	}

	/**
	 * Find the smallest item the tree.
	 * 
	 * @return the smallest item.
	 * @exception ItemNotFound
	 *                if the tree is empty.
	 */
	public Comparable findMin() throws ItemNotFoundException {
		if (isEmpty())
			throw new ItemNotFoundException("RedBlackTree findMin");

		BinaryNode itr = header.right;

		while (itr.left != nullNode)
			itr = itr.left;

		return itr.element;
	}

	/**
	 * Find the largest item in the tree.
	 * 
	 * @return the largest item.
	 * @exception ItemNotFound
	 *                if the tree is empty.
	 */
	public Comparable findMax() throws ItemNotFoundException {
		if (isEmpty())
			throw new ItemNotFoundException("RedBlackTree findMax");

		BinaryNode itr = header.right;

		while (itr.right != nullNode)
			itr = itr.right;

		return itr.element;
	}

	/**
	 * Find an item in the tree.
	 * 
	 * @param x
	 *            the item to search for.
	 * @return the matching item.
	 * @exception ItemNotFound
	 *                if no item that matches x can be found in the tree.
	 */
	public Comparable find(Comparable x) throws ItemNotFoundException {
		nullNode.element = x;
		current = header.right;

		for (;;) {
			if (x.compareTo(current.element) < 0)
				current = current.left;
			else if (current.element.compareTo(x) < 0)
				current = current.right;
			else if (current != nullNode)
				return current.element;
			else
				throw new ItemNotFoundException("RedBlackTree find");
		}
	}

	/**
	 * Make the tree logically empty.
	 */
	public void makeEmpty() {
		header.right = nullNode;
	}

	/**
	 * Test if the tree is logically empty.
	 * 
	 * @return true if empty, false otherwise.
	 */
	public boolean isEmpty() {
		return header.right == nullNode;
	}

	/**
	 * Print the tree contents in sorted order.
	 */
	public void printTree() {
		if (header.right == null)
			System.out.println("Empty tree");
		else
			printTree(header.right);
	}

	/**
	 * Internal method to print a subtree in sorted order.
	 * 
	 * @param t
	 *            the node that roots the tree.
	 */
	private void printTree(BinaryNode t) {
		if (t != t.left) {
			printTree(t.left);
			System.out.println(t.element.toString());
			printTree(t.right);
		}
	}

	/**
	 * Internal routine that is called during an insertion if a node has two red
	 * children. Performs flip and rotatons.
	 * 
	 * @param item
	 *            the item being inserted.
	 */
	private void handleReorient(Comparable item) {
		// Do the color flip
		current.color = RED;
		current.left.color = BLACK;
		current.right.color = BLACK;

		if (parent.color == RED) // Have to rotate
		{
			grand.color = RED;
			if (item.compareTo(grand.element) < 0 != item.compareTo(parent.element) < 0)
				parent = rotate(item, grand); // Start dbl rotate
			current = rotate(item, great);
			current.color = BLACK;
		}
		header.right.color = BLACK; // Make root black
	}

	/**
	 * Internal routine that performs a single or double rotation. Because the
	 * result is attached to the parent, there are four cases. Called by
	 * handleReorient.
	 * 
	 * @param item
	 *            the item in handleReorient.
	 * @param parent
	 *            the parent of the root of the rotated subtree.
	 * @return the root of the rotated subtree.
	 */
	private BinaryNode rotate(Comparable item, BinaryNode parent) {
		if (item.compareTo(parent.element) < 0)
			return parent.left = item.compareTo(parent.left.element) < 0? Rotations
					.withLeftChild(parent.left) : // LL
					Rotations.withRightChild(parent.left); // LR
		else
			return parent.right = item.compareTo(parent.right.element) < 0 ? Rotations
					.withLeftChild(parent.right) : // RL
					Rotations.withRightChild(parent.right); // RR
	}

	private BinaryNode header;
	private static BinaryNode nullNode;
	static // Static initializer for nullNode
	{
		nullNode = new BinaryNode(null);
		nullNode.left = nullNode.right = nullNode;
	}

	private static final int BLACK = 1; // Black must be 1
	private static final int RED = 0;

	// Used in insert routine and its helpers
	private static BinaryNode current;
	private static BinaryNode parent;
	private static BinaryNode grand;
	private static BinaryNode great;

	// Test program; should print min and max and nothing else
	public static void main(String[] args) {
		RedBlackTree t = new RedBlackTree(new Integer(Integer.MIN_VALUE));
		final int NUMS = 4;
		final int GAP = 1;

		System.out.println("Checking... (no more output means success)");

//		try {
//			for (int i = GAP; i != 0; i = (i + GAP) % NUMS)
//				t.insert(new Integer(i));
//
//			if (NUMS < 40)
//				t.printTree();
//			if (((Integer) (t.findMin())).intValue() != 1
//					|| ((Integer) (t.findMax())).intValue() != NUMS - 1)
//				System.out.println("FindMin or FindMax error!");
//
//			for (int i = 2; i < NUMS; i += 2)
//				if (((Integer) (t.find(new Integer(i)))).intValue() != i)
//					System.out.println("Error! at " + i);
//			try {
//				t.find(new Integer(0));
//				System.out.println("OOPS -- 0");
//			} catch (ItemNotFoundException e) {
//			}
//		} catch (DuplicateItemException e) {
//			System.out.println(e);
//		} catch (ItemNotFoundException e) {
//			System.out.println(e);
//		}
	}
}


