public class RedBlackTree<T extends Comparable<? super T>> extends BinarySearchTree<T>{
  RedBlackNode root;

  public RedBlackNode getRoot(){
    return this.root;
  }

  public RedBlackTree() {
    super();
  }

  public RedBlackTree(T rootData) {
    super();
    this.root = new RedBlackNode<T>(rootData);
  }

  // returns f if item already exists
  public boolean addNode(T newEntry){
    return addNode(getRoot(), newEntry);
  }

  private boolean addNode(RedBlackNode<T> rootNode, T newEntry){
    // BASE CASE - tree/subtree is empty (null node)
    if(rootNode == null) {
      RedBlackNode<T> newNode = new RedBlackNode<T>(newEntry);
      newNode.setBlack();
      rootNode = newNode;
      return true;
    }

    // CASE 1 - entry is already in tree, return false
    if (newEntry.equals(rootNode.getData())) return false;

    // CASE 2 - entry belongs to the left of root
    else if (newEntry.compareTo(rootNode.getData()) < 0) {
      // CASE 2A - there's no entry to the left of root, so
      // we can add newEntry as a red node
      if (!rootNode.hasLeft()) {
        RedBlackNode<T> newNode = new RedBlackNode<T>(newEntry);
        newNode.setRed();
        rootNode.setLeft(newNode);
        return true;
      } 
      // CASE 2B - 
      else {
        RedBlackNode<T> left = (RedBlackNode<T>) rootNode.getLeft();
        if(left.isRed() && rootNode.hasRight()){
          RedBlackNode<T> right = (RedBlackNode<T>) rootNode.getRight();
          if(right.isRed()){
            right.setBlack();
            left.setBlack();
            rootNode.setRed();
          }
        }
        if(addNode(left, newEntry)) {

          // if child was added to the left of left,
          if(left.hasLeft()){
            System.out.println("doing single rotation with root " + rootNode.getData().toString());
            // change left to black and root to red
            left.setBlack();
            rootNode.setRed();

            // do a single right rotation
            //     R        L
            //   L     => C   R
            // C
            //
            if(getRoot().getData().equals(rootNode.getData())) {
              setRoot(rotateRight(rootNode));
            } else {
              RedBlackNode<T> parent = (RedBlackNode<T>)findNode(rootNode).getParent();
              if(parent.hasLeft()&&parent.getLeft() == rootNode) {
                parent.setLeft(rotateRight(rootNode));
              } else {
                parent.setRight(rotateRight(rootNode));
              }
            }
          }
          else {
            System.out.println("doing double rotation with root " + rootNode.getData().toString());
            // do a double rotation
            //   R          R         C
            // L     =>   C     =>  L   R
            //   C      L
            rootNode.setRed();
            left.getRight().setBlack();

            rootNode.setLeft(rotateLeft(left));
            if(getRoot().getData().equals(rootNode.getData())) {
              setRoot(rotateRight(rootNode));
            } else {
              RedBlackNode<T> parent = (RedBlackNode<T>)findNode(rootNode).getParent();
              if(parent.hasLeft()&&parent.getLeft() == rootNode) {
                parent.setLeft(rotateRight(rootNode));
              } else {
                parent.setRight(rotateRight(rootNode));
              }
            }
          }
          inorderTraverse();
          System.out.println();
          return true;
        }
      }
    } 
    // CASE 3 - entry belongs to the right of the root
    else {
      if (!rootNode.hasRight()) {
        RedBlackNode<T> newNode = new RedBlackNode<T>(newEntry);
        newNode.setRed();
        rootNode.setRight(newNode);
      } 
      // CASE 3B - 
      else {
        RedBlackNode<T> right = (RedBlackNode<T>) rootNode.getRight();
        if(right.isRed() && rootNode.hasLeft()){
          RedBlackNode<T> left = (RedBlackNode<T>) rootNode.getLeft();
          if(left.isRed()){
            left.setBlack();
            right.setBlack();
            rootNode.setRed();
          }
          return true;
        }
        if(addNode(right, newEntry)) {
          // if child was added to the right of right,
          if(right.hasRight()){
            // change right to black and root to red
            right.setBlack();
            rootNode.setRed();

            System.out.println("doing single rotation with root " + rootNode.getData().toString());

            // do a single left rotation
            if(getRoot().getData().equals(rootNode.getData())) {
              setRoot(rotateLeft(rootNode));
            } else {
              RedBlackNode<T> parent = (RedBlackNode<T>) findNode(rootNode).getParent();
              if(parent.hasRight()&&parent.getRight() == rootNode) {
                parent.setRight(rotateLeft(rootNode));
              } else {
                parent.setLeft(rotateLeft(rootNode));
              }
            }
          }
          else {
            // do a double rotation
            //   R      R           C
            //     P =>   C   =>  R   P
            //   C          P

            rootNode.setRed();
            right.getLeft().setBlack();
            System.out.println("doing double rotation with root " + rootNode.getData().toString());

            rootNode.setRight(rotateRight(right));
            if(getRoot().getData().equals(rootNode.getData())) {
              setRoot(rotateLeft(rootNode));
            } else {
              RedBlackNode<T> parent = (RedBlackNode<T>)findNode(rootNode).getParent();
              if(parent.hasRight()&&parent.getRight() == rootNode) {
                parent.setRight(rotateLeft(rootNode));
              } else {
                parent.setLeft(rotateLeft(rootNode));
              }
            }
          }
          inorderTraverse();
          System.out.println();
          return true;

        }
      }
    }
    System.out.println("reached end return statement");
    return true;
  }

  private RedBlackNode rotateLeft(RedBlackNode rootNode) {
    // returns new root
    RedBlackNode<T> leftChild   = rootNode.getLeft();
    RedBlackNode<T> rightChild  = rootNode.getRight();
    RedBlackNode<T> rightOrphan = rightChild.getLeft();

    rootNode.setRight(rightOrphan);
    rightChild.setLeft(rootNode);

    return rightChild;
  }

  private RedBlackNode rotateRight(RedBlackNode rootNode) {
    RedBlackNode<T> leftChild   = rootNode.getLeft();
    RedBlackNode<T> rightChild  = rootNode.getRight();
    RedBlackNode<T> leftOrphan  = leftChild.getRight(); // possibly null

    rootNode.setLeft(leftOrphan);
    leftChild.setRight(rootNode);

    return leftChild;
  }


  public T getPredecessor(T entry) {
    return ((RedBlackNode<T>)getPredecessorNode((RedBlackNode<T>)findNode(entry).getChild())).getData();
  }

  private RedBlackNode<T> getPredecessorNode(RedBlackNode<T> node) {
    return findRightmostChild((RedBlackNode<T>) node.getLeft());
  }

  private RedBlackNode<T> findRightmostChild(RedBlackNode<T> node) {
    return node.hasRight() ? findRightmostChild((RedBlackNode<T>) node.getRight()) : node;
  }
  private NodePair findNode(RedBlackNode<T> node){
    return findNode((T) node.getData(), new NodePair(null, this.root));
  }
  private NodePair findNode(T entry) {
    return findNode(entry, new NodePair(null, this.root));
  }

  private NodePair findNode(T entry, NodePair pair) {
    BinaryNode<T> parent = null;
    BinaryNode<T> child = this.root;
    if (entry.equals(child.getData())) {
      return new NodePair(parent, child);
    } else if (entry.compareTo(child.getData()) < 0) {
      return findNode(entry, new NodePair(child, child.getLeft()));
    } else {
      return findNode(entry, new NodePair(child, child.getRight()));
    }

  }
}	