
public class bTree {
	
	// Sets the root node to a null value
	bNode root = null;
	
	/** 
	 * This is a wrapper for the currentNode method
	 * creates a new node and assigns to root
	 * calls the currentNode method in the process
	 * @param data is the external input value
	 */
	public void addNode(String data) {
		
		root = currentNode(root, data);
	
	}
	
	/**
	 *  currentNode method returns a new node
	 *  currentNode declared as private. Accessible only within the bTree class.
	 *  @param root is the root node
	 *  @param data is the external input value
	 *  @return returns a new node
	 */
	private bNode currentNode(bNode root, String data) {
		
		// Check if the root node is the terminal node
		if(root == null) {
			
			// If root is terminal node, create new node
			// Left and right successor nodes already set to null
			bNode node = new bNode();
			node.data = data;
			
			// The new node will be the root node
			root = node;
			return root;
		
		}
		
		// If the root node is not the terminal node
		// and if the data value is smaller than the current root value
		// Traverse through tree until terminal node reached
		else if(data.compareToIgnoreCase(root.data) < 0) {
			
			// Go down left branch of node
			// Changes "focus" to the left successor node
			// Repeat process by calling method until terminal node reached
			root.left = currentNode(root.left, data);
	
		}
		
		// If the root is not null and data value is greater
		// Go down right successor node
		else {
			
			// Changes "focus" to the right successor node
			// Repeat process until terminal node reached
			root.right = currentNode(root.right, data);
			
		}
	
		return root;
		
	}
		
	// Traversal methods inorder traversal
	
	/**
	 * This method is a wrapper for the inorder traversal method
	 * Hides recursive method
	 * Calls traverse_inorder method
	 */
	public void inOrderTraversal() {
		traverse_inorder(root);
	}
	
	// To record the values obtained from the inorder traversal method
	// Need to create a stack
	Stack nameStack = new Stack();
	
	/**
	 * Recursive inorder tree traversal method
	 * General process is left node, root node, right node
	 * @param root is the root node 
	 */
	private void traverse_inorder(bNode root) {
		
		// Goes down to the leftmost node first
		// That will be the first value
		// Checks if there is a left successor node at each step
		// Repeats process until terminal node reached
		if(root.left != null) {
			traverse_inorder(root.left);
		}
		
		// Prints the nodes visited in inorder traversal
		// Already in sort order
		System.out.println(root.data);
		
		// To get reverse order need to use stack
		// Pushes elements into stack
		nameStack.push(root.data);
		
		// Checks if the right successor node has a value
		// If true, then repeats the traverse_inorder method
		if(root.right != null) {
			traverse_inorder(root.right);
		}
		
	}
	
}
