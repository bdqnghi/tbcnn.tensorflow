package com.mosby.common.structure;

/**
 * AVL ??
 */
public class AvlTree <T extends Comparable<? super T>> {
	private static  class AvlNode <T extends Comparable<? super T>>{
		AvlNode(T element){
			this(element, null, null);
		}
		AvlNode(T element, AvlNode<T> left, AvlNode<T> right){
			this.element = element;
			this.left = left;
			this.right = right;
			this.height = 0;
		}
		T element;
		AvlNode<T> left;
		AvlNode<T> right;
		int height;
		@Override
		public String toString(){
			return element.toString();
		}
	}
	public AvlTree(){
		root = null;
	}
	public void insert(T x){
		root = insert(x, root);
	}
	
	public void remove(T x){
		System.out.println("Sorry, remove unimplemented");
	}
	
	public T findMin(){
		return elementAt(findMin(root));
	}
	public T findMax(){
		return elementAt(findMax(root));
	}
	public T find(T x){
		return elementAt(find(x, root));
	}
	public void makeEmpty(){
		root = null;
	}
	
	public boolean isEmpty(){
		return root == null;
	}
	private T elementAt(AvlNode<T> t){
		return t == null ? null : t.element;
	}
	private AvlNode<T> findMin(AvlNode<T> t){
		if(t == null){
			return null;
		}
		while(t.left != null){
			t = t.left;
		}
		return t;
	}
	private AvlNode<T> findMax(AvlNode<T> t){
		if(t == null){
			return t;
		}
		while(t.right != null){
			t = t.right;
		}
		return t;
	}
	private AvlNode<T> find(T x, AvlNode<T> t){
		while(t != null){
			if(x.compareTo(t.element) < 0){
				t = t.left;
			}else if(x.compareTo(t.element) > 0){
				t = t.right;
			}else{
				return t;
			}
		}
		return null;
	}
	/**
	 * ??????
	 * @param x
	 * @param t
	 * @return
	 */
	private AvlNode<T> insert(T x, AvlNode<T> t){
		if(t == null){
			return new AvlNode<T>(x);
		}else if(x.compareTo(t.element) < 0){
			t.left = insert(x, t.left);
			if(height(t.left) - height(t.right) == 2){
				if(x.compareTo(t.left.element) < 0){
					t = rotateWithLeftChild(t);
				}else{
					t = doubleWithLeftChild(t);
				}
			}
		}else if(x.compareTo(t.element) > 0){
			t.right = insert(x, t.right);
			if(height(t.right) - height(t.left) == 2){
				if(x.compareTo(t.right.element) > 0){
					t = rotateWithRightChild(t);
				}else{
					t = doubleWithRightChild(t);
				}
			}
		}else{
			//Duplicate; do nothing
		}
		t.height = max(height(t.left), height(t.right)) + 1;
		return t;
	}
	
	/**
	 * ??????????
	 */
	private static <T extends Comparable<? super T>> int height(AvlNode<T> t){
		return t == null ? -1 : t.height;
	}
	private static int max(int lhs, int rhs){
		return lhs > rhs ? lhs : rhs;
	}
	/**
	 * ???????? 1 ????????
	 * 
	 * 				5
	 * 			  /	  \
	 * 			4 		6
	 * 		  /   \
	 * 		3		?
	 * 
	 * 	 			4
	 * 			  /	  \
	 * 			3 		5
	 * 		  /   	  /   \
	 * 		2		?		6
	 * 
	 * ? ??????????????????????????????
	 * @param k2
	 * @return
	 */
	private static <T extends Comparable<? super T>> AvlNode<T> rotateWithLeftChild(AvlNode<T> k2){
		//k2 ???? 5??k1 ???? 4
		AvlNode<T> k1 = k2.left;
		k2.left = k1.right;
		k1.right = k2;
		/**
		 * ??????????????????????????????????3,4,5.
		 * ??????????????????????????????
		 * 2, null
		 * ------
		 * 2,    3
		 * ------
		 * 2,    4
		 * ------
		 * 2,    5
		 */
		k2.height = max(height(k2.left), height(k2.right)) + 1;
		k1.height = max(height(k1.left), height(k1.right)) + 1;
		return k1;
	}
	/**
	 * ???????? 4 ????????
	 * 
	 *	 			5
	 * 			  /   \
	 * 			4		6
	 * 				   /  \
	 * 				 ?  	7
	 * 
	 * 
	 * 		 		6
	 * 			  /   \
	 * 			5		7
	 * 		  /   \	      \
	 * 		4		? 		8
	 * 
	 * @param k1
	 * @return
	 */
	private static<T extends Comparable<? super T>> AvlNode<T> rotateWithRightChild(AvlNode<T> k1){
		//k1 ???? 5??k2 ???? 6
		AvlNode<T> k2 = k1.right;
		k1.right = k2.left;
		k2.left = k1;
		/**
		 * ??????? 3 ?????????????5,6,7
		 * ????????????????????????
		 * 8, null
		 * ------
		 * 8,    7
		 * ------
		 * 8,    6
		 * ------
		 * 8,    5
		 */
		k1.height = max(height(k1.left), height(k1.right)) + 1;
		k2.height = max(height(k2.left), height(k2.right)) + 1;
		return k2;
	}
	
	/**
	 * ???????? 2 ?????????
	 * 
	 * 			   k3
	 * 			  /	  \
	 * 		   k1 		D
	 * 		  /   \
	 * 		A	   k2
	 *
	 * ?????? B ?? C??B ?? C ?????????????????????????? Avl ???????????
	 *
	 * 			   k3
	 * 			  /	  \
	 * 		   k1 		D
	 * 		  /   \
	 * 		A	   k2
	 * 			   / \
	 * 			 B	   C
	 * 
	 * k3.left = rotateWithRightChild(k3.left),?? k3.left ?? k1 ?????????????????
	 * 
	 * 			   k3
	 * 			  /	  \
	 * 		   k2 		D
	 * 		  /   \
	 * 		k1	   C
	 * 	   / \	     
	 * 	 A	  B	
	 * 
	 * rotateWithLeftChild(k3)
	 * 
	 * 			     k2
	 * 			  /	     \
	 * 		   k1 	      k3
	 * 		  /   \	      /  \
	 * 		A 		B	C	   D
	 * 
	 * @param k3
	 * @return
	 */
	private static <T extends Comparable<? super T>> AvlNode<T> doubleWithLeftChild(AvlNode<T> k3){
		/**
		 * k1 ???? 4??k2 ???? 5??k3 ???? 7
		 * ???????????????????��??��??????????????k2??k3
		 * ?????????????????????????
		 * B|C	null
		 * --------
		 * B|C	k2
		 * --------
		 * B|C	k1
		 * --------
		 * B|C	k3
		 */
		k3.left = rotateWithRightChild(k3.left);
		return rotateWithLeftChild(k3);
	}
	private static <T extends Comparable<? super T>> AvlNode<T> doubleWithRightChild(AvlNode<T> k1){
		k1.right = rotateWithLeftChild(k1.right);
		return rotateWithRightChild(k1);
	}
	private AvlNode<T> root;
	
	public static void main(String[] args) {
		AvlTree<Integer> avl = new AvlTree<Integer>();
		avl.insert(5);
		avl.insert(4);
		avl.insert(3);
		avl.insert(2);
		avl.insert(1);
		avl.insert(0);
	}
}































