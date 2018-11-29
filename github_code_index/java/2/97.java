package AvlTree;

import java.util.Scanner;

public class AvlTree {
    public static Node root;
    
    /* Constructor */
    public AvlTree()
    {
    	root=null;
    }
    // To get maximum of two heights
    int max(int h1, int h2) {
        return (h1 > h2) ? h1 : h2;
    }
    // Check balancing of node
    int checkBalance(Node node){
    	if(node==null)
    		return 0;
    	else
    		return(getheight(node.left)-getheight(node.right));
    }
    
    //Function to rotate right at Node node
    Node rotateRight(Node node){
    	Node root = node.left;
    	Node temp = root.right;
    	node.left.right=node;
    	node.left=temp;
    	//Update heights of nodes
    	node.height = 1 + max(getheight(node.left), getheight(node.right));
    	root.height = 1 + max(getheight(root.left), getheight(root.right));
    	
    	
    	return root;
    	
    	
    }
    
    //Function to rotate left at Node node
    Node rotateLeft(Node node){
    	Node root = node.right; 
    	Node temp = root.left;
    	node.right.left=node;
    	node.right=temp;
    	
    	//Update heights of nodes
    	node.height = 1 + max(getheight(node.left), getheight(node.right));
    	root.height = 1 + max(getheight(root.left), getheight(root.right));
    	
    	
    	return root;
    	
    	
    }
    
    // Function to return height of node and 0 in node==null
    int getheight(Node N) {
        if (N == null)
            return 0;
        else
        	return N.height;
    }
    
    
    /*  Function to insert an element  */
    public Node insert(Node root,int val)
    {
        
        if (root == null){
        	Node node = null;
            node = new Node(val,1, null, null);//height set to 1 for new element.
            return node;
        }
        	
        else
        	//If val is less than node value go to left else go to left
        	if(root.value>val)
        		root.left=insert(root.left,val);
        	else
        		root.right=insert(root.right,val);
        //Update height of node.
        root.height = 1 + max(getheight(root.left), getheight(root.right));
        int bal = checkBalance(root);// Check balancing at node
        
        // Case 1: All 3 element in left straight line(req. one right rotation)
        if( bal > 1 && val < root.left.value)
        	return(rotateRight(root));
        
        // Case 2: All 3 element in left zig-zag line(req. left and right rotation)
        else if( bal > 1 && val > root.left.value){
        	root.left=rotateLeft(root.left);
        	return(rotateRight(root));
        }
        
        // Case 3: All 3 element in right straight line(req. one left rotation)
        else if( bal < -1 && val > root.right.value)
            return(rotateLeft(root));
        
        // Case 4: All 3 element in right zig-zag line(req. right and left rotation)
        else if( bal < -1 && val < root.right.value){
        	root.right=rotateRight(root.right);
        	return(rotateLeft(root));
        }
        return root;//return updated root each time
        
        	
    }
    
    
    /*  Function for inorder traversal for binary search tree */
    public void inorder(Node node)
    {
        if (node == null) 
        {
            return;
        }
        inorder(node.left);
        //System.out.print("\n"+node.value+" balance"+ checkBalance(node));
        System.out.print("\n"+node.value);
        inorder(node.right);
        
    }

    public static void main(String[] args)
    {             
        Scanner scan = new Scanner(System.in);
        /* Creating object of Binary search tree */
        AvlTree avl = new AvlTree(); 
        System.out.println("AVL Tree\n");
        System.out.println("Please Insert No. of element you want to insert in tree\n");
        int size = scan.nextInt();
        if(size>0)
        {
        	for(int i=0;i<size;)
        	{
        		System.out.println("\nPlease enter element no."+(i));
        		int val = scan.nextInt();
        		root=avl.insert(root, val ); 
        		i++;
        		
        	}
        	System.out.println("\nInorder traversal for tree\n");
        	avl.inorder(root);
        }
        else
        {
        	System.out.println("\nNot valid entry\n");
        } 

    }
}
