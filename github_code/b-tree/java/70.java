package Main;

public class bTree {
	
	bNode root = null;
	
	/** Wrapper that calls the rNode class to hide details from the user.
	 * 
	 * @param data data from the new Node to carry. [String]
	 */
	public void addNode (String data) {
		root = rNode(root,data);
	}
	
	/** rNode method creates a new Node by recursively traversing the tree until
	 *  a left Node is found.
	 *  
	 *  
	 * @param root
	 * @param data
	 * @return returns handle to node
	 */
	private bNode rNode (bNode root, String data) {
		
		if(root == null) {
			bNode node = new bNode(); //Create new bNode
			node.data = data; //Store data
			node.left = null;
			node.right = null;
			root = node;
			return root; //Returns handle to node
		} 
		// if not a terminal node, recurse left if data < root.data
		// otherwise recurse right
		else if (data.compareToIgnoreCase(root.data) < 0) { //Might have screwed this up
			root.left = rNode(root.left, data);
		} else {
			root.right = rNode(root.right,data);
		}
		return root;
	}
	
	// Method to print tree in order (Wrapper for recursive method)
	public void inOrder (bNode root) {
		traverse_inorder(root);
	}
	
	// Recursive inorder tree traversal
	private void traverse_inorder (bNode root) {
		// If root.left exists, go to that one instead then repeat method
		if (root.left != null) traverse_inorder(root.left);     // Left
		System.out.println(root.data);     					    // Root
		if (root.right != null) traverse_inorder(root.right);   // Right
	}
	
	// Method to print tree pre order (Wrapper for recursive method)
	public void preOrder (bNode root) {
		traverse_preorder(root);
	}
	
	// Recursive preorder tree traversal
	private void traverse_preorder (bNode root) {
		System.out.println(root.data);                          // Root
		if (root.left != null) traverse_preorder(root.left);    // Left
		if (root.right != null) traverse_preorder(root.right);  // Right
	}
	
	// Method to print tree in post order (Wrapper for recursive method)
	public void postOrder (bNode root) {
		traverse_postorder(root);
	}
	
	// Recursive postorder tree traversal
	private void traverse_postorder(bNode root) {
		if (root.left != null) traverse_preorder(root.left);    // Left
		if (root.right != null) traverse_preorder(root.right);  // Right
		System.out.println(root.data);                          // Root
	}
	
	// Special inorder method that pushes to stack instead of printing, then returns stack
	public Stack inOrderToStack (bNode root) {
		Stack s = new Stack();
		traverse_inorder_stack(root,s);
		return s;
	}
	
	// Recursive inorder tree traversal for stacks
	private void traverse_inorder_stack (bNode root, Stack s) {
		// If root.left exists, go to that one instead then repeat method
		if (root.left != null) traverse_inorder_stack(root.left,s);     // Left
		s.push(root.data);    					                        // Root
		if (root.right != null) traverse_inorder_stack(root.right,s);   // Right
	}
}
