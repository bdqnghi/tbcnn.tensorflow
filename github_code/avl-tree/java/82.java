import java.util.function.BiPredicate;

/**
 * TODO: This is your second major task.
 *
 * This class implements a generic height-balanced binary search tree, 
 * using the AVL algorithm. Beyond the constructor, only the insert()
 * method needs to be implemented. All other methods are unchanged.
 */

public class AVLTree<K> extends BinarySearchTree<K> {

  /**
   * Creates an empty AVL tree as a BST organized according to the
   * lessThan predicate.
   */
  public AVLTree(BiPredicate<K, K> lessThan) {
    super(lessThan);
  }

  /**
   * TODO
   * 
   * Inserts the given key into this AVL tree such that the ordering 
   * property for a BST and the balancing property for an AVL tree are
   * maintained.
   */
  
  public Node insert(K key) {
    Node q = super.insert(key);
    if (Math.abs(root.left.height - root.right.height) >= 2){
    	return null;
    }
	return q;
  }
  
 /**
  * left left rotation  
  * @param n
  * @return
  */
  private Node LeftLeft(Node n){
      Node rightchild = root.right;
      root.right = rightchild.left;
      rightchild.left = root;
      root.height = Math.max(root.left.height, root.right.height) + 1;
      rightchild.height = Math.max(rightchild.right.height, rightchild.left.height) + 1;
      return rightchild;
  }
  
  /**
   * right right rotation
   * @param n
   * @return
   */
  private Node RightRight(Node n){
      Node leftchild = root.right;
      root.left = leftchild.right;
      leftchild.right = root;
      root.height = Math.max(root.right.height, root.left.height) + 1;
      leftchild.height = Math.max(leftchild.left.height, leftchild.right.height) + 1;
      return leftchild;
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
}
