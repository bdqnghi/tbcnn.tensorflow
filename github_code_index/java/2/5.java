package net.datastructures;
import java.util.Comparator;

//begin#fragment AVLTree
/**  Implementation of an AVL tree. */
//end#fragment AVLTree
/** 
 * AVLTree class - implements an AVL Tree by extending a binary
 * search tree.
 *
 * @author Michael Goodrich, Roberto Tamassia, Eric Zamore
 */

//begin#fragment AVLTree
public class AVLTree<K,V>
  extends BinarySearchTree<K,V> implements Dictionary<K,V> {
  public AVLTree(Comparator<K> c)  { super(c); }
  public AVLTree() { super(); }
  /** Nested class for the nodes of an AVL tree. */ 
  protected static class AVLNode<K,V> extends BTNode<Entry<K,V>> {
    protected int height;  // we add a height field to a BTNode
    AVLNode() {/* default constructor */}
    /** Preferred constructor */
    AVLNode(Entry<K,V> element, BTPosition<Entry<K,V>> parent,
	    BTPosition<Entry<K,V>> left, BTPosition<Entry<K,V>> right) {
      super(element, parent, left, right);
      height = 0;
      if (left != null) 
        height = Math.max(height, 1 + ((AVLNode<K,V>) left).getHeight());
      if (right != null) 
        height = Math.max(height, 1 + ((AVLNode<K,V>) right).getHeight());
    } // we assume that the parent will revise its height if needed
    public void setHeight(int h) { height = h; }
    public int getHeight() { return height; }
  }
  /** Creates a new binary search tree node (overrides super's version). */
  protected BTPosition<Entry<K,V>> createNode(Entry<K,V> element, 
      BTPosition<Entry<K,V>> parent, BTPosition<Entry<K,V>> left, 
      BTPosition<Entry<K,V>> right) {
    return new AVLNode<K,V>(element,parent,left,right);  // now use AVL nodes
  }
  /** Returns the height of a node (call back to an AVLNode). */
  protected int height(Position<Entry<K,V>> p)  {
    return ((AVLNode<K,V>) p).getHeight();
  }
  /** Sets the height of an internal node (call back to an AVLNode). */
  protected void setHeight(Position<Entry<K,V>> p) { 
    ((AVLNode<K,V>) p).setHeight(1+Math.max(height(left(p)), height(right(p))));
  }
  /** Returns whether a node has balance factor between -1 and 1. */
  protected boolean isBalanced(Position<Entry<K,V>> p)  {
    int bf = height(left(p)) - height(right(p));
    return ((-1 <= bf) &&  (bf <= 1));
  }
//end#fragment AVLTree
//begin#fragment AVLTree2
  /** Returns a child of p with height no smaller than that of the other child */
//end#fragment AVLTree2
  /** 
    * Return a child of p with height no smaller than that of the
    * other child.
    */
//begin#fragment AVLTree2
  protected Position<Entry<K,V>> tallerChild(Position<Entry<K,V>> p)  {
    if (height(left(p)) > height(right(p))) return left(p);
    else if (height(left(p)) < height(right(p))) return right(p);
    // equal height children - break tie using parent's type
    if (isRoot(p)) return left(p);
    if (p == left(parent(p))) return left(p);
    else return right(p);
  }
  /**  
    * Rebalance method called by insert and remove.  Traverses the path from 
    * zPos to the root. For each node encountered, we recompute its height 
    * and perform a trinode restructuring if it's unbalanced.
    */
  protected void rebalance(Position<Entry<K,V>> zPos) {
    if(isInternal(zPos))
       setHeight(zPos);
    while (!isRoot(zPos)) {  // traverse up the tree towards the root
      zPos = parent(zPos);
      setHeight(zPos);
      if (!isBalanced(zPos)) { 
	// perform a trinode restructuring at zPos's tallest grandchild
        Position<Entry<K,V>> xPos =  tallerChild(tallerChild(zPos));
        zPos = restructure(xPos); // tri-node restructure (from parent class)
        setHeight(left(zPos));  // recompute heights
        setHeight(right(zPos));
        setHeight(zPos);
      }
    }
  } 
  // overridden methods of the dictionary ADT
//end#fragment AVLTree2
  /** 
    * Inserts an item into the dictionary and returns the newly created
    * entry. 
    */
//begin#fragment AVLTree2
  public Entry<K,V> insert(K k, V v) throws InvalidKeyException  {
    Entry<K,V> toReturn = super.insert(k, v); // calls our createNode method
    rebalance(actionPos); // rebalance up from the insertion position
    return toReturn;
  }
//end#fragment AVLTree2
  /** Removes and returns an entry from the dictionary. */
//begin#fragment AVLTree2
  public Entry<K,V> remove(Entry<K,V> ent) throws InvalidEntryException {
    Entry<K,V> toReturn = super.remove(ent);
    if (toReturn != null)   // we actually removed something
      rebalance(actionPos);  // rebalance up the tree
    return toReturn;
  }
} // end of AVLTree class
//end#fragment AVLTree2
