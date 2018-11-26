import java.math.BigInteger;

/**
 * Red Black Trees
 * A red-black tree is a binary search tree with an extra bit of storage per node.
 * The extra bit represents the color of the node. It's either red or black.
 * Each node contains the fields: color, key, left, right, and p. Any nil
 * pointers are regarded as pointers to external nodes (leaves) and key bearing
 * nodes are considered as internal nodes of the tree.
 *
 * Red-black tree properties:
 * 1. Every node is either red or black.
 * 2. The root is black.
 * 3. Every leaf (nil) is black.
 * 4. If a node is red then both of its children are black.
 * 5. For each node, all paths from the node to descendant leaves contain the
 *    same number of black nodes.

 * From these properties, it can be shown (by an iduction proof) that
 * the tree has a height no more than 2 * Lg(n + 1).

 * In the implementation of the tree, we use a single node to represent all
 * of the external nulls. Its color will always be black. The parent pointer (p)
 * in the root will point to this node and so will all the internal nodes
 * that would normally contain a left or right value of null. In other words,
 * instead of containing a null pointer as a left child or a null pointer as a
 * right child, these internal nodes will point to the one node that represents
 * the external nulls.
 */
public class RedBlackTree {

	private RedBlackNode tree;
	private RedBlackNode nil;
	private int recentCompares;
	private int treeSize;
	private int maxDepth;
	private int depthCount;
	
	/**
	 * This constructor creates an empty RedBlackTree.
	 * It creates a RedBlackNode that represents null.
	 * It sets the internal variable tree to point to this
	 * node. This node that an empty tree points to will be 
	 * used as a sentinel node. That is, all pointers in the 
	 * tree that would normally contain the value null, will instead
	 * point to this sentinel node.
	 * */
	RedBlackTree(){
		nil = new RedBlackNode("nil", BigInteger.valueOf(0), RedBlackNode.BLACK, nil, nil, nil);
		tree = nil;
		recentCompares = 0;
		treeSize = 0;
		maxDepth = 0;
		depthCount = 0;
	}
	
	/**
	 * The insert() method places a data item into the tree.
	 * Parameters:
	 * key - is a string to be inserted.
	 * value - is a BigInteger to be inserted.
	 * Pre-Condition: memory is available for insertion.
	 * Post-Condition: inserts new RedBlackNode object with key-value pair.  If key already exists in RB tree,
	 * will overwrite value with new value (will NOT create a new node).
	 */
	public void insert(String key, BigInteger value){
		if(!this.contains(key)){
			RedBlackNode newNode = new RedBlackNode(key, value, RedBlackNode.BLACK, nil, nil, nil);
			RedBlackNode y = nil;
			RedBlackNode x = tree;
			while (x != nil){
				y = x;
				if(newNode.getKey().compareTo(x.getKey()) < 0){
					x = x.getLc();
				} else {
					x = x.getRc();
				}
			}
			newNode.setP(y);
			if(y == nil){
				this.tree = newNode;
			} else {
				if(newNode.getKey().compareTo(y.getKey()) < 0){
					y.setLc(newNode);
				} else {
					y.setRc(newNode);
				}
			}
			newNode.setLc(nil);
			newNode.setRc(nil);
			newNode.setColor(RedBlackNode.RED);
			this.RBInsertFixup(newNode);
			this.treeSize += 1;
		} else {
			RedBlackNode y = tree;
			while (y.getKey().compareTo(key) != 0){
				if(key.compareTo(y.getKey()) < 0){
					y = y.getLc();
				} else {
					y = y.getRc();
				}
			}
			y.setData(value);
		}
	}

	/**
	 * leftRotate() performs a single left rotation.
	 * Parameters: x is the Node around which the rotation is done.
	 * Pre-Condition: right[x] != nil[T]
 	 * Pre-Condition: root's parent is nill[T]
	 * Post-Condition: updates RedBlackTree object for a full left rotation.
	 */
	public void leftRotate(RedBlackNode x){
		if(x.getRc() != nil && tree.getP() == nil){
			RedBlackNode y;
			y = x.getRc();
			x.setRc(y.getLc());
			y.getLc().setP(x);
			y.setP(x.getP());
			
			if(x.getP() == nil){
				this.tree = y;
			} else {
				if(x == x.getP().getLc()){
					x.getP().setLc(y);
				} else {
					x.getP().setRc(y);
				}
			}
			
			y.setLc(x);
			x.setP(y);
		}
	}	
	
	/**
	 * rightRotate() performs a single right rotation.
	 * Parameters: x is the Node around which the rotation is done.
	 * Pre-Condition: left[x] != nil[T]
	 * Pre-Condition: root's parent is nil[T]
	 * Post-Condition: updates RedBlackTree object for a full right rotation.
	 */
	public void rightRotate(RedBlackNode x){
		if(x.getLc() != nil && tree.getP() == nil){
			RedBlackNode y;
			y = x.getLc();
			x.setLc(y.getRc());
			y.getRc().setP(x);
			y.setP(x.getP());
		
			if(x.getP() == nil){
				this.tree = y;
			} else {
				if(x == x.getP().getLc()){
					x.getP().setLc(y);
				} else {
					x.getP().setRc(y);
				}
			}
		y.setRc(x);
		x.setP(y);
		}
	}
	
	/**
	 * RBInsertFixup() fixes the tree so that Red Black Properties are preserved.
	 * Parameters: 
	 * z - is the new node
	 */
	public void RBInsertFixup(RedBlackNode z){
		RedBlackNode y;
		while(z.getP().getColor() == RedBlackNode.RED){
			if(z.getP() == z.getP().getP().getLc()){
				y = z.getP().getP().getRc();
				if(y.getColor() == RedBlackNode.RED){
					z.getP().setColor(RedBlackNode.BLACK);
					y.setColor(RedBlackNode.BLACK);
					z.getP().getP().setColor(RedBlackNode.RED);
					z = z.getP().getP();
				} else {
					if(z == z.getP().getRc()){
						z = z.getP();
						this.leftRotate(z);
					}
					z.getP().setColor(RedBlackNode.BLACK);
					z.getP().getP().setColor(RedBlackNode.RED);
					this.rightRotate(z.getP().getP());
				}
			} else {
				y = z.getP().getP().getLc();
				if(y.getColor() == RedBlackNode.RED){
					z.getP().setColor(RedBlackNode.BLACK);
					y.setColor(RedBlackNode.BLACK);
					z.getP().getP().setColor(RedBlackNode.RED);
					z = z.getP().getP();
				} else {
					if(z == z.getP().getLc()){
						z = z.getP();
						this.rightRotate(z);
					}
					z.getP().setColor(RedBlackNode.BLACK);
					z.getP().getP().setColor(RedBlackNode.RED);
					this.leftRotate(z.getP().getP());
				}
			}
		}
			tree.setColor(RedBlackNode.BLACK);
	}
	
	/**
	 * InOrderTraversal() performs an in-order traversal of the tree.
	 * The method is recursive and displays the content of the RedBlackNodes within the tree.
	 * It makes calls on System.out.println(). This method would normally be private.
	 * Pre-Condition: assumes nil-terminating, valid RB tree.
	 * Parameters:
	 * t - the root of the tree on the first call.
	 */
	public void inOrderTraversal(RedBlackNode t){
		
		if(t.getLc() != nil){
			this.inOrderTraversal(t.getLc());
		}
		System.out.println(t);
		if(t.getRc() != nil){
			this.inOrderTraversal(t.getRc());
		}
	}

	/**
	 * InOrderTraversal() performs an in-order traversal of the tree.
	 * The method is recursive and displays the content of the RedBlackNodes within the tree.
	 * It makes calls on System.out.println(). This method would normally be private.
	 * Pre-Condition: assumes nil-terminating, valid RB tree.
	 * Parameters:
	 * None - calls the method passing the root of the tree.
	 */
	public void inOrderTraversal(){
		
		this.inOrderTraversal(tree);
	}

	/**
	 * ReverseOrderTraversal() performs a reverse-order traversal of the tree.
	 * The method is recursive and displays the content of the RedBlackNodes within the tree.
	 * It makes calls on System.out.println(). This method would normally be private.
	 * Pre-Condition: assumes nil-terminating, valid RB tree.
	 * Parameters:
	 * t - the root of the tree on the first call.
	 */
	public void reverseOrderTraversal(RedBlackNode t){
		
		if(t.getRc() != nil){
			this.reverseOrderTraversal(t.getRc());
		}
		System.out.println(t);
		if(t.getLc() != nil){
			this.reverseOrderTraversal(t.getLc());
		}
	}

	/**
	 * ReverseOrderTraversal() performs a reverse-order traversal of the tree.
	 * The method is recursive and displays the content of the RedBlackNodes within the tree.
	 * It makes calls on System.out.println(). This method would normally be private.
	 * Pre-Condition: assumes nil-terminating, valid RB tree.
	 * Parameters:
	 * None - calls the method passing the root of the tree.
	 */
	public void reverseOrderTraversal(){
		
		this.reverseOrderTraversal(tree);
	}
	
	/**
	 * height() is a recursive routine that is used to compute the height of the RedBlackTree.
	 * The height() method passes the root of the tree to this method.
	 * Max height: 2 * log(n + 1)
	 * Pre-Condition: assumes nil-terminating, valid RB tree.
	 * Parameters:
	 * t - a pointer to a node in the tree.
	 */
	public int height(RedBlackNode t){
		this.depthCount += 1;
		if(this.depthCount > this.maxDepth){
			this.maxDepth = this.depthCount;
		}
		if(t.getLc() != nil){
			this.height(t.getLc());
		}
		if(t.getRc() != nil){
			this.height(t.getRc());
		}
		this.depthCount -= 1;
		return this.maxDepth;
	}

	/**
	 * height() is a recursive routine that is used to compute the height of the RedBlackTree.
	 * The height() method calls itself with the root node as argument.
	 * Max height: 2 * log(n + 1)
	 * Pre-Condition: assumes nil-terminating, valid RB tree.
	 */
	public int height(){
		return height(tree);
	}
	
	/**
	 * The boolean contains() returns true if the String v is in the RedBlackTree and false otherwise.
	 * It counts each comparison it makes in the variable recentCompares.
	 * Pre-Condition: assumes nil-terminating, valid RB tree.
	*/
	public boolean contains(String v){
		boolean cont = false;
		this.recentCompares = 0;
		
		RedBlackNode y = tree;
		while (y != nil){
			this.recentCompares += 1;
			if(y.getKey().compareTo(v) == 0){
				cont = true;
				break;
			} else if(v.compareTo(y.getKey()) < 0){
				y = y.getLc();
			} else {
				y = y.getRc();
			}
		}
		
		return cont;
	}
	
	/**
	 * The queryNode() function takes a String as input and returns a String value of the BigInteger stored in the RedBlackNode which matches the input.
	 * If no match is found, throws an Exception.
	 * Pre-Condition: assumes nil-terminating, valid RB tree.
	*/
	public String queryNode(String v){
		RedBlackNode y = tree;
		String output = "";
		while (y != nil){
			if(y.getKey().compareTo(v) == 0){
				break;
			} else if(v.compareTo(y.getKey()) < 0){
				y = y.getLc();
			} else {
				y = y.getRc();
			}
		}
		if(y != nil){
			output = y.toString();
		} else {
			try{
			throw new CustomException("Error: " + v + " not a defined value.");
			} catch(CustomException e){
				e.printStackTrace();
				System.exit(0);
			}
		}
		return output;
	}
	
	/**
	 * getSize() Returns number of nodes in RB tree object.
	*/
	public int getSize(){
		return this.treeSize;
	}
	
	/**
	 * getRecentCompares() Returns recentCompares variable for RB tree object.
	 * Pre-Condition: to be run in conjunction with contains() method.
	*/
	public int getRecentCompares(){
		return this.recentCompares;
	}
	
	/**
	 * getRoot() returns root node for RB tree object.
	*/
	public RedBlackNode getRoot(){
		return this.tree;
	}
}
