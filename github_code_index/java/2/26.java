// AvlTree class by Weiss
// McCauley added displayTree method to make trees visually
// recognizable

//Updated by Liz Healy

import java.util.LinkedList;
import java.util.Queue;

//
// CONSTRUCTION: with no initializer
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// boolean contains( x )  --> Return true if x is present
// boolean remove( x )    --> Return true if x was present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as appropriate

/**
 * Implements an AVL tree.
 * Note that all "matching" is based on the compareTo method.
 * @author Mark Allen Weiss
 */
public class AVLTree<AnyType extends Comparable<? super AnyType>>
{
    private static class AvlNode<AnyType>
    {
        // Constructors
        AvlNode( AnyType theElement )
        {
            this( theElement, null, null );
        }
        
        AvlNode( AnyType theElement, AvlNode<AnyType> lt, AvlNode<AnyType> rt )
        {
            element  = theElement;
            left     = lt;
            right    = rt;
            height   = 0;
        }
        
        AnyType           element;      // The data in the node
        AvlNode<AnyType>  left;         // Left child
        AvlNode<AnyType>  right;        // Right child
        int               height;       // Height
    }
    
    /** The tree root. */
    private AvlNode<AnyType> root;

    /**
     * Construct the tree.
     */
    public AVLTree( )
    {
        root = null;
    }

    /**
     * Insert into the tree; duplicates are ignored.
     * @param x the item to insert.
     */
    public void insert( AnyType x )
    {
        root = insert( x, root );
    }

    /**
     * Remove from the tree. Nothing is done if x is not found.
     * @param x the item to remove.
     */
    public void remove( AnyType x )
    {
        root = remove( x, root );
    }

       
    /**
     * Internal method to remove from a subtree.
     * @param x the item to remove.
     * @param t the node that roots the subtree.
     * @return the new root of the subtree.
     */
    private AvlNode<AnyType> remove( AnyType x, AvlNode<AnyType> t )
    {
        if( t == null )
            return t;   // Item not found; do nothing
            
        int compareResult = x.compareTo( t.element );
            
        if( compareResult < 0 )
            t.left = remove( x, t.left );
        else if( compareResult > 0 )
            t.right = remove( x, t.right );
        else if( t.left != null && t.right != null ) // Two children
        {
            t.element = findMin( t.right ).element;
            t.right = remove( t.element, t.right );
        }
        else
            t = ( t.left != null ) ? t.left : t.right;
        return balance( t );
    }
    
    /**
     * Find the smallest item in the tree.
     * @return smallest item or null if empty.
     */
    public AnyType findMin( )
    {
        if( isEmpty( ) )
            throw new UnderflowException( );
        return findMin( root ).element;
    }

    /**
     * Find the largest item in the tree.
     * @return the largest item of null if empty.
     */
    public AnyType findMax( )
    {
        if( isEmpty( ) )
            throw new UnderflowException( );
        return findMax( root ).element;
    }

    /**
     * Find an item in the tree.
     * @param x the item to search for.
     * @return true if x is found.
     */
    public boolean contains( AnyType x )
    {
        return contains( x, root );
    }

    /**
     * Make the tree logically empty.
     */
    public void makeEmpty( )
    {
        root = null;
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

    private static final int ALLOWED_IMBALANCE = 1;
    
    // Assume t is either balanced or within one of being balanced
    private AvlNode<AnyType> balance( AvlNode<AnyType> t )
    {
        if( t == null )
            return t;
        
        if( height( t.left ) - height( t.right ) > ALLOWED_IMBALANCE )
            if( height( t.left.left ) >= height( t.left.right ) )
                t = rotateWithLeftChild( t );
            else
                t = doubleWithLeftChild( t );
        else
        if( height( t.right ) - height( t.left ) > ALLOWED_IMBALANCE )
            if( height( t.right.right ) >= height( t.right.left ) )
                t = rotateWithRightChild( t );
            else
                t = doubleWithRightChild( t );

        t.height = Math.max( height( t.left ), height( t.right ) ) + 1;
        return t;
    }
    
    public void checkBalance( )
    {
        checkBalance( root );
    }
    
    private int checkBalance( AvlNode<AnyType> t )
    {
        if( t == null )
            return -1;
        
        if( t != null )
        {
            int hl = checkBalance( t.left );
            int hr = checkBalance( t.right );
            if( Math.abs( height( t.left ) - height( t.right ) ) > 1 ||
                    height( t.left ) != hl || height( t.right ) != hr )
                System.out.println( "OOPS!!" );
        }
        
        return height( t );
    }
    
    
    /**
     * Internal method to insert into a subtree.
     * @param x the item to insert.
     * @param t the node that roots the subtree.
     * @return the new root of the subtree.
     */
    private AvlNode<AnyType> insert( AnyType x, AvlNode<AnyType> t )
    {
        if( t == null )
            return new AvlNode<>( x, null, null );
        
        int compareResult = x.compareTo( t.element );
        
        if( compareResult < 0 )
            t.left = insert( x, t.left );
        else if( compareResult > 0 )
            t.right = insert( x, t.right );
        else
            ;  // Duplicate; do nothing
        return balance( t );
    }

    /**
     * Internal method to find the smallest item in a subtree.
     * @param t the node that roots the tree.
     * @return node containing the smallest item.
     */
    private AvlNode<AnyType> findMin( AvlNode<AnyType> t )
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
    private AvlNode<AnyType> findMax( AvlNode<AnyType> t )
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
     * @return true if x is found in subtree.
     */
    private boolean contains( AnyType x, AvlNode<AnyType> t )
    {
        while( t != null )
        {
            int compareResult = x.compareTo( t.element );
            
            if( compareResult < 0 )
                t = t.left;
            else if( compareResult > 0 )
                t = t.right;
            else
                return true;    // Match
        }

        return false;   // No match
    }

    /**
     * Internal method to print a subtree in sorted order.
     * @param t the node that roots the tree.
     */
    private void printTree( AvlNode<AnyType> t )
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
    private int height( AvlNode<AnyType> t )
    {
        return t == null ? -1 : t.height;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then return new root.
     */
    private AvlNode<AnyType> rotateWithLeftChild( AvlNode<AnyType> k2 )
    {
        AvlNode<AnyType> k1 = k2.left;
        k2.left = k1.right;
        k1.right = k2;
        k2.height = Math.max( height( k2.left ), height( k2.right ) ) + 1;
        k1.height = Math.max( height( k1.left ), k2.height ) + 1;
        return k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then return new root.
     */
    private AvlNode<AnyType> rotateWithRightChild( AvlNode<AnyType> k1 )
    {
        AvlNode<AnyType> k2 = k1.right;
        k1.right = k2.left;
        k2.left = k1;
        k1.height = Math.max( height( k1.left ), height( k1.right ) ) + 1;
        k2.height = Math.max( height( k2.left ), k1.height ) + 1;
        return k2;
    }

    /**
     * Double rotate binary tree node: first left child
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then return new root.
     */
    private AvlNode<AnyType> doubleWithLeftChild( AvlNode<AnyType> k3 )
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
    private AvlNode<AnyType> doubleWithRightChild( AvlNode<AnyType> k1 )
    {
        k1.right = rotateWithLeftChild( k1.right );
        return rotateWithRightChild( k1 );
    }

    /**
     * Double rotate binary tree node k1 without calling other
     * rotation methods. 
     * Update heights, then return new root.
     *//* COMMENTED OUT TO prevent name-class with other version
    private AvlNode<AnyType> doubleWithRightChild( AvlNode<AnyType> k1 )
    {
        AvlNode<AnyType> k1;
        AvlNode<AnyType> k2;
        k1 = k2.left;
        k2.left = k1.right;
        k1.right = k2;
        k2.height = Math.max( height( k2.left ), height( k2.right ) ) + 1;
        k1.height = Math.max( height( k1.left ), k2.height ) + 1;
        k1 = k1.right;
    
        k2 = k1.right;
        k1.right = k2.left;
        k2.left = k1;
        k1.height = Math.max( height( k1.left ), height( k1.right ) ) + 1;
        k2.height = Math.max( height( k2.left ), k1.height ) + 1;
        return k2;
    
        
    }
    */
    
  /**
   * Output all nodes, level by level
   * 
   */ 
  public void displayTree()
  {
      System.out.println("The tree contains:");
      displayLevel(root);
  }
  
  /** 
   * Output all nodes, level by level
   * @ param node - the node that roots the current subtree
   */
  private void displayLevel(AvlNode node) {
      if (node == null) {
         System.out.print(" - ");
      }
      else {
        //Queue that holds the nodes on the current level
        Queue<AvlNode> thisLevel = new LinkedList<AvlNode>();
        //Queue that holds the nodes on the next level
        Queue<AvlNode> nextLevel = new LinkedList<AvlNode>(); 
        //put the root on the current level's queue
        thisLevel.add(node);
        int h = height(root);
        int levelTotal = 0;  //keeps track of the total levels printed so we don't  pass the height and print a billion "null"s
        while(!thisLevel.isEmpty()&& (levelTotal<= h))
        {

            while (!thisLevel.isEmpty()) // print nodes at current level
            {
               if (thisLevel.peek() != null)
               {
                  System.out.print(thisLevel.peek().element + " ");
                  // if there is a left pointer , put on next level; if none, put a null
                  node = thisLevel.peek().left; // look at the left pointer of node
                  nextLevel.add(node); 
                  node = thisLevel.remove().right; // get right pointer and remove node
                  nextLevel.add(node); 
               }
               else
               {
                  System.out.print(" - ");
                  nextLevel.add(null); 
                  nextLevel.add(null);
                  thisLevel.remove();
               }
            }  // end while (!thisLevel.isEmpty())
            // Moving to the next level, copy nodes to thisLevel so we know to 
            // advance level count and line in output
            while (!nextLevel.isEmpty())
            {
                  thisLevel.add(nextLevel.remove());
            } // end while (!nextLevel.isEmpty()
            System.out.println(); 
            levelTotal++;
        } // end while(!thisLevel.isEmpty()&& (levelTotal<= h))
      System.out.println(); // an extra line feed to separate this printout of from next
    }
    System.out.println("------ End of tree -------\n");
  }

        // Test program
    public static void main( String [ ] args )
    {
        AVLTree<Integer> avl1 = new AVLTree<>();
        avl1.displayTree();
        System.out.println("Inserting 100");
        avl1.insert(100);
        avl1.displayTree();
        System.out.println("Inserting 90");
        avl1.insert(90); 
        avl1.displayTree();
        System.out.println("Inserting 80");
        System.out.println("Inserting into left subtree of left child of 100, makes");
        System.out.println("tree unbalanced at 100 and causes a single left rotation.");
        System.out.println("That is, 100 is rotated with its left child, 90.\n");
        avl1.insert(80);
        avl1.displayTree();
        System.out.println("Inserting 70");

        avl1.insert(70);
        avl1.displayTree();
        System.out.println("Inserting 60");
        System.out.println("Inserting into left subtree of left child of 80, makes tree unbalanced");
        System.out.println("at 80 and causes a single left rotation.");
        System.out.println("That is, 80 is rotated with its left child, 70.\n");
        avl1.insert(60);
        avl1.displayTree();
        System.out.println("Inserting 50");
        System.out.println("Inserting into left subtree of left child of 90, makes tree unbalanced");
        System.out.println("at 90 and causes a single left rotation.");
        System.out.println("That is, 90 is rotated with its left child, 70.\n"); 
        avl1.insert(50);
        avl1.displayTree();
        System.out.println("Deleting 80");
        avl1.remove(80);
        avl1.displayTree();
        System.out.println("Deleting 100");
        avl1.remove(100);
        avl1.displayTree();
        avl1.insert(65);
        avl1.displayTree();
        //After adding rotateWithRightChild, uncomment this
        //requires a doubleWithLeftRotation that uses rotateWithRightChild
        System.out.println("Adding 67 cause the tree to be unbalanced.");
        System.out.println("A single right rotation was performed.");
        System.out.println("This causes 70 to be rotated with it's right child, 65.\n");
        avl1.insert(67);
        avl1.displayTree();
        
        
        /* Add more tests for
        -- single right rotation
        -- doubleWithRightRotation
        */
        avl1.insert(45);
        avl1.displayTree();
        
        avl1.insert(40);
        avl1.displayTree();
        
        System.out.println("Adding 35 cause the tree to be unbalanced.");
        System.out.println("A single left rotation was performed.");
        System.out.println("This causes 45 to be rotated with it's left child, 40.\n");
        avl1.insert(35);
        avl1.displayTree();
        
        System.out.println("Deleting 35");
        avl1.remove(35);
        avl1.displayTree();
        
        System.out.println("Deleting 40");
        avl1.remove(40);
        avl1.displayTree();
        
        System.out.println("Deleting 45");
        avl1.remove(45);
        avl1.displayTree();
        
        avl1.insert(100);
        avl1.displayTree();
        
        System.out.println("Adding 105 cause the tree to be unbalanced.");
        System.out.println("A single right rotation was performed.");
        System.out.println("This causes 90 to be rotated with it's right child, 100.\n");
        avl1.insert(105);
        avl1.displayTree();
        
        System.out.println("Adding 110 cause the tree to be unbalnaced.");
        System.out.println("A single right rotation was performed.");
        System.out.println("This causes 70 to be rotated with it's right child, 100.\n");
        avl1.insert(110);
        avl1.displayTree();
        
        System.out.println("Adding 115 cause the tree to be unbalnaced.");
        System.out.println("A single right rotation was performed.");
        System.out.println("This causes 105 to be rotated with it's right child, 110.\n");
        avl1.insert(115);
        avl1.displayTree();
        
        System.out.println("Adding 119 cause the tree to be unbalnaced.");
        System.out.println("A double rotation was performed.");
        System.out.println("This causes 65 to be rotated with it's right child, 100. Making 100 the new node. \n");
        avl1.insert(119);
        avl1.displayTree();
   
   
   
    }
}
