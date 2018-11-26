package BinaryTree;

public class TreeAvl extends Tree 
{
	public Node Root;
	
	public int offSpring(Node node)
	{
		return (node.left != null) ? (node.right != null ? 2 : 1) : (node.right != null ? 1 : 0);
	}
	
	public Node rightRotate(Node nodo)
	{
		Node temp = nodo.left;
		Node temp2 = temp.right;
		
		temp.right = nodo;
		nodo.left = temp2;
		
		nodo.altulra = max(nodo.left.altulra, nodo.right.altulra) + 1;
		temp.altulra = max(temp.left.altulra, nodo.right.altulra) + 1;
		
		return temp;
		
	}
	
	public int getBalance(Node N) 
	{
	        if (N == null)
	            return 0;
	        else
	        	return this.height(N.left) - this.height(N.right);
	 }
	public Node leftRotate(Node nodo)
	{
		Node temp = nodo.right;
		Node Temp2 = temp.left;
		
		temp.left = nodo;
		nodo.right = Temp2;
		
		nodo.altulra = max(this.height(nodo.left), this.height(nodo.right)) + 1;
		temp.altulra = max(this.height(temp.left), this.height(nodo.right)) + 1;
		
		return temp;
	}
	
	 public int height(Node N)
	    {
	        if (N == null)
	             return 0;
	         return N.altulra;
	    }
	
	 public int max(int a, int b) 
	 {
		 return (a > b) ? a : b;
	 }
	 
	public Node insert(Node root, int toAdd)
	{
		if(root == null)
			return new Node(toAdd);
		
		if(toAdd < root.value)
			root.left = this.insert(root.left, toAdd);
		else if(toAdd > root.value)
			root.right = this.insert(root.right, toAdd);
		else
			return root;
		
		root.altulra = 1 + max(this.height(root.left), this.height(root.right));
		
		int balance = getBalance(root);
		
		 if (balance > 1 && toAdd < root.left.value)
			 return rightRotate(root);
		 
		 if (balance < -1 && toAdd > root.right.value)
			 return leftRotate(root);
		
		 if (balance > 1 && toAdd > root.left.value) 
		 {
			 root.left = leftRotate(root.left);
			 return rightRotate(root);
	     }
		 if (balance < -1 && toAdd < root.left.value) 
		 {
			 root.right = rightRotate(root.right);
			 return	leftRotate(root);
	     }
		 
		 return root;
	}
	
	public Node delete(Node root, int toDelete)
	{
		if(root == null)
			return root;
		if( toDelete < root.value)
			root.left =  this.delete(root.left, toDelete);
		else if(toDelete > root.value)
			root.right = this.delete(root.right, toDelete);
		else
		{
			 if (root.left == null)
	                return root.right;
	            else if (root.right == null)
	                return root.left;
	 
			  Node temp = minValueNode(root.right);
              root.value= temp.value;
	      
	            root.right = delete(temp, root.value);    
		}

		
        root.altulra = max(height(root.left), height(root.right)) + 1;
 
        int balance = getBalance(root);
 
        if (balance > 1 && getBalance(root.left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root.left) < 0)
        {
            root.left = leftRotate(root.left);
            return rightRotate(root);
        }
 
        if (balance < -1 && getBalance(root.right) <= 0)
            return leftRotate(root);
 
        if (balance < -1 && getBalance(root.right) > 0)
        {
            root.right = rightRotate(root.right);
            return leftRotate(root);
        }
 
		return root;
	}
	 Node minValueNode(Node node)
	    {
	        Node current = node;
	        while (current.left != null)
	           current = current.left;
	        return current;
	    }
	 void preOrder(Node node)
	    {
	        if (node != null)
	        {
	            System.out.print(node.value + " ");
	            preOrder(node.left);
	            preOrder(node.right);
	        }
	    }
	 
	    public static void main(String[] args)
	    {
	        TreeAvl tree = new TreeAvl();
	 
	        /* Constructing tree given in the above figure */
	        tree.root = tree.insert(tree.root, 9);
	        tree.root = tree.insert(tree.root, 5);
	        tree.root = tree.insert(tree.root, 10);
	        tree.root = tree.insert(tree.root, 0);
	        tree.root = tree.insert(tree.root, 6);
	        tree.root = tree.insert(tree.root, 11);
	        tree.root = tree.insert(tree.root, -1);
	        tree.root = tree.insert(tree.root, 1);
	        tree.root = tree.insert(tree.root, 2);
	 
	        /* The constructed AVL Tree would be
	           9
	          /  \
	         1    10
	        /  \    \
	        0    5    11
	        /    /  \
	        -1   2    6
	         */
	        System.out.println("Preorder traversal of "+
	                            "constructed tree is : ");
	        tree.preOrder(tree.root);
	 
	        tree.root = tree.delete(tree.root, 10);
	 
	        /* The AVL Tree after deletion of 10
	           1
	          /  \
	         0    9
	        /     / \
	        -1    5   11
	        /  \
	        2    6
	         */
	        System.out.println("");
	        System.out.println("Preorder traversal after "+
	                           "deletion of 10 :");
	        tree.preOrder(tree.root);
	    }
}
