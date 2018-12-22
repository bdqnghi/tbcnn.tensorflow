package lab3AndAnd;

/**
 * 
 * Created by @author Andreas Andersson, Systemutveckling on 2015-09-25.
 *
 * AvlTree inserts/deletes,prints,finds, balances and rotates nodes/the entire tree.
 * Communicates with TreeNode to create the tree-structure and an effective algorithm. 
 */


public class AvlTree {		

    private int size;
    private TreeNode root;  
   
    /**
     * Adds a new TreeNode to the AVL-Tree, the parameter is the new TreeNodes key/value.
     * Uses the "insert" method.
     * @param data -the key/Value to the new TreeNode.
     */
    public void add(int data){	
        TreeNode newNode= new TreeNode(data); 
     
         insert(root,newNode,data);	
           
         size++;

    }
    
    /**
     * Returns the number of TreeNodes in the AVL-Tree.
     * @return int
     */
    public int getSize(){		
    	return size;
    }
   
    /**
     * This method is used to Delete a TreeNode from the Tree.
     *  Calls the "Remove" method. The parameter int"Data" is used as
     *  KEY to locate the TreeNode.
     * @param data -The TreeNodes key.
     */
    public void delete(int data){	
       remove(root, data); 
        
    }
    
    /**
     * This method compares a TreeNode to the given KEY to find the
     * TreeNode that should be removed. 
     * @param node	- The TreeNode to compare with the Key.
     * @param key -The Key to the TreeNode that will be removed.
     */
    public void remove(TreeNode node,int key) {
    	
  	  if(node==null) {
  	   
  	  } else {
  		  int data=node.getData();
  	   if(data>key)  {
  	    remove(node.getLeft(),key);
  	   } else if(data<key) {
  	    remove(node.getRight(),key);
  	   } else if(data==key) {
  	   
  	    removeFoundNode(node);
  	    System.out.println("Delete '"+key+"' Genomförd.");
  	    size--;
  	   }
  	  }
  	 }
   
    /**
     * This method executes the "Deletion" of the node and 
     * connects the Affected TreeNodes plus Re-balances and rotates the new Avl-Tree.
     * nodeToRemove is the TreeNode that will be Deleted.
     * @param nodeToRemove - the TreeNode that will be removed.
     */
    public void removeFoundNode(TreeNode nodeToRemove) {	
		
    	Boolean rootRemoved=true;
    	TreeNode remove;

		if (nodeToRemove.getLeft() == null || nodeToRemove.getRight() == null) {

			if (nodeToRemove.getParent() == null) {
				this.root = null;
				nodeToRemove = null;
				rootRemoved=false;
			}
			remove = nodeToRemove;
		} else {

			remove = findSuccessor(nodeToRemove);
			nodeToRemove.setData(remove.getData());
		}
		if(rootRemoved){
		TreeNode node;
		TreeNode removeParent=remove.getParent();
		TreeNode removeLeft=remove.getLeft();
		
		if (removeLeft != null) {
			node = removeLeft;
		} else {
			node = remove.getRight();
		}

		if (node != null) {
			node.setParent(removeParent);
		}

		if (removeParent == null) {
			this.root = node;
		} else {		
			if (remove == removeParent.getLeft()) {
				removeParent.setLeft(node);
			} else {
				removeParent.setRight(node);
			}

			balanceNodes(removeParent);
		}
		remove = null;
		}
	}
     
    /**
     * Inserts a new TreeNode into the Avl-tree. newNode is the TreeNode to Insert, current 
     * is used to compare values to find the right location for the new TreeNode.
     *  Value is simply newNode's "Key" and Value. 
     *  Compares Higher/Lower Key/Value to find the right sub-tree and node to insert in.
     * @param current -the current TreeNode to compare to.
     * @param newNode -The new TreeNode to insert.
     * @param value	-The new Node's Key/Value.
     */
    public void insert(TreeNode current,TreeNode newNode, int value){	
    	
		if (current == null) {
			root = newNode;
		} else {

			TreeNode right = current.getRight();
			TreeNode left = current.getLeft();

			if (value < current.getData()) {
				if (left == null) {
					current.setLeft(newNode);
					newNode.setParent(current);

					balanceNodes(current);
					System.out.println("Insert "+value+ " Genomförd.");
				} else {
					insert(left, newNode, value);
				}
			} else if (value > current.getData()) {
				if (right == null) {
					newNode.setParent(current);
					current.setRight(newNode);

					balanceNodes(current);
					System.out.println("Insert "+value+ " Genomförd.");
				} else {
					insert(right, newNode, value);
				}
			} else {
				System.out.println("Värdet '" + value + "' finns redan");
			}
		}
		
    }
         
    /**
     * This method controls the weight of the Treenodes subtree's. If it's "Heavy" /to many TreeNodes
     * in one subtree compared to the other- a rotation will be performed to "Balance" the tree.
     * @param node -the node to balance/control balance.
     */
    public void balanceNodes(TreeNode node){	
    	
		setBalance(node);
		int balance = node.getBalance();

		if (balance == -2) {
			TreeNode nodeLeft = node.getLeft();

			if (height(nodeLeft.getLeft()) >= height(nodeLeft.getRight())) {
				node = rotateRight(node);
			} else {
				node.setLeft(rotateLeft(nodeLeft));
				node = rotateRight(node);
			}
		} else if (balance == 2) {
			TreeNode nodeRight = node.getRight();
			if (height(nodeRight.getRight()) >= height(nodeRight.getLeft())) {
				node = rotateLeft(node);
			} else {
				node.setRight(rotateRight(nodeRight));
				node = rotateLeft(node);
				
			}
		}

		if (node.getParent() != null) {
			balanceNodes(node.getParent());
		} else {
			this.root = node;
			
		}
    }
    
    /**
     * Set's the TreeNode's Balance-value by comparing the "Height" of
     * it's right and left sub-tree.
     * @param node -The TreeNode that will have a new balance-value.
     */
    private void setBalance(TreeNode node) {	
  	  node.setBalance(height(node.getRight())-height(node.getLeft())) ;
  	 }
    
    /**
     * Uses a TreeNode and returns an int with the nodes height value.
     * Height=number of subtree-nodes.
     * @param node - The TreeNode that will control/Count its sub-trees height.
     * @return int
     */
    private int height(TreeNode node) {	 	 
    	
		if (node == null) {
			return -1;
		}

		TreeNode left = node.getLeft();
		TreeNode right = node.getRight();

		if (left == null && right == null) {
			return 0;
		} else if (left == null) {
			return 1 + height(right);
		} else if (right == null) {
			return 1 + height(left);
		} else {
			return 1 + heighest(height(left), height(right));
		}
  	 }
    
    /**
     * Returns an int with the heighest value of the two parameters: left and right.
     * @param left -int with height for the left subtree of a TreeNode
     * @param right -int with height for the right subtree of a TreeNode
     * @return int
     */
    private int heighest(int left, int right) {	
		
    	if (left >= right) {
			return left;
		} else {
			return right;
		}
  	 }

    /**
     * Recieves an Unbalanced TreeNode that needs a Rotation to the Left
     * and returns a TreeNode.
     * @param node -the Node to rotate.
     * @return TreeNode
     */
    public TreeNode rotateLeft(TreeNode node){	

		TreeNode nRight = node.getRight();
		nRight.setParent(node.getParent());
		TreeNode nRP = nRight.getParent();

		node.setRight(nRight.getLeft());

		TreeNode newNR = node.getRight();

		if (newNR != null) {
			newNR.setParent(node);
		}

		nRight.setLeft(node);
		node.setParent(nRight);

		if (nRP != null) {
			if (nRP.getRight() == node) {
				nRP.setRight(nRight);
			} else if (nRP.getLeft() == node) {
				nRP.setLeft(nRight);
			}
		}

		setBalance(node);
		setBalance(nRight);

		return nRight;
    }
  
    /**
     * Recieves an Unbalanced TreeNode that needs a Rotation to the Right
     * and returns a TreeNode.
     * @param node -the Node to rotate.
     * @return TreeNode
     */
    public TreeNode rotateRight(TreeNode node){		

		TreeNode left = node.getLeft();
		left.setParent(node.getParent());

		node.setLeft(left.getRight());

		TreeNode nl = node.getLeft();

		if (nl != null) {
			nl.setParent(node);
		}

		left.setRight(node);
		node.setParent(left);

		TreeNode lp = left.getParent();

		if (lp != null) {
			if (lp.getRight() == node) {
				lp.setRight(left);
			} else if (lp.getLeft() == node) {
				lp.setLeft(left);
			}
		}

		setBalance(node);
		setBalance(left);

		return left;
    }
 
    /**
     * A search method to find a specific TreeNode with the Key/Value it takes as
     * parameter. Returns the found TreeNode.
     * @param value -the Key to search for
     * @return TreeNode
     */
    public TreeNode find(int value){		

		TreeNode findNode = find(value, root);
		if (findNode != null) {
			System.out.println("Värdet '" + value + "' hittades.");
		} else {
			System.out.println("Värdet '" + value + "' hittades inte.");
		}
		return findNode;
    }	
    
    /**
     * A search method to find a TreeNode with a special Key/value.
     * Recieves a parameter with a Key to the TreeNode, and a TreeNode to compare it to.
     * @param key - The Key/Value to the TreeNode we're looking for.
     * @param node -TreeNode to compare with the Key
     * @return TreeNode
     */
    public TreeNode find(int key, TreeNode node){		
    		
		if (node == null || node.getData() == key) {
			return node;
		} else if (key < node.getData()) {
			return find(key, node.getLeft());
		} else if (key > node.getData()) {
			return find(key, node.getRight());
		} else {
			return null;
		}
    		   
    }

    /**
     * Recieves a TreeNode to search after its right subtree's lowest
     * Value/Key and returns that TreeNode.
     * @param node - the TreeNode to search in
     * @return TreeNode
     */
    public TreeNode findSuccessor(TreeNode node) {		
    	
    	if (node.getRight() != null) {
			TreeNode right = node.getRight();

			while (right.getLeft() != null) {
				right = right.getLeft();
			}

			return right;
		} else {

			TreeNode parent = node.getParent();
			while (parent != null && node == parent.getRight()) {
				node = parent;
				parent = node.getParent();
			}
			return parent;
		}
	}
    
    /**
     * Prints the TreeNodes Key/Values sorted by number-order.
     * Take's an node and call it's children to get the lowest number and print it.
     * @param node -the node to print and/or get next node from.
     */
    public void inOrder(TreeNode node){		
		
    	if (node != null) {
			inOrder(node.getLeft());
			System.out.print(node.getData() + ", ");
			inOrder(node.getRight());
		}
    }
   
    /**
     * Returns this trees Root.
     * @return TreeNode
     */
    public TreeNode getRoot(){	
        return root;
    }
 
    /**
     * Prints the Entire AVL-Tree.
     */
    public void printTree(){ 
    	
        root.printTree();
    }
}
