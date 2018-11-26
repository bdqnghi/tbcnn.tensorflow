package aud;

/** Simple implementation of an AVL tree.<p>
    
    This implementation is based on {@link BinarySearchTree} and in
    particular {@link BinarySearchTree#restructure} for rebalancing.

    This implementation <b>does not</b> implement removal of nodes!
    {@link #remove} always throws {@code
    UnsupportedOperationException}!

    @see aud.example.AVLTreeExample
 */
public class AVLTree<Key extends Comparable<Key>,Value> 
  extends BinarySearchTree<Key,Value> {
  
  /** Node in an {@link AVLTree}.<p>

      The node stores the height of its subtree for balancing.  Note
      that it is sufficient to store the balance (in only 2
      bits). Referring to height instead of balance simplifies this
      implementation.
   */
  protected class AVLNode extends BinarySearchTree<Key,Value>.Node {
    AVLNode(AVLTree<Key,Value> tree,Key key,Value value) { 
      super(tree,key,value);
      tree_=tree;
      height_=1;
    }
    
    /** compute height of subtree recursively (for testing only) */
    public int computeHeight() {
      int hl=getLeft() !=null ? ((AVLNode) getLeft()) .computeHeight() : 0;
      int hr=getRight()!=null ? ((AVLNode) getRight()).computeHeight() : 0;
      return 1+(hl>hr ? hl : hr);
    }
        
    int height_;

    /** get height of subtree
        @return height >=1 or 0 for {@code node==null}
     */
    public int getHeight(AVLNode node) { return node==null ? 0 : node.height_; }
    
    /** update height from children */
    void updateHeight() {
      int hl=getHeight((AVLNode) getLeft());
      int hr=getHeight((AVLNode) getRight());
      height_=1+(hl>hr ? hl : hr);
    }

    /** get height difference between left and right subtree */
    public int getBalance() {
      return getHeight((AVLNode) getLeft())-getHeight((AVLNode) getRight());
    }
    /** {@code |getBalance()|<=1} ? */
    public boolean isBalanced() {
      int b=getBalance();
      return -1<=b && b <=+1;
    }

    @Override protected String textLabel() { 
      return getData().toString()+" ("+height_+")"; 
    }
  }
  
  /** override: create new AVLNode */
  @Override protected Node createNode(Key key,Value value) {
    return new AVLNode(this,key,value);
  }
  
  /** create empty tree */
  public AVLTree() {
    super();
  }
  
  /** get height of tree */
  public int getHeight() { return ((AVLNode) head_).height_-1; }

  @Override protected void onInsert(Node _node) {
    AVLNode node=(AVLNode) _node;
    AVLNode parent=(AVLNode) node.getParent();

    parent.updateHeight(); // update immediate parent
    
    if (parent!=head_)     // rebalcing requires to check grand parent
      rebalance(node,parent,(AVLNode) parent.getParent());
  }

  protected void rebalance(AVLNode x,AVLNode y,AVLNode z) {
    assert(x!=null && x!=head_);
    assert(y!=null);
    assert(x.isBalanced());
    assert(y==head_ || y.isBalanced());
    
    if (z==null) {
      assert(y==head_);                       // nothing to do
      return;
    }
    
    z.updateHeight();

    if (z!=head_) {
      if (!z.isBalanced()) { 

        AVLNode b=(AVLNode) restructure(x);   // new root
        AVLNode a=(AVLNode) b.getLeft();
        AVLNode c=(AVLNode) b.getRight();

        a.updateHeight();
        c.updateHeight();

        b.updateHeight();

        assert(b.isBalanced());
        assert(a.isBalanced());
        assert(c.isBalanced());

        y=b;
        z=(AVLNode) b.getParent();            // prepare for traversal (below)
                                              // note: z may equal head_ now!
      }

      rebalance(y,z,(AVLNode) z.getParent()); // traverse to root
      
    } else  {
      z.updateHeight();                       // z==head_
    } 
  }
  
  /** <b>not implemented!</b> 
      @throws UnsupportedOperationException <b>always!</b>
   */
  @Override public Value remove(Key key) {
    throw new UnsupportedOperationException("AVLTree#remove");
  }

  
  /** additionally check heights and balancing */
  @Override protected void checkConsistency(Node node) {
    super.checkConsistency(node);
    
    AVLNode anode=(AVLNode) node;
    assert(anode.height_==anode.computeHeight());
    assert(anode.isBalanced());

    if (anode.height_!=anode.computeHeight())
      throw new RuntimeException("imvalid height for node '"+anode+"': "+
            anode.height_+"!="+anode.computeHeight());
    if (!anode.isBalanced())
      throw new RuntimeException("unbalanced node '"+anode+"': balance="
            +anode.getBalance());
  }
  
  /** example and test */
  public static void main(String[] args) {
    
    AVLTree<String,Object> tree=new AVLTree<String,Object> ();
    System.out.println(tree);
    
    String[] keys={"c","b","a"};

    for (String key : keys) {
      System.out.println("insert '"+key+"'");
      tree.insert(key,null);
      System.out.println(tree); 
      System.out.println(tree.toText()); 
      tree.checkConsistency();
    }      
  }
}