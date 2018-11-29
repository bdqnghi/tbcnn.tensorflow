/*

<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      This project has been coded by geekyprincess(aka Ashima)     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      Other Project partners are Divya, Rohit , Manish     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

*/



import java.awt.*; // for drawing
import java.awt.event.*; // for window closing
import java.awt.geom.*; // for Rectangle
import javax.swing.*; // for JFrame

/** 

   java AvlTreeApp xSize ySize num range

   It would then create a xSize x ySize JFrame. The application 
   then generates num many random numbers less than range and
   inserts them into an AVL tree which it then graphically draws.
		
*/

public class AvlTreeApp extends JFrame
{
   /**
      The constructor creates a new AvlTree and insert into it
      numberOfRandoms meany  random numbers less than rangeOfNumbers.

      @param numberOfRandoms - the number of random numbers to generate.
      @param rangeOfRandoms - the max value for the random numbers
   */
   public AvlTreeApp( int numberOfRandoms, int rangeOfRandoms) 
   {
      super("AVL Drawer");	
							
      avlTree = new AvlTree();
      int random;


      for(int i = 0; i < numberOfRandoms; i++)
      {
           random = (int)(Math.random()*rangeOfRandoms);
           avlTree.insert(new Integer(random));
	
      }

   }

   /**
      Called whenever our frame needs to be painted.
      This method clear the screen and gets the size of the
      rectangle that tree must draw into. Then draws the AvlTree.

      @param g - graphics context for frame
   */
   public void paint(Graphics g)
   {
 	Rectangle screenBounds = getContentPane().getBounds();
        screenBounds.y += screenBounds.height/SCALING;
        screenBounds.height -= screenBounds.height/SCALING;
        
        
        g.clearRect(screenBounds.x, screenBounds.y,
                    screenBounds.width, screenBounds.height);

        g.setColor(Color.blue);

        avlTree.drawTree(g, screenBounds);    
   }

   // Main entry point
   public static void main(String[] args) 
   {
      if( args.length < 4 )
      {
         System.err.println("You need four command line arguments:"); 
         System.err.println("sizeX sizeY number_of_randoms randoms_range"); 
         System.exit(1);
      }
		
      AvlTreeApp app = new AvlTreeApp(Integer.parseInt(args[2]),
                                   Integer.parseInt(args[3]));

      app.setSize(Integer.parseInt(args[0]), Integer.parseInt(args[1]));

      app.setBackground(Color.black);
		
      app.addWindowListener( new WindowAdapter() //anonymous inner class
         {
            public void windowClosing( WindowEvent e)
            {
               System.exit(0);
            }
         }
      );	


      app.show();

   }

   AvlTree avlTree;
   static final int SCALING = 8;

} //end AvlTreeApp.java

/**
 made class non-public so everything fits into one file. We have added
  to the class a drawTree method that can be used to draw the
  AvlTree to a Graphics object.
*/

class AvlTree
{
   /**
     Construct the tree.
   */
   public AvlTree( )
   {
      root = null;
   }

   /**
      Insert into the tree; duplicates are ignored.
      @param x the item to insert.
   */
   public void insert( Comparable x )
   {
       root = insert( x, root );
   }

   /**
      Draws the current AvlTree to the graphics context
      within the specified rectangular bounds.

      @param g - the graphics context
      @param bounds - the rectangular bounds.
   */
   public void drawTree(Graphics g, Rectangle bounds)
   {
       int screenHeightOffset = bounds.height/root.height;

       drawTree(g,root,bounds,screenHeightOffset);
   }

   /*
      Draws tree rooted at t to graphics context g within the
      rectangular bounds and with each level of tree offset
      many pixels below previous.
   */
   private void drawTree(Graphics g, AvlNode t, Rectangle bounds, int offset)
   {
       int treeY = bounds.y;
       int fontHeight = g.getFontMetrics().getHeight();
       int subtreeY = treeY + offset;
       int subtreeHeight = bounds.height - offset;
       int subtreeWidth = bounds.width/2;
       int leftTreeX = bounds.x;
       int rightTreeX = leftTreeX + subtreeWidth;
       
       // draw in post-order

       if(t.left != null)  //draw left tree and line from root
       { 
         drawTree(g, t.left, new Rectangle(leftTreeX, subtreeY,
                          subtreeWidth, subtreeHeight), offset);
         g.drawLine(rightTreeX, treeY, 
              leftTreeX + subtreeWidth/2, subtreeY-fontHeight);
       }

       if(t.right != null) //draw right tree and line from root
       {
          drawTree(g, t.right, new Rectangle(rightTreeX, subtreeY,
                          subtreeWidth, subtreeHeight), offset);
          g.drawLine(rightTreeX, treeY, 
              rightTreeX + subtreeWidth/2, subtreeY-fontHeight);
       }

       //draw root
       g.drawString(t.element.toString(), rightTreeX, treeY);   
   }

   private AvlNode insert( Comparable x, AvlNode t )
   {
     if( t == null )
        t = new AvlNode( x, null, null );
     else if( x.compareTo( t.element ) < 0 )
     {
        t.left = insert( x, t.left );
        if( height( t.left ) - height( t.right ) == 2 )
           if( x.compareTo( t.left.element ) < 0 )
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

   /*
    Return the height of node t, or -1, if null.
   */
   private static int height( AvlNode t )
   {
      return t == null ? -1 : t.height;
   }

   /*
     Return maximum of lhs and rhs.
   */
   private static int max( int lhs, int rhs )
   {
      return lhs > rhs ? lhs : rhs;
   }

   /*
     Rotate binary tree node with left child.
     For AVL trees, this is a single rotation for case 1.
     Update heights, then return new root.
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

   /*
     Rotate binary tree node with right child.
     For AVL trees, this is a single rotation for case 4.
     Update heights, then return new root.
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

   /*
     Double rotate binary tree node: first left child
     with its right child; then node k3 with new left child.
     For AVL trees, this is a double rotation for case 2.
     Update heights, then return new root.
   */
   private static AvlNode doubleWithLeftChild( AvlNode k3 )
   {
      k3.left = rotateWithRightChild( k3.left );
      return rotateWithLeftChild( k3 );
   }

   /*
     Double rotate binary tree node: first right child
     with its left child; then node k1 with new right child.
     For AVL trees, this is a double rotation for case 3.
     Update heights, then return new root.
   */
   private static AvlNode doubleWithRightChild( AvlNode k1 )
   {
      k1.right = rotateWithLeftChild( k1.right );
      return rotateWithRightChild( k1 );
   }

   /* The tree root. */
   private AvlNode root;
 
}

/*
  This class encapsulates the nodes for the AvlTree class.
*/
class AvlNode
{
   // Constructors
   AvlNode( Comparable theElement )
   {
      this( theElement, null, null );
   }

   AvlNode( Comparable theElement, AvlNode lt, AvlNode rt )
   {
      element  = theElement;
      left     = lt;
      right    = rt;
      height   = 0;
   }

   // Friendly data; accessible by other package routines
   Comparable element;      // The data in the node
   AvlNode    left;         // Left child
   AvlNode    right;        // Right child
   int        height;       // Height
}
