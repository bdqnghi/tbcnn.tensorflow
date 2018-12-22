/*
 * Created on 09.04.2005
 *
 *
 */
package org.visnacom.model;

import java.util.*;
import java.math.BigInteger;

/**
 * @author F. Pfeiffer
 * 
 * This class implements an AVL Tree according to Goodrich, ...
 */
public class AVLTree {

	// root of AVLTree
	private AVLNode root;

	// node which is affected by current action
	private AVLNode action;

	// comparator for ordering of nodes
	private Comparator comp;

	// determines whether tree is empty
	private boolean isEmpty = true;

	// maps elements to number of occurencies in tree
	private HashMap multiplicity;

	// maps elements to edges causing element to be stored in tree
	public HashMap edges;

	// list for elements
	private DLL inorder;

	/**
	 * Constructor.
	 * 
	 * @param c
	 *            Comparator used in AVLTree.
	 */
	public AVLTree(Comparator c) {
		root = new AVLNode(null, null, 1);
		comp = c;
		multiplicity = new HashMap();

		edges = new HashMap();

		inorder = new DLL();
	}

	/**
	 * Calculates height of subtree rooted at given node.
	 * 
	 * @param n
	 *            Root of subtree.
	 * @return Height of subtree.
	 */
	private int height(AVLNode n) {
		if (n == null) {
			return 0;
		}
		return n.getHeight();
	}

	/**
	 * Sets height of subtree rooted at given node.
	 * 
	 * @param n
	 *            Root of subtree.
	 */
	private void setHeight(AVLNode n) {
		n.setHeight(1 + Math.max(height(n.getLeft()), height(n.getRight())));
	}

	/**
	 * Checks if node is balanced.
	 * 
	 * @param n
	 *            The node to be checked for being balanced.
	 * @return True if node is balanced, false otherwise.
	 */
	private boolean isBalanced(AVLNode n) {
		int balanceFactor = height(n.getLeft()) - height(n.getRight());
		return ((-1 <= balanceFactor) && (balanceFactor <= 1));
	}

	/**
	 * Gets the taller child of a given node.
	 * 
	 * @param n
	 *            The node for the child of which one is looking.
	 * @return The taller child.
	 */
	private AVLNode tallerChild(AVLNode n) {
		if (height(n.getLeft()) >= height(n.getRight())) {
			return n.getLeft();
		}
		return n.getRight();
	}

	/**
	 * Inserts an object into tree. Number of occurencies and edges can be
	 * specified.
	 * 
	 * @param o
	 *            The object to be inserted.
	 * @param mult
	 *            The number of occurencies.
	 * @param c
	 *            Collection of edges.
	 */
	public void insert(Object o, BigInteger mult, Collection c) {
		if (!mult.equals(new BigInteger("0", 2))) {
			insert(o);
			BigInteger bInt = (BigInteger) multiplicity.get(o);
			BigInteger newMult = bInt
					.add(mult.subtract(new BigInteger("1", 2)));
			multiplicity.put(o, newMult);
		}
		Collection collO = (Collection) edges.get(o);
		if (collO == null) {
			edges.put(o, c);
		} else {
			collO.addAll(c);
		}
	}

	/**
	 * Inserts an object into tree. Edges can be specified.
	 * 
	 * @param o
	 *            The object to be inserted.
	 * @param edge
	 *            Corresponding edge.
	 */
	public void insert(Object o, Edge edge) {

		DLL t = (DLL) edges.get(o);
		if (t == null) {
			DLL newSet = new DLL();
			newSet.add(edge);
			edges.put(o, newSet);
		} else {
			t.add(edge);
		}
		insert(o);
	}

	/**
	 * Inserts new object into tree.
	 * 
	 * @param o
	 *            The object to be inserted.
	 */
	public void insert(Object o) {
		// if element is already stored, its number of occurencies is updated
		Object rem = multiplicity.get(o);
		// indicates whether new object has been inserted into tree
		boolean newNode = false;
		// flags indication whether new object is largest or smallest element
		boolean largestElement = true;
		boolean smallestElement = true;
		AVLNode insert = null;
		if (rem == null) {
			multiplicity.put(o, new BigInteger("1", 2));
		} else {
			BigInteger remInt = (BigInteger) rem;
			multiplicity.put(o, remInt.add(new BigInteger("1", 2)));
		}

		isEmpty = false;
		// insertion into empty tree handled specially
		if (root.getElement() == null) {
			root.setElement(o);
			//			newNode = true;
			insert = root;
			inorder.add(o);
		} else {
			AVLNode current = root;
			AVLNode next = root;
			// traverses tree in order to find correct position in tree
			while (next != null) {
				if (comp.compare(current.getElement(), o) < 0) {
					smallestElement = false;
					next = current.getRight();
					if (next == null) {
						insert = new AVLNode(o, current, 1);
						current.setRight(insert);
						newNode = true;
					}
				} else if (comp.compare(current.getElement(), o) > 0) {
					largestElement = false;
					next = current.getLeft();
					if (next == null) {
						insert = new AVLNode(o, current, 1);
						current.setLeft(insert);
						newNode = true;
					}
				} else {
					break;
				}
				if (next != null) {
					current = next;
				}
			}
			if (insert != null) {
				//rebalances tree
				rebalance(insert);
			}
		}

		// updates largest element and inserts new element into
		// internal dll
		if (newNode) {
			if (largestElement) {
				inorder.addPred(null, o);
			} else if (smallestElement) {
				inorder.addSucc(null, o);
			} else {
				AVLNode s = (AVLNode) succ(o, true, true);
				if (s != null) {
					inorder.addPred(s.element, o);
				}
			}
		}
	}

	/**
	 * Rebalances node.
	 * 
	 * @param n
	 *            The node which is not balanced.
	 */
	private void rebalance(AVLNode n) {
		while (n != null) {
			setHeight(n);
			if (n.getLeft() != null) {
				setHeight(n.getLeft());
			}
			if (n.getRight() != null) {
				setHeight(n.getRight());
			}

			if (!isBalanced(n)) {
				AVLNode x = tallerChild(tallerChild(n));
				n = restructure(x);
				setHeight(n.getLeft());
				setHeight(n.getRight());
				setHeight(n);
			}
			n = n.getParent();
		}
	}

	/**
	 * Restructures AVL node. Used for rebalancing.
	 * 
	 * @param x
	 *            The node to be restructured.
	 * @return AVLNode.
	 */
	private AVLNode restructure(AVLNode x) {

		// used for sorting elements
		TreeSet inorderNodes = new TreeSet(new AVLComparator());
		LinkedList inorderTrees = new LinkedList();

		AVLNode y = x.getParent();
		AVLNode z = y.getParent();

		AVLNode a = x;
		AVLNode b = y;
		AVLNode c = z;

		inorderNodes.add(x);
		inorderNodes.add(y);
		inorderNodes.add(z);

		Iterator it = inorderNodes.iterator();
		int count = 0;
		while (it.hasNext()) {
			AVLNode n = (AVLNode) it.next();
			if (count == 0) {
				a = n;
			} else if (count == 1) {
				b = n;
			} else if (count == 2) {
				c = n;
			}
			AVLNode left = n.getLeft();
			AVLNode right = n.getRight();
			if (left != x && left != y && left != z) {
				inorderTrees.add(left);
			}
			if (right != x && right != y && right != z) {
				inorderTrees.add(right);
			}
			count++;
		}

		AVLNode parentZ = z.getParent();
		if (parentZ != null) {
			if (parentZ.getLeft() == z) {
				parentZ.setLeft(b);
			} else {
				parentZ.setRight(b);
			}
		}

		// sets new pointers
		b.setParent(parentZ);
		b.setLeft(a);
		b.setRight(c);
		a.setParent(b);
		c.setParent(b);

		// iterates node in sorted order, and sets new pointers, accordind to
		// Goodrich
		it = inorderTrees.iterator();
		count = 0;
		while (it.hasNext()) {
			AVLNode n = (AVLNode) it.next();
			if (count == 0) {
				a.setLeft(n);
				if (n != null) {
					n.setParent(a);
				}
			} else if (count == 1) {
				a.setRight(n);
				if (n != null) {
					n.setParent(a);
				}
			} else if (count == 2) {
				c.setLeft(n);
				if (n != null) {
					n.setParent(c);
				}
			} else if (count == 3) {
				c.setRight(n);
				if (n != null) {
					n.setParent(c);
				}
			}
			count++;
		}
		if (root == z) {
			root = b;
		}
		return b;
	}

	/**
	 * Finds AVL node containing given object.
	 * 
	 * @param o
	 *            The object to be looked for.
	 * @return The AVL node containing the given object.
	 */
	private AVLNode find(Object o) {
		AVLNode current = root;
		if (isEmpty) {
			return null;
		}
		while (current != null) {
			Object element = current.getElement();
			if (o == element) {
				return current;
			}
			if (comp.compare(element, o) < 0) {
				current = current.getRight();
			} else if (comp.compare(element, o) > 0) {
				current = current.getLeft();
			}
		}
		return null;
	}

	/**
	 * Checks whether an object is contained in tree.
	 * 
	 * @param o
	 *            The object to be looked for.
	 * @return True if object is contained, false otherwise.
	 */
	public boolean contains(Object o) {
		return (find(o) != null);
	}

	/**
	 * Removes object and edge which is causing object to be contained in tree.
	 * 
	 * @param o
	 *            The object to be removed.
	 * @param edge
	 *            The edge to be removed.
	 * @return The removed object.
	 */
	public Object remove(Object o, Edge edge) {
		DLL t = (DLL) edges.get(o);
		if (t != null) {
			t.remove(edge);
		}
		Object res = remove(o);
		assert (!(contains(o) && getEdges(o).isEmpty()));
		return res;
	}

	/**
	 * Removes object and edges which are causing object to be contained in
	 * tree.
	 * 
	 * @param o
	 *            The object to be removed.
	 * @param edgs
	 *            The edges to be removed.
	 * @return The removed object.
	 */
	public Object remove(Object o, Collection edgs) {
		DLL t = (DLL) edges.get(o);
		if (t != null) {
			t.removeAll(edgs);
		}
		Object res = remove(o);
		return res;
	}

	/**
	 * Removes an element from tree.
	 * 
	 * @param o
	 *            The object to be removed.
	 * @return The removed object.
	 */
	public Object remove(Object o) {
		if (isRemovable(o)) {
			multiplicity.remove(o);

			// gets position of object to be removed
			AVLNode rem = find(o);

			// tree consists only of root element
			if (rem == root && root.getLeft() == null
					&& root.getRight() == null) {
				root.setElement(null);
				isEmpty = true;
				inorder.remove(o);
				return o;
			}
			AVLNode replace = rem;
			if (rem == null) {
				return null;
			}

			// get element to be placed at position of deleted one
			if (rem.getLeft() != null && rem.getRight() != null) {
				AVLNode swap = rem;
				rem = swap.getRight();
				while (rem.getLeft() != null) {
					rem = rem.getLeft();
				}
			}
			replace.setElement(rem.getElement());
			removeAboveEx(rem);
			rebalance(action);
			inorder.remove(o);
			return o;
		}
		decrement(o);
		return null;
	}

	/**
	 * Deletes external node in AVLTree. (external node = node with at most one
	 * child)
	 * 
	 * @param rem
	 *            External node to be removed.
	 */
	private void removeAboveEx(AVLNode rem) {
		// root is only node
		if (rem == root && root.getLeft() == null && root.getRight() == null) {
			root.setElement(null);
			action = root;

			// root to be deleted,root has left child
		} else if (rem == root && root.getLeft() != null) {
			root.setElement(root.getLeft().getElement());
			root.setLeft(null);
			action = root;

			// root to be deleted,root has right child
		} else if (rem == root && rem.getRight() != null) {
			root.setElement(root.getRight().getElement());
			root.setRight(null);
			action = root;

			// deleted node is not root
		} else {
			AVLNode parent = rem.getParent();

			// external node has a right child
			if (rem.getLeft() == null && rem.getRight() != null) {
				action = rem.getRight();
				if (rem == parent.getLeft()) {
					parent.setLeft(rem.getRight());
					rem.getRight().setParent(parent);
				} else {
					parent.setRight(rem.getRight());
					rem.getRight().setParent(parent);
				}

				// external node has a left child
			} else if (rem.getRight() == null && rem.getLeft() != null) {
				action = rem.getLeft();
				if (rem == parent.getLeft()) {
					parent.setLeft(rem.getLeft());
					rem.getLeft().setParent(parent);
				} else {
					parent.setRight(rem.getLeft());
					rem.getLeft().setParent(parent);
				}

				// external node has a no child
			} else if (rem.getRight() == null && rem.getLeft() == null) {
				action = rem.getParent();
				if (rem == parent.getLeft()) {
					parent.setLeft(null);
				} else {
					parent.setRight(rem.getLeft());
				}
			}
			rem.setParent(null);
		}
	}

	/**
	 * Gets the successor of a given object.
	 * 
	 * @param o
	 *            The successor of this object is looked for.
	 * @param trueSucc
	 *            True iff successor may not be element itself.
	 * @param avl
	 *            True iff position and not element is to be returned.
	 * @return The successor in this AVLTree.
	 */
	public Object succ(Object o, boolean trueSucc, boolean avl) {
		if (isEmpty) {
			return null;
		}
		Object result = null;
		AVLNode current = root;
		while (current != null) {
			Object el = current.getElement();

			// element equal to given object
			if (comp.compare(el, o) == 0) {
				if (!trueSucc) {
					if (avl) {
						return current;
					}
					return el;
				}
				current = current.getRight();

				// element smaller
			} else if (comp.compare(el, o) < 0) {
				current = current.getRight();

				// element bigger
			} else {
				if (avl) {
					result = current;
				} else {
					result = el;
				}
				current = current.getLeft();
			}
		}
		return result;
	}

	/**
	 * Returns the successor of a given node in constant time.
	 * 
	 * @param n
	 *            One wants the successor of this node.
	 * @return The successor element.
	 */
	public Object succConstantRuntime(Object n) {
		return inorder.getSuccEl(n);
	}

	/**
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		String result = "AVL: ";

		//		Iterator it = (new AVLIterator(this));
		Iterator it = iterator();

		while (it.hasNext()) {
			Node next = (Node) it.next();
			result += next.toString() + " ";
			result += " (mult: " + getMultiplicity(next) + ") ";
		}

		return result;
	}

	/**
	 * Gets the root of this AVLTree.
	 * 
	 * @return The root.
	 */
	public AVLNode getRoot() {
		return root;
	}

	/**
	 * 
	 * @author F.Pfeiffer
	 * 
	 * Comparator for comparing positions in AVLTree.
	 */
	class AVLComparator implements Comparator {

		/**
		 * Compares two objects in tree.
		 * 
		 * @param o1
		 *            First object.
		 * @param o2
		 *            Second object.
		 * @return The comparison result.
		 */
		public int compare(Object o1, Object o2) {
			AVLNode avl1 = (AVLNode) o1;
			AVLNode avl2 = (AVLNode) o2;
			Object n1 = avl1.getElement();
			Object n2 = avl2.getElement();
			return comp.compare(n1, n2);
		}
	}

	/**
	 * Completely rebuilds AVLTree.
	 *  
	 */
	public void reorder() {
		HashMap removClone = new HashMap(multiplicity);
		DLL inorderCopy = new DLL(inorder);
		Iterator it = inorderCopy.iterator();
		this.clear();
		while (it.hasNext()) {
			this.insert((Node) it.next());
		}
		multiplicity = removClone;
	}

	/**
	 * Deletes all elements in AVLTree.
	 *  
	 */
	public void clear() {
		root = new AVLNode(null, null, 1);
		this.isEmpty = true;
		inorder.clear();
	}

	/**
	 * Returns an iterator for AVLTrees.
	 * 
	 * @return AVLTree iterator.
	 */
	public Iterator getAVLIterator() {
		return new AVLIterator();
	}

	/**
	 * Checks if tree is empty.
	 * 
	 * @return True iff tree is empty.
	 */
	public boolean isEmpty() {
		return isEmpty;
	}

	/**
	 * Decrements the multiplicity of an element.
	 * 
	 * @param o
	 *            The element of which one wants the multiplicity.
	 */
	private void decrement(Object o) {
		BigInteger remInt = (BigInteger) multiplicity.get(o);
		if (remInt != null) {
			if (remInt.compareTo(new BigInteger("1", 2)) <= 0) {
				multiplicity.remove(o);
			} else {
				multiplicity.put(o, remInt.subtract(new BigInteger("1", 2)));
			}
		}
	}

	/**
	 * Checks if an element can be removed from tree.
	 * 
	 * @param o
	 *            The element to be checked for deletion.
	 * @return True iff element can be removed.
	 */
	public boolean isRemovable(Object o) {
		Object object = multiplicity.get(o);
		if (object == null) {
			return false;
		}
		BigInteger i = (BigInteger) object;
		return i.compareTo(new BigInteger("1", 2)) <= 0;
	}

	/**
	 * Gets the multiplicity of an element.
	 * 
	 * @param n
	 *            The multiplicity of this element is looked for.
	 * @return The multiplicity.
	 */
	public BigInteger getMultiplicity(Object n) {
		BigInteger res = (BigInteger) multiplicity.get(n);
		if (res == null) {
			return new BigInteger("0", 2);
		}
		return res;
	}

	/**
	 * Get the edges associated with an element.
	 * 
	 * @param o
	 *            The element with which the edges are associated.
	 * @return The edges.
	 */
	public Collection getEdges(Object o) {
		if (((DLL) edges.get(o)) == null) {
			System.out.println(o);
		}
		return new DLL((DLL) edges.get(o));
	}

	/**
	 * Gets an iterator for tree.
	 * 
	 * @return Iterator for tree.
	 */
	public Iterator iterator() {
		return new AVLIterator();
	}

	/**
	 * @author F. Pfeiffer
	 * 
	 * Iterator for AVLTrees.
	 */
	private class AVLIterator implements Iterator {

		// iterator for inorder list
		private Iterator it;

		/**
		 * Constructor.
		 *  
		 */
		public AVLIterator() {
			it = inorder.iterator();
		}

		/**
		 * @see java.util.Iterator#hasNext()
		 */
		public boolean hasNext() {
			return it.hasNext();

		}

		/**
		 * @see java.util.Iterator#next()
		 */
		public Object next() {
			return it.next();
		}

		/**
		 * @see java.util.Iterator#remove()
		 */
		public void remove() {
			throw new UnsupportedOperationException();
		}
	}

	/**
	 * @author F. Pfeiffer
	 * 
	 * Node (position) in AVLTree.
	 */
	private class AVLNode {

		// element contained in node
		private Object element;

		// children and parent pointers
		private AVLNode left, right, parent;

		// heigth oh subtree rooted at this node
		private int height;

		/**
		 * Constructor.
		 * 
		 * @param el
		 *            Element to be contained.
		 * @param par
		 *            Parent of node.
		 * @param h
		 *            Height.
		 */
		public AVLNode(Object el, AVLNode par, int h) {
			element = el;
			parent = par;
			height = h;
			left = null;
			right = null;
		}

		/**
		 * Gets the contained element.
		 * 
		 * @return The contained element.
		 */
		public Object getElement() {
			return element;
		}

		/**
		 * Gets the left child.
		 * 
		 * @return The left child.
		 */
		public AVLNode getLeft() {
			return left;
		}

		/**
		 * Gets the right child.
		 * 
		 * @return The right child.
		 */
		public AVLNode getRight() {
			return right;
		}

		/**
		 * Gets the parent node.
		 * 
		 * @return The parent node.
		 */
		public AVLNode getParent() {
			return parent;
		}

		/**
		 * Gets the height.
		 * 
		 * @return The height.
		 */
		public int getHeight() {
			return height;
		}

		/**
		 * Sets the contained element.
		 * 
		 * @param el
		 *            The new element.
		 */
		public void setElement(Object el) {
			element = el;
		}

		/**
		 * Sets the left child.
		 * 
		 * @param n
		 *            The new left child.
		 */
		public void setLeft(AVLNode n) {
			left = n;
		}

		/**
		 * Sets the right child.
		 * 
		 * @param n
		 *            The new right child.
		 */
		public void setRight(AVLNode n) {
			right = n;
		}

		/**
		 * Sets the parent node.
		 * 
		 * @param n
		 *            The new parent node.
		 */
		public void setParent(AVLNode n) {
			parent = n;
		}

		/**
		 * Sets the height.
		 * 
		 * @param h
		 *            The new height.
		 */
		public void setHeight(int h) {
			height = h;
		}

		/**
		 * @see java.lang.Object#toString()
		 */
		public String toString() {
			String result = "";
			result += "AVLNode :\n";
			result += "Element: " + this.element;
			result += " Height: " + this.height;
			if (parent != null)
				result += " Parent: " + this.parent.getElement();
			if (left != null)
				result += " left: " + left.getElement();
			if (right != null)
				result += " right: " + right.getElement();
			//			result += "\n";
			return result;
		}

	}

}