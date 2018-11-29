
/** Starter code for Red-Black Tree
 */

/*
 * Group members:
Mukesh Kumar(mxk170430)
Shikhar Pandya (sdp170030)
Arijeet Roy (axr165030)
*/
package cs6301.g40;

import java.util.Comparator;
import java.util.Scanner;

import cs6301.g40.BST;

public class RedBlackTree<T extends Comparable<? super T>> extends BST<T> {
	// create nullnode with color black;
	Entry<T> nullNode;
	Entry<T> root;
	int size;
	int index = 0;

	static class Entry<T> extends BST.Entry<T> {
		boolean isRed;
		Entry<T> parent;

		Entry(T x, Entry<T> left, Entry<T> right, Entry<T> parent, boolean isRed) {
			super(x, left, right);
			this.isRed = isRed;
			this.parent = parent;
		}
	}

	// initialize a sentinel node with a black node
	RedBlackTree() {
		super();
		nullNode = new Entry<T>(null, nullNode, nullNode, nullNode, false);
		root = nullNode;
	}

	// function to add a new node and fix the structure of tree maintaining
	// the black height of left and right subtrees
	public boolean add(T x) {
		Entry<T> temp = root;
		boolean isAdded = false;
		if (root == nullNode) {
			Entry<T> node = new Entry<T>(x, nullNode, nullNode, nullNode, false);
			root = node;
			size++;
			isAdded = true;
		} else {
			Entry<T> node = new Entry<T>(x, nullNode, nullNode, nullNode, true);
			while (temp != nullNode) {
				if (x.compareTo(temp.element) < 0) {
					if (temp.left == nullNode) {
						temp.left = node;
						node.parent = temp;
						size++;
						break;
					} else {
						temp = (Entry<T>) temp.left;
					}
					isAdded = true;
				} else if (x.compareTo(temp.element) > 0) {
					if (temp.right == nullNode) {
						temp.right = node;
						node.parent = temp;
						size++;
						break;
					} else {
						temp = (Entry<T>) temp.right;
					}
					isAdded = true;
				} else {
					temp.element = x;
					isAdded = false;
					break;
				}
			}
			fixStructureAfterInsert(node);
		}
		return isAdded;
	}

	// fix the structure of the tree according to the color of the uncle
	private void fixStructureAfterInsert(Entry<T> node) {
		while (node.parent.isRed) {
			Entry<T> uncle = nullNode;
			if (node.parent == node.parent.parent.left) {
				uncle = (Entry<T>) node.parent.parent.right;
				if (uncle != nullNode && uncle.isRed) {
					node.parent.isRed = false;
					uncle.isRed = false;
					node.parent.parent.isRed = true;
					node = node.parent.parent;
					continue;
				}
				if (node == node.parent.right) {
					node = node.parent;
					leftRotate(node);
				}
				node.parent.isRed = false;
				node.parent.parent.isRed = true;
				rightRotate(node.parent.parent);
			} else {
				uncle = (Entry<T>) node.parent.parent.left;
				if (uncle != nullNode && uncle.isRed) {
					node.parent.isRed = false;
					uncle.isRed = false;
					node.parent.parent.isRed = true;
					node = node.parent.parent;
					continue;
				}
				if (node == node.parent.left) {
					node = node.parent;
					rightRotate(node);
				}
				node.parent.isRed = false;
				node.parent.parent.isRed = true;
				leftRotate(node.parent.parent);
			}
		}
		root.isRed = false;
	}

	// rotate left the node to maintain height balance
	private void leftRotate(Entry<T> node) {
		if (node.parent != nullNode) {
			if (node == node.parent.left) {
				node.parent.left = node.right;
			} else {
				node.parent.right = node.right;
			}
			((Entry<T>) node.right).parent = node.parent;
			node.parent = (Entry<T>) node.right;
			if (node.right.left != nullNode) {
				((Entry<T>) node.right.left).parent = node;
			}
			node.right = node.right.left;
			node.parent.left = node;
		} else {
			Entry<T> right = (Entry<T>) root.right;
			root.right = right.left;
			((Entry<T>) right.left).parent = root;
			root.parent = right;
			right.left = root;
			right.parent = nullNode;
			root = right;
		}
	}

	// rotate right once to maintain height balance
	private void rightRotate(Entry<T> node) {
		if (node.parent != nullNode) {
			if (node == node.parent.left) {
				node.parent.left = node.left;
			} else {
				node.parent.right = node.left;
			}

			((Entry<T>) node.left).parent = node.parent;
			node.parent = (Entry<T>) node.left;
			if (node.left.right != nullNode) {
				((Entry<T>) node.left.right).parent = node;
			}
			node.left = node.left.right;
			node.parent.right = node;
		} else {
			Entry<T> left = (Entry<T>) root.left;
			root.left = root.left.right;
			((Entry<T>) left.right).parent = root;
			root.parent = left;
			left.right = root;
			left.parent = nullNode;
			root = left;
		}
	}

	// search for a node in the tree and return if exists
	private Entry<T> find(T x, Entry<T> node) {
		if (root == nullNode) {
			return nullNode;
		}

		if (x.compareTo(node.element) < 0) {
			if (node.left != nullNode) {
				return find(x, (Entry<T>) node.left);
			}
		} else if (x.compareTo(node.element) > 0) {
			if (node.right != nullNode) {
				return find(x, (Entry<T>) node.right);
			}
		} else if (x.compareTo(node.element) == 0) {
			return node;
		}
		return nullNode;
	}

	// function to remove a node by finding the inorder successor of a node and
	// then
	// then fixing the tree structure
	public T remove(T x) {
		Entry<T> node = find(x, root);
		if (node == nullNode)
			return null;
		Entry<T> temp;
		Entry<T> inOrderSucc = node;
		boolean tempColor = inOrderSucc.isRed;

		if (node.left == nullNode) {
			temp = (Entry<T>) node.right;
			replace(node, (Entry<T>) node.right);
		} else if (node.right == nullNode) {
			temp = (Entry<T>) node.left;
			replace(node, (Entry<T>) node.left);
		} else {
			inOrderSucc = inOrderSuccessor((Entry<T>) node.right);
			tempColor = inOrderSucc.isRed;
			temp = (Entry<T>) inOrderSucc.right;
			if (inOrderSucc.parent == node)
				temp.parent = inOrderSucc;
			else {
				replace(inOrderSucc, (Entry<T>) inOrderSucc.right);
				inOrderSucc.right = node.right;
				((Entry<T>) inOrderSucc.right).parent = inOrderSucc;
			}
			replace(node, inOrderSucc);
			inOrderSucc.left = node.left;
			((Entry<T>) inOrderSucc.left).parent = inOrderSucc;
			inOrderSucc.isRed = node.isRed;
		}
		if (!tempColor)
			fixStructureAfterDelete(temp);
		size--;
		return x;

	}

	// fix the tree structure keeping note of the sibling color
	private void fixStructureAfterDelete(Entry<T> node) {
		while (node != root && !node.isRed) {
			if (node == node.parent.left) {
				Entry<T> w = (Entry<T>) node.parent.right;
				if (w.isRed) {
					w.isRed = false;
					node.parent.isRed = true;
					leftRotate(node.parent);
					w = (Entry<T>) node.parent.right;
				}
				if (!((Entry<T>) w.left).isRed && !((Entry<T>) w.right).isRed) {
					w.isRed = true;
					node = node.parent;
					continue;
				} else if (!((Entry<T>) w.right).isRed) {
					((Entry<T>) w.left).isRed = false;
					w.isRed = true;
					rightRotate(w);
					w = (Entry<T>) node.parent.right;
				}
				if (((Entry<T>) w.right).isRed) {
					w.isRed = node.parent.isRed;
					node.parent.isRed = false;
					((Entry<T>) w.right).isRed = false;
					leftRotate(node.parent);
					node = root;
				}
			} else {
				Entry<T> w = (Entry<T>) node.parent.left;
				if (w.isRed) {
					w.isRed = false;
					node.parent.isRed = true;
					rightRotate(node.parent);
					w = (Entry<T>) node.parent.left;
				}
				if (!((Entry<T>) w.right).isRed && !((Entry<T>) w.left).isRed) {
					w.isRed = true;
					node = node.parent;
					continue;
				} else if (!((Entry<T>) w.left).isRed) {
					((Entry<T>) w.right).isRed = false;
					w.isRed = true;
					leftRotate(w);
					w = (Entry<T>) node.parent.left;
				}
				if (((Entry<T>) w.left).isRed) {
					w.isRed = node.parent.isRed;
					node.parent.isRed = false;
					((Entry<T>) w.left).isRed = false;
					rightRotate(node.parent);
					node = root;
				}
			}
		}
		node.isRed = false;
	}

	// function to find the inorder successor of a node
	private Entry<T> inOrderSuccessor(Entry<T> node) {
		while (node.left != nullNode) {
			node = (Entry<T>) node.left;
		}
		return node;
	}

	// replace a nnode with another
	public void replace(Entry<T> toNode, Entry<T> withNode) {
		if (toNode.parent == nullNode) {
			root = withNode;
		} else if (toNode == toNode.parent.left) {
			toNode.parent.left = withNode;
		} else
			toNode.parent.right = withNode;
		withNode.parent = toNode.parent;
	}

	public static void main(String[] args) {
		RedBlackTree<Integer> t = new RedBlackTree<>();
		Scanner in = new Scanner(System.in);
		while (in.hasNext()) {
			int x = in.nextInt();
			if (x > 0) {
				System.out.print("Add " + x + " : ");
				t.add(x);
				t.printTree();
			} else if (x < 0) {
				System.out.print("Remove " + x + " : ");
				t.remove(-x);
				t.printTree();
			} else {
				Comparable[] arr = t.toArray();
				System.out.print("Final: ");
				for (int i = 0; i < t.size; i++) {
					System.out.print(arr[i] + " ");
				}
				System.out.println();
				return;
			}
		}
		in.close();
	}

	public Comparable[] toArray() {
		Comparable[] arr = new Comparable[size];
		/* write code to place elements in array here */
		storeInArray(root, arr);
		return arr;
	}

	/**
	 * TO DO: Is x contained in tree?
	 */
	public boolean contains(T x) {
		Entry<T> node = find(x, root);
		if (node == nullNode)
			return false;
		return true;
	}
	
	/**
	 * TO DO: Is there an element that is equal to x in the tree? Element in
	 * tree that is equal to x is returned, null otherwise.
	 */
	public T get(T x) {
		Entry<T> node = find(x, root);
		if (node == nullNode)
			return null;
		return node.element;
	}
	
	private void storeInArray(Entry<T> node, Comparable[] arr) {
		// TODO Auto-generated method stub
		if (node != nullNode) {
			storeInArray((Entry<T>) node.left, arr);
			if (node.element != null) {
				arr[index++] = node.element;
			}
			storeInArray((Entry<T>) node.right, arr);
		}
	}

	public void printTree() {
		System.out.print("[" + size + "]");
		printTree(root);
		System.out.println();
	}

	// Inorder traversal of tree
	void printTree(Entry<T> node) {
		if (node != nullNode) {
			printTree((Entry<T>) node.left);
			if (node.element != null) {
				System.out.print(" " + node.element);
			}
			printTree((Entry<T>) node.right);
		}
	}
}
