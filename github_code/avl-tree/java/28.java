package edu.miracosta.cs113;



public class AVLTree<E extends Comparable<E>> extends BinarySearchTreeWithRotate<E> {
	private boolean increase;
	private boolean decrease;

	@Override
	public boolean add(E item) {
		increase = false;
		decrease = false;
		root = add((AVLNode<E>) root, item);
		return addReturn;
	}

	/**
	 * Recursive add method. Inserts the given object into the tree. post:
	 * addReturn is set true if the item is inserted,false if the item is
	 * already in the tree.
	 * 
	 * @param localRoot
	 *            The local root of the subtree
	 * @param item
	 *            The object to be inserted
	 * @return The new local root of the subtree with the item inserted
	 * 
	 */

	private AVLNode<E> add(AVLNode<E> localRoot, E item) {

		if (localRoot == null) {
			addReturn = true;
			increase = true;
			return new AVLNode<E>(item);
		}
		if (item.compareTo(localRoot.data) == 0) {
			// Item is already in the tree.
			increase = false;
			addReturn = false;
			return localRoot;
		} else if (item.compareTo(localRoot.data) < 0) {
			// item < data
			localRoot.left = add((AVLNode<E>) localRoot.left, item);

			if (increase) {

				decrementBalance(localRoot);
				if (localRoot.balance < AVLNode.LEFT_HEAVY) {
					increase = false;
					return rebalanceLeft(localRoot);
				}

			}

		} else if (item.compareTo(localRoot.data) > 0) {
			localRoot.right = add((AVLNode<E>) localRoot.right, item);

			if (increase) {
				incrementBalance(localRoot);
				if (localRoot.balance > AVLNode.RIGHT_HEAVY) {
					increase = false;
					return rebalanceRight(localRoot);
				}

			}
		}
		return localRoot; // Rebalance not needed.

	}

	/**
	 * Helper Method. rebalances tree to the left that has become out of balance
	 * 
	 * @param localRoot
	 *            root to be rebalanced to the lett
	 * @return returns rebalanced tree
	 */
	private AVLNode<E> rebalanceLeft(AVLNode<E> localRoot) {
		AVLNode<E> nextLeft = (AVLNode<E>) localRoot.left;

		if (nextLeft.balance > AVLNode.BALANCED) {
			AVLNode<E> nextLeftRight = (AVLNode<E>) localRoot.left.right;

			if (nextLeftRight.balance < AVLNode.BALANCED) {
				incrementBalance(nextLeftRight);
				incrementBalance(localRoot);
			} else if (nextLeftRight.balance > AVLNode.BALANCED) {
				decrementBalance(nextLeftRight);
				decrementBalance(nextLeft);
			}

			decrementBalance(nextLeft);
			localRoot.left = rotateLeft(localRoot.left);
			incrementBalance(localRoot);
			incrementBalance(localRoot);

			return (AVLTree<E>.AVLNode<E>) rotateRight(localRoot);

		} else {

			incrementBalance(nextLeft);

			incrementBalance(localRoot);
			incrementBalance(localRoot);

			return (AVLTree<E>.AVLNode<E>) rotateRight(localRoot);

		}

	}

	/**
	 * Helper Method. rebalances tree to the right that has become out of
	 * balance
	 * 
	 * @param localRoot
	 *            root to be rebalanced to the right
	 * @return returns rebalanced tree
	 */
	private AVLNode<E> rebalanceRight(AVLNode<E> localRoot) {
		AVLNode<E> nextRight = (AVLNode<E>) localRoot.right;

		if (nextRight.balance > AVLNode.BALANCED) {
			decrementBalance(nextRight);
			decrementBalance(localRoot);
			decrementBalance(localRoot);

			return (AVLTree<E>.AVLNode<E>) rotateLeft(localRoot);
		} else {
			AVLNode<E> rightLeft = (AVLNode<E>) localRoot.right.left;
			incrementBalance((AVLNode<E>) localRoot.right);

			if (rightLeft.balance < AVLNode.BALANCED) {
				incrementBalance(nextRight);
				incrementBalance((AVLNode<E>) nextRight.left);

			} else if (rightLeft.balance > AVLNode.BALANCED) {
				decrementBalance(localRoot);
				decrementBalance((AVLNode<E>) nextRight.left);
			}

			localRoot.right = rotateRight(localRoot.right);

			decrementBalance(localRoot);
			decrementBalance(localRoot);

			return (AVLTree<E>.AVLNode<E>) rotateLeft(localRoot);

		}
	}

	/**
	 * Helper Method. decrements the balance of a node
	 * 
	 * @param node
	 *            node whos balance is to be decremented
	 * 
	 */
	private void decrementBalance(AVLNode<E> node) {
		// Decrement the balance.
		node.balance--;
		if (node.balance == AVLNode.BALANCED) {
			/** If now balanced, overall height has not increased. */
			increase = false;
		}
	}

	/**
	 * Helper Method. increments the balance of a node
	 * 
	 * @param node
	 *            node whos balance is to be increments
	 * 
	 */
	private void incrementBalance(AVLNode<E> node) {
		// Decrement the balance.
		node.balance++;
		if (node.balance == AVLNode.BALANCED) {
			/** If now balanced, overall height has not increased. */
			increase = false;
		}
	}

	/**
	 * removes target from tree and returns it
	 * 
	 * @param target
	 *            target to be removed from tree
	 * @return returns target if found and removed. otherwise, returns null
	 */
	@Override
	public E delete(E target) {

		increase = false;
		decrease = false;
		deleteReturn = null;
		root = delete((AVLNode<E>) root, target);
		return deleteReturn;
	}

	
	/**
	 * Helper Method. deletes the target node if in tree.
	 * 
	 * @param localRoot
	 *            current root being examined
	 * @param target
	 *            data to be removed
	 * @return returns reference to the node that containds the data to be
	 *         removed. otherwise returns false
	 */
	private Node<E> delete(AVLNode<E> localRoot, E target) {
		if (localRoot == null) {
			deleteReturn = null;

		} else {

			int compResult = target.compareTo(localRoot.data);
			if (compResult == 0) {
				deleteReturn = localRoot.data;
				decrease = true;

				if (localRoot.left == null && localRoot.right == null) {
					return null;
				} else if (localRoot.left == null) {
					//decrease = true;
					return localRoot.right;

				} else if (localRoot.right == null) {
					//decrease = true;
					return localRoot.left;
				} else if (localRoot.left.right == null) {
					//decrease = true;
					localRoot.data = localRoot.left.data;
					localRoot.left = localRoot.left.left;
					incrementBalance(localRoot);

					if (localRoot.balance > AVLNode.RIGHT_HEAVY) {
						increase = false;
						return rebalanceRight(localRoot);
					}
					return localRoot;
				} else {
					localRoot.data = rightmostNodeDataAndRemove((AVLNode<E>) localRoot.left, localRoot);
					if (decrease) {
						incrementBalance(localRoot);
						if (localRoot.balance > AVLNode.RIGHT_HEAVY) {
							return rebalanceLeft(localRoot);
						}
					}
					return localRoot;
				}

			} else if (compResult < 0) {
				// item is less than localRoot.data
				localRoot.left = delete((AVLNode<E>) localRoot.left, target);
				if (decrease) {
					incrementBalance(localRoot);
					if (localRoot.balance > AVLNode.RIGHT_HEAVY) {
						return rebalanceRight(localRoot);
					}
				}
			} else {
				// item is greater than localRoot.data
				localRoot.right = delete((AVLNode<E>) localRoot.left, target);
				if (decrease) {
					decrementBalance(localRoot);
					if (localRoot.balance < AVLNode.LEFT_HEAVY) {
						return rebalanceLeft(localRoot);
					}
				}
			}

		}

		return localRoot;
	}

	/**
	 * Helper method. finds the rightmost node, returns its data and removes
	 * that node
	 * 
	 * @param localRoot
	 *            current root being examined
	 * @param parentRoot
	 *            local roots parent
	 * @return returns data of rightmost root
	 */

	private E rightmostNodeDataAndRemove(AVLNode<E> localRoot, AVLNode<E> parentRoot) {
		
		if (localRoot.right == null) {
			E temp = localRoot.data;
			localRoot = (AVLNode<E>) localRoot.left;
			decrease = false;
			
			if (parentRoot.left == null) {
				decrease = true;
				decrementBalance(parentRoot);
			}
			parentRoot.right = localRoot;
			return temp;
		} else {

			return rightmostNodeDataAndRemove((AVLNode<E>) localRoot.right, localRoot);
		}
	}

	@SuppressWarnings("serial")
	private class AVLNode<E> extends BinaryTree.Node<E> {
		private static final int LEFT_HEAVY = -1;
		private static final int RIGHT_HEAVY = 1;
		private static final int BALANCED = 0;
		private int balance;

		/**
		 * Constructor for AVLNode
		 * 
		 * @param data
		 *            data to be inserted into new AVLNode
		 */
		public AVLNode(E data) {
			super(data);
			balance = 0;
		}

		@Override
		public String toString() {
			return data.toString() + " (" + balance + ")";
		}

	}

}
