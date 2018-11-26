package tree;

import java.util.ArrayList;

/**
 * This class is the complete and tested implementation of an AVL-tree.
 */
public class AVL_trees {
 
 protected AvlNode root; // the root node
 
/***************************** Core Functions ************************************/

 /**
  * Add a new element with key "k" into the tree.
  * 
  * @param k
  *            The key of the new node.
  */
 public void insert(int k) {
  // create new node
  AvlNode n = new AvlNode(k);
  // start recursive procedure for inserting the node
  insertAVL(this.root,n);
 }
 
 /**
  * Recursive method to insert a node into a tree.
  * 
  * @param p The node currently compared, usually you start with the root.
  * @param q The node to be inserted.
  */
 public void insertAVL(AvlNode p, AvlNode q) {
  // If  node to compare is null, the node is inserted. If the root is null, it is the root of the tree.
  if(p==null) {
   this.root=q;
  } else {
   
   // If compare node is smaller, continue with the left node
   if(q.key<p.key) {
    if(p.left==null) {
     p.left = q;
     q.parent = p;
     
     // Node is inserted now, continue checking the balance
     recursiveBalance(p);
    } else {
     insertAVL(p.left,q);
    }
    
   } else if(q.key>p.key) {
    if(p.right==null) {
     p.right = q;
     q.parent = p;
     
     // Node is inserted now, continue checking the balance
     recursiveBalance(p);
    } else {
     insertAVL(p.right,q);
    }
   } else {
    // do nothing: This node already exists p = q
   }
  }
 }
 
 /**
  * Check the balance for each node recursively and call required methods for balancing the tree until the root is reached.
  * 
  * @param cur : The node to check the balance for, usually you start with the parent of a leaf.
  */
 public void recursiveBalance(AvlNode cur) {
  
  // we do not use the balance in this class, but the store it anyway
  setBalance(cur);
  int balance = cur.balance;
  
  // check the balance
  if(balance==-2) {
   
   if(height(cur.left.left)>=height(cur.left.right)) {
    cur = rotateRight(cur);
   } else {
    cur = doubleRotateLeftRight(cur);
   }
  } else if(balance==2) {
   if(height(cur.right.right)>=height(cur.right.left)) {
    cur = rotateLeft(cur);
   } else {
    cur = doubleRotateRightLeft(cur);
   }
  }
  
  // we did not reach the root yet
  if(cur.parent!=null) {
   recursiveBalance(cur.parent);// while loop works cur = cur.parent
  } else {
   this.root = cur;
   System.out.println("------------ Balancing finished ----------------");
  }
 }

 /**
  * Removes a node from the tree, if it is existent.
  */
 public void remove(int k) {
  // First we must find the node, after this we can delete it.
  removeAVL(this.root,k);
 }
 
 /**
  * Finds a node and calls a method to remove the node.
  * 
  * @param p The node to start the search.
  * @param q The KEY of node to remove.
  */
 public void removeAVL(AvlNode p,int q) {
  if(p==null) {
   // der Wert existiert nicht in diesem Baum, daher ist nichts zu tun
   return;
  } else {
   if(p.key>q)  {
    removeAVL(p.left,q);
   } else if(p.key<q) {
    removeAVL(p.right,q);
   } else if(p.key==q) {
    // we found the node in the tree.. now lets go on!
    removeFoundNode(p);
   }
  }
 }
 
 /**
  * Removes a node from a AVL-Tree, while balancing will be done if necessary.
  * 
  * @param q The node to be removed.
  */
 public void removeFoundNode(AvlNode q) {
  AvlNode r;
  // at least one child of q, q will be removed directly
  if(q.left==null || q.right==null) {
   // the root is deleted
   if(q.parent==null) {
    this.root=null;
    q=null;
    return;
   }
   r = q;
  } else {
   // q has two children --> will be replaced by successor
   r = successor(q);
   q.key = r.key;
  }
  
  AvlNode p;
  if(r.left!=null) {
   p = r.left;
  } else {
   p = r.right;
  }
  
  if(p!=null) {
   p.parent = r.parent;
  }
  
  if(r.parent==null) {
   this.root = p;
  } else {
   if(r==r.parent.left) {
    r.parent.left=p;
   } else {
    r.parent.right = p;
   }
   // balancing must be done until the root is reached.
   recursiveBalance(r.parent);
  }
  r = null;
 }
 
 /**
  * Left rotation using the given node.
  * 
  * 
  * @param n
  *            The node for the rotation.
  * 
  * @return The root of the rotated tree.
  */
 public AvlNode rotateLeft(AvlNode n) {
  
  AvlNode v = n.right;
  v.parent = n.parent;
  
  n.right = v.left;
  
  if(n.right!=null) {
   n.right.parent=n;
  }
  
  v.left = n;
  n.parent = v;
  
  if(v.parent!=null) {
   if(v.parent.right==n) {
    v.parent.right = v;
   } else if(v.parent.left==n) {
    v.parent.left = v;
   }
  }
  
  setBalance(n);
  setBalance(v);
  
  return v;
 }
 
 /**
  * Right rotation using the given node.
  * 
  * @param n
  *            The node for the rotation
  * 
  * @return The root of the new rotated tree.
  */
 public AvlNode rotateRight(AvlNode n) {
  
  AvlNode v = n.left;
  v.parent = n.parent;
  
  n.left = v.right;
  
  if(n.left!=null) {
   n.left.parent=n;
  }
  
  v.right = n;
  n.parent = v;
  
  
  if(v.parent!=null) {
   if(v.parent.right==n) {
    v.parent.right = v;
   } else if(v.parent.left==n) {
    v.parent.left = v;
   }
  }
  
  setBalance(n);
  setBalance(v);
  
  return v;
 }
 /**
  * 
  * @param u The node for the rotation.
  * @return The root after the double rotation.
  */
 public AvlNode doubleRotateLeftRight(AvlNode u) {
  u.left = rotateLeft(u.left);
  return rotateRight(u);
 }
 
 /**
  * 
  * @param u The node for the rotation.
  * @return The root after the double rotation.
  */
 public AvlNode doubleRotateRightLeft(AvlNode u) {
  u.right = rotateRight(u.right);
  return rotateLeft(u);
 }
 
/***************************** Helper Functions ************************************/
 
 /**
  * Returns the successor of a given node in the tree (search recursively).
  * 
  * @param q The predecessor.
  * @return The successor of node q.
  */
 public AvlNode successor(AvlNode q) {
  if(q.right!=null) {
   AvlNode r = q.right;
   while(r.left!=null) {
    r = r.left;
   }
   return r;
  } else {
   AvlNode p = q.parent;
   while(p!=null && q==p.right) {
    q = p;
    p = q.parent;
   }
   return p;
  }
 }
 
 /**
  * Calculating the "height" of a node.
  * 
  * @param cur
  * @return The height of a node (-1, if node is not existent eg. NULL).
  */
 private int height(AvlNode cur) {
  if(cur==null) {
   return -1;
  }
  if(cur.left==null && cur.right==null) {
   return 0;
  } else if(cur.left==null) {
   return 1+height(cur.right);
  } else if(cur.right==null) {
   return 1+height(cur.left);
  } else {
   return 1+ Math.max(height(cur.left), height(cur.right));
  }
 }
 
 /**
  * Return the maximum of two integers.
  */
// private int maximum(int a, int b) {
//	 return a>b?a:b;
// }

 /** 
  * Only for debugging purposes. Gives all information about a node.
  
  * @param n The node to write information about.
  */
 public void debug(AvlNode n) {
  int l = 0;
  int r = 0;
  int p = 0;
  if(n.left!=null) {
   l = n.left.key;
  }
  if(n.right!=null) {
   r = n.right.key;
  }
  if(n.parent!=null) {
   p = n.parent.key;
  }
  
  System.out.println("Left: "+l+" Key: "+n+" Right: "+r+" Parent: "+p+" Balance: "+n.balance);
  
  if(n.left!=null) {
   debug(n.left);
  }
  if(n.right!=null) {
   debug(n.right);
  }
 }
 
 private void setBalance(AvlNode cur) {
  cur.balance = height(cur.right)-height(cur.left);
 
 }
 
 /**
  * Calculates the In-order traversal of this tree.
  * 
  * @return An Array-List of the tree in in-order traversal.
  */
 final protected ArrayList<AvlNode> inorder() {
  ArrayList<AvlNode> ret = new ArrayList<AvlNode>();
  inorder(root, ret);
  return ret;
 }
 
 /**
  * Function to calculate in-order recursively.
  * 
  * @param n
  *            The current node.
  * @param io
  *            The list to save the in-order traversal.
  */
 final protected void inorder(AvlNode n, ArrayList<AvlNode> io) {
  if (n == null) return;
  inorder(n.left, io);
  io.add(n);
  inorder(n.right, io);
  
 }
}

