package p3;

import static org.junit.Assert.assertEquals;
import java.util.function.BiPredicate;

/**
 * This class implements a generic height-balanced binary search tree, using the
 * AVL algorithm. Beyond the constructor, only the insert() method needs to be
 * implemented. All other methods are unchanged.
 * 
 * @author mrlonis (Matthew Lonis)
 */
public class AVLTree<K> extends BinarySearchTree<K> {

	/**
	 * Creates an empty AVL tree as a BST organized according to the lessThan
	 * predicate.
	 */
	public AVLTree(BiPredicate<K, K> lessThan) {
		super(lessThan);
	}

	/**
	 * Inserts the given key into this AVL tree such that the ordering property
	 * for a BST and the balancing property for an AVL tree are maintained.
	 * 
	 * @param key
	 *            The data for the Node to be inserted.
	 * @return The Node that was inserted into this tree.
	 */
	public Node insert(K key) {
		
		Node r, q, p, returnValue;
		q = super.insert(key);
		returnValue = q;
		r = null;
		p = q.parent;
		
		if (p == null) {
			return returnValue;
		} else {
			while (p != null) {
				int balance = p.getBalance();
				
				if (balance >= 2) {
					if (p.left == q && q.left == r) {
						p = LL_Rotation(p);
					} else if (p.left == q && q.right == r) {
						p = LR_Rotation(p);
					} else if (p.right == q && q.left == r) {
						p = RL_Rotation(p);
					} else if (p.right == q && q.right == r) {
						p = RR_Rotation(p);
					}
				}
				
				r = q;
				q = p;
				p = p.parent;
			}
		}
		return returnValue;
		/*
		 * This is my first working version of insert using Strings. Not efficient.
		
		Node q = super.insert(key);
		Node c = q;
		Node p = q.parent;
		String rotation = "";
		if (p == null) {
			return q;
		} else {
			while (p != null) {
				int balance = p.getBalance();
				
				if (balance >= 2) {
					if (p.left != null && p.right != null) {
						if (p.left.height > p.right.height) {
							rotation += "L";
							c = p.left;
						} else {
							rotation += "R";
							c = p.right;
						}
					} else if (p.left != null) {
						rotation += "L";
						c = p.left;
					} else if (p.right != null) {
						rotation += "R";
						c = p.right;
					}

					if (c.left != null && c.right != null) {
						if (c.left.height > c.right.height) {
							rotation += "L";
						} else {
							rotation += "R";
						}
					} else if (c.left != null) {
						rotation += "L";
					} else if (c.right != null) {
						rotation += "R";
					}

					if (rotation.equals("LL")) {
						p = LL_Rotation(p);
					} else if (rotation.equals("RR")) {
						p = RR_Rotation(p);
					} else if (rotation.equals("LR")) {
						p = LR_Rotation(p);
					} else {
						p = RL_Rotation(p);
					}
				}

				p = p.parent;
			}
		}
		return q;
		*/
	}

	/**
	 * Performs an LL rotation on oldParent
	 * 
	 * @param oldParent
	 *            The pivot Node for rotation.
	 * @return The New parent Node that took oldParent's place
	 */
	private Node LL_Rotation(Node oldParent) {
		Node newParent = oldParent.left;
		newParent.parent = oldParent.parent;
		oldParent.parent = newParent;

		oldParent.left = newParent.right;
		if (oldParent.left != null) {
			oldParent.left.parent = oldParent;
		}

		newParent.right = oldParent;
		newParent.right.fixHeight();
		newParent.fixHeight();
		Node parent = newParent.parent;

		if (newParent.parent != null) {
			if (parent.left != null && parent.left == oldParent) {
				parent.left = newParent;
			} else if (parent.right != null && parent.right == oldParent) {
				parent.right = newParent;
			}
			
			while (parent != null) {
				parent.fixHeight();
				parent = parent.parent;
			}
		} else {
			this.root = newParent;
		}

		return newParent;
	}

	/**
	 * Performs an RR rotation on oldParent
	 * 
	 * @param oldParent
	 *            The pivot Node for rotation.
	 * @return The New parent Node that took oldParent's place
	 */
	private Node RR_Rotation(Node oldParent) {
		Node newParent = oldParent.right;
		newParent.parent = oldParent.parent;
		oldParent.parent = newParent;
		
		oldParent.right = newParent.left;
		if (oldParent.right != null) {
			oldParent.right.parent = oldParent;
		}

		newParent.left = oldParent;
		newParent.left.fixHeight();
		newParent.fixHeight();
		Node parent = newParent.parent;

		if (newParent.parent != null) {
			if (parent.left != null && parent.left == oldParent) {
				parent.left = newParent;
			} else if (parent.right != null && parent.right == oldParent) {
				parent.right = newParent;
			}
			
			while (parent != null) {
				parent.fixHeight();
				parent = parent.parent;
			}
		} else {
			this.root = newParent;
		}

		return newParent;
	}

	/**
	 * Performs an LR rotation on oldParent
	 * 
	 * @param oldParent
	 *            The pivot Node for rotation.
	 * @return The New parent Node that took oldParent's place
	 */
	private Node LR_Rotation(Node oldParent) {
		oldParent.left = RR_Rotation(oldParent.left);
		return LL_Rotation(oldParent);
	}

	/**
	 * Performs an RL rotation on oldParent
	 * 
	 * @param oldParent
	 *            The pivot Node for rotation.
	 * @return The New parent Node that took oldParent's place
	 */
	private Node RL_Rotation(Node oldParent) {
		oldParent.right = LL_Rotation(oldParent.right);
		return RR_Rotation(oldParent);
	}
	
	/**
	 * Simple Testing.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		int[] a;
		AVLTree<Integer> avl = new AVLTree<>((Integer x, Integer y) -> x < y);
		a = new int[] {5, 3, 1, 2, 7, 6, 9, 8, -1, -7, -5, -2, -3, 10, 15, 13, 12, 19, 20, 21};
		for (Integer x : a) {
			avl.insert(x);
		}
		System.out.println(avl.keys().toString());
		avl.printAll();
		System.out.println(avl.toString());
		assertEquals(5, avl.height());
	}
}