import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Collection;
import java.util.List;
import java.util.NoSuchElementException;

/**
 * Implementation of an AVL Tree.
 *
 * @author Mikayla Crawford
 * @version 1.0
 */
public class AVL<T extends Comparable<? super T>> implements AVLInterface<T> {
    private AVLNode<T> root;
    private int size;

    /**
     * A no argument constructor that should initialize an empty AVL tree.
     */
    public AVL() {
    }

    /**
     * Initializes the AVL tree with the data in the Collection. The data
     * should be added in the same order it is in the Collection.
     *
     * @param data the data to add to the tree
     * @throws IllegalArgumentException if data or any element in data is null
     */
    public AVL(Collection<T> data) {
        if (data == null) {
            throw new IllegalArgumentException(
                    "init error: Collection is null");
        }
        for (T entry : data) {
            if (entry == null) {
                throw new IllegalArgumentException(
                        "init error: data in collection is null");
            }
            add(entry);
        }
    }

    /**
     * Add the data as a leaf to the AVL. Should traverse the tree to find the
     * appropriate location. If the data is already in the tree, then nothing
     * should be done (the duplicate shouldn't get added, and size should not be
     * incremented).
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @param data the data to be added
     */
    public void add(T data) {
      if (data == null) throw new IllegalArgumentException("Cannot add null data to AVL tree.");

      root = addNode(root, data);
    }

    /**
     * Recursive helper method for adding a node to the AVL tree.
     *
     * @param parent the node to start searching from
     * @param data the data to add
     * @return the current node in the stack
     */
    private AVLNode<T> addNode(AVLNode<T> parent, T data)  {
      if (parent == null) { //Base case: insert node
        parent = new AVLNode<T>(data); //New node
        parent.setHeight(0); //Set height to 0
        parent.setBalanceFactor(0); //Set BF to 0
        size++;
      } else if (data.compareTo(parent.getData()) < 0) { //Recursive case: left subtree
        parent.setLeft(addNode(parent.getLeft(), data));
        updateNodeValues(parent); //Update parent's values

        //Rebalance
        if (parent.getBalanceFactor() > 1) {
          if (data.compareTo(parent.getLeft().getData()) < 0) { //Left-left tree (single rotation LL)
            parent = rotateRight(parent);
          } else { //Left-right tree (double rotation LR)
            parent.setLeft(rotateLeft(parent.getLeft()));
            parent = rotateRight(parent);
          }
        }
      } else if (data.compareTo(parent.getData()) > 0) { //Recursive case: right subtree
        parent.setRight(addNode(parent.getRight(), data)); //Update parent's values
        updateNodeValues(parent);

        //Rebalance
        if (parent.getBalanceFactor() < -1) {
          if (data.compareTo(parent.getRight().getData()) > 0) { //Right-right tree (single rotation RR)
            parent = rotateLeft(parent);
          } else { //Right-left tree (double RL)
            parent.setRight(rotateRight(parent.getRight()));
            parent = rotateLeft(parent);
          }
        }

      } //Base case: duplicate, do not add

      return parent;
    }

    /**
     * Helper method for rebalancing tree. Handles case for rotating right around a left node.
     *
     *       A (parent)       B  (returned)
     *      / \             /   \
     *     B  T1     =>    C     A
     *    / \                   / \
     *   C  T2                T2  T1
     *
     * @param parent the parent of the node to rotate
     * @return the new parent of the subtree
     */
    private AVLNode<T> rotateRight(AVLNode<T> parent) {
      AVLNode<T> left = parent.getLeft(); //Left child
      AVLNode<T> leftRight = left.getRight(); //Left's right child

      parent.setLeft(leftRight); //Updates parent's left child to left's right
      left.setRight(parent); //Updates left's right to parent

      updateNodeValues(parent);
      updateNodeValues(left);

      return left;
    }


    /**
     * Helper method for rebalancing tree. Handles case for rotating left around right node.
     *
     *      A (parent)        B (returned)
     *    /  \               / \
     *   T1   B      =>     A   C
     *       / \          /  \
     *     T2   C        T1  T2
     *
     * @param parent the parent of the node to rotate
     * @return the new parent of the subtree
     */
    private AVLNode<T> rotateLeft(AVLNode<T> parent) {
      AVLNode<T> right = parent.getRight(); //Right child
      AVLNode<T> rightsLeft = right.getLeft(); //Right's left child

      parent.setRight(rightsLeft); //Updates parent's right child to right's Left
      right.setLeft(parent); //Updates right's left to parent

      updateNodeValues(parent);
      updateNodeValues(right);

      return right;
    }

    /**
      * This method updates the height and balance factor of the specified node.
      *
      * @param node the node to update
      */
    private void updateNodeValues(AVLNode<T> node) {
      AVLNode<T> left = node.getLeft();
      AVLNode<T> right = node.getRight();

      if (left != null && right != null) { //Both children
        node.setHeight(Math.max(left.getHeight(), right.getHeight()) + 1);
        node.setBalanceFactor(left.getHeight() - right.getHeight());
      } else if (left == null && right != null) { //Right only
        node.setHeight(right.getHeight() + 1);
        node.setBalanceFactor(-1 - right.getHeight());
      } else if (left != null && right == null) { //Left only
        node.setHeight(left.getHeight() + 1);
        node.setBalanceFactor(left.getHeight() + 1);
      } else { //Leaf node
        node.setHeight(0);
        node.setBalanceFactor(0);
      }
    }

    /**
     * Removes the data from the tree. If the node has two children, it is
     * replaced with its predecessor.
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @throws java.util.NoSuchElementException if the data is not in the tree
     * @param data data to remove from the tree
     * @return the data removed from the tree.  Do not return the same data
     * that was passed in.  Return the data that was stored in the tree.
     */
    public T remove(T data) {
      if (data == null) throw new IllegalArgumentException("Cannot remove null data from AVL tree.");

      List<AVLNode<T>> foundData = remove(root, data);

      if (foundData.get(1) == null) throw new NoSuchElementException("Cannot remove data that doesn't exist in AVL tree.");

      root = foundData.get(0); //Updates the root if a remove was successful
      size--; //Updates size

      return foundData.get(1).getData(); //Returns the found data
    }

    /**
     * Recursive helper method for removing data from AVL tree.
     *
     * @param node the parent node to compare to
     * @param data the data to look for
     * @return a list of nodes. The first element is the new root of the tree
     * and the 2nd is the node that was removed. The 2nd will be null if the
     * element was not found.
     */
    private List<AVLNode<T>> remove(AVLNode<T> node, T data) {
      List<AVLNode<T>> foundData = new ArrayList<AVLNode<T>>(); //First index holds root of subtree, 2nd the node being removed
      AVLNode<T> replacement = null; //The node to replace the removed

      //Add base case: data not found
      foundData.add(node);
      foundData.add(null);

      //If root node exists
      if (node != null) {
        if (data.compareTo(node.getData()) < 0) { //Go down left
            foundData = remove(node.getLeft(), data); //Returns [newLeftNode, nodeToRemove (data only)]

            node.setLeft(foundData.get(0)); //Updates left (may have changed to replacement)

            replacement = node; //Replace node with itself
        } else if (data.compareTo(node.getData()) > 0) { //Go down right
            foundData = remove(node.getRight(), data); //Returns [newRightNode, nodeToRemove (data only)]

            node.setRight(foundData.get(0)); //Updates right (may have changed to replacement)

            replacement = node; //Replace node with itself
        } else { //Match -> remove
          AVLNode<T> left = node.getLeft();
          AVLNode<T> right = node.getRight();

          //Finds replacement (base case null)
          if (left != null && right == null) { //Left child
            replacement = left;
          } else if (left == null && right != null) { //Right child
            replacement = right;
          } else if (left != null && right != null) { //Both children
            AVLNode<T> pred = findPred(node); //The nodes predecessor
            foundData = remove(left, pred.getData()); //Returns [leftNode, predecessor (data only)]

            //Updates replacement
            replacement = foundData.get(1);
            replacement.setRight(right); //Updates replacement's right
            replacement.setLeft(foundData.get(0)); //Updates replacement's left
          }

          //Updating with data found
          foundData.remove(1);
          foundData.add(1, new AVLNode<T>(data));
        }

        //Rebalance if necessary (can happen more than once) -> not hitting other nodes on path (for additional rotations)
        if (replacement != null) {
          updateNodeValues(replacement);

          //Loops while the replacement is not balanced. Handles case where
          //consecutive new roots are unbalanced since they are not considered
          //in the path (no recursion called on them)
          while (Math.abs(replacement.getBalanceFactor()) > 1) {
            if (replacement.getBalanceFactor() > 1) { //Left subtree bigger -> deleted on right side
              if (replacement.getLeft().getBalanceFactor() >= 0) { //Double rotation LL
                replacement = rotateRight(replacement);
              } else { //Double rotation LR
                replacement.setLeft(rotateLeft(replacement.getLeft()));
                replacement = rotateRight(replacement);
              }
            } else if (replacement.getBalanceFactor() < -1) { //Right subtree bigger -> deleted on left side
              if (replacement.getRight().getBalanceFactor() <= 0) { //single rotation RR
                replacement = rotateLeft(replacement);
              } else { //Double rotation RL
                replacement.setRight(rotateRight(replacement.getRight()));
                replacement = rotateLeft(replacement);
              }
            }
          }
        }

        //Updating with replacement node
        foundData.remove(0);
        foundData.add(0, replacement);
      }

      return foundData;
    }

    /**
      * This method finds the predecessor of the specified node.
      *
      * @param node the node to find the predecessor of
      * @return the predecessor node
      */
    private AVLNode<T> findPred(AVLNode<T> node) {
      AVLNode<T> curr = node.getLeft();

      while (curr != null && curr.getRight() != null) {
        curr = curr.getRight();
      }

      return curr;
    }

    /**
     * Returns the data in the tree matching the parameter passed in.
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @throws java.util.NoSuchElementException if the data is not found
     * @param data data to get in the AVL tree
     * @return the data in the tree equal to the parameter.  Do not return the
     * same data that was passed in.  Return the data that was stored in the
     * tree.
     */
    public T get(T data) {
      if (data == null) throw new IllegalArgumentException("Cannot retrieve null data from AVL tree.");

      T foundData = subtreeContains(root, data);

      if (foundData == null) throw new NoSuchElementException("Cannot retrieve data that doesn't exist in AVL tree.");

      return foundData;
    }

    /**
     * Returns whether or not the parameter is contained within the tree.
     *
     * @throws java.lang.IllegalArgumentException if the data is null
     * @param data data to find in the AVL tree
     * @return whether or not the parameter is contained within the tree
     */
    public boolean contains(T data) {
      if (data == null) throw new IllegalArgumentException("Cannot find null data in AVL tree.");

      return (subtreeContains(root, data) != null);
    }

    /**
     * Recursive helper method for finding if a value is contained within the tree.
     *
     * @param subtree the subtree to traverse
     * @param data the data to find in the AVL tree
     * @return the data that was found in the tree. Null if the data is not contained
     */
    private T subtreeContains(AVLNode<T> node, T data) {
      T found = null; //Base case: false

      if (node != null) {
        if (data.equals(node.getData())) { //Base case: match
          found = node.getData();
        } else if (node.getLeft() != null && data.compareTo(node.getData()) < 0) { //Left subtree
          found = subtreeContains(node.getLeft(), data);
        } else if (node.getRight() != null && data.compareTo(node.getData()) > 0) { //Right subtree
          found = subtreeContains(node.getRight(), data);
        }
      }

      return found;
    }

    /**
     * Get the number of elements in the tree.
     *
     * @return the number of elements in the tree
     */
    public int size() {
        return size;
    }

    /**
     * Get the preorder traversal of the tree.
     *
     * @return a preorder traversal of the tree, or an empty list
     */
    public List<T> preorder() {
      List<T> list = new LinkedList<T>(); //List to add traversal to
      return preorderHelper(root, list);
    }

    /**
      * Recursive helper method for preorder traversal of tree.
      *
      * @param node the node to preorder
      * @param list the list to add the traversal to
      */
    private List<T> preorderHelper(AVLNode<T> node, List<T> list) {
      if (node != null) { //If node is not null
        list.add(node.getData()); //Base case: add root

        //Left child: recursive case
        if (node.getLeft() != null) {
          preorderHelper(node.getLeft(), list);
        }

        //Right child: recursive case
        if (node.getRight() != null) {
          preorderHelper(node.getRight(), list);
        }
      }

      return list; //return preordered list
    }

    /**
     * Get the postorder traversal of the tree.
     *
     * @return a postorder traversal of the tree, or an empty list
     */
    public List<T> postorder() {
      List<T> list = new LinkedList<T>(); //List to add traversal to
      return postorderHelper(root, list);
    }

    /**
      * Recursive helpther method for postoder traversal.
      *
      * @param node the node to postorder
      * @param list the list to add the traversal to
      */
    private List<T> postorderHelper(AVLNode<T> node, List<T> list) {
      if (node != null) { //If node is not null

        //Left child: recursive case
        if (node.getLeft() != null) {
          postorderHelper(node.getLeft(), list);
        }

        //Right child: recursive case
        if (node.getRight() != null) {
          postorderHelper(node.getRight(), list);
        }

        list.add(node.getData()); //Base case: add root
      }

      return list; //Return postordered list
    }

    /**
     * Get the inorder traversal of the tree.
     *
     * @return an inorder traversal of the tree, or an empty list
     */
    public List<T> inorder() {
      List<T> list = new LinkedList<T>(); //List to add traversal to
      return inorderHelper(root, list);
    }

    /**
      * Recursive helpther method for inorder traversal.
      *
      * @param node the node to inorder
      * @param list the list to add the traversal to
      */
    private List<T> inorderHelper(AVLNode<T> node, List<T> list) {
      if (node != null) { //If node is not null

        //Left child: recursive case
        if (node.getLeft() != null) {
          inorderHelper(node.getLeft(), list);
        }

        list.add(node.getData()); //Base case: add root

        //Right child: recursive case
        if (node.getRight() != null) {
          inorderHelper(node.getRight(), list);
        }
      }

      return list; //Return postordered list
    }

    /**
     * Get the level order traversal of the tree.
     *
     * @return a level order traversal of the tree, or an empty list
     */
    public List<T> levelorder() {
      Queue<AVLNode<T>> queue = new LinkedList<AVLNode<T>>();
      List<T> list = new LinkedList<T>();

      if (root != null) queue.add(root); //Add root if it isn't null

      while (!queue.isEmpty()) {
        AVLNode<T> node = queue.poll(); //The node just removed

        //If the node wasn't null
        if (node != null) {
          list.add(node.getData()); //Add node
          queue.add(node.getLeft()); //Add left to queue
          queue.add(node.getRight()); //Add right to queue
        }
      }

      return list; //Return levelordered list
    }

    /**
     * Clear the tree.
     */
    public void clear() {
        root = null;
        size = 0;
    }

    /**
     * Return the height of the root of the tree.
     *
     * @return the height of the root of the tree, -1 if the tree is empty
     */
    public int height() {
      return (size == 0 ? -1 : root.getHeight());
    }

    /**
     * THIS METHOD IS ONLY FOR TESTING PURPOSES.
     *
     * @return the root of the tree
     */
    public AVLNode<T> getRoot() {
        return root;
    }
}
