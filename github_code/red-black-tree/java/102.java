
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

	public void remove(int id){
		remove(id, true);

	}

    public void remove(int id, boolean delete) {
    	treeNode node = Root.find(id);
    	if (!node.isEmpty()){
    		treeNode parent = parentOf(node);
    		boolean leftChild = (parent.left==node);
    		treeNode sibling = leftChild ? parent.right : parent.left;
    		if(node.right.isEmpty() && node.left.isEmpty()) {  // no child
    			if (node.isRed){  // node is red
    				if (delete) if (leftChild) parent.left = Root.nullnode; else parent.right = Root.nullnode;
    			}else{  //node is black
    				if (sibling.isEmpty() && parent.isRed){ // no sibling and red parent
    					if (delete) if (leftChild) parent.left = Root.nullnode; else parent.right = Root.nullnode;
    					parent.isRed = false;
    				}else{ //has sibling
	    				if (sibling.isRed){  // case 1
	    					sibling.isRed = false;
	    					parent.isRed = true;
	    					if (leftChild) leftRotate(parent); else rightRotate(parent);
	    					remove(id);
	    				}else{ 
	    					treeNode distant_nephew = leftChild ? sibling.right : sibling.left;
	    					treeNode close_nephew = leftChild ? sibling.left : sibling.right;
	    					if(distant_nephew.isRed){  // case 2
	    						sibling.isRed = parent.isRed;
	    						parent.isRed = false;
	    						distant_nephew.isRed = false;
	    						if (delete) if (leftChild) parent.left = Root.nullnode; else parent.right = Root.nullnode;
	    						if (leftChild) leftRotate(parent); else rightRotate(parent);
	    					}else if(close_nephew.isRed){   // case 3
	    						close_nephew.isRed = false;
	    						sibling.isRed = true;
	    						if (leftChild) rightRotate(parent); else leftRotate(parent);
	    						remove(id);
	    					}else if(sibling.left.isEmpty() && sibling.right.isEmpty()){ 
	    						if(parent.isRed) {        // case 4
		    						parent.isRed = false;
		    						sibling.isRed = true;
		    						if (delete) if (leftChild) parent.left = Root.nullnode; else parent.right = Root.nullnode;
		    						sibling.isRed = true;
		    						if (delete){
		    							if (leftChild) parent.left = Root.nullnode; else parent.right = Root.nullnode;
		    							remove(parent.iData, false);
		    						}
		    					}
	    					}
	    				}
    				}				
    			}
    		}else if(node.right.isEmpty()^node.left.isEmpty()){ // one child (it will always be black-red)
    				treeNode child = (node.right.isEmpty() ? node.right : node.left);
	    			child.isRed = false;
	    			node = child;
    		}else{                             // two child
	    		treeNode minNode = node.right.findMin();
	    		remove(minNode.iData);
		    	node.iData = minNode.iData;
		    }
	    }
    }

	  /* *************************************************** *
	   *  PRIVATE METHODS                                    *
	   * *************************************************** */

	  	private void leftRotate(treeNode parent){
	  		int temp = parent.iData;
	  		treeNode a = parent.left;
	  		treeNode b = parent.right.left;
	  		treeNode c = parent.right.right;
	  		parent.iData = parent.right.iData;
	  		parent.right.iData = temp;
	  		parent.left = parent.right;
	  		parent.left.left = a;
	  		parent.left.right = b;
	  		parent.right = c;
	  	}

	  	private void rightRotate(treeNode parent){
	  		int temp = parent.iData;
	  		treeNode a = parent.left.left;
	  		treeNode b = parent.left.right;
	  		treeNode c = parent.right;
	  		parent.iData = parent.left.iData;
	  		parent.left.iData = temp;
	  		parent.right = parent.left;
	  		parent.left = a;
	  		parent.right.left = b;
	  		parent.right.right = c;
	  	}

	  	private treeNode parentOf(treeNode node) {
    		if (Root.iData == node.iData) return Root.nullnode;
    		treeNode parent = Root.nullnode;
    		treeNode current = Root;
    		while(current!=Root.nullnode){
    			if (node.iData < current.iData){
    				parent = current;
    				current = current.left;
    			}else if (node.iData > current.iData){
    				parent = current;
    				current = current.right;
    			}else{
    				break;
    			}
    		}
    		return parent;
    	}

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


}
