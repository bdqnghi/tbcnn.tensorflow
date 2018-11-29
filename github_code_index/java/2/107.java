package main.ashu.data_structure.binarytreesandbst;

//AVL tree is self-balancing BST in which max diff b/w heights of left/right subtrees is 1.
//Height of BST is always log(n)..n= number of nodes.
//Insert, delete, search - O(logn) time
//The AVL trees are more balanced compared to Red Black Trees, but they may cause more rotations during insertion and deletion. 
//So if your application involves many frequent insertions and deletions, then Red Black trees should be preferred. 
//And if the insertions and deletions are less frequent and search is more frequent operation, then AVL tree should be preferred over Red Black Tree.
class Node {
	double data;
	Node left, right;
	int height;
	public Node(double value) {
		this.data = value;
		this.left = this.right = null;
		this.height = 1;
	}
}

public class AVLTree {
	Node root;  //representing the tree

	public int getBalanceFactor(Node root) {
		if(root == null) return 0;
		return getHeight(root.left) - getHeight(root.right);
	}
	public void inorder() {
		inorderUtil(root);
	}
	public void inorderUtil(Node root) {
		if(root == null) return;
		inorderUtil(root.left);
		System.out.print(root.data+" ");
		inorderUtil(root.right);
	}
	public void preorder() {
		preorderUtil(root);
	}
	public void preorderUtil(Node node) {
		if(node != null) {
			System.out.print(node.data+" ");
			preorderUtil(node.left);
			preorderUtil(node.right);
		}
	}
	public void insert(int key) {
		root = insertNodeUtil(root, key);   	
	}
	//modified insertion in BST
	public Node insertNodeUtil(Node node, int key) {
		if(node == null) {
			node = new Node(key);
			return node;
		}
		if(node.data > key) node.left = insertNodeUtil(node.left, key);
		else if(node.data < key)node.right = insertNodeUtil(node.right, key);
		else return node;  //not allowing duplicates
		//in return call...update the height of the ancestors
		node.height = 1 + Math.max(getHeight(node.left), getHeight(node.right));
		//now check if this ancestor node is balanced
		int balanceFactor = getBalanceFactor(node);
		//left left case
		if(balanceFactor>1 && key < node.left.data) return rotateRight(node);
		//left right case
		if(balanceFactor>1 && key > node.left.data) {
			node.left = rotateLeft(node.left);
			return rotateRight(node);
		}
		//right right case
		if(balanceFactor < -1 && node.right.data < key) return rotateLeft(node);
		//right left case
		if(balanceFactor < -1 && node.right.data > key) {
			node.right = rotateRight(node.right);
			return rotateLeft(node);
		}
		return node;
	}
	public int getHeight(Node root) {
		return (root==null) ? 0 : root.height;
	}
	public Node rotateLeft(Node root) {
		//save right node
		Node x = root.right;
		//save left of x
		Node T1 = x.left;
		//now rotate
		x.left = root;
		root.right = T1;
		//update the heights..first of old root and then of new root
		root.height = Math.max(getHeight(root.left), getHeight(root.right)) +1;
		x.height = Math.max(getHeight(x.left), getHeight(x.right)) +1;
		return x;  //return new root
	}
	public Node rotateRight(Node root) {
		//save left and its right child
		Node x = root.left;
		Node T2 = x.right;
		//rotate
		x.right = root;
		root.left = T2;
		//update heights ofold and new root
		root.height = Math.max(getHeight(root.left), getHeight(root.right)) + 1;
		x.height = Math.max(getHeight(x.left), getHeight(x.right)) + 1;
		return x; //return new root
	}
	public Node getInorderSucessor(Node node) {
		Node temp = node.right;
		while(temp.left != null) temp = temp.left;
		return temp;
	}
	public void delete(int key) {
		this.root = deleteNodeUtil(this.root, key);
	}
	//return type is Node to keep the links updated while deletion
	//note that unlike insertion, balancing will have to be done at the ancestors of the deleted nodes as well.
	//hence go with recursive implementation so that balance check can be done at ancestor node progressively as recursive calls return
	//Steps : Do standard deletion in BST, update height, maintain the balance of height
	public Node deleteNodeUtil(Node root, double data) {
		if(root == null) return root;
		if(data < root.data) {
			root.left = deleteNodeUtil(root.left, data);
		} 
		else if(data > root.data) {
			root.right = deleteNodeUtil(root.right, data);
		}
		else { //delete the current node
			if(root.left != null && root.right != null) {
				Node temp = getInorderSucessor(root);
				root.data = temp.data;
				root.right = deleteNodeUtil(root.right, temp.data);
			} 
			//single child case
			else if(root.left != null) root = root.left;
			else if(root.right != null) root = root.right;
			else root = null; //leaf node
		}
		//if deleted node was leaf node....return as no balance check required
		if(root == null) return root;
		//otherwise if in the middle of returning recursive call, check if height is balanced at the current node
		//update height now
		root.height = Math.max(getHeight(root.left), getHeight(root.right)) + 1;
		int balance = getBalanceFactor(root);
		//do balancing..pay special attention to relational operators
		//left left case
		if(balance > 1 &&  getBalanceFactor(root.left) >= 0) {
			return rotateRight(root);
		}
		//left right case
		else if(balance > 1 && getBalanceFactor(root.left) < 0) {
			root.left = rotateLeft(root.left);
			return rotateRight(root);
		}
		//right right case
		else if(balance < -1 && getBalanceFactor(root.right) <=0) {
			return rotateLeft(root);
		}
		else if(balance < -1 && getBalanceFactor(root.right) >0) {
			root.right = rotateRight(root.right);
			return rotateLeft(root);
		}
		return root;
	}

	public static void main(String args []) {
		AVLTree tree = new AVLTree();
		tree.insert(9);
		tree.insert(5);
		tree.insert(10);
		tree.insert(0);
		tree.insert(6);
		tree.insert(11);
		tree.insert(-1);
		tree.insert(1);
		tree.insert(2);
		System.out.print("Inorder traversal is : ");
		tree.inorder();
		System.out.println();
		System.out.print("Preorder traversal is : ");
		tree.preorder();
		System.out.println();
		System.out.println("Delteing 10 from the AVL tree");
		tree.delete(10);
		System.out.print("Inorder traversal after "+"deletion : ");
		tree.inorder();
		System.out.println();
		System.out.print("Preorder traversal after "+"deletion : ");
		tree.preorder();
	}
}
