
/**
 * AvlNonEmptyBinaryTree - this is a binary search tree that is either an inner node
 * of the tree or a leaf node.  Leaf nodes will have 2 empty nodes attached to 
 * the right and the left subtrees.  Note that the insert and remove operation return 
 * the changed tree and they will generally modify existing trees.   this code uses the
 * avl approach to re-balance the tree after an element has been inserted.
 * 
 * @author Eric McCreath - GPLv2
 */


public class AvlNonEmptyBinaryTree extends NonEmptyBinaryTree {

	public AvlNonEmptyBinaryTree(int data) {
		super(data, new AvlEmptyBinaryTree(), new AvlEmptyBinaryTree());
		
	}
	
	public AvlNonEmptyBinaryTree(int data, BinaryTree left, BinaryTree right) {
		super(data,left,right);
	}
	
	public BinaryTree remove(int d) {
		throw new Error();  // currently the avl remove has not be implemented
		
		
	}
	public BinaryTree insert(int d) {
		AvlNonEmptyBinaryTree res;
		if (data == d) {
			res = this;
		} else if (d < data) {
			left = left.insert(d);
			res = this;
		} else {
			right = right.insert(d);
			res = this;
		}
		if (res.balanceFactor() == -2 && res.right.balanceFactor() == 1) { 
			return rotateRL();
		} else if (res.balanceFactor() == -2 && res.right.balanceFactor() == -1) {
			return rotateRR();
		} else if (res.balanceFactor() == 2 && res.left.balanceFactor() == 1) {
			return rotateLL();
		} else if (res.balanceFactor() == 2 && res.left.balanceFactor() == -1) {
			return rotateLR();
		} 
		return res;
	}
	
	
	private AvlNonEmptyBinaryTree rotateRL() {
		AvlNonEmptyBinaryTree r = (AvlNonEmptyBinaryTree) this.right;
		AvlNonEmptyBinaryTree rl = (AvlNonEmptyBinaryTree) ((AvlNonEmptyBinaryTree) this.right).left;
		return (new AvlNonEmptyBinaryTree(rl.data,new AvlNonEmptyBinaryTree(data,left,rl.left),new AvlNonEmptyBinaryTree(r.data,rl.right,r.right)));
	}
	private AvlNonEmptyBinaryTree rotateRR() {
		AvlNonEmptyBinaryTree r = (AvlNonEmptyBinaryTree) this.right;
		AvlNonEmptyBinaryTree rr = (AvlNonEmptyBinaryTree) ((AvlNonEmptyBinaryTree) this.right).right;
		return (new AvlNonEmptyBinaryTree(r.data,new AvlNonEmptyBinaryTree(data,left,r.left),rr));
	}
	private AvlNonEmptyBinaryTree rotateLL() {
		AvlNonEmptyBinaryTree l = (AvlNonEmptyBinaryTree) this.left;
		AvlNonEmptyBinaryTree ll = (AvlNonEmptyBinaryTree) ((AvlNonEmptyBinaryTree) this.left).left;
		return (new AvlNonEmptyBinaryTree(l.data, ll,new AvlNonEmptyBinaryTree(data,l.right,right)));
	}
	private AvlNonEmptyBinaryTree rotateLR() {
		AvlNonEmptyBinaryTree l = (AvlNonEmptyBinaryTree) this.left;
		AvlNonEmptyBinaryTree lr = (AvlNonEmptyBinaryTree) ((AvlNonEmptyBinaryTree) this.left).right;
		return (new AvlNonEmptyBinaryTree(lr.data,new AvlNonEmptyBinaryTree(l.data,l.left,lr.left),new AvlNonEmptyBinaryTree(data,lr.right,right)));
	}
}
