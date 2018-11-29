
import java.util.*;


/**
 * Implementation of an AVL Tree 
 */

public class AVLTree {
	/** Root of the AVL tree. */
	public Node root;

	/**
	 * The constructor creating a binary search tree with just a
	 * null, which is the root.
	 */
	public AVLTree() {
		root = null;
	}

	
	/**
     * Builds tree from sorted ArrayList of AvlTreeNode objects. This runs in O(n) time.
     * @param size Number of events to be added to the tree.
     * @param iterator This iterator has the Event objects to be read.
     */
    public void buildTreeFromSortedList(int size, Iterator<Node> iterator) {
        root = buildTree(0, 0, size - 1, iterator);
        avlBalance(root);
    }

    /**
     * Builds the tree by placing the middle element to current position. Places [begin; middle) elements to left
     * subtree and (middle, end) elements to right subtree.
     * @param currentLevel The current level of the tree.
     * @param begin The starting index of the subtree.
     * @param end The ending index of the subtree.
     * @param iterator The Event objects are read from this ArrayList Iterator.
     * @return The root of the subtree.
     */
    private Node buildTree(int currentLevel, int begin, int end, Iterator<Node> iterator) {
        if(end < begin) {
            return null;
        }
        int mid = (begin + end) / 2;
        Node left = null;
        if(begin < mid) {
            left = buildTree(currentLevel + 1, begin, mid - 1, iterator);
        }

        Node middle = iterator.next();

        if(left != null) {
            middle.left = left;
            left.parent = middle;
        }

        if(mid < end) {
        	Node right = buildTree(currentLevel + 1, mid + 1, end, iterator);
            if(right != null) {
                middle.right = right;
                right.parent = middle;
            }
        }

        return middle;
    }
    
	/**
	 * Searches the tree for a node with a given ID.
	 * @param a  The ID being searched for.
	 * @return Returns the Node which contains the ID
	 */
	public Node search(int a) {
		Node avlTreeNode = search(root, a);
		return avlTreeNode;
	} 

	/**
	 * Searches the subtree rooted at a given node for a node with a given ID.
	 * @param avlTreeNode  Root of the subtree.          
	 * @param a The ID being searched for.
	 * @return A reference to a Node object with ID 
	 *         if such a node exists.If no node exists, returns Null.       
	 */
	protected Node search(Node avlTreeNode, int a) {
		while ((avlTreeNode != null) && (a != avlTreeNode.ID)) {
			if (a < avlTreeNode.ID)
				avlTreeNode = avlTreeNode.left;
			else
				avlTreeNode = avlTreeNode.right;
		}

		if (avlTreeNode != null) {
			return avlTreeNode;
		} else {
			return null;
		}
	} 

	/**
	 * Returns the successor of a given node in an in-order walk of the tree.
	 * @param  avlTreeNode The node whose successor is returned.
	 * @return successor node is returned.
	 */
	protected Node successor(Node avlTreeNode) {
		Node tempNodeA = avlTreeNode;

		if (tempNodeA.right != null)
			return treeMinimum(tempNodeA.right);

		Node tempNodeB = tempNodeA.parent;
		while (tempNodeB != null && tempNodeA == tempNodeB.right) {
			tempNodeA = tempNodeB;
			tempNodeB = tempNodeB.parent;
		}

		return tempNodeB;
	} 


	/**
	 * Inserts a ID and a count item into the tree, creating a new node for this
	 * ID and count pair.
	 * @param ID and Count.
	 */
	public void insert(int ID, int count) {
		Node n = new Node(ID, count);
		avlInsert(this.root, n);
	} 


	// If node to compare is null, the node is inserted. If the root is
			// null, it is the root of the tree.
	// If compare node is smaller, continue with the left node
	// Node is inserted now, continue checking the balance

	// Node is inserted now, continue checking the balance
	// do nothing: This node already exists
	public void avlInsert(Node avlNodeA, Node avlNodeB) {
		if (avlNodeA == null) {
			this.root = avlNodeB;
		} else {
			if (avlNodeB.ID < avlNodeA.ID) {
				if (avlNodeA.left == null) {
					avlNodeA.left = avlNodeB;
					avlNodeB.parent = avlNodeA;
					avlBalance(avlNodeA);
				} else {
					avlInsert(avlNodeA.left, avlNodeB);
				}

			} else if (avlNodeB.ID > avlNodeA.ID) {
				if (avlNodeA.right == null) {
					avlNodeA.right = avlNodeB;
					avlNodeB.parent = avlNodeA;
					avlBalance(avlNodeA);
				} else {
					avlInsert(avlNodeA.right, avlNodeB);
				}
			} 
		}
	}

	/**
	  * Making sure the avlTree property holds true for each node by invoking the relevant rotations
	  * @param currentNode : The node whose balance is not as per avlTree definition 
	  */
	public void avlBalance(Node currentNode) {
		setBalance(currentNode);
		int balance = currentNode.balance;
		if (balance == -2) {
			if (height(currentNode.left.left) >= height(currentNode.left.right)) {
				currentNode = avlRotateRight(currentNode);
			} else {
				currentNode = avlRotateLeftRight(currentNode);
			}
		} else if (balance == 2) {
			if (height(currentNode.right.right) >= height(currentNode.right.left)) {
				currentNode = avlRotateLeft(currentNode);
			} else {
				currentNode = avlRotateRightLeft(currentNode);
			}
		}
		if (currentNode.parent != null) {
			avlBalance(currentNode.parent);
		} else {
			this.root = currentNode;
		}
	}
	 
/**
 * set balance function	
 */
	
	 private void setBalance(Node avlTreeNode) {
		  avlTreeNode.balance = height(avlTreeNode.right)-height(avlTreeNode.left);
		 }
/**
 * Get the height of the node	 
 */
	 
	 
	private int height(Node avlTreeNode) {
		if (avlTreeNode == null) {
			return -1;
		}
		if (avlTreeNode.left == null && avlTreeNode.right == null) {
			return 0;
		} else if (avlTreeNode.left == null) {
			return 1 + height(avlTreeNode.right);
		} else if (avlTreeNode.right == null) {
			return 1 + height(avlTreeNode.left);
		} else {
			return 1 + Math.max(height(avlTreeNode.left), height(avlTreeNode.right));
		}
	}
		 
	 /**
	  * Left rotation using the given node.
	  * @param avlTreeNode The node for the rotation.
	  * @return The root of the rotated tree.
	  */
	public Node avlRotateLeft(Node avlTreeNode) {

		Node tempNode = avlTreeNode.right;
		tempNode.parent = avlTreeNode.parent;

		avlTreeNode.right = tempNode.left;

		if (avlTreeNode.right != null) {
			avlTreeNode.right.parent = avlTreeNode;
		}

		tempNode.left = avlTreeNode;
		avlTreeNode.parent = tempNode;

		if (tempNode.parent != null) {
			if (tempNode.parent.right == avlTreeNode) {
				tempNode.parent.right = tempNode;
			} else if (tempNode.parent.left == avlTreeNode) {
				tempNode.parent.left = tempNode;
			}
		}

		setBalance(avlTreeNode);
		setBalance(tempNode);

		return tempNode;
	}
	 
	 /**
	  * Right rotation using the given node.
	  * @param avlTreeNode The node for the rotation
	  * @return The root of the new rotated tree.
	  */
	public Node avlRotateRight(Node avlTreeNode) {

		Node tempNode = avlTreeNode.left;
		tempNode.parent = avlTreeNode.parent;

		avlTreeNode.left = tempNode.right;

		if (avlTreeNode.left != null) {
			avlTreeNode.left.parent = avlTreeNode;
		}

		tempNode.right = avlTreeNode;
		avlTreeNode.parent = tempNode;

		if (tempNode.parent != null) {
			if (tempNode.parent.right == avlTreeNode) {
				tempNode.parent.right = tempNode;
			} else if (tempNode.parent.left == avlTreeNode) {
				tempNode.parent.left = tempNode;
			}
		}

		setBalance(avlTreeNode);
		setBalance(tempNode);

		return tempNode;
	}
	
	 /**
	  * @param avlTreeNode The node for the rotation.
	  * @return The root after the double rotation.
	  */
	
	public Node avlRotateLeftRight(Node avlTreeNode) {
		avlTreeNode.left = avlRotateLeft(avlTreeNode.left);
		return avlRotateRight(avlTreeNode);
	}
	 
	 /** 
	  * @param avlTreeNode The node for the rotation.
	  * @return The root after the double rotation.
	  */
	
	public Node avlRotateRightLeft(Node avlTreeNode) {
		avlTreeNode.right = avlRotateRight(avlTreeNode.right);
		return avlRotateLeft(avlTreeNode);
	}

	 /**
	  * Removes a node from the tree, if it is existent.
	  */
	public void remove(int ID) {
		avlRemoveNode(this.root, ID);
	}
	 
	 /**
	  * Finds a node and calls a method to remove the node. 
	  * @param avlTreeNode The node to start the search.
	  * @param val The ID of node to remove.
	  */
	public void avlRemoveNode(Node avlTreeNode, int val) {
		if (avlTreeNode == null) {
			return;
		} else {
			if (avlTreeNode.ID > val) {
				avlRemoveNode(avlTreeNode.left, val);
			} else if (avlTreeNode.ID < val) {
				avlRemoveNode(avlTreeNode.right, val);
			} else if (avlTreeNode.ID == val) {
				removeFoundNode(avlTreeNode);
			}
		}
	}
	 
	 /**
	  * Removes a node from a AVL-Tree, while balancing will be done if necessary.
	  * @param avlTreeNode The node to be removed.
	  */
	public void removeFoundNode(Node avlTreeNode) {
		Node tempNode1;
		if (avlTreeNode.left == null || avlTreeNode.right == null) {
			if (avlTreeNode.parent == null) {
				this.root = null;
				avlTreeNode = null;
				return;
			}
			tempNode1 = avlTreeNode;
		} else {
			tempNode1 = successor(avlTreeNode);
			avlTreeNode.ID = tempNode1.ID;
		}
		Node tempNode2;
		if (tempNode1.left != null) {
			tempNode2 = tempNode1.left;
		} else {
			tempNode2 = tempNode1.right;
		}
		if (tempNode2 != null) {
			tempNode2.parent = tempNode1.parent;
		}
		if (tempNode1.parent == null) {
			this.root = tempNode2;
		} else {
			if (tempNode1 == tempNode1.parent.left) {
				tempNode1.parent.left = tempNode2;
			} else {
				tempNode1.parent.right = tempNode2;
			}
			avlBalance(tempNode1.parent);
		}
		tempNode1 = null;
	}

	
	  /**
     * Finds the predecessor of the input ID in the sorted order determined by an inorder traversal.
     * @param avlTreeNode The subtree node to be searched for predecessor.
     * @param ID The ID whose predecessor is to be determined.
     * @return The node with the greatest ID smaller than the input ID.
     */
    public Node treePredecessor(Node avlTreeNode, int ID) {
        if(avlTreeNode == null) {
            return null;
        }
        if(avlTreeNode.ID == ID) {
            if(avlTreeNode.left != null) {
                return treeMaximum(avlTreeNode.left);
            } else {
                Node parentNode = avlTreeNode.parent;
                Node childNode = avlTreeNode;
                while (parentNode != null && childNode == parentNode.left) {
                    childNode = parentNode;
                    parentNode = parentNode.parent;
                }
                return parentNode;
            }
        }
        if(ID < avlTreeNode.ID) {
            return treePredecessor(avlTreeNode.left, ID);
        }
        Node temp = treePredecessor(avlTreeNode.right, ID);
        if(temp != null) {
            return temp;
        } else {
            return avlTreeNode;
        }
    }

    /**
     * Finds the successor of the input ID in the sorted order determined by an inorder traversal.
     * @param avlTreeNode The subtree node to be searched for successor.
     * @param ID The ID whose successor is to be determined.
     * @return The node with the smallest ID greater than the input ID.
     */
    public Node treeSuccessor(Node avlTreeNode, int ID) {
        if(avlTreeNode == null) {
            return null;
        }
        if(avlTreeNode.ID == ID) {
            if(avlTreeNode.right != null) {
                return treeMinimum(avlTreeNode.right);
            } else {
                Node parentNode = avlTreeNode.parent;
                Node childNode = avlTreeNode;
                while (parentNode != null && childNode == parentNode.right) {
                    childNode = parentNode;
                    parentNode = parentNode.parent;
                }
                return parentNode;
            }
        }
        if(ID < avlTreeNode.ID) {
            Node temp = treeSuccessor(avlTreeNode.left, ID);
            if (temp != null) {
                return temp;
            } else {
                return avlTreeNode;
            }
        }
        return treeSuccessor(avlTreeNode.right, ID);
    }

    /**
     * Stores all nodes in the tree whose IDs are in the range between ID1 and ID2.
     * @param rootNode The root node of the tree.
     * @param ID1 The left limit of the range.
     * @param ID2 The right limit of the range.
     * @param nodesInRange The ArrayList which stores the found nodes.
     * @return The ArrayList containing nodes between the range of ID1 and ID2.
     */
    public ArrayList<Node> rangeSearch(Node rootNode, int ID1, int ID2,
                                                   ArrayList<Node> nodesInRange) {
        if(rootNode != null) {
            if(rootNode.ID > ID1) {
                nodesInRange = rangeSearch(leftChildOf(rootNode), ID1, ID2, nodesInRange);
            }

            if(rootNode.ID >= ID1 && rootNode.ID <= ID2) {
                nodesInRange.add(rootNode);
            }

            if(rootNode.ID < ID2) {
                nodesInRange = rangeSearch(rightChildOf(rootNode), ID1, ID2, nodesInRange);
            }
        }

        return nodesInRange;
    }

    /**
     * Returns the left child of a node. Returns null if the input node is null.
     * @param avlTreeNode The node whose left child is needed.
     * @return The left child of avlTreeNode.
     */
    private static Node leftChildOf(Node avlTreeNode) {
        if(avlTreeNode == null) {
            return null;
        } else {
            return avlTreeNode.left;
        }
    }
    
    /**
     * Returns the right child of a node. Returns null if the input node is null.
     * @param avlTreeNode The node whose right child is requested.
     * @return The right child of avlTreeNode.
     */
    private static Node rightChildOf(Node avlTreeNode) {
        if(avlTreeNode == null) {
            return null;
        } else {
            return avlTreeNode.right;
        }
    }
    
    /**
     * Finds element in a tree whose ID is a minimum.
     * @param avlTreeNode The node which is a root of the subtree which needs to be searched for minimum.
     * @return The node containing the minimum element in the subtree rooted at avlTreeNode.
     */
    
    public Node treeMinimum(Node avlTreeNode) {
        while (avlTreeNode.left != null) {
            avlTreeNode = avlTreeNode.left;
        }
        return avlTreeNode;
    }
    
    /**
     * Finds element in a tree whose ID is a maximum.
     * @param avlTreeNode The node which is a root of the subtree which needs to be searched for maximum.
     * @return The node containing the maximum element in the subtree rooted at avlTreeNode.
     */
    
    public Node treeMaximum(Node avlTreeNode) {
        while (avlTreeNode.right != null) {
            avlTreeNode = avlTreeNode.right;
        }
        return avlTreeNode;
    }
 
   
    
}