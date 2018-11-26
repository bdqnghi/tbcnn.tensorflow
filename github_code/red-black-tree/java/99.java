import java.util.ArrayList;
import java.util.Collections;

/**
 * Class for red black tree
 * This is a purely functional solution, meaning that rather
 * than inserting a new node into the tree, we create immutable 
 * copies of existing nodes all the way down the tree to the new node, 
 * and all of the unchanged nodes from the operation can still be 
 * referenced from the new copy, resulting in no destructive updates 
 * of any variable. Thus creating an immutable Red Black Tree.
 * @author Kanishk Yadav
 */

public class RedBlackTree {
    
	private static final int RED   = 0;
	private static final int BLACK = 1;
	final RedBlackTree left;
	final RedBlackTree right;
	final int val;
	final int color;
    
	/**
	 * Constructor for immutable red black tree
	 * @param left
	 * @param val
	 * @param right
	 * @param color
	 */
    public RedBlackTree(RedBlackTree left, int val, RedBlackTree right, int color) 
    {
		this.left = left;
		this.val = val;
		this.right = right;
		this.color = color;
	}

	private RedBlackTree blacken()
    {
    	if(this.isRed())
    	{
    		RedBlackTree temp = new RedBlackTree(this.left, this.val, this.right, BLACK);
    		return temp;
    	}
    	return this;
    }

	/**
	 * Method used to set recursive condition
	 * for update method
	 * Inherited by EmptyRedBlackTree
	 * @return
	 */
    protected boolean isEmpty()
    {
    	if(this.val == Integer.MAX_VALUE)
    	{
    		return true;
    	}
    	return false;
    }
    
    private boolean isBlack()
    {
    	return (this.color == BLACK);
    }

    private boolean isRed()
    {
    	return (this.color == RED);
    }    

    private RedBlackTree rotateLeft()
    {
    	EmptyRedBlackTree tempEmptyTree = new EmptyRedBlackTree();
    	RedBlackTree temp1 = new RedBlackTree(this.left, this.val, tempEmptyTree.update(this.right.left), this.color);
    	RedBlackTree temp2 = new RedBlackTree(temp1, this.right.val, this.right.right, this.right.color );
    	return temp2;
    }
 
    private RedBlackTree rotateRight()
    {
    	EmptyRedBlackTree tempEmptyTree = new EmptyRedBlackTree();
    	RedBlackTree temp1 = new RedBlackTree(tempEmptyTree.update(this.left.right), this.val, this.right, this.color);
    	RedBlackTree temp2 = new RedBlackTree(this.left.left, this.left.val, temp1, this.left.color );
    	return temp2;
    }    

    private RedBlackTree recolored()
    {
    	RedBlackTree temp = new RedBlackTree(this.left.blacken(), this.val, this.right.blacken(), RED);
    	return temp;
    }
    
    private RedBlackTree balance() 
    {
    	if(this.isRed())
    	{
    		return this;
    	}
    	
    	if(this.left.isRed())
    	{
    		if(this.right.isRed())
    		{
    			return this.recolored();
    		}
    		if(this.left.left.isRed())
    		{
    			return this.rotateRight().recolored();
    		}
    		if(this.left.right.isRed())
    		{
    			RedBlackTree temp = new RedBlackTree(this.left.rotateLeft(), this.val, this.right, this.color);
    			return temp.rotateRight().recolored();
    		}
    		return this;
    	}
    	
    	if(this.right.isRed())
    	{
    		if(this.right.right.isRed())
    		{
    			return this.rotateLeft().recolored();
    		}
    		if(this.right.left.isRed())
    		{
    			RedBlackTree temp = new RedBlackTree(this.left, this.val, this.right.rotateRight(), this.color);
    			return temp.rotateLeft().recolored();
    		}
    	}
    	
    	return this;
    }
    
    /**
     * method to update the current red black tree
     * inherited by EmptyRedBlackTree
     * @param node
     * @return
     */
    protected RedBlackTree update(RedBlackTree node) 
    {
    	if(this.isEmpty())
    	{
    		return this;
    	}
    	
    	if(node.val < this.val)
    	{
    		RedBlackTree temp = new RedBlackTree(this.left.update(node).balance(), this.val, this.right, this.color);
    		return temp.balance();
    	}
    	
    	RedBlackTree temp = new RedBlackTree(this.left, this.val, this.right.update(node).balance(), this.color);
    	return temp.balance();
    }
    /**
     * Method to insert value to red black tree
     * @param val
     * @return
     */
	protected RedBlackTree insert(int val) 
	{
		RedBlackTree temp = new RedBlackTree(new EmptyRedBlackTree(), val, new EmptyRedBlackTree(), RED);
		return this.update(temp).blacken();
	}
   
}
