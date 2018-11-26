package lab3AndAnd;

/**
 * Created by @author Andreas Andersson, Systemutveckling on 2015-09-25.
 * 
 * TreeNode is a Node in the Avl-tree that keeps references to 3 other TreeNodes- 1 TreeNode for the 
 * Left Sub-tree, one for the right and one TreeNode for it's "Parent".
 * The class is used to set/get information about these references, but also to carry a "Key"/"Value"
 * and a "balance" value between it's right and left sub-tree. The "PrintTree and PrintNodeValue" methods 
 * are used to print a visualized image of the nodes together.
 * 
 */
public class TreeNode {	
	
	private int balance;
    private int data;
    private TreeNode left;
    private TreeNode right;
    private TreeNode parent;
  
    /**
     * Constructor that recieves an int that will be used as this TreeNodes "Key/Value".
     * This "Key" is used to locate this TreeNode-Object.
     * @param data - this TreeNodes Key.
     */
    public TreeNode (int data){    	 	
        this.data=data;
    }
    
    /**
     * A Method that sets "balance" depending on the number of nodes in the
     * left and right subtree. The Parameter recieves an int to do this.
     *
     * @param value - the balance variable's new value.
     */
    public void setBalance(int value){
    	balance=value;
    }
    
    /**
     * Returns an int with the left&right sub-tree balance.
     * @return int
     */
    public int getBalance(){
    	return balance;
    }
    
    /**
     * SetData is used to change the value or KEY of this TreeNode.
     * primarily used when a TreeNode is removed from the AVLtree.
     * @param data -int with the new Key
     */
    public void setData(int data){
	   this.data=data;
   }
    
    /**
     * A Method to give this TreeNode a new Parent-TreeNode.
     * @param node - TreeNode, the new Parent TreeNode
     */
    public void setParent(TreeNode node){
	   parent=node;
   }
    
    /**
     * Return this TreeNodes parent.
     * @return TreeNode
     */
    public TreeNode getParent(){
	   return parent;
   }
    
    /**
     * Set this TreeNodes left child, Receieves a TreeNode as parameter.
     * @param left -This TreeNodes left-child.
     */
    public void setLeft(TreeNode left){
        this.left=left;
    }
    
    /**
     * Set this TreeNodes right child, Receives a TreeNode as parameter.
     * @param right -This TreeNodes right-child
     */
    public void setRight(TreeNode right){
        this.right=right;
    }
    
    /**
     * Returns this TreeNodes Key as an int.
     * @return int
     */
    public int getData(){
        return data;
    }
    
    /**
     * Returns the Left-Child as a TreeNode.
     * @return TreeNode
     */
    public TreeNode getLeft(){
        return left;
    }
    
    /**
     * Returns the Right-Child as a TreeNode.
     * @return TreeNode
     */
    public TreeNode getRight(){
        return right;
    }

    //Print methods
    
    /**
     * A Method that is used to print the TreeNodes in the entire AVL-TREE.
     * Uses printTree(boolean,String) for the actual print.
     */
    public void printTree(){

        if(this.right!=null){
            right.printTree(true, "");
        }
        printNodeValue();
        if(this.left!=null){
            left.printTree(false, "");
        }
    }
    
    /**
     * A part of the process to print the tree. This method does the actual "print".
     * Receives a Boolean and a String. The Boolean is used to determine 
     * if the visual print should be a / or a \ . (Right or left child).
     * 
     * @param isRight -boolean for / or \ print.
     * @param indent -String to print.
     */
    private void printTree(boolean isRight, String indent){

        if(right!=null){
            right.printTree(true,indent+(isRight ? "      ":" |     ")); 
        }
        System.out.print(indent);
        if(isRight){
            System.out.print(" /");
        }else{
            System.out.print(" \\");
        }
        System.out.print("----- ");
        printNodeValue();
        if(left!=null){
            left.printTree(false,indent+ (isRight? " |    ":"      "));
        }

    }
    
    /**
     * Prints the Key and a newline in the Console.
     * Is used with PrintTree.
     */
    private void printNodeValue(){
        System.out.print(data);
        System.out.print('\n');         
    }

}
