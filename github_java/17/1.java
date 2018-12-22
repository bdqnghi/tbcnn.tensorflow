import java.util.ArrayList;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Stack;

/**
 * A BinarySearchTree implementation class
 * @author risdenkj
 * 
 */

public class RedBlackTree<T extends Comparable<? super T>> implements Iterable<T> {
	public enum Color {RED, BLACK};
	private BinaryNode root;
	private int modCount = 0;
	private int rotationCount = 0;
	
	/**
	 * Constructs a BinarySearchTree
	 * Sets the root to null
	 */
	public RedBlackTree() {
		root = null;
	}

	/**
	 * Checks if the BinarySearchTree has no nodes
	 * 
	 * @return 	true if the BinarySearchTree has no nodes; false if has nodes
	 */
	public boolean isEmpty() {
		return root == null ? true : false;
	}
	
	/**
	 * Default iterator method returns the nodes in order
	 * 
	 * @return 	an iterator to traverse the nodes in order 
	 */
	public Iterator<T> inOrderIterator() {
		return new inOrderTreeIterator(root);
	}
	
	/**
	 * Iterator that returns the nodes in preorder
	 * 
	 * @return 	an iterator to traverse the nodes in preorder
	 */
	public Iterator<T>iterator() {
		return new preOrderTreeIterator(root);
	}
	
	/**
	 * Method that returns an ArrayList representation of the BinarySearchTree
	 * 
	 * @return 	ArrayList with the nodes in order
	 */
	public ArrayList<T> toArrayList() {
		if(root == null) {
			return new ArrayList<T>();
		}
		return root.toArrayList(new ArrayList<T>());
	}
	
	/**
	 * Method that returns an Array representation of the BinarySearchTree
	 * 
	 * @return 	Array with the nodes in order
	 */
	public Object[] toArray() {
		return toArrayList().toArray();
	}

	/**
	 * Method to determine the height of the BinarySearchTree
	 * 
	 * @return 	height of the BinarySearchTree; -1 if BinarySearchTree is empty
	 */
	public int height(){
		return !isEmpty() ? root.height() : -1;
	}
	
	/**
	 * Method that returns a String representation of the BinarySearchTree
	 * 
	 * @return 	string in [element, element] format with the BinarySearchTree BinaryNodes in order 
	 */
	public String toString() {
		String temp = "";
		if(root == null) {
			return temp;
		}
		Iterator<T> i = iterator();
		while(i.hasNext()) {
			temp += "[" + i.next() + "]";
			if(i.hasNext()) {
				temp += ", ";
			}
		}
		return temp;
	}
	
	/**
	 * Method to determine the size of the BinarySearchTree
	 * 
	 * @return 	size of the BinarySearchTree; 0 if BinarySearchTree is empty
	 */
	public int size() {
		return !isEmpty() ? root.size() : 0;
	}
	
	/**
	 * Returns a boolean value representing whether the tree was modified
	 * or not. The item argument must be of the same type that was used 
	 * when initiating the BinarySearchTree class.
	 *
	 * @param item	the item to be inserted into the BinarySearchTree
	 * @return      true if the tree was modified, false if not
	 * @exception	IllegalArgumentException if item is null
	 */
	public boolean insert(T item) {
		if(item == null) {
			throw new IllegalArgumentException();
		}
		boolean temp;
		if(root != null) {
			temp = root.insert(null, null, item);
		} else {
			root = new BinaryNode(item);	
			modCount++;
			temp = true;
		}
		root.setColor(Color.BLACK);
		return temp;
	}
	
	/**
	 * Removes the provided item from the BinarySearchTree
	 * 
	 * @param item	the item that will be removed from the BinarySearchTree
	 * @return		true if remove successful; false if not
	 * @exception	IllegalArgumentException if item is null
	 */
	public boolean remove(T item) {
		modWrapper mod = new modWrapper();
		if(item == null) {
			throw new IllegalArgumentException();
		}
		if(root != null) {
			root = root.remove(item, mod);
			if(root != null) {
				root.setColor(Color.BLACK);
			}
		}
		if(mod.getValue()) {
			modCount++;
		}
		
		return mod.getValue();
	}
	
	/**
	 * Get method that returns a pointer to the item provided
	 * 
	 * @param item item to be found in the BinarySearchTree
	 * @return pointer to item if found; null if not found
	 * @exception IllegalArgumentException if item is null
	 */
	public T get(T item) {
		if(item == null) {
			throw new IllegalArgumentException();
		}
		return root.get(item);
	}
	
	public int getRotationCount() {
		return rotationCount;
	}
	
	/**
	 * A BinaryNode Implementation Class
	 * @author risdenkj
	 * 
	 */
	public class BinaryNode {
		private T element;
		private BinaryNode left,right;
		private Color color;
		
		/**
		 * Constructs a BinaryNode
		 * Sets the left and right children to null
		 * 
		 * @param initelement	The element that becomes the BinaryNode
		 */
		public BinaryNode(T initelement) {
			element = initelement;
			left = null;
			right = null;
			color = Color.RED;
		}
		
		/**
		 * Returns the string representation of the current BinaryNode
		 * 
		 * @return	string of the current BinaryNode
		 */
		public String toString() {
			String temp = this.element + ", " + this.color + ", ";
			if(left != null) {
				temp += left.element;
			} else {
				temp += "null";
			}
			temp += ", ";
			if(right != null) {
				temp += right.element;
			} else {
				temp += "null";
			}
			return temp;
		}
		
		/**
		 * Recursive method that returns an ArrayList of the BinaryNode and its children
		 * 
		 * @param list	the ArrayList that elements should be added onto
		 * @return 	ArrayList of the BinaryNode and its children
		 */
		public ArrayList<T> toArrayList(ArrayList<T> list) {
			if(left != null) {
				left.toArrayList(list);
			}
			list.add(element);
			if(right != null) {
				right.toArrayList(list);
			}
			return list;
		}
		
		/**
		 * Method that determines the height of the BinaryNode
		 * 
		 * @return 	height of the BinaryNode
		 */
		public int height() {
			int leftheight = 0, rightheight = 0;
			if(left != null) {
				leftheight = 1 + left.height();
			}
			if(right != null) {
				rightheight = 1 + right.height();
			}
			if(leftheight > rightheight) {
				return leftheight;
			} else { 
				return rightheight;
			}
		}
		
		/**
		 * Method that determines the size of the BinaryNode 
		 * 
		 * @return 	size of the BinaryNode
		 */
		public int size() {
			int size = 1;
			if(left != null) {
				size += left.size();
			}
			if(right != null) {
				size += right.size();
			}
			return size;
		}
		
		/**
		 * Inserts the provided element as a child to the BinaryNode
		 * The item becomes a left child if less than current BinaryNode
		 * The item becomes a right child if greater than current BinaryNode
		 * If the insert is successful adds 1 to the modCount
		 * 
		 * @param item	item to be inserted as a child to the BinaryNode
		 * @return 	true if insert successful; false if not
		 */
		public boolean insert(BinaryNode GP, BinaryNode P, T item) {
			if(this.getColor() == Color.BLACK && left != null && right != null && left.getColor() == Color.RED && right.getColor() == Color.RED) {
				if(root != this) {
					this.setColor(Color.RED);
				}
				left.setColor(Color.BLACK);
				right.setColor(Color.BLACK);
			}
			if(P != null) {
				if(P.getColor() == Color.RED && this.getColor() == Color.RED) {
					if(GP != null) {
						if(GP.left == P) {
							if(P.left == this) {
								GP = singleRightRotation(GP);
							} else if(P.right == this) {
								GP = doubleLeftRotation(GP);
							}
						} else if(GP.right == P) {
							if(P.right == this) {
								GP = singleLeftRotation(GP);
							} else if(P.left == this) {
								GP = doubleRightRotation(GP);
							}
						}
					}
				}
			}
			if(element.compareTo(item) < 0) {
				if(right != null) {
					return right.insert(P, this, item);
				} else {
					right = new BinaryNode(item);
					if(this.getColor() == Color.RED) {
						if(P != null) { 
							if(P.left == this) {
								P = doubleLeftRotation(P);
							} else if(P.right == this) {
								P = singleLeftRotation(P);
							}
						}
					}
					modCount++;
					return true;
				}
			} else if(element.compareTo(item) > 0){
				if(left != null) {
					return left.insert(P, this, item);
				} else {
					left = new BinaryNode(item);
					if(this.getColor() == Color.RED) {
						if(P != null) { 
							if(P.left == this) {
								P = singleRightRotation(P);
							} else if(P.right == this) {
								P = doubleRightRotation(P);
							}
						}
					}
					modCount++;
					return true;
				}
			} else {
				return false;
			}
		}
		
		/**
		 * Method that rotates the tree left around the specified
		 * AVLNode right child.
		 * @param node The node to rotate around
		 * @return node An AVLNode that has been rotated
		 */
		public BinaryNode singleLeftRotation(BinaryNode node) {			
			BinaryNode temp1 = node.right;
			BinaryNode temp2 = new BinaryNode(node.element);
			
			temp2.left = node.left;
			temp2.right = temp1.left;
			node.right = temp1.right;
			node.element = temp1.element;
			node.left = temp2;
			
			rotationCount++;
			return node;
		}
		
		/**
		 * Method that rotates the tree first left around the specified
		 * AVLNode left child then right around the specified AVLNode 
		 * 
		 * @param node The node to rotate around
		 * @return node An AVLNode that has been rotated
		 */
		public BinaryNode doubleLeftRotation(BinaryNode node) {
			singleLeftRotation(node.left);
			singleRightRotation(node);
			return node;
		}
		
		/*
		 * Method that rotates the tree right around the specified
		 * AVLNode left child.
		 * 
		 * @param node The node to rotate around
		 * @return node An AVLNode that has been rotated
		 */
		public BinaryNode singleRightRotation(BinaryNode node) {
			BinaryNode temp1 = node.left;
			BinaryNode temp2 = new BinaryNode(node.element);
			
			temp2.right = node.right;
			temp2.left = temp1.right;
			node.left = temp1.left;
			node.element = temp1.element;
			node.right = temp2;
			
			rotationCount++;
			return node;
		}
		
		/**
		 * Method that rotates the tree first right around the specified
		 * AVLNode right child then left around the specified AVLNode 
		 * 
		 * @param node The node to rotate around
		 * @return node An AVLNode that has been rotated
		 */
		public BinaryNode doubleRightRotation(BinaryNode node) {
			singleRightRotation(node.right);
			singleLeftRotation(node);
			return node;
		}
		
		/**
		 * Removes the provided item from the BinaryNode
		 * In the event of the BinaryNode having two children, the
		 * algorithm finds the largest left child.
		 * 
		 * @param item 	the item that will be removed from the BinaryNode
		 * @param mod 	ModWrapper boolean that will be set to true if remove successful
		 * @return 	BinaryNode that is removed
		 */
		public BinaryNode remove(T item, modWrapper mod) {
			return removeStep1(item, mod);
		}
		
		private BinaryNode removeStep1(T item, modWrapper mod) {
			if(left != null && left.getColor() == Color.BLACK && right != null && right.getColor() == Color.BLACK) {
				this.setColor(Color.RED);
				int compare = item.compareTo(element); 
				if(compare == 0) {
					return this.removeStep3(null, item, mod);
				} else if(compare < 0) {
					left = left.removeStep2(this, item, mod);
					return this;
				} else {
					right = right.removeStep2(this, item, mod);
					return this;
				}
			} else {
				return this.removeStep2B(null, item, mod);
			}
		}
		
		private BinaryNode removeStep2(BinaryNode P, T item, modWrapper mod) {
			if((left != null && left.getColor() == Color.RED) || (right != null && right.getColor() == Color.RED)) {
				return this.removeStep2B(P, item, mod);
			} else {
				return this.removeStep2A(P, item, mod);
			}
		}
		
		private BinaryNode removeStep2A(BinaryNode P, T item, modWrapper mod) {
			BinaryNode S;
			if(P == null) {
				P = root;
			}
			if(P.left != null && P.left == this){
				S = P.right;
				if((S.left != null && S.right != null && S.left.getColor() == Color.BLACK && S.right.getColor() == Color.BLACK) || (S.left == null && S.right == null)) {
					return this.removeStep2A1(P, S, item, mod);
				}
				if(S.left != null && S.left.getColor() == Color.RED && ((S.right != null && S.right.getColor() == Color.BLACK) || (S.right == null))) {
					P = this.removeStep2A2(P, S, item, mod);
					return P.left;
				}
				if(S.right != null && S.right.getColor() == Color.RED) {
					P = this.removeStep2A3(P, S, item, mod);
					return P.left;
				}
				//if(S.left.getColor() == Color.RED && S.right.getColor() == Color.RED) {
				return this.removeStep2A4(P, S, item, mod);
				//}
			} else {
				S = P.left;
				if((S.left != null && S.right != null && S.left.getColor() == Color.BLACK && S.right.getColor() == Color.BLACK) || (S.left == null && S.right == null)) {
					return this.removeStep2A1(P, S, item, mod);
				}
				if(S.right != null && S.right.getColor() == Color.RED && ((S.left != null && S.left.getColor() == Color.BLACK) || (S.left == null))) {
					P = this.removeStep2A2(P, S, item, mod);
					return P.right;
				}
				if(S.left != null && S.left.getColor() == Color.RED) {
					P = this.removeStep2A3(P, S, item, mod);
					return P.right;
				}
				//if(S.left.getColor() == Color.RED && S.right.getColor() == Color.RED) {
				return this.removeStep2A4(P, S, item, mod);
				//}
			}
		}
		
		private BinaryNode removeStep2A1(BinaryNode P, BinaryNode S, T item, modWrapper mod) {
			P.setColor(Color.BLACK);
			this.setColor(Color.RED);
			S.setColor(Color.RED);
			int compare = item.compareTo(element);
			if(compare == 0) {
				return this.removeStep3(P, item, mod);
			} else if(compare < 0) {
				if(left != null) {
					left = left.removeStep2(this, item, mod);
				}
				return this;
			} else {
				if(right != null) {
					right = right.removeStep2(this, item, mod);
				}
				return this;
			}
		}
		
		private BinaryNode removeStep2A2(BinaryNode P, BinaryNode S, T item, modWrapper mod) {
			if(P.right == S) {
				P = doubleRightRotation(P);
				S = P;
				P = S.left;
				S.right.setColor(Color.BLACK);
			} else {
				P = doubleLeftRotation(P);
				S = P;
				P = S.right;
				S.left.setColor(Color.BLACK);
			}
			
			P.setColor(Color.BLACK);
			this.setColor(Color.RED);
			
			int compare = item.compareTo(element);
			if(compare == 0) {
				if(P.left == this) {
					P.left = removeStep3(P, item, mod);
				} else {
					P.right = removeStep3(P, item, mod);
				}
				return S;
			} else if(compare < 0) {
				left = left.removeStep2(this, item, mod);
				return this;
			} else {
				left = right.removeStep2(this, item, mod);
				return this;
			}
		}
		
		private BinaryNode removeStep2A3(BinaryNode P, BinaryNode S, T item, modWrapper mod) {
			if(P.right == S) {
				P = singleLeftRotation(P);
				S = P;
				P = S.left;
				S.right.setColor(Color.BLACK);
			} else {
				P = singleRightRotation(P);
				S = P;
				P = S.right;
				S.left.setColor(Color.BLACK);
			}
			S.setColor(Color.RED);
			P.setColor(Color.BLACK);
			this.setColor(Color.RED);
			
			int compare = item.compareTo(element);
			if(compare == 0) {
				if(P.right == this) {
					P.right = this.removeStep3(P, item, mod);
				} else {
					P.left = this.removeStep3(P, item, mod);
				}
				return S;
			} else if(compare < 0) {
				left = left.removeStep2(this, item, mod);
			} else {
				right = right.removeStep2(this, item, mod);
			}
			return this;
		}
		
		private BinaryNode removeStep2A4(BinaryNode P, BinaryNode S, T item, modWrapper mod) {
			return removeStep2A3(P, S, item, mod);
		}
		
		private BinaryNode removeStep2B(BinaryNode P, T item, modWrapper mod) {
			int compare = item.compareTo(element);
			if(compare == 0) {
				return removeStep3(P, item, mod);
			} else if(compare < 0) {
				if(left != null) {
					if(left.getColor() == Color.RED) {
						left = left.removeStep2B1(this, item, mod);
					} else {
						P = left.removeStep2B2(this, item, mod);
						return P;
					}
					return this;
				}
			} else {
				if(right != null) {
					if(right.getColor() == Color.RED) {
						right = right.removeStep2B1(this, item, mod);
					} else {
						P = right.removeStep2B2(this, item, mod);
						return P;
					}
					return this;
				}
			}
			return this;
		}
		
		private BinaryNode removeStep2B1(BinaryNode P, T item, modWrapper mod) {
			int compare = item.compareTo(element);
			if(compare == 0) {
				return removeStep3(P, item, mod);
			} else if(compare < 0) {
				if(left != null) {
					left = left.removeStep2(this, item, mod);
				}
			} else {
				if(right != null) {
					right = right.removeStep2(this, item, mod);
				}
			}
			return this;
		}

		private BinaryNode removeStep2B2(BinaryNode P, T item, modWrapper mod) {
			BinaryNode S;
			if(P.left != null && P.left == this){
				S = rotateLeftSimple(P);
				P = S.left;
			} else {
				S = rotateRightSimple(P);
				P = S.right;
			}
			S.setColor(Color.BLACK);
			P.setColor(Color.RED);
			if(P.right == this) {
				P.right = this.removeStep2(P, item, mod);
			} else {
				P.left = this.removeStep2(P, item, mod);
			}
			return S;
		}
		
		private BinaryNode rotateLeftSimple(BinaryNode node) {
			BinaryNode S = node.right;
			BinaryNode P = new BinaryNode(node.element);
			P.left = node.left;
			P.right = S.left;
			node.right = S.right;
			node.element = S.element;
			node.left = P;
			rotationCount++;
			return node;
		}
		
		private BinaryNode rotateRightSimple(BinaryNode node) {
			BinaryNode S = node.left;
			BinaryNode P = new BinaryNode(node.element);
			P.right = node.right;
			P.left = S.right;
			node.right = P;
			node.element = S.element;
			node.left = S.left;
			rotationCount++;
			return node;
		}
		
		private BinaryNode removeStep3(BinaryNode P, T item, modWrapper mod) {
			if(left != null && right != null) {
				T tempelement = element;
				BinaryNode temp = findLargestChild(left);
				this.removeStep2(P, temp.element, mod);
				if(this.element == tempelement) {
					element = temp.element;
				} else {
					if(left != null && left.element == tempelement) {
						left.element = temp.element;
					} else {
						right.element = temp.element;
					}
				}
				mod.setTrue();
				return this;
			} else if(left == null && right == null) {
				mod.setTrue();
				return null;
			} else {
				if(left != null) {
					element = left.element;
					left = null;
					mod.setTrue();
				} else {
					element = right.element;
					right = null;
					mod.setTrue();
				}
				return this;
			}
		}
		
		/**
		 * Method that finds the largest left child
		 * 
		 * @param node	BinaryNode to look for largest left child
		 * @return 	the largest left child of the provided BinaryNode
		 */
		public BinaryNode findLargestChild(BinaryNode node) {
			while(node.right != null) {
				node = node.right;
			}
			return node;
		}
		
		public T getElement() {
			return element;
		}
		
		/**
		 * Get method that returns a pointer to the item provided
		 * 
		 * @param item item to be found in the BinaryNode
		 * @return pointer to item if found; null if not found
		 */
		public T get(T item) {
			if(item.compareTo(element) > 0) {
				return right.get(item);
			} else if(item.compareTo(element) < 0) {
				return left.get(item);
			} else {
				return element;
			}
		}
		
		public Color getColor() {
			return color;
		}
		
		public void setColor(Color color) {
			this.color = color;
		}
	}
	
	/**
	 * Creates a wrapper for the mod boolean
	 * @author risdenkj
	 * 
	 */
	private class modWrapper {
		private boolean mod = false;
		
		public void setTrue() {
			this.mod = true;
		}
		
		public void setFalse() {
			this.mod = false;
		}

		public boolean getValue() {
			return mod;
		}
	}
	
	/**
	 * A preorder BinarySearchTree iterator implementation class
	 * @author risdenkj
	 * 
	 */
	public class preOrderTreeIterator implements Iterator<T> {
		private Stack<BinaryNode> list = new Stack<BinaryNode>();
		private BinaryNode node = null;
		private int mod;
		
		/**
		 * Constructs a preOrderTreeIterator
		 * Sets the modification boolean flag to false
		 * 
		 * @param node	BinaryNode to start the iterator from
		 */
		public preOrderTreeIterator(BinaryNode node) {
			if(node != null) {
				list.push(node);
			}
			this.mod = modCount;
		}
		
		/**
		 * Checks if there is another element in the BinarySearchTree that hasn't been accessed
		 * 
		 * @return	true if there is another element to return; false if not
		 */
		public boolean hasNext() {
			return !list.empty();
		}

		/**
		 * Method that returns the next BinaryNode element from the BinarySearchTree
		 * 
		 * @return BinaryNode	element in the BinarySearchTree
		 * @exception 	ConcurrentModificationException if the BinarySearchTree was modified after initializing the iterator
		 * @exception 	NoSuchElementException if there are no more elements to return
		 */
		public T next() {
			if(this.mod != modCount) {
				throw new ConcurrentModificationException();
			}
			BinaryNode item = null;
			
			if(!list.empty()) {
				item = list.pop();
			} else {
				throw new NoSuchElementException();
			}
			
			if(item.right != null) {
				list.push(item.right);
			}
			if(item.left != null) {
				list.push(item.left);
			}
			node = item;
			return item.element;
		}
		
		/**
		 * Removes an element from the BinarySearchTree
		 * 
		 * @exception	IllegalStateException if next() not called before
		 */
		public void remove() {
			if(node == null) {
				throw new IllegalStateException();
			}
			if(RedBlackTree.this.remove(node.element)) {
				node = null;
				mod++;
			}
		}
	}
	
	/**
	 * An in order BinarySearchTree iterator implementation class
	 * @author risdenkj
	 * 
	 */
	public class inOrderTreeIterator implements Iterator<T> {
		private Stack<BinaryNode> list = new Stack<BinaryNode>();
		private BinaryNode node = null;
		private int mod;
		
		/**
		 * Constructs an inOrderTreeIterator
		 * Sets the modification boolean flag to false
		 * 
		 * @param node	BinaryNode to start the iterator from
		 */
		public inOrderTreeIterator(BinaryNode node) {
			this.mod = modCount;
			checkLeft(node);
		}
		
		/**
		 * Checks if there is another element in the BinarySearchTree that hasn't been accessed
		 * 
		 * @return 	true if there is another element to return; false if not
		 */
		public boolean hasNext() {
			return !list.empty();
		}
		
		/**
		 * Method that returns the next BinaryNode element from the BinarySearchTree
		 * 
		 * @return BinaryNode	element in the BinarySearchTree
		 * @exception 	ConcurrentModificationException if the BinarySearchTree was modified after initializing the iterator
		 * @exception 	NoSuchElementException if there are no more elements to return
		 */
		public T next() {
			if(this.mod != modCount) {
				throw new ConcurrentModificationException();
			}
			BinaryNode item = null;
			if(list.empty()) {
				throw new NoSuchElementException();
			}
			item = list.pop();
			checkLeft(item.right);
			node = item;
			return item.element;
		}

		/**
		 * Checks if the provided BinaryNode has a left child
		 * 
		 * @param node	node to to check if it has a left child
		 */
		public void checkLeft(BinaryNode node) {
			while(node != null) {
				list.push(node);
				node = node.left;
			}
		}
		
		/**
		 * Removes an element from the BinarySearchTree
		 * 
		 * @exception	IllegalStateException if next() not called before
		 */
		public void remove() {
			if(node == null) {
				throw new IllegalStateException();
			}
			if(RedBlackTree.this.remove(node.element)) {
				node = null;
				mod++;
			}
		}
	}
}
