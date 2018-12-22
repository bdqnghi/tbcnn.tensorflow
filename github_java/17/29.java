/*
 * RedBlackTree Rules
 * 1. Every is red or balck
 * 2. root is Black
 * 3. newNode is Red
 * 4. no two consecutive red node
 * 5. root-leaf should have the same black nodes
 * 6. nulls are black
 * #  Red aunt color flip
 * #  Black aunt rotate
 */
public class RedBlackTree<K , V> {
	
	Node<K , V> root;
	int currentSize;
	class Node<K, V>{	// ADT
		K key;
		V value;
		Node<K , V > left , right , parent;
		boolean isLeftChild, black;
		public Node(K key , V value) {
			this.key = key;
			this.value = value;
			left = right = parent = null;
			black = false;	// new nodes are red
			isLeftChild = false;	// doesn't matter not knowwing whether is right or left
		}
	}
	public void add(K key , V value) {
		Node<K , V> node = new Node<K , V>(key , value);
		if(root == null) {
			root = node;
			root.black = true;
			currentSize++;
			System.out.println("newNode : "  + node.value + "\nCurrentSize : " + currentSize + "\n");
			return;
		}
		add(root , node);
		System.out.println("newNode : " + node.value + "\nCurrentSize : " + currentSize + "\n");
	}
	private void add(Node<K , V> parent , Node<K , V> newNode) {
		if(((Comparable<K>)parent.key).compareTo(newNode.key) < 0) {
			if(parent.right == null) {
				parent.right = newNode;
				newNode.parent = parent;
				newNode.black = false; // default is set as false but it's good to keep in mind that the new insertion is red
				newNode.isLeftChild = false;
				currentSize++;
				return;
			}
			add(parent.right , newNode);
		}
		if(((Comparable<K>)parent.key).compareTo(newNode.key) > 0) {
			if(parent.left == null) {
				parent.left = newNode;
				newNode.parent = parent;
				newNode.black = false; // default is set as false but it's good to keep in mind that the new insertion is red
				newNode.isLeftChild = true;
				currentSize++;
				return;
			}
			add(parent.left , newNode);
		}
		checkColor(newNode);	// ever newNode should be checked --- > ?
		
	}
	/*
	 * no consecutive two red nodes(otherwise will violate the RBTree)
	 */
	public void checkColor(Node<K , V> newNode) {
		if(newNode == root) {
			return;
		}
		if( !newNode.black && !newNode.parent.black) {
			correctTree(newNode);
		}
		checkColor(newNode.parent);
	}
	public void correctTree(Node<K, V> node) {
		if(node.parent == root) {
			root.black = true;
			return;
		}
		if(node.parent.isLeftChild) {
			if(node.parent.parent.right == null || node.parent.parent.right.black) {	// aunt is black , and black aunt rotate
				rotate(node);
				return;
			}
			if(node.parent.parent.right != null) { // aunt is red , and red aunt color flip
				node.parent.parent.right.black = true;
			}
			node.parent.parent.black = false; // grandparent becomes red, parent and aunt becomes black after teh colorflip
			node.parent.black = true;
			return;
		}
		if(!node.parent.isLeftChild) {
			//  aunt is grandParent.left
			if(node.parent.parent.left == null || node.parent.parent.left.black) {	// aunt is black , and black aunt rotate
				rotate(node);
				return;
			}
			if(node.parent.parent.left != null) { // aunt is red , nad red aunt color flip 
				node.parent.parent.left.black = true;
			}
			node.parent.parent.black = false;
			node.parent.black = true;
		}
	}
	public void rotate(Node<K , V> node) {
		if(node.isLeftChild) {
			if(node.parent.isLeftChild) {
				rightRotate(node.parent.parent);
				node.black = false;
				node.parent.black = true;
				if(node.parent.right != null) {
					node.parent.right.black = false;
				}
				return;
			}
			// node.parent is not left child. RLrotate
			rightLeftRotate(node.parent.parent);
			node.black = true;
			node.right.black = node.left.black = false; // nullPointer Exception
			return;										// rightLeftRotate returns the grandParents node
		}
		// handle the rightChild here
		if(!node.parent.isLeftChild) {
			leftRotate(node.parent.parent);
			node.black = false;
			node.parent.black = true;
			if(node.parent.left != null) {
				node.parent.left.black = false;
			}
			return;
		}
		// node.parent is not right child. LRrotate
		leftRightRotate(node);
		node.black = true;
		node.right.black = node.left.black = false;
		return;
	}
	public void leftRotate(Node<K , V> node) {	// this node is the grandParent Node
		Node<K , V > temp = node.right;			// check again
		node.right = temp.left;
		if(node.right != null) {
			node.right.parent = node;
			node.right.isLeftChild = false;
		}
		if(node.parent == null) {
			// this is the root Node
			root = temp;
			temp.parent = null;
		}else {
			temp.parent = node.parent;
			if(node.isLeftChild) {
				temp.isLeftChild = true;
				temp.parent.left = temp;
			}else {
				temp.isLeftChild = false;
				temp.parent.right = temp;
			}	
		}
		temp.left = node;
		node.isLeftChild = true;
		node.parent = temp;
	}
	public void rightRotate(Node<K , V> node) {
		Node<K , V> temp = node.left;
		node.left = temp.right;
		if(node.left != null) {
			node.left.parent = node;
			node.left.isLeftChild = true;
		}
		if(node.parent == null) {
			// this is the root Node
			root = temp;
			temp.parent = null;
		}else {
			temp.parent = node.parent;
		//
			if(node.isLeftChild) {
				temp.isLeftChild = true;
				node.parent.left = temp;
			}else {
				temp.isLeftChild = false;
				node.parent.right = temp;
			}
		}
		temp.right = node;
		node.isLeftChild = false;
		node.parent = temp;
	}
	public void leftRightRotate(Node<K , V> node) {
		leftRotate(node.left);
		rightRotate(node);
	}
	public void rightLeftRotate(Node<K , V> node) {
		rightRotate(node.right);
		leftRotate(node);
	}
	public int height() {
		if(root == null) {
			return 0;
		}
		return height(root) - 1;
	}
	public int height(Node<K , V> node) {
		if(node == null) return 0;
		int leftHeight = height(node.left);
		int rightHeight = height(node.right);
		
		return Math.max(leftHeight, rightHeight) + 1;
	}
	/*
	 *  check the black Node from root-leaf
	 *  each path should have teh same amount of black Nodes
	 *  still questionable
	 */
	public int blackNodes(Node<K , V> node) {
		if(node == null) {
			return 1;
		}
		int rightBlackNodes = blackNodes(node.right);
		int leftBlackNodes  = blackNodes(node.left);
		if(rightBlackNodes != leftBlackNodes) {
			
		}
		if(node.black) {
			leftBlackNodes++;
		}
		return leftBlackNodes;
	}
	public void printNodeColor(Node<K , V> node) {
		String strColor = (node.black == true) ? "Black" : "Red";
		System.out.println("\nColor : " + strColor + "\n");
	}
	public void printTree(Node<K , V> node) {
		if(node == null) {
			return;
		}
		printTree(node.left);
		printTree(node.right);
		System.out.print("key : " + node.key + "\nValue : " + node.value); 
		printNodeColor(node);
	}
}
