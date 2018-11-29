package jason.jml.avltree;

//@ model import org.jmlspecs.models.*;

/**
 * A JML annotated version of class
 * kiasan.examples.avltree.AvlTree
 */
public class AvlTree {

	private/*@ helper @*/static/*@ nullable @*/AvlNode doubleWithLeftChild(final/*@ nullable @*/AvlNode k3) {
		k3.left = AvlTree.rotateWithRightChild(k3.left);
		return AvlTree.rotateWithLeftChild(k3);
	}

	private/*@ helper @*/static/*@ nullable @*/AvlNode doubleWithRightChild(final/*@ nullable @*/AvlNode k1) {
		k1.right = AvlTree.rotateWithLeftChild(k1.right);
		return AvlTree.rotateWithRightChild(k1);
	}

	/*@
	  @ assignable \nothing; 
	  @*/
	private /*@ helper @*/static int height(final/*@ nullable @*/AvlNode t) {
		return t == null ? -1 : t.height;
	}

	/*@
	  @ assignable \nothing; 
	  @*/
	private /*@ helper @*/static int max(final int lhs, final int rhs) {
		return lhs > rhs ? lhs : rhs;
	}

	private /*@ helper @*/static/*@ nullable @*/AvlNode rotateWithLeftChild(final/*@ nullable @*/AvlNode k2) {
		final AvlNode k1 = k2.left;
		k2.left = k1.right;
		k1.right = k2;
		k2.height = AvlTree.max(AvlTree.height(k2.left), AvlTree.height(k2.right)) + 1;
		k1.height = AvlTree.max(AvlTree.height(k1.left), k2.height) + 1;
		return k1;
	}

	private /*@ helper @*/static/*@ nullable @*/AvlNode rotateWithRightChild(final/*@ nullable @*/AvlNode k1) {
		final AvlNode k2 = k1.right;
		k1.right = k2.left;
		k2.left = k1;
		k1.height = AvlTree.max(AvlTree.height(k1.left), AvlTree.height(k1.right)) + 1;
		k2.height = AvlTree.max(AvlTree.height(k2.right), k1.height) + 1;
		return k2;
	}

	private/*@ nullable @*/AvlNode root;

	//@ public model non_null JMLObjectSet nodes;

	/*@ 
	  @ private represents nodes \such_that nodes.int_size()==\reach(root,AvlNode,left).int_size() &&
	  @                             (\forall AvlNode node ; nodes.has(node) <==> \reach(root,AvlNode,left).has(node)); 
	  @*/

	/*@
	  @ private invariant (\forall AvlNode x ; \reach(root,AvlNode,left).has(x) ;
	  @
	  @                                !\reach(x.left,AvlNode,left).has(x) && !\reach(x.right,AvlNode,left).has(x) &&
	  @ 
	  @                                (\forall AvlNode y ; \reach(x.left,AvlNode,left).has(y) ; y.element < x.element ) &&
	  @
	  @                                (\forall AvlNode y ; \reach(x.left,AvlNode,left).has(y) ; x.element < y.element ) &&
	  @
	  @                                ( ( x.left==null && x.right==null ) ==> x.height==0 ) &&
	  @
	  @                                ( ( x.left==null && x.right!=null ) ==> ( x.height==1 && x.right.height==0 )) &&
	  @
	  @                                ( ( x.left!=null && x.right==null ) ==> ( x.height==1 && x.left.height==0 ) ) &&
	  @
	  @                                ( ( x.left!=null && x.right!=null ) ==> ( 
	  @                                                                         ( x.height== (x.left.height > x.right.height ? x.left.height : x.right.height )+1) && 
	  @                                                                         ( (x.left.height > x.right.height ? x.left.height - x.right.height : x.right.height - x.left.height )<=1 )
	  @                                                                       ) 
	  @                                )
	  @            ); 
	  @*/

	/*@
	  @ assignable \nothing; 
	  @*/
	private/*@ helper @*/int elementAt(final/*@ nullable @*/AvlNode t) {
		return t == null ? -1 : t.element;
	}

	/*@
	  @ assignable \nothing;
	  @ ensures (\exists AvlNode n; nodes.has(n) && n.element==x) ==> \result==x;
      @ ensures !(\exists AvlNode n; nodes.has(n) && n.element==x) ==> \result==-1;	  
	  @*/
	public int find(final int x) {
		return elementAt(find(x, this.root));
	}

	/*@
	  @ assignable \nothing; 
	  @*/
	private/*@ helper @*//*@ nullable @*/AvlNode find(final int x, /*@ nullable @*/ AvlNode t) {
		while (t != null) {
			if (x < t.element) {
				t = t.left;
			} else if (x > t.element) {
				t = t.right;
			} else {
				return t; // Match
			}
		}

		return null; // No match
	}

	/*@
	  @ 
	  @   assignable \nothing;
	  @   ensures nodes.int_size()==0 ==> \result==-1;
	  @   ensures nodes.int_size()>0 ==> (\exists AvlNode max_node; 
	  @                                     nodes.has(max_node) && 
	  @                                     max_node.element==\result &&
	  @                                     (\forall AvlNode node ; nodes.has(node) ; \result >= node.element )
	  @                                  ); 
	  @*/
	public int findMax() {
		return elementAt(findMax(this.root));
	}

	/*@
	  @ assignable \nothing; 
	  @*/
	private/*@ helper @*//*@ nullable @*/AvlNode findMax(/*@ nullable @*/AvlNode t) {
		if (t == null) {
			return t;
		}

		while (t.right != null) {
			t = t.right;
		}
		return t;
	}

	/*@
	  @ 
	  @   assignable \nothing;
	  @   ensures nodes.int_size()==0 ==> \result==-1;
	  @   ensures nodes.int_size()>0 ==> (\exists AvlNode min_node; 
	  @                                     nodes.has(min_node) && 
	  @                                     min_node.element==\result &&
	  @                                     (\forall AvlNode node ; nodes.has(node) ; \result <= node.element )
	  @                                  ); 
	  @*/
	public int findMin() {
		return elementAt(findMin(this.root));
	}

	/*@
	  @ assignable \nothing; 
	  @*/
	private/*@ helper @*//*@ nullable @*/AvlNode findMin(/*@ nullable @*/AvlNode t) {
		if (t == null) {
			return t;
		}

		while (t.left != null) {
			t = t.left;
		}
		return t;
	}

	/*@
	  @ assignable \everything;
	  @*/
	public void insert(final int x) {
		this.root = insert(x, this.root);
	}

	private/*@ helper @*//*@ nullable @*/AvlNode insert(final int x, /*@ nullable @*/ AvlNode t) {
		if (t == null) {
			t = new AvlNode(x, null, null);
		} else if (x < t.element) {
			t.left = insert(x, t.left);
			if (AvlTree.height(t.left) - AvlTree.height(t.right) == 2) {
				if (x < t.left.element) {
					t = AvlTree.rotateWithLeftChild(t);
				} else {
					t = AvlTree.doubleWithLeftChild(t);
				}
			}
		} else if (x > t.element) {
			t.right = insert(x, t.right);
			if (AvlTree.height(t.right) - AvlTree.height(t.left) == 2) {
				if (x > t.right.element) {
					t = AvlTree.rotateWithRightChild(t);
				} else {
					t = AvlTree.doubleWithRightChild(t);
				}
			}
		} else {
			; // Duplicate; do nothing
		}
		t.height = AvlTree.max(AvlTree.height(t.left), AvlTree.height(t.right)) + 1;
		return t;
	}
}
