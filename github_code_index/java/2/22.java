public class AvlTree {
	private AvlNode root;
	
	/*
	 * Iterate over the binary tree to find a specific node.
	 * Returns the node
	 * @params AvlNode root, int data
	 * @author Luke Pfeiffer
	 */
	public AvlNode search(AvlNode root, int data ) {
		AvlNode returnNode = null;
		if( root == null ) {
			return null;
	    } else if( root.getData() == data ) {
			return root;
		} else if ( root.getRight() == null && root.getLeft() == null ) {
			return null;
		}
		
		if( root.getData() <= data ) {
			returnNode = search( root.getLeft(), data );
		} else if( root.getData() > data ) {
			returnNode = search( root.getLeft(), data );
		}
		
		return returnNode;
	}
	
	/*
	 * Preorder traversal of the tree
	 * @params AvlNode root, StringBuilder sBuilder
	 * @author Luke Pfeiffer
	 */
	public String preOrder( AvlNode root, StringBuilder sBuilder ) {
		if( root == null ) {
			return sBuilder.toString();
		}
	    
		sBuilder.append( root.getData() + " " );
		if( root.getLeft() != null ) {
			preOrder( root.getLeft(), sBuilder );
		}
		
		if( root.getRight() != null ) {
			preOrder( root.getRight(), sBuilder);
		}
		
		return sBuilder.toString();
	}
	
	/*
	 * Return string of in order traversal of tree
	 * @params AvlNode root, StringBuilder sBuilder
	 * @author Luke Pfeiffer
	 */
	public String inOrder( AvlNode root, StringBuilder sBuilder ) {
		if( root == null ) {
			return sBuilder.toString();
		}
	    
		if( root.getLeft() != null ) {
			preOrder( root.getLeft(), sBuilder );
		}
		
		sBuilder.append( root.getData() + " " );

		if( root.getRight() != null ) {
			preOrder( root.getRight(), sBuilder);
		}
		
		return sBuilder.toString();
	}
	
	/*
	 * Returns string of post order traversal of tree
	 * @params AvlNode root, StringBuilder sBuilder
	 * @author Luke Pfeiffer
	 */
	
	public String postOrder( AvlNode root, StringBuilder sBuilder ) {
		if( root == null ) {
			return sBuilder.toString();
		}
	    
		if( root.getLeft() != null ) {
			preOrder( root.getLeft(), sBuilder );
		}

		if( root.getRight() != null ) {
			preOrder( root.getRight(), sBuilder);
		}
		
		sBuilder.append( root.getData() + " ");
		
		return sBuilder.toString();
	}


	/*
	 * Insert a new node into the tree like a normal binary search tree.
	 * The difference being that after each addition of a node, check the balance
	 * of the tree and balance if needed
	 * @params int data
	 * @author Luke Pfeiffer
	 */
	public AvlNode insert(AvlNode node, int data ) {
		
		//If root of tree is null, set root and return
	    if( this.root == null ) {
	    	this.root = new AvlNode( data );
	        return this.root;
	    }
	    
	    //If node is null, return a new node with data
	    if( node == null ) {
	    	return new AvlNode( data );
	    }
	    
	    //Normal insertion for binary tree
		if( data < node.getData() ) {
			node.setLeft( insert( node.getLeft(), data ) );
		} else if( data > root.getData() ) {
			node.setRight( insert( node.getRight(), data ));
		} else {
			return node;
		}
		
		//Set the new height of the node to be the max of its children
		node.setHeight( max( nodeHeight( node.getLeft()), nodeHeight( node.getRight() ) + 1 ) );
		
		//Get balance factor
		int balance = getBalanceFactor( node );
		
		//Left followed by left case
		if( balance > 1 && data < node.getLeft().getData() ) {
			return rotateRight( node );
		}
		
		//Right followed by right case
		if( balance < -1 && data > node.getRight().getData() ) {
			return rotateLeft( node );
		}
		
		//Left then right case
		if( balance > 1 && data > node.getLeft().getData() ) {
			node.setLeft( rotateLeft( node.getLeft() ) );
			return rotateRight( node );
		}
		
		//Right then left case;
		if( balance < -1 && data < node.getRight().getData() ) {
			node.setRight( rotateRight( node.getRight() ) );
			return rotateLeft( node );
		}
		
		return node;
	}
	
	private int getBalanceFactor( AvlNode node ) {
		if( node == null ) {
			return 0;
		}
		
		return nodeHeight( node.getLeft() ) - nodeHeight( node.getRight() );
	}
	
	//Utitility function to get max of two integers
	private int max( int a, int b ) {
		if( a > b ) {
			return a;
		} else {
			return b;	
		}
	}
	
	//Utitlity function to return height of a given node
	private int nodeHeight( AvlNode node ) {
		if( node == null ) {
			return 0;
		}
		
		return node.getHeight();
	}
	
	//Rotate the tree right around a given node
	private AvlNode rotateRight( AvlNode root ) {
		//Establisting temp variables
		AvlNode newRoot = root.getLeft();
		AvlNode tempTwo = newRoot.getRight();
		
		//Right rotation
		newRoot.setRight( root )	;
		root.setLeft( tempTwo );
		
		//Increment heights
		root.setHeight( max( nodeHeight( root.getLeft()), nodeHeight( root.getRight() ) ) + 1 );
		newRoot.setHeight( max( nodeHeight( newRoot.getLeft() ), nodeHeight( newRoot.getRight() )) + 1 );
		
		return newRoot;
	}
	
	//Rotate the tree left around a given node
	private AvlNode rotateLeft( AvlNode root ) {
		//Establishing temp variables
		AvlNode newRoot = root.getRight();
		AvlNode tempTwo = newRoot.getLeft();
		
		//Left rotation
		newRoot.setLeft( root );
		root.setRight( tempTwo );
		
		//Create new height
		root.setHeight( max( nodeHeight( root.getLeft()), nodeHeight( root.getRight() ) ) + 1 );
		newRoot.setHeight( max( nodeHeight( newRoot.getLeft() ), nodeHeight( newRoot.getRight() )) + 1 );
		
		//Return the new root
		return newRoot;
	}
	
	public AvlNode getRoot() {
		return root;
	}
}