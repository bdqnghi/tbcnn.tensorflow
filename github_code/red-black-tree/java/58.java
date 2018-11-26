package datastructures;

public class RedBlackTree {
	RedBlackNode root;
	public void insert(int data){
		RedBlackNode n = new RedBlackNode(data);
		
		if(root==null){
			root = n;
		} else{
			insertRedBlackNode(root,n);
		}
	}
	
	public void insertRedBlackNode(RedBlackNode p, RedBlackNode n){
		 if(p.data < n.data || p.data == n.data){ // there is some red black property here...
			if(p.left==null){
				p.left = n;
				n.parent = p;
			} else {
				insertRedBlackNode(p.left,n);
			}
		 } else {
			 if(p.right==null){
				 p.right = n;
				 n.parent = p;
			 } else {
				 insertRedBlackNode(p.right,n);
			 }
		 }
		 fixRedBlackTree(n);
	}
	
	public void leftRotate(RedBlackNode n){
		RedBlackNode t = n.right;
		n.right = t.left;
		if(t!=null){
			if(t.left!=null){
				t.left.parent=n;
			}
			
			// setting t's parent
			t.parent = n.parent;
			
			// Setting n's parent's left and right nodes.
			if(n.parent == null){
				root = t;
			} else if(n == n.parent.left){ // losing n.parent.left???
				n.parent.left = t;
			} else{
				n.parent.right = t;
			}
			
			// Setting parent of t and n.
			t.left = n;
			n.parent = t;
		}
	}
	
	public void rightRotate(RedBlackNode n){
		
	}
	
	public void fixRedBlackTree(RedBlackNode n){
		while(!n.parent.black){
			if(n.parent == n.parent.parent.left){
				RedBlackNode y = n.parent.parent.right;
				
				if(!y.black){ // if uncle red, recolor parent black, grandpa red, uncle black
					y.parent.left.black = true;
					y.black = true;
					y.parent.black = false;
					n = n.parent.parent;
				} else if(n == n.parent.right){ // if forms a triangle and uncle black, left rotate z.p
					n = n.parent;
					leftRotate(n);
				} else {
					// if uncle black but forms a line, recolor parent black and grandpa black and left right rotate grandpa
					n.parent.black = true;
					n.parent.parent.black = false;
					rightRotate(n.parent.parent);
				}
			} else{// Same as if but right and left are exchanged
				RedBlackNode y = n.parent.parent.left;
				
				if(!y.black){
					n.parent.black = true;
					y.black = true;
					n.parent.parent.black = false;
					n = n.parent.parent;
				} else if(n == n.parent.left){
					n = n.parent;
					rightRotate(n);
				} else{
					n.parent.black = true;
					n.parent.parent.black = false;
					leftRotate(n.parent.parent);
				}
			}
		}
		root.black = true;
	}
	

}
