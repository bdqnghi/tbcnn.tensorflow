package collections.intervalTree;


/**
 * Class to represent a node of a IntervalTree.
 * IntervalNode objects are used internally by IntervalTree, end-user shouldn't 
 * need to create an instace of IntervalNode.
 * 
 * @author Javier Iserte / Based on c# code of Interval-Tree from vvondra in
 *         github.
 *
 * @param <T>
 *          A comparable type.
 * @see <a href="https://github.com/vvondra/Interval-Tree">https://github.com/
 *      vvondra/Interval-Tree </a>
 */
public class IntervalNode<T extends Comparable<T>>
    implements Comparable<IntervalNode<T>> {

  // ------------------------------------------------------------------------ //
  // Instance variables
  /**
   * Left branch/child of the current node. Is null if node does not have a
   * left child. 
   */
  public IntervalNode<T> left;
  /**
   * Right branch/child of the current node. Is null if node does not have a
   * right child. 
   */
  public IntervalNode<T> right;
  /**
   * Parent of the current node. Null if node is root.
   */
  public IntervalNode<T> parent;
  /**
   * The max end value of all intervals in childs and itself.
   */
  public T maxEnd;
  /**
   * The interval stored in the node.
   */
  public Interval<T> interval;
  /**
   * Node color, required for red-black-tree implementation.
   */
  public NodeColor color;
  // ------------------------------------------------------------------------ //

  // ------------------------------------------------------------------------ //
  // Constructors
  /**
   * Creates a new Empty IntervalNode
   */
  public IntervalNode() {
    this.parent = null;
    this.left = null;
    this.right = null;
    this.color = NodeColor.Black;
  }

  /**
   * Creates a new IntervalNode with the interval value.
   */
  public IntervalNode(Interval<T> interval) {
    this.parent = null;
    this.left = null;
    this.right = null;
    this.color = NodeColor.Black;
    this.maxEnd = interval.end;
    this.interval = interval;
  }
  // ------------------------------------------------------------------------ //

  // ------------------------------------------------------------------------ //
  // Public Interaface
  /**
   * Get the color of the Node, required for red-black-tree implementation.
   * @return a NodeColor enumeraion value for the current node.
   */
  public NodeColor getColor() {
    return this.color;
  }
  /**
   * Set the color of the Node, required for red-black-tree implementation.
   */
  public void setColor(NodeColor color) {
    this.color = color;
  }

  /**
   * Check if this node is root.
   * @return true if this node has no parents.
   */
  public boolean isRoot() {
    return this.parent == null;
  }

  /**
   * Check if this node is a terminal node.
   * @return true if this node has no childs.
   */
  public boolean isLeaf() {
    return this.right == null && this.left == null;
  }

  /**
   * Looks for the direction where the parent node is ,from the node point of 
   * view. If node is left child of parent, then parent if the the right of the
   * node.
   * @return NodeDirection enumeration value with the direction of the father.
   */
  public NodeDirection parentDirection() {
    if (this.parent == null) {
      return NodeDirection.None;
    }
    return this.parent.left == this ? NodeDirection.Right : NodeDirection.Left;
  }

  /**
   * Retrieves the most left node of the right child. 
   * @return
   */
  public IntervalNode<T> getSuccessor() {
    if (this.right == null) {
      return null;
    }

    IntervalNode<T> node = this.right;
    while (node.left != null) {
      node = node.left;
    }

    return node;
  }

  @Override
  /**
   * Compare an IntervalNode with another by the interval they store.
   */
  public int compareTo(IntervalNode<T> o) {
    return this.interval.compareTo(o.interval);
  }

  public void recalculateMaxEnd() {

    T max = this.interval.end;

    if (this.right != null) {
      if (this.right.maxEnd.compareTo(max) > 0) {
        max = this.right.maxEnd;
      }
    }

    if (this.left != null) {
      if (this.left.maxEnd.compareTo(max) > 0) {
        max = this.left.maxEnd;
      }
    }

    this.maxEnd = max;

    if (this.parent != null) {
      this.parent.recalculateMaxEnd();
    }
  }

  public IntervalNode<T> grandParent() {
    if (this.parent != null) {
      return this.parent.parent;
    }
    return null;
  }

  public IntervalNode<T> uncle() {
    IntervalNode<T> gparent = this.grandParent();
    if (gparent == null) {
      return null;
    }
    if (this.parent == gparent.left) {
      return gparent.right;
    }

    return gparent.left;
  }

  public IntervalNode<T> sibling() {
    if (this.parent != null) {
      if (this.parent.right == this) {
        return this.parent.left;
      }
      return this.parent.right;
    }
    return null;
  }

  public int size() {
    int leftSize = 0;
    int rightSize = 0;
    if (this.left != null) {
      leftSize = this.left.size();
    }
    if (this.right != null) {
      rightSize = this.right.size();
    }
    return 1 + leftSize + rightSize;

  }
  
  /** 
   * Get the left most node of the current node.
   * @return
   */
  public IntervalNode<T> leftMost() {
    if ( this.left == null) {
      return this;
    } else {
      return this.left.leftMost();
    }
  }
  // ------------------------------------------------------------------------ //



}
