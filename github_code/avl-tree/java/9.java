package analysis.in.java.chapter4;

import analysis.in.java.util.UnderflowException;

public class AvlTree <AnyType extends Comparable<? super AnyType>>{

	public static enum Traveral{
		PRE_ORDER,IN_ORDER,POST_ORDER
	}
	private static class AvlNode<AnyType>{
		AnyType element;
		AvlNode<AnyType> left;
		AvlNode<AnyType> right;
		int height;
		
		public AvlNode(AnyType element){
			this(element,null,null);
		}
		
		public AvlNode(AnyType element,AvlNode<AnyType> left,
				AvlNode<AnyType> right){
			this.element=element;
			this.left=left;
			this.right=right;
		}
	}
	
	private AvlNode<AnyType> root;
	
	public AvlTree(){
		root=null;
	}
	
	public void makeEmpty(){
		root=null;
	}
	
	public boolean isEmpty(){
		return null==root;
	}
	
	public void printTree(Traveral type){
		printTree(root,type);
	}
	/**
	 * Internal method to print a subtree in sorted order
	 * @param t the node that roots the subtree
	 */
	private void printTree(AvlNode<AnyType> t,Traveral type){
		if(null!=t){
			switch(type){
			case PRE_ORDER:
				printName(t.element,t.height);
				printTree(t.left,type);
				printTree(t.right,type);
				break;
			case IN_ORDER:
				printTree(t.left,type);
				printName(t.element,t.height);
				printTree(t.right,type);
				break;
			case POST_ORDER:
				printTree(t.left,type);
				printTree(t.right,type);
				printName(t.element,t.height);
				break;
			}
		}
	}
	private void printName(AnyType element,int depth){
		System.out.println(element);
	}
	
	public void insert(AnyType element){
		root=insert(element,root);
	}
	/**
	 * Internal method to insert into a subtree.
	 * @param element the item to insert.
	 * @param t the node that roots the subtree.
	 * @return the new root of the subtree.
	 */
	private AvlNode<AnyType> insert(AnyType element,AvlNode<AnyType> t){
		if(null==t){
			return new AvlNode<AnyType>(element);
		}
		int compareResult=element.compareTo(t.element);
		if(compareResult<0){
			t.left=insert(element,t.left);
			//  maybe can call rotate instead of those code
//			if(height(t.left)-height(t.right) == 2){
//				if(element.compareTo(t.left.element)<0){
//					t=rotateWithLeftChild(t);
//				}else {
//					t=doubleWithLeftChild(t);
//				}
//			}
		}else if(compareResult>0){
			t.right=insert(element,t.right);
//			if(height(t.right)-height(t.left) == 2){
//				if(element.compareTo(t.right.element)>0){
//					t=rotateWithRightChild(t);
//				}else {
//					t=doubleWithRightChild(t);
//				}
//			}
		}else{
			//Duplicate ;do nothing
		}
		t=rotate(t);
		updateHeight(t);
		return t;
	}
	
	
	public void remove(AnyType element){
		root=remove(element,root);
	}
	
	/**
	 * 删除一个节点的主要步骤如下所示：
	 * 1.如果是null节点，则直接返回null
	 * 2.如果删除的值<当前节点，则转入left节点进行递归删除
	 * 3.如果删除的值>当前节点，则转入right节点进行递归删除
	 * 4.如果删除的值为当前节点，如果当前节点只有一个子树，则直接返回该子树
	 * 5.如果删除的值为当前节点，且当前节点有两个子树，则将当前值更改为右子树中最小的节点值，并递归在右子树中删除该节点值
	 * 6.重新修正该处理节点的height值
	 * 7.对处理节点进行重新翻转处理，以修正在删除过程中可能出现的树不平衡情况
	 * @param element
	 * @param t
	 * @return
	 */
	private  AvlNode<AnyType> remove(AnyType element, AvlNode<AnyType> t) {
        if(t == null)
            return null;
        int cmp = element.compareTo(t.element);
        if(cmp < 0) {
            t.left = remove(element, t.left);
        } else if(cmp > 0) {
            t.right = remove(element, t.right);
        } else if(t.left != null && t.right != null) {
            t.element = findMin(t.right).element;
            t.right = remove(t.element, t.right);
        } else {
            t = t.left == null ? t.right : t.left;
        }
        t = rotate(t);
        updateHeight(t);
        return t;
    }
	public boolean contains(AnyType element){
		return contains(element,root);
	}
	/**
	 * Internal method to search an item in a subtree
	 * @param element the item to search for.
	 * @param t the node that roots the subtree. 
	 * @return whether the subtree has a node that containing the search element.
	 */
	private boolean contains(AnyType element,AvlNode<AnyType> t){
		if(null==t){
			return false;
		}
		int compareResult=element.compareTo(t.element);
		if(compareResult<0){
			return contains(element,t.left);
		}else if(compareResult>0){
			return contains(element,t.right);
		}
		//Match
		return true;
	}
	public AnyType findMin(){
		if(null==root){
			throw new UnderflowException();
		}
		return findMin(root).element;
	}
	/**
	 * Internal method to find the smallest item in a subtree.
	 * @param t the node that roots the subtree.
	 * @return node that containing the smallest item.
	 */
	private AvlNode<AnyType> findMin(AvlNode<AnyType> t){
		if(null!=t){
			while(t.left!=null){
				t=t.left;
			}
		}
		return t;
	}
	public AnyType findMax(){
		if(null==root){
			throw new UnderflowException();
		}
		return findMax(root).element;
	}
	/**
	 * Internal method to find the largest item in a subtree.
	 * @param t the node that roots the subtree.
	 * @return node that containing the largest item.
	 */
	private AvlNode<AnyType> findMax(AvlNode<AnyType> t){
		if(null!=t){
			while(t.right!=null){
				t=t.right;
			}
		}
		return t;
	}
	/**
	 * Internal method to get the height of a node
	 * @param t
	 * @return the height of node t,or -1,if null.
	 */
	private int height(AvlNode<AnyType> t){
		return null==t?-1:t.height;
	}
	
	/**
	 * Internal method to update the height of a node.
	 * you should update t's left and right child first to update t.
	 * @param t the node that roots the subtree.
	 */
	private void updateHeight(AvlNode<AnyType> t){
		t.height=Math.max(height(t.left),height(t.right))+1;
	}


	
	private  AvlNode<AnyType> rotate( AvlNode<AnyType> t) {
        if(t == null)
            return null;
        if(height(t.left) - height(t.right) == 2) {
            if(height(t.left.left) >= height(t.left.right))
                return rotateWithLeftChild(t);
            else
                return doubleWithLeftChild(t);
        } else if(height(t.right) - height(t.left) == 2) {
            if(height(t.right.right) >= height(t.right.left))
                return rotateWithRightChild(t);
            else
                return doubleWithRightChild(t);
        }
        return t;
    }
	/**
	 * Rotate binary tree node with left child. 
	 * For AVL trees, this is a single rotation for case 1
	 * Update heights,then return new root.
	 */
	private AvlNode<AnyType> rotateWithLeftChild(AvlNode<AnyType> k2){
		AvlNode<AnyType> k1=k2.left;
		k2.left=k1.right;
		k1.right=k2;
		updateHeight(k2);
		updateHeight(k1);
		return k1;
	}
	/**
	 * Rotate binary tree node with right child. 
	 * For AVL trees, this is a single rotation for case 3
	 * Update heights,then return new root.
	 */
	private AvlNode<AnyType> rotateWithRightChild(AvlNode<AnyType> k2){
		AvlNode<AnyType> k1=k2.right;
		k2.right=k1.left;
		k1.left=k2;
		updateHeight(k2);
		updateHeight(k1);
		return k1;
	}
	/**
	 * Double rotate binary tree node: first left child 
	 * with its right child;then node k3 with new left child. 
	 * For AVL trees, this is a double rotation for case 2.
	 * Update heights,then return new root.
	 */
	private AvlNode<AnyType> doubleWithLeftChild(AvlNode<AnyType> k3){
		k3.left=rotateWithRightChild(k3.left);
		return rotateWithLeftChild(k3);
	}
	
	/**
	 * Double rotate binary tree node: first right child 
	 * with its left child; then node k3 with new right child.
	 * For AVL trees, this is a double rotation for case 4.
	 * Update heights, then return new root
	 */
	private  AvlNode<AnyType> doubleWithRightChild(AvlNode<AnyType> k3){
		k3.right=rotateWithLeftChild(k3.right);
		return rotateWithRightChild(k3);
	}
	




}
