package tree;




public class blackRedTree {
	
	private static final boolean RED = true;
	private static final boolean BLACK = false;

	class RBNode{
		int data;
		RBNode left;
		RBNode right;
		boolean color; //color of parent link
		public RBNode(int val,boolean color){
			left = null;
			right = null;
			this.color = color;
			this.data = val;
			
		}
	}
	
	private boolean isRed(RBNode n){
		if( n == null ){
			return false;
		}
		return n.color == RED;
	}
	
	public RBNode get(RBNode root,int n){
		if(root == null) {
			return null;
		}
		RBNode t = root;
		while( t!= null){
			if(t.data > n){
				t = t.left;
			}else if(t.data < n){
				t = t.right;
			}else{
				return t;
			}
		}
		return null;
	}
	private RBNode rotateLeft(RBNode n){
		if(n == null){
			return null; 
		}
		RBNode t = n.right;
		n.right = t.left;
		t.left = n;
		t.color = n.color;
		n.color = RED;
		return t;
	}
	private RBNode rotateRight(RBNode n){
		if(n == null){
			return null;
		}
		RBNode t = n.left;
		n.left = t.right;
		t.right = n;
		t.color = n.color;
		n.color = RED;
		return t;
	}
	
	private void flipColor(RBNode r){
		r.left.color = BLACK;
		r.right.color = BLACK;
		r.color = RED;
	}
	
	private RBNode put(RBNode r,int val){
		if(r == null){
			 return new RBNode(val,RED);
		}
		if(r.data > val){
			r = put(r.left, val);
		}else if(r.data < val){
			r = put(r.right,val);
		}else{
			r.data = val;
		}
		
		if(isRed(r.right) && !isRed(r.left) ){
			r = rotateLeft(r);
		}
		if(isRed(r.left) && isRed(r.left.left) ){
			r = rotateRight(r);
		}
		if(isRed(r.left) && isRed(r.right) ){
			flipColor(r);
		}
		return r;
	}

	
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
