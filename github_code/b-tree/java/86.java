package main.datastructures.tree;

import java.util.ArrayList;
import java.util.List;

public class Tree {

	private int value = 0;
	private Tree leftTree = null;
	private Tree rightTree = null;

	// TODO - add delete(int value) method
	public Tree(int value, Tree firstChild, Tree secondChild) {

		this.value = value;

		if (firstChild != null) {
			if (firstChild.value < value) {
				this.leftTree = firstChild;
				this.rightTree = secondChild;
			} else if (firstChild.value > value) {
				this.leftTree = secondChild;
				this.rightTree = firstChild;
			}
		}
		if (secondChild != null) {
			if (secondChild.value > value) {
				this.leftTree = firstChild;
				this.rightTree = secondChild;
			} else if (secondChild.value < value) {
				this.leftTree = secondChild;
				this.rightTree = firstChild;
			}
		}
	}

	public Tree(int value) {

		this.value = value;

	}

	/**
	 * Inserts a given tree into this tree
	 * 
	 * @param newSection
	 */
	public void insert(Tree newSection) {
		insert(this, newSection);
	}

	/**
	 * Implementation of insert Inserts a given tree into another tree
	 * 
	 * @param tree
	 * @param newSection
	 */
	private void insert(Tree tree, Tree newSection) {

		// If value less than tree.value, go left, else right
		if (newSection.value < tree.value) {
			if (tree.leftTree == null) {
				tree.leftTree = newSection;
			}
			insert(tree.leftTree, newSection);
		} else if (newSection.value > tree.value) {
			if (tree.rightTree == null) {
				tree.rightTree = newSection;
			}
			insert(tree.rightTree, newSection);

		}
	}

	/**
	 * Searches this tree for a value
	 * 
	 * @param value
	 * @return true if value in tree, else false
	 */
	public boolean search(int value) {
		return search(this, value);
	}

	/**
	 * Implementation of search Searches a given tree for a value
	 * 
	 * @param tree
	 * @param value
	 * @return true if value in tree, else false
	 */
	private boolean search(Tree tree, int value) {

		if (tree == null) {
			return false;
		}

		// If value less than tree.value, go left, else right
		if (value < tree.value) {
			return search(tree.leftTree, value);
		} else if (value > tree.value) {
			return search(tree.rightTree, value);
		} else if (value == tree.value) {
			return true;
		}

		return false;
	}

	/**
	 * Traverses a tree by visiting its left branch, then the node, then its right
	 * branch
	 * 
	 * @param tree
	 * @return
	 */
	public List<Integer> inOrderTraversal() {

		ArrayList<Integer> nodes = new ArrayList<>();

		return inOrderTraversal(this, nodes);

	}

	// Implementation of the preOrderTraversal method
	private ArrayList<Integer> inOrderTraversal(Tree tree, ArrayList<Integer> nodes) {

		if (tree.leftTree != null) {
			inOrderTraversal(tree.leftTree, nodes);
		}

		nodes.add(tree.value);

		if (tree.rightTree != null) {
			inOrderTraversal(tree.rightTree, nodes);
		}
		return nodes;
	}

	/**
	 * Traverses a tree by visiting its left branch, then its right branch, then the
	 * node
	 * 
	 * @param tree
	 * @return
	 */
	public List<Integer> postOrderTraversal() {

		ArrayList<Integer> nodes = new ArrayList<>();

		return postOrderTraversal(this, nodes);

	}

	// Implementation of the preOrderTraversal method
	private List<Integer> postOrderTraversal(Tree tree, ArrayList<Integer> nodes) {

		if (tree.leftTree != null) {
			postOrderTraversal(tree.leftTree, nodes);
		}

		if (tree.rightTree != null) {
			postOrderTraversal(tree.rightTree, nodes);
		}

		nodes.add(tree.value);
		return nodes;
	}

	/**
	 * Traverses a tree by visiting a node, then its left branch, then its right
	 * branch
	 * 
	 * @param tree
	 * @return
	 */
	public List<Integer> preOrderTraversal() {

		ArrayList<Integer> nodes = new ArrayList<>();

		return preOrderTraversal(this, nodes);

	}

	// Implementation of the preOrderTraversal method
	private ArrayList<Integer> preOrderTraversal(Tree tree, ArrayList<Integer> nodes) {

		nodes.add(tree.value);

		if (tree.leftTree != null) {
			preOrderTraversal(tree.leftTree, nodes);
		}

		if (tree.rightTree != null) {
			preOrderTraversal(tree.rightTree, nodes);
		}
		return nodes;
	}

	public List<Integer> breadthFirstTraversal() {

		ArrayList<Tree> nodes = new ArrayList<>();
		ArrayList<Integer> values = new ArrayList<>();

		// Add the current node to the node list
		nodes.add(this);

		// Iterate through the nodes, using the nodes list to queue up child trees
		// Iterator<Tree> treeIterator = nodes.iterator();
		Tree currentTree = this;
		int i = 0;
		while (currentTree != null) {

			// Add the current value to the values list
			values.add(currentTree.value);

			// Queue up the child trees if they exist
			if (currentTree.leftTree != null) {
				nodes.add(currentTree.leftTree);
			}
			if (currentTree.rightTree != null) {
				nodes.add(currentTree.rightTree);
			}

			// Move to the next tree if possible
			i++;
			try {
				currentTree = nodes.get(i);
			} catch (IndexOutOfBoundsException outOfBounds) {
				currentTree = null;
			}

		}

		return values;

	}

	public boolean delete(int value) {

		return delete(this, value);
	}

	private boolean delete(Tree tree, int value) {

		// If the node isn't in the tree then just return false
		if (!this.search(value)) {
			return false;
		}

		// Otherwise find parent of the node by following left/right trees
		if (tree.leftTree.value == value || tree.rightTree.value == value) {
			// If a node has a left/right tree with the correct value then we've found the
			// parent
			Tree toDelete = (tree.leftTree.value == value) ? tree.leftTree : tree.rightTree;

			// Handle the deletion depending on number of children
			if (toDelete.leftTree == null && toDelete.rightTree == null) {
				// If node is a leaf we can just delete
				if (tree.leftTree.value == value) {
					tree.leftTree = null;
				} else {
					tree.rightTree = null;
				}

				return true;

			} else if (toDelete.leftTree == null || toDelete.rightTree == null) {
				// If node just has one child then just point its parent to its child
				if (toDelete.leftTree != null) {
					tree.leftTree = toDelete.leftTree;
				} else {
					tree.rightTree = toDelete.rightTree;
				}

				return true;

			} else {
				/*
				 * Otherwise the node to be deleted has two children so we need to replace it
				 ** with either the largest node in the left subtree or the smallest in the right
				 ** subtree
				 */

				// Don't always choose the same option to help keep the tree balanced
				Tree nodeToSwap = (value % 2 == 0) ? getLargest(toDelete.leftTree) : getSmallest(toDelete.rightTree);

				// Make a new node with the replacement value and the deleted node's subtrees
				Tree swappedNode = new Tree(nodeToSwap.value, toDelete.leftTree, toDelete.rightTree);

				// Delete the node that has been swapped for the deleted node
				delete(tree, nodeToSwap.value);

				return true;

			}

		} else if (value < tree.value) {
			delete(tree.leftTree, value);
		} else if (value > tree.value) {
			delete(tree.rightTree, value);
		}
		
		// catch all
		return false;

	}
	
	private Tree getLargest(Tree tree) {
		Tree currNode = tree;
		
		while(currNode.rightTree != null) {
			currNode = currNode.rightTree;
		}
		
		return currNode;
	}
	
	private Tree getSmallest(Tree tree) {
		Tree currNode = tree;
		
		while(currNode.leftTree != null) {
			currNode = currNode.leftTree;
		}
		
		return currNode;
	}

}
