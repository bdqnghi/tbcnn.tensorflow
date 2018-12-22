/**
 * Demo implementation of the Binary Seacrh Tree class
 *
 * @author Nikita Gerasimov
 * @version 2018-05-28
 */
public class AVLTree {

    private static AVLNode root;

    /**
     * Constructor for objects of class BSTree
     */
    public AVLTree() {
        root = null;
    }

    /**
     * public add method, starts from root
     */
    public void add(int value) {        
        root = add(root, value);
    }

    /**
     * Traverse the tree from the root and find the place for the new value
     * @return the node that will be added to the tree
     */
    private static AVLNode add(AVLNode current, int value) {
        if (current == null) {                                           
            return new AVLNode(value);
        } 

        if (value < current.data) {                                      
            current.left = add(current.left, value);                     
        } else if (value > current.data) {                               
            current.right = add(current.right, value);                   
        } else {                                                         
            current.data = value;
            return current;                                              
        }

        current.height = height(current);                                
        return balance(current);                                        
        // return current;
    }

    /**
     * Balances the tree after adding or removing values
     * @return balanced subtree
     */
    private static AVLNode balance(AVLNode node) {
        if (getBalance(node) < - 1) {                                   
            if (getBalance(node.right) > 0) {                           
                node.right = rotateRight(node.right);                   
            }                                                           
            node = rotateLeft(node);                                    
        } else if (getBalance(node) > 1) {                              
            if (getBalance(node.left) < 0) {                            
                node.left = rotateLeft(node.left);                      
            }                                                          
            node = rotateRight(node);
        }
        return node;
    }

    /**
     * Removes the given value from the tree
     */
    public static void remove(int value) {
        root = remove(root, value);
    }

    /**
     * Removes the given value from the tree
     * @return the udpated subtree
     */
    private static AVLNode remove(AVLNode current, int data) {
        if (current == null) {                                          
            return null;
        } else if (current.data > data) {                                
            current.left = remove(current.left, data);
        } else if (current.data < data) {
            current.right = remove(current.right, data);
        } else {                                                         
            if (current.right == null) {                                 
                return current.left;                                      
            } else if (current.left == null) {
                return current.right;
            } else {                                                     
                current.data = getMinimum(current.right);                
                current.right = remove(current.right, current.data);    
            }
        }
        current.height = height(current);
        return balance(current);
    }

    /**
     * Utility method used to get the balance factor of the given node
     * @return balance factor
     */
    private static int getBalance(AVLNode node) {
        if (node == null) return 0;
        return height(node.left) - height(node.right);
    }

    /**
     * Utility method for left rotation
     * @return the left rotated subtree
     */
    private static AVLNode rotateLeft(AVLNode current) {
        AVLNode detached = current.right;                               
        current.right = detached.left;                                  
        detached.left = current;                                         

        current.height = height(current);                               
        detached.height = height(detached);

        return detached;
    }

    /**
     * Utility method for right rotation
     * @return the right rotated subtree
     */
    private static AVLNode rotateRight(AVLNode current) {
        AVLNode detached = current.left;                                 
        current.left = detached.right;                                    
        detached.right = current;                                         

        current.height = height(current);                               
        detached.height = height(detached);

        return detached;
    }

    /**
     * Traversing the tree inOrder for the print method
     */
    public static void inOrder(AVLNode node) {                 
        if (node != null) {
            inOrder(node.left);
            System.out.println("" + node.data + " of height " + height(node));
            inOrder(node.right);
        }
    }

    /**
     * Returns the number of nodes in the tree
     * @return int the number of nodes in the tree
     */
    public static int size(AVLNode current) {                  
        if (current == null) {
            return 0;
        } else {
            return 1 + size(current.left) + size(current.right);        
        }
    }

    /**
     * Utility method used to update heights of nodes
     * @return the height of the current node
     */
    private static int height(AVLNode node) {
        if (node == null) return 0;
        int left = (node.left == null) ? 0 : node.left.height;
        int right = (node.right == null) ? 0 : node.right.height;
        return max(left, right) + 1;
    }

    /**
     * Utility method to find the maximum of two numbers
     * @return the bigger of two integers
     */
    private static int max (int a, int b) {
        return a > b ? a : b;
    }

    /**
     * Utility method to print out all nodes in-order
     */
    public static void print(AVLNode current) {
        System.out.println("The size of the tree now is: " + size(current));
        System.out.println("Traversing the tree in order: ");
        inOrder(current);
    }

    /**
     * Getter memthod for the root of the tree
     * @return the root
     */
    public static AVLNode getRoot() {
        return root;
    }


    /**
     * Checks if the tree is balanced
     * @return true if the tree is balanced
     */
    private static boolean isAVL() {
        return isAVL(root);
    }

    /**
     * Checks if the tree is balanced
     * @param subtree
     * @return true if the tree is balanced
     */
    private static boolean isAVL(AVLNode node) {
        if (node == null) return true;
        int bf = getBalance(node);
        if (bf > 1 || bf < -1) return false;
        return isAVL(node.left) && isAVL(node.right);
    }

    /**
     * returns the minimum value of the given subtree
     * @return the minimum value
     */
    private static int getMinimum(AVLNode current) {                              
        if (current.left == null) {                                      
            return current.data;                                        
        } else {                                                         
            return getMinimum(current.left);
        }
    }

    /**
     * Utility tester method
     */
    public static void test() {
        AVLTree tree = new AVLTree();
        int[] added = {14, 17, 11, 7, 53, 4, 13, 12, 8};
        for (int i: added) {
            System.out.println("Adding " + i);
            tree.add(i);

            System.out.println("Is the tree balanced? " + isAVL());
        }
        System.out.println("The root now is " + getRoot().data);
        print(root);
        
        int[] removed = {53, 11, 8};
        for(int n: removed) {
            System.out.println("Removing " + n);
            tree.remove(n);
            System.out.println("The root now is " + getRoot().data);
            System.out.println("Is the tree balanced? " + isAVL());
            System.out.println("Balance factor of the root " + getBalance(root));
            print(root);
        }     
    }
}