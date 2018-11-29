
public class redblacktree {

	  private treeNode Root;
	  
	  public treeNode getRoot() { return Root; }
	  
	  // Constructs a new empty red-black tree.
	  public redblacktree() { Root = Root.nullnode;}
	  public void clear() { Root = Root.nullnode; }
	  
	  public boolean isEmpty() { return Root.isEmpty(); }	  

	  public int size() { return Root.size(); }
	    
	  public treeNode find(int key) {
		  if (Root.isEmpty()) return Root;
		  return Root.find(key);
	  }

	  public void checkRedBlack() {
		  if (Root.isRed) 
			  System.out.println( "The root is red");
		  Root.bheight();
	  }
	  
	  public void insert(int id) { // call recursive insert
	       treeNode nnd = new treeNode(id);    // make new node

	       if (Root.isEmpty()) Root = nnd;
	       else if (id < Root.iData) {
	    	   if (Root.left.isEmpty())
	    		   Root.left = nnd;
	    	   else if (insert(nnd, Root.left, Root)) {
	  	    	   // red-red violation exists at Root.left and its children
			       if (Root.right.isRed) { // red uncle case:
			    	   Root.right.isRed = Root.left.isRed = false;
			       } else { // black uncle case:			    	   
			    	   Root.isRed = true;
			           if (nnd.iData < Root.left.iData) {
			               Root = Root.rotateToRight();
			           } else {
			               Root = Root.doubleRotateToRight();
			           } 			 
			       } // else
	    	   }
	       } else if (Root.right.isEmpty()) {
	    		   Root.right = nnd;
	       } else if (insert(nnd, Root.right, Root)) {
  	    	   // red-red violation exists at Root.right and its children
		       if (Root.left.isRed) { // red uncle case:
		    	   Root.right.isRed = Root.left.isRed = false;
		       } else { // black uncle case:		    	   
		    	   Root.isRed = true;
		           if (nnd.iData >= Root.right.iData) {
		               Root = Root.rotateToLeft();
		           } else {
		               Root = Root.doubleRotateToLeft();
		           } 
		       } // else
	       }
	       Root.isRed = false;
	    }  // end insert()
	  
	  /* *************************************************** *
	   *  PRIVATE METHODS                                    *
	   * *************************************************** */
	  
	  /* Inserts a node into tree and returns a boolean */
	  private boolean insert(treeNode nnd, treeNode t, treeNode par) {
		  // return true iff t is red and t has a red child

		  if (nnd.iData < t.iData) {
		      if (t.left.isEmpty()) {
		         t.left = nnd;  //attach new node as leaf
		      } else if (insert(nnd, t.left, t)) { 
		    	 // red-red violation exists at t.left and its children
		    	 if (t.right.isRed) { // red uncle case:
		    		 t.right.isRed = t.left.isRed = false;
		    		 t.isRed = true;
		    	 } else { // black uncle case:
		    		 treeNode nt;
		    		 
		             if (nnd.iData < t.left.iData) {
		                nt = t.rotateToRight();
		             } else {
		                nt = t.doubleRotateToRight();
		             } 
		    		 t.isRed = true;
		    		 nt.isRed = false;
		    		 if (nt.iData < par.iData) par.left = nt;
		    		 else par.right = nt;
		         } //if
		      }
		      
		      return (t.isRed && t.left.isRed);
		 } else { // branch right
		      if (t.right.isEmpty()) {
		           t.right = nnd;   // attach new node as leaf
			  } else if (insert(nnd, t.right, t)) { 
			       // red-red violation exists at t.right and its children
			       if (t.left.isRed) { // red uncle case:
			    		 t.right.isRed = t.left.isRed = false;
			    		 t.isRed = true;
			       } else { // black uncle case:
			    		 treeNode nt;
			    		 
			             if (nnd.iData >= t.right.iData) {
			                nt = t.rotateToLeft();
			             } else {
			                nt = t.doubleRotateToLeft();
			             } 
			    		 t.isRed = true;
			    		 nt.isRed = false;
			    		 if (nt.iData < par.iData) par.left = nt;
			    		 else par.right = nt;
			       } // else
			  } 
		      
			  return (t.isRed && t.right.isRed);
		 } // else
	  }  // end insert

	/* removes a node from tree and updates tree to fit red-black properties*/
	public void remove(int key){
		treeNode t = Root.find(key);
		treeNode y;
		treeNode x;

		if (t.left == null || t.right == null) {
			y = t;
		}
		else {
			y = Root.successor(key);
		}

		if (y.left != null) {
			x = y.left;
		}
		else {
			x = y.right;
		}
		//x.parent = y.parent;
		if (Root.predecessor(y.iData) == null)
			Root = x;
//		else if (y.parent.left != null && y == y.parent.left)
//			y.parent.left = x;
//		else if (y.parent.right != null && y == y.parent.right)
//			y.parent.right = x;
		if (y != t) {
			t.iData = y.iData;
		}

		if (!y.isRed){
			correctRBTree(x);
		}

	}// end remove()

	private void correctRBTree(treeNode t){
		treeNode w;
		while (t != Root && !t.isRed) {
			if (t == Root.predecessor(t.iData).left) { //if we are working with left child
				w = Root.predecessor(t.iData).right;

				if (w.isRed) {
					w.isRed = false;
					Root.predecessor(t.iData).isRed = true;
					Root.predecessor(t.iData).rotateToLeft();
					w = Root.predecessor(t.iData).right;
				}
				if (!w.left.isRed && !w.right.isRed) {
					w.isRed = true;
					t = Root.predecessor(t.iData);
				}
				else{
					if (!w.right.isRed) { // if right child is black
						w.left.isRed = false;
						w.isRed = true;
						w.rotateToRight();
						w = Root.predecessor(t.iData).right;
					}
					// w is black and it's right child is red
					w.isRed = Root.predecessor(t.iData).isRed;
					Root.predecessor(t.iData).isRed = false;
					w.right.isRed = false;
					Root.predecessor(t.iData).rotateToLeft();
					t = Root;
				}
			}
			else{
				w = Root.predecessor(t.iData).left;

				if (w.isRed) {
					w.isRed = false;
					Root.predecessor(t.iData).isRed = true;
					Root.predecessor(t.iData).rotateToRight();
					w = Root.predecessor(t.iData).left;
				}
				if (!w.right.isRed && !w.left.isRed) {
					w.isRed = true;
					t = Root.predecessor(t.iData);
				}
				else{
					if (!w.left.isRed) { // if right child is black
						w.right.isRed = false;
						w.isRed = true;
						w.rotateToLeft();
						w = Root.predecessor(t.iData).left;
					}
					// w is black and it's right child is red
					w.isRed = Root.predecessor(t.iData).isRed;
					Root.predecessor(t.iData).isRed = false;
					w.left.isRed = false;
					Root.predecessor(t.iData).rotateToRight();
					t = Root;
				}
			}
		}
		t.isRed = false;
	}
}
