package Trees;

import java.util.Random;

public class RedBlackTree<T extends Comparable<? super T>> {

	private final RBNode<T> NIL = new RBNode<T>(null, RBNode.BLACK);
	private RBNode<T> root = NIL;
	private int size = 0;

	private void LeftRotate(RBNode x) {
		RBNode<T> y = x.right;
		x.right = y.left;

		if (!y.left.equals(NIL)) {
			y.left.p = x;
		}
		y.p = x.p;
		if (x.p.equals(NIL)) {
			root = y;
		} else if (x.equals(x.p.left)) {
			x.p.left = y;
		} else {
			x.p.right = y;
		}
		y.left = x;
		x.p = y;
	}
	private void RightRotate(RBNode x) {
		RBNode<T> y = x.left;
		x.left = y.right;

		if (!y.right.equals(NIL)) {
			y.right.p = x;
		}
		y.p = x.p;
		if (x.p.equals(NIL)) {
			root = y;
		} else if (x.equals(x.p.right)) {
			x.p.right = y;
		} else {
			x.p.left = y;
		}
		y.right = x;
		x.p = y;
	}
	private void InsertFixup(RBNode z) {

		while (z.p.color == RBNode.RED) {
			if (z.p.equals(z.p.p.left)) {
				RBNode<T> y = z.p.p.right;
				if (y.color == RBNode.RED) {
					z.p.color = RBNode.BLACK;
					y.color = RBNode.BLACK;
					z.p.p.color = RBNode.RED;
					z = z.p.p;
				} else {
					if (z.equals(z.p.right)) {
						z = z.p;
						LeftRotate(z);
					}
					z.p.color = RBNode.BLACK;
					z.p.p.color = RBNode.RED;
					RightRotate(z.p.p);
				}
			} else {
				RBNode<T> y = z.p.p.left;
				if (y.color == RBNode.RED) {
					z.p.color = RBNode.BLACK;
					y.color = RBNode.BLACK;
					z.p.p.color = RBNode.RED;
					z = z.p.p;
				} else {
					if (z.equals(z.p.left)) {
						z = z.p;
						RightRotate(z);
					}
					z.p.color = RBNode.BLACK;
					z.p.p.color = RBNode.RED;
					LeftRotate(z.p.p);
				}
			}
		}
		root.color = RBNode.BLACK;
	}
	private void InsertNode(RBNode z) {
		RBNode<T> y = NIL;
		RBNode<T> x = root;

		while (x != NIL) {
			y = x;
			if (z.compareTo(y) < 0) {
				x = x.left;
			} else {
				x = x.right;
			}
		}

		z.p = y;
		if (y == NIL) {
			root = z;
		} else if (z.compareTo(y) < 0) {
			y.left = z;
		} else {
			y.right = z;
		}
		z.left = NIL;
		z.right = NIL;
		z.color = RBNode.RED;
		InsertFixup(z);
		size++;
	}

	private RBNode<T> Minimum(RBNode n) {
		if (n.left == NIL) {
			return n;
		}

		return Minimum(n.left);
	}
	private RBNode<T> Maximum(RBNode n) {
		if (n.right == NIL) {
			return n;
		}

		return Maximum(n.right);
	}
	private int RecurseHeight(RBNode n) {
		if (n == NIL) {
			return -1;
		}

		return Integer.max(RecurseHeight(n.left), RecurseHeight(n.right)) + 1;
	}
	
	private RBNode<T> FindNode(T k){
		RBNode<T> x = new RBNode(k);
		return FindNode(root, x);		
	}
	private RBNode<T> FindNode(RBNode n, RBNode x){
		if(n == NIL) return null;
		
		if(x.compareTo(n) == 0) return n;
		else if(x.compareTo(n) < 0) return FindNode(n.left,x);
		else return FindNode(n.right, x);
	}
	
	private void Transplant(RBNode u, RBNode v) {
		if (u.p == NIL) {
			root = v;
		} else if (u == u.p.left) {
			u.p.left = v;
		} else {
			u.p.right = v;
		}
		v.p = u.p;
	}
	private void DeleteNode(RBNode z) {
		RBNode<T> y = z;
		RBNode<T> x;
		int originalColor = y.color;

		if (z.left == NIL) {
			x = z.right;
			Transplant(z, z.right);
		} else if (z.right == NIL) {
			x = z.left;
			Transplant(z, z.left);
		} else {
			y = Minimum(z.right);
			originalColor = y.color;
			x = y.right;
			if (y.p == z) {
				x.p = y;
			} else {
				Transplant(y, y.right);
				y.right = z.right;
				y.right.p = y;
			}
			Transplant(z, y);
			y.left = z.left;
			y.left.p = y;
			y.color = z.color;
		}
		if (originalColor == RBNode.BLACK) {
			DeleteFixup(x);
		}
	}
	private void DeleteFixup(RBNode x) {
		RBNode<T> w;

		while (x != root && x.color == RBNode.BLACK) {
			if (x == x.p.left) {
				w = x.p.right;
				if (w.color == RBNode.RED) {
					w.color = RBNode.BLACK;
					x.p.color = RBNode.RED;
					LeftRotate(x.p);
					w = x.p.right;
				}
				if (w.left.color == RBNode.BLACK && w.right.color == RBNode.BLACK) {
					w.color = RBNode.RED;
					x = x.p;
				} else {
					if (w.right.color == RBNode.BLACK) {
						w.left.color = RBNode.BLACK;
						w.color = RBNode.RED;
						RightRotate(w);
						w = x.p.right;
					}
					w.color = x.p.color;
					x.p.color = RBNode.BLACK;
					w.right.color = RBNode.BLACK;
					LeftRotate(x.p);
					x = root;
				}
			} else {
				w = x.p.left;
				if (w.color == RBNode.RED) {
					w.color = RBNode.BLACK;
					x.p.color = RBNode.RED;
					RightRotate(x.p);
					w = x.p.left;
				}
				if (w.right.color == RBNode.BLACK && w.left.color == RBNode.BLACK) {
					w.color = RBNode.RED;
					x = x.p;
				} else {
					if (w.left.color == RBNode.BLACK) {
						w.right.color = RBNode.BLACK;
						w.color = RBNode.RED;
						LeftRotate(w);
						w = x.p.left;
					}
					w.color = x.p.color;
					x.p.color = RBNode.BLACK;
					w.left.color = RBNode.BLACK;
					RightRotate(x.p);
					x = root;
				}
			}
		}
		x.color = RBNode.BLACK;
	}

	public T insert(T i) {
		RBNode<T> z = new RBNode(i);
		InsertNode(z);
		
		return i;
	}
	public T delete(T k){
		RBNode<T> z = FindNode(k);
		
		if(z == null) return null;
		
		DeleteNode(z);
		return k;
	}
	public T max(T k){
		return Maximum(root).key;
	}
	public T min(T k){
		return Minimum(root).key;
	}
	
	public RBNode getRoot(){
		return root;
	}
	
	public RBNode getNIL(){
		return NIL;
	}
	
	public void printTree(){

		printTree(root, 0);
		
	}
	
	public void printTree(RBNode n, int dist){
		
		if(n.color == RBNode.RED){
			System.out.println("-" + n.key + "-");
		} else{
			System.out.println("[" + n.key + "]");
		}
		if(n.left != NIL){
			for(int i=0; i<dist; i++){
				System.out.print("     ");
			}
			System.out.print("  |_ ");
			printTree(n.left, dist+1);
		}
		if(n.right != NIL){
			for(int i=0; i<dist; i++){
				System.out.print("     ");
			}
			System.out.print("  |_ ");
			printTree(n.right, dist+1);
		}
	}
	
	public int size() {
		return size;
	}

	public int height() {
		return RecurseHeight(root);
	}

	public static void main(String[] args) {

		RedBlackTree<Integer> tree = new RedBlackTree<>();
		
		Random r = new Random(System.currentTimeMillis());
		
		tree.insert(11);
		tree.insert(2);
		tree.insert(1);
		tree.insert(14);
		tree.insert(15);
		tree.insert(7);
		tree.insert(5);
		tree.insert(8);
		tree.insert(4);
		
		

		tree.printTree();
		System.out.println(tree.height());
	}
}
