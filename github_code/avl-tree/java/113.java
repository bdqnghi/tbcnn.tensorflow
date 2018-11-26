package structures;

import java.util.ArrayList;

/**
 * This class implements an AVL tree.
 * 
 * @author RU NB CS112
 *
 */
public class AVLTree {

	/**
	 * The root of this AVL tree.
	 */
	public AVLTreeNode root;
	
	/**
	 * Number of nodes in this AVL tree. 
	 */
	public int size;
	
	/**
	 * Initializes this AVL tree to empty.
	 *
	 */
	public AVLTree() {
		root = null;
		size = 0;
	}
	
	/**
	 * Searches for the given key in this AVL tree and returns the associated
	 * value if the key exists, otherwise returns null. Search takes 
	 * O(log n) time in the worst case.
	 * 
	 * @param key Key 
	 * @return value associated with key if exists, else null
	 */
	public String get(int key) {
		AVLTreeNode node = root;
		while (node != null) {
			if (key == node.key) {
				return node.value;
			}
			if (key < node.key) {
				node = node.left;
			} else {
				node = node.right;
			}
		}
		return null;
	}

	/**
	 * Inserts a (key,value) pair into this AVL tree. If key already exists, then
	 * replaces the old value with the given value and returns the old. Otherwise,
	 * inserts and returns null. Insertion takes O(log n) time in the worst case.
	 * 
	 * @param key Key 
	 * @param value Value
	 * @return Old value
	 */
	public String put(int key, String value) {
		/** COMPLETE THIS METHOD **/
		if(root==null)
		{
			root=new AVLTreeNode(key, value);
			root.balanceFactor=0;
			root.height=0;
			size=0;
			return null;
			
		}
		AVLTreeNode ptr=root;
		AVLTreeNode lag=null;
		boolean right=false;
		
		while(ptr!=null)
		{
			if(ptr.key==key)
			{
				String temp=ptr.value;
				ptr.value=value;
				return temp;
			}
			lag=ptr;
			if(ptr.key<key)
			{
				ptr=ptr.right;
				right=true;
			}
			else
			{
				ptr=ptr.left;
				right=false;
			}
			
		}
		AVLTreeNode n = new AVLTreeNode(key, value);
		n.balanceFactor=0;
		n.height=0;
		n.parent=lag;
		if(right)
		{
			lag.right=n;
			
		}
		else
		{
			lag.left=n;
		}
		ptr=n.parent;
		lag=n;
		
		if (lag.key > ptr.key) right = true;
		else right=false;
		while(true){
			ptr.height = Math.max(height(ptr.left), height(ptr.right)) + 1;
			if(right){
				if (ptr.balanceFactor == 0) ptr.balanceFactor = 1;
				else if (ptr.balanceFactor == -1) ptr.balanceFactor = 0;
				else{ //unbalanced balancefactor = 1
					if (height(ptr.right) - height(ptr.left) == 2){
						if (ptr.balanceFactor != lag.balanceFactor){ //case 2
							lag = rotateRight(lag);
							lag.parent = ptr;
							ptr.right = lag;
						}
					
						if (ptr == root){
							root = rotateLeft(ptr);
							root.parent = null;
							return null;
						}
						else{ //ptr != root
							if (ptr.parent.right == ptr){
								AVLTreeNode parent = ptr.parent;
								ptr = rotateLeft(ptr);
								ptr.parent = parent;
								parent.right = ptr;
							}
							else{
								AVLTreeNode parent = ptr.parent;
								ptr = rotateLeft(ptr);
								ptr.parent = parent;
								parent.left = ptr;
							}
							return null;
						}
					}
				}
			}
			else{ //left
				if (ptr.balanceFactor == 0) ptr.balanceFactor = -1;
				else if (ptr.balanceFactor == 1) ptr.balanceFactor = 0;
				else{ //unbalanced balancefactor = -1
					if (height(ptr.left) - height(ptr.right) == 2){
						if (ptr.balanceFactor != lag.balanceFactor){ //case 2
							lag = rotateLeft(lag);
							lag.parent = ptr;
							ptr.left = lag;
						}
	
						if (ptr == root){
							root = rotateRight(ptr);
							root.parent = null;
							return null;
						}
						else{ //ptr != root
							if (ptr.parent.right == ptr){
								AVLTreeNode parent = ptr.parent;
								ptr = rotateRight(ptr);
								ptr.parent = parent;
								parent.right = ptr;
							}
							else{
								AVLTreeNode parent = ptr.parent;
								ptr = rotateRight(ptr);
								ptr.parent = parent;
								parent.left = ptr;
							}
								return null;
						}
					}
				}
				
			}
				lag = ptr;
				ptr = ptr.parent;
				if (ptr == null) break;
				if (lag.key > ptr.key) right = true;
				else right = false;
		}
		return null;
	}

	/**
	 * Makes an isomorphic AVL tree for a given BST that is AVL-balanced, 
	 * in O(n) time. 
	 *  
	 * @param root Root of the BST
	 * @return AVL tree
	 */
	public static AVLTree makeIsomorphicAVL(BSTNode root) {
		/** COMPLETE THIS METHOD **/
		if(root==null)
		{	
			return new AVLTree();
		}
		AVLTree n = new AVLTree();
		n.root = new AVLTreeNode(root.key, root.value);
		n.root.left= makeIsomorphicAVL(root.left).root;
		n.root.right = makeIsomorphicAVL(root.right).root;
		if (n.root.right == null){
			if(n.root.left == null)
				n.root.height = 0;
			else n.root.height = n.root.left.height+1;
		}
		else if(n.root.left == null){
			if(n.root.right == null)
				n.root.height = 0;
			else n.root.height = n.root.right.height+1;
			
		}
		else{
			if(n.root.right.height >= n.root.left.height) n.root.height = n.root.right.height+1;
			else n.root.height = n.root.left.height+1;
		}
		
		if(n.root.right != null){
			if(n.root.left != null){
				if(n.root.left.height > n.root.right.height) n.root.balanceFactor = -1;
				else if (n.root.left.height < n.root.right.height) n.root.balanceFactor = 1;
				else n.root.balanceFactor = 0;
			}
			else n.root.balanceFactor = 1;
		}
		else{
			if (n.root.left != null) n.root.balanceFactor = -1;
			else n.root.balanceFactor = 0;
		}
		// following line is a placeholder for compiler
        return n;
	}
	
	/**
	 * Builds an AVL tree out of an array list of (key,value) pairs sorted in ascending order
	 * of keys, in worst case O(n) time where n is the number of (key,value) pairs.
	 * 
	 * @param al Sorted array list of (key,value) pairs
	 * @return AVL Tree
	 */
	public static AVLTree makeAVLTree(ArrayList<KeyValuePair> al) {
			/** COMPLETE THIS METHOD **/
			
			if(al==null)
			{
				return null;
			}
			if (al.size() == 0) return null;
			AVLTree finaltree = new AVLTree();
			finaltree.root = new AVLTreeNode(al.get(0).key, al.get(0).value);
			finaltree.root.height = al.size() - 1;
			AVLTreeNode ptr = finaltree.root;
			for(int i = 1; i < al.size(); i++){
				ptr.right = new AVLTreeNode(al.get(i).key, al.get(i).value);
				ptr.right.parent = ptr;
				ptr.height = Math.max( height(ptr.left), height(ptr.right) ) + 1;
				ptr = ptr.right;
			}
			if (al.size() <=2)return finaltree;
			ptr= ptr.parent.parent;
			//ptr.right.height=1;
			while(ptr!= null){
				ptr.height = Math.max( height(ptr.left), height(ptr.right) ) + 1;
				AVLTreeNode parent = ptr.parent;
				if (parent != null){
					ptr = rotateLeft(ptr);
					ptr.parent = parent;
					if (ptr.key > ptr.parent.key) ptr.parent.right = ptr;
					else ptr.parent.left = ptr;
				}
				else{ // ptr = root
					finaltree.root = rotateLeft(ptr);
					finaltree.root.parent = null;
					ptr = finaltree.root;
					ptr.height = Math.max( height(ptr.left), height(ptr.right) + 1 );
					if (unbalanced(ptr.left)){
						ptr.left = rotateLeft(ptr.left);
						ptr.left.parent = ptr;
					}
					finaltree.size = height(finaltree.root);
					return finaltree;
				}
				if (unbalanced(ptr.left)){
					ptr.left = rotateLeft(ptr.left);
					ptr.left.parent = ptr;
				}
				if (unbalanced(ptr)){
					if(ptr == finaltree.root){
						ptr = autoRotate(ptr);
						ptr.parent = null;
						
					}
					else{ // ptr isnt root
						parent = ptr.parent;
						if (ptr.key > parent.key){
							ptr = rotateRight(ptr);
							parent.right = ptr;
							ptr.parent = parent;
						}
						else{ // ptr.key < parent.key
							ptr = autoRotate(ptr);
							parent.left = ptr;
							ptr.parent = parent;
						}
					}
				}
				
				ptr.height = Math.max( height(ptr.left), height(ptr.right) ) + 1;
				ptr  = ptr.parent;
			}
			return finaltree;
		}
	
	
	public void printPreorder() {
    	printPreorder(root);
    	System.out.println();
    }

    static void printPreorder(AVLTreeNode root) {
    	if (root == null) {
    		return;
    	}

    	System.out.print(" " + root + " ");
    	printPreorder(root.left);
    	printPreorder(root.right);
    }
   
    public void printInorder() {
    	printInorder(root);
    	System.out.println();
    }
    
    static void printInorder(AVLTreeNode root) {
    	if (root == null) {
    		return;
    	}

    	printInorder(root.left);
    	System.out.print(" " + root + " ");
    	printInorder(root.right);
    }
    private static AVLTreeNode rotateLeft(AVLTreeNode x)
    {
    	AVLTreeNode q = x.right;
    	AVLTreeNode temp=q.left;
    	x.right=temp;
    	q.left=x;
    	x.parent=q;
    	if(x.right != null) x.right.parent = x;
    	x.height = Math.max( height(x.left), height(x.right) ) +1;
    	if (height(x.left) < height(x.right)) x.balanceFactor = 1;
    	else if(height(x.left) > height(x.right)) x.balanceFactor = -1;
    	else x.balanceFactor = 0;
    	q.height = Math.max( height(q.left), height(q.right) ) + 1;
    	if (height(q.left) > height(q.right)) q.balanceFactor = -1;
    	else if(height(q.left)< height(q.right)) q.balanceFactor = 1;
    	else q.balanceFactor = 0;
    	
    	return q;
    
    }
    private static AVLTreeNode rotateRight(AVLTreeNode x)
    {
    	AVLTreeNode q = x.left;
    	AVLTreeNode temp=q.right;
    	x.left=temp;
    	q.right=x;
    	x.parent=q;
    	if (x.left != null) x.left.parent = x;
    	x.height = Math.max( height(x.left), height(x.right) ) +1;
    	if (height(x.left) < height(x.right)) x.balanceFactor = 1;
    	else if(height(x.left) > height(x.right)) x.balanceFactor = -1;
    	else x.balanceFactor = 0;
    	q.height = Math.max( height(q.left), height(q.right) ) + 1;
    	if (height(q.left) > height(q.right)) q.balanceFactor = -1;
    	else if(height(q.left)< height(q.right)) q.balanceFactor = 1;
    	else q.balanceFactor = 0;
    	
    	return q;
    	
    }
    private static boolean unbalanced(AVLTreeNode n)
    {
    	if (n == null) return false;
    	if(n.left==null)
    	{
    		if (n.right == null) return false;
    		if(n.right.height>=1) return true;
    		else return false;
    	}
    	if(n.right == null){
    		if (n.left.height >=1) return true;
    		else return false;
    	}
    	else
    	{
    		if(Math.abs((float)n.left.height - (float)n.right.height) >= 2) return true;
    		else return false;
    	}
    }
    private static int height(AVLTreeNode curr)
    {
    	return curr == null ? -1 : curr.height;
    }
    private static AVLTreeNode autoRotate(AVLTreeNode x){
    	if (x.left == null && x.right == null) return x;
    	if (height(x.left) - height(x.right) == 2){
    		if (x.left.balanceFactor != 0 && x.balanceFactor != x.left.balanceFactor){
    			x.left = rotateLeft(x.left);
    			x.left.parent = x;
    		}
    		return rotateRight(x);
    		
    	}
    	else if (height(x.left) < height(x.right)){
    		if (x.right.balanceFactor != 0 && x.balanceFactor != x.right.balanceFactor){
    			x.right = rotateRight(x.right);
    			x.right.parent = x;
    		}
    		return rotateLeft(x);
    		
    	}    	
    	return null;
    	
    	
    	
    	
    }
   
}