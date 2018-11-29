package cmsc420.meeshquest.part1;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

// BinarySearchTree class
//
// CONSTRUCTION: with no initializer
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// Comparable find( x )   --> Return item that matches x
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order

/**
 * Implements an AVL tree.
 * Note that all "matching" is based on the compareTo method.
 * @author Mark Allen Weiss
 */
public class AvlTree
{
    int cardinality;

    public int getHeight() {return getHeight(root);}
    
    private int getHeight(AvlNode n) {
    	if (n == null) return 0;
    	
    	return 1+ Math.max(height(root.left), height(root.right));
    }
    
	class AvlNode
	 {    
	     AvlNode left, right;
	     City element;
	     int height;
	 
	     /* Constructor */
	     public AvlNode()
	     {
	         left = null;
	         right = null;
	         element = null;
	         height = 0;
	     }
	     /* Constructor */
	     public AvlNode(City n)
	     {
	         left = null;
	         right = null;
	         element = n;
	         height = 0;
	     }     
	     
	     public AvlNode(City n, AvlNode l, AvlNode r) {
	    	 this.element = n;
	    	 this.left = l;
	    	 this.right = r;
	     }
	 }
	
    /**
     * Construct the tree.
     */
    public AvlTree( )
    {
        root = null;
        cardinality = 0;
    }

    /**
     * Insert into the tree; duplicates are ignored.
     * @param x the item to insert.
     */
    public void insert(City x )
    {
        root = insert( x, root );
    }

    /**
     * Remove from the tree. Nothing is done if x is not found.
     * @param x the item to remove.
     */
    public void remove(City x )
    {
        System.out.println( "Sorry, remove unimplemented" );
    }

    /**
     * Find the smallest item in the tree.
     * @return smallest item or null if empty.
     */
    public City findMin( )
    {
        return elementAt( findMin( root ) );
    }

    /**
     * Find the largest item in the tree.
     * @return the largest item of null if empty.
     */
    public City findMax( )
    {
        return elementAt( findMax( root ) );
    }

    /**
     * Find an item in the tree.
     * @param x the item to search for.
     * @return the matching item or null if not found.
     */
    public City find( City x )
    {
        return elementAt( find( x, root ) );
    }

    /**
     * Make the tree logically empty.
     */
    public void makeEmpty( )
    {
        root = null;
        cardinality = 0;
    }

    /**
     * Test if the tree is logically empty.
     * @return true if empty, false otherwise.
     */
    public boolean isEmpty( )
    {
        return root == null;
    }

    /**
     * Print the tree contents in sorted order.
     */
    public void printTree( )
    {
        if( isEmpty( ) )
            System.out.println( "Empty tree" );
        else
            printTree( root );
    }

    /**
     * Internal method to get element field.
     * @param t the node.
     * @return the element field or null if t is null.
     */
    private City elementAt( AvlNode t )
    {
        return t == null ? null : t.element;
    }

    /**
     * Internal method to insert into a subtree.
     * @param x the item to insert.
     * @param t the node that roots the tree.
     * @return the new root.
     */
    private AvlNode insert( City x, AvlNode t )
    {
        if( t == null ) {
            t = new AvlNode( x, null, null );
            cardinality++;
        }else if( x.compareTo(t.element ) < 0 )
        {
            t.left = insert( x, t.left );
            if( height( t.left ) - height( t.right ) == 2 )
                if(x.compareTo(t.left.element) < 0 )
                    t = rotateWithLeftChild( t );
                else
                    t = doubleWithLeftChild( t );
        }
        else if( x.compareTo( t.element ) > 0 )
        {
            t.right = insert( x, t.right );
            if( height( t.right ) - height( t.left ) == 2 )
                if( x.compareTo( t.right.element ) > 0 )
                    t = rotateWithRightChild( t );
                else
                    t = doubleWithRightChild( t );
        }
        else
            ;  // Duplicate; do nothing
        t.height = max( height( t.left ), height( t.right ) ) + 1;
        return t;
    }

    /**
     * Internal method to find the smallest item in a subtree.
     * @param t the node that roots the tree.
     * @return node containing the smallest item.
     */
    private AvlNode findMin( AvlNode t )
    {
        if( t == null )
            return t;

        while( t.left != null )
            t = t.left;
        return t;
    }

    /**
     * Internal method to find the largest item in a subtree.
     * @param t the node that roots the tree.
     * @return node containing the largest item.
     */
    private AvlNode findMax( AvlNode t )
    {
        if( t == null )
            return t;

        while( t.right != null )
            t = t.right;
        return t;
    }

    /**
     * Internal method to find an item in a subtree.
     * @param x is item to search for.
     * @param t the node that roots the tree.
     * @return node containing the matched item.
     */
    private AvlNode find( City x, AvlNode t )
    {
        while( t != null )
            if( x.compareTo(t.element ) < 0 )
                t = t.left;
            else if(x.compareTo(t.element ) > 0 )
                t = t.right;
            else
                return t;    // Match

        return null;   // No match
    }

    /**
     * Internal method to print a subtree in sorted order.
     * @param t the node that roots the tree.
     */
    private void printTree( AvlNode t )
    {
        if( t != null )
        {
            printTree( t.left );
            System.out.println( t.element );
            printTree( t.right );
        }
    }

    /**
     * Return the height of node t, or -1, if null.
     */
    private static int height( AvlNode t )
    {
        return t == null ? -1 : t.height;
    }

    /**
     * Return maximum of lhs and rhs.
     */
    private static int max( int lhs, int rhs )
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then return new root.
     */
    private static AvlNode rotateWithLeftChild( AvlNode k2 )
    {
        AvlNode k1 = k2.left;
        k2.left = k1.right;
        k1.right = k2;
        k2.height = max( height( k2.left ), height( k2.right ) ) + 1;
        k1.height = max( height( k1.left ), k2.height ) + 1;
        return k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then return new root.
     */
    private static AvlNode rotateWithRightChild( AvlNode k1 )
    {
        AvlNode k2 = k1.right;
        k1.right = k2.left;
        k2.left = k1;
        k1.height = max( height( k1.left ), height( k1.right ) ) + 1;
        k2.height = max( height( k2.right ), k1.height ) + 1;
        return k2;
    }

    /**
     * Double rotate binary tree node: first left child
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then return new root.
     */
    private static AvlNode doubleWithLeftChild( AvlNode k3 )
    {
        k3.left = rotateWithRightChild( k3.left );
        return rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then return new root.
     */
    private static AvlNode doubleWithRightChild( AvlNode k1 )
    {
        k1.right = rotateWithLeftChild( k1.right );
        return rotateWithRightChild( k1 );
    }

      /** The tree root. */
    private AvlNode root;

    public Element printAvlGTree(Document d, Element e) {
    	return printAvlGTree(root, d, e);
    }
    
    private static Element printAvlGTree(AvlNode a, Document res, Element e) {
		if (a == null) {
			Element empty = res.createElement("emptyChild");
			return empty;
		} else {
			Element node = res.createElement("node");
			node.setAttribute("name", a.element.name);
			node.setAttribute("radius", a.element.radius+"");
			node.appendChild(printAvlGTree(a.left, res, node));
			node.appendChild(printAvlGTree(a.right, res, node));
			return node;
		}
	}

        // Test program
    public static void main( String [ ] args )
    {
    	
    }
}
