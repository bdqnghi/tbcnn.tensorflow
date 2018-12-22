package com.datastructure.redblacktree;


public final class RedBlackTree implements IRBTree {	// final implementation  

	
	
	
	private Node root = null;


	
	
	@Override
	public void add(Integer data) {

		//System.out.println("Adding node to the tree: " + data);	// testing 

		Node newNode = new Node();	// create a new node 
		newNode.setData(data);
		newNode.setColor('r');		// set color of new node to RED as it gets attached as leaf, initially. 
		
		Node currentNode = root;	// current node under consideration 
		Node tempNode = null;

		if (root == null) {			// tree is empty
			root = newNode;
			root.setColor('b'); 	// set root to 'BLACK' color
			return;
		} else {					// tree is not empty, find ideal location in BST

			while (currentNode != null) {

				newNode.setParent(currentNode);				// update parent of newNode as we move down the tree. 		  
				if (currentNode.getData() > data) {			// go left
					currentNode = currentNode.getLeft();
				} else if (currentNode.getData() < data) {	// go right
					currentNode = currentNode.getRight();
				} else {
					System.out.println("Duplicate element, do nothing.");
					return; 								// do not insert, duplicate data
				}

			}

			tempNode = newNode.getParent();					// get parent node & set 'newNode' on left/right of its parent. 
			if (data < tempNode.getData()) {
				tempNode.setLeft(newNode);
			} else if (data > tempNode.getData()) {
				tempNode.setRight(newNode);
			}

		}

		fixRedBlackTreeProperties(newNode); // fix RED-BLACK-TREE properties to make it a BALANCED BST.
		
		//levelPrint();	// testing 
	}

	/**
	 * 
	 * @param k - new Node inserted into the tree. Also, referred to as 'KID' 
	 */
	private void fixRedBlackTreeProperties(Node k) {

		Node p = k.getParent();			// get parent of KID
		Node g = p.getParent();			// get grand parent of KID 

		if (p.getColor() == 'b') {		// RED-BLACK-TREE properties are unharmed.  
			
			//System.out.println("do nothing");	// testing 
			
		} else {						// KID's parent is RED & KID is RED too. 	
		/*
		 *  KIS's parent 'p' is RED, handle 4 conditions by rotation.
		 *  
		 *  			 POSITIONS OF NODES IN TREE
		 *  PARENT		left	left	right	right
		 *	KID			left	right	left	right
		 *  
		 */
										
			
			/*
			 * KID's parents(p's) sibling(s) is NULL or BLACK.	
			 * Sibling 's' can be on right or left.						 
			 */
			// get KID's parents sibling. 
			Node s = null;
			if( (g!=null)   &&   (g.getLeft()==p) ){			// Sibling is yet to be selected. Either left/right of grand parent Node 'g'.
				s = g.getRight();								// select right of grand parent (g) Node as sibling (s).
			}else{
				s = g.getLeft();
			}
						
						
			if ( s == null || s.getColor() == 'b' ) {											// KID's parents sibling is null or BLACK, then rotate 
									
					if ( (g.getLeft()!=null)  &&  (p.getData() == g.getLeft().getData()) ) { 	// KID's parent is on left
						
						if ( (p.getLeft()!=null)  &&  (k.getData() == p.getLeft().getData()) ) { // KID is on left of it's left parent 'p'. 
							
							p.setParent(g.getParent());
							if(p.getParent()==null){											// update root 
								root = p;
							}else{																// 'p' is attached to left/right of it's parent 
								if(g.getParent().getRight().getData() == g.getData()){
									p.getParent().setRight(p);
								}else{
									p.getParent().setLeft(p);
								}
							}
													
							g.setParent(p);														// update all parent and child relations & vice versa
							g.setLeft(p.getRight());
							
							p.getRight().setParent(g);
							
							p.setRight(g);	
							
							p.setColor('b');
							g.setColor('r');						
							
						} else {																// KID is on right of it's left parent 'p'.
							
							k.setParent(g.getParent());
							if(k.getParent()==null){
								root = k;
							}else{																// 'k' is attached to left/right of it's parent 
								if(g.getParent().getRight().getData() == g.getData()){
									k.getParent().setRight(k);
								}else{
									k.getParent().setLeft(k);
								}
							}
							
							k.setLeft(p);														// update all parent and child relations & vice versa
							p.setParent(k);
							
							k.setRight(g);
							g.setParent(k);
							
							p.setRight(null);
							g.setLeft(null);
							
							k.setColor('b');
							g.setColor('r');
							
						}
						
					} else if ( (g.getRight()!=null)  &&  (p.getData() == g.getRight().getData()) ) {	// KID's parent is on right.  
						
						if ( (p.getLeft()!=null)   &&   (k.getData() == p.getLeft().getData()) ) { 		// KID is on left of it's right parent 'p'.
							
							k.setParent(g.getParent());
							if(k.getParent()==null){
								root = k;
							}else{																		// 'k' is attached to left/right of it's parent 
								if(g.getParent().getRight().getData() == g.getData()){
									k.getParent().setRight(k);
								}else{
									k.getParent().setLeft(k);
								}
							}
							
							k.setLeft(g);
							g.setParent(k);
							
							k.setRight(p);							
							p.setParent(k);
							
							p.setLeft(null);
							g.setRight(null);
							
							k.setColor('b');
							g.setColor('r');
							
						} else {																		// KID is on right of it's right parent 'p'.
								
							p.setParent(g.getParent());
							if(p.getParent()==null){
								root = p;
							}else{																		// 'p' is attached to left/right of it's parent 
								if(g.getParent().getRight().getData() == g.getData()){
									p.getParent().setRight(p);
								}else{
									p.getParent().setLeft(p);
								}
							}
							
							g.setRight(p.getLeft());
							
							p.setLeft(g);
							g.setParent(p);
							
							p.setColor('b');
							g.setColor('r');
							
						}
						
					}	// end of inner if.  

			}else if( s.getColor()=='r' ){					// KID's parents sibling is RED, just re color and move up the tree if same.
					
				//System.out.println("re coloring");		// testing 
				g.setColor('r'); 							// re color the Nodes.
				p.setColor('b');
				if (s != null) {
					s.setColor('b');
				}
				k.setColor('r');

				if (root.getColor() == 'r') {
					root.setColor('b');
				}

				if (g.getParent() != null && g.getColor() == 'r'  &&   g.getColor() == g.getParent().getColor()) {
					fixRedBlackTreeProperties(g);
				}

			}

		}
	}
	
	
	
	
	@Override
	public void remove(Integer data){
		// to be implemented
		
	}
	
	
	
	
	@Override
	public Node search(Integer data){
		
		Node currentNode = root;
		
		while (currentNode != null) {

			if(currentNode.getData()==data){
				return currentNode;
			}
			 		  
			if (data < currentNode.getData()) {			// go left
				currentNode = currentNode.getLeft();
			} else if (data > currentNode.getData()) {	// go right
				currentNode = currentNode.getRight();
			} 		
		}
		
		return null;
	}
	
	
	
	
	
	/*
	 * 	The following material was used as a 'theoretical reference' to implement operations on RB Tree.
	 * 
	 *  				Reference's    
	 *  http://pages.cs.wisc.edu/~cs367-1/readings/Red-Black-Trees/index.html
	 *  https://www.youtube.com/watch?v=g9SaX0yeneU
	 *  
	 */
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
	 * 						HELPER   FUNCTIONS
	 * 	
	 * These functions are used for debugging the implementation of RB Tree.
	 * 
	 */
	
	@Override
	public long height() {
		return (computeLevels(root) + 1); 
	}

	private int computeLevels(Node node) {
		if (node == null) {
			return -1; // Child of leaf node has height -1 & Leaf node has
						// height 0.
		} else {
			int lHeight = computeLevels(node.getLeft());
			int rHeight = computeLevels(node.getRight());

			if (lHeight > rHeight) {
				return (lHeight + 1);
			} else {
				return (rHeight + 1);
			}
		}
	}

	@Override		
	public void levelPrint(){
		
		long height = height();	//	Height = 3 means tree has 0, 1, 2 levels. 
		int level = 0;			//	for printing 
		
		for(int i=0;   i<(int)(height);   i++){					// to start printing from root, reverse the for loop. 
			System.out.print("\nNodes at level:"+(level++)+"	");
			nodeAtLevel(root, i);
		}
				
	}
		
	private void nodeAtLevel(Node node, int level){
				
		if(level==0 && node != null){
			System.out.print("  "+node.getData()+"("+node.getColor()+")");
		}else{
			if(node.getLeft()!=null){
				nodeAtLevel(node.getLeft(), level-1);				
			}
			if(node.getRight()!=null){
				nodeAtLevel(node.getRight(), level-1);	
			}
		}
		
	}
	
	// end of Helper Functions  
	
	
} // end of class
