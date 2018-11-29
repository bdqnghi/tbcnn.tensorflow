/**
 *
 * @author Gaurab R. Gautam
 */

package binarysearchtrees;

import binarysearchtrees.Node.Color;

public class RedBlackTree<T extends Comparable<? super T>> extends BinarySearchTree<T>
{
    private static enum Debug 
    {
        YES("yes"), 
        NO("no");

        private final String name;

        Debug(String val)
        {
            name = val;
        }

        @Override
        public String toString()
        {
            return name;
        }
    };
    
    private int height = 0;
    final Debug DEBUG = Debug.NO;
    
    public RedBlackTree(T[] vals)
    {
        buildRBT(vals);
    }
    
    private void buildRBT(T[] vals)
    {
        for (T t : vals)
        {
            insert(t);
        }
        
        System.out.println();
    }
    
    // upper bound of height of balanced binary tree
    @Override
    public int getHeight() {
        this.height = 2 * (int)Math.floor(Math.log(this.getSize() + 1)/Math.log(2));
        return this.height;
    }
    
    @Override
    public Node<T> insert(T key)
    {
        Node<T> node = super.insert(key);
        node.color = Color.RED;
        validateRBTProperties(node);
        
        return node;
    }

    // validate RBT properties during insertion
    private void validateRBTProperties(Node<T> node)
    {
        // Tree was empty and the new node becomes root
        // Color root node black
        if (super.getRoot() == node)
        {
            super.getRoot().color = Color.BLACK;  
        }
        else if (node.parent.color == Color.BLACK) {
            // no violation, do nothing;
        }
        // If new node's parent is not black, RBT property is violated upon
        // inserting the new node, fix it
        else if (node.parent.color == Color.RED && node.color == Color.RED) 
        {
            // two cases follow depending on new node's uncle color
            Node<T> parent = node.parent;
            Node<T> grandparent = parent.parent;
            Node<T> uncle = null;
            
            // grandparent is never null, so could avoid null checking
            // parent is grandparent's left child
            if (parent == grandparent.left)
            {
                uncle = grandparent.right;
            }
            else
            {
                uncle = grandparent.left;
            }

            // case 1: Uncle's color is also red
            //         Recolor parent and uncle black, and grandparent red
            //         Check if coloring grandparent red violets RBT properties; 
            //         if RBT properites get violated, propogate recoloring up the tree
            if (uncle != null && uncle.color == Color.RED)
            {
                parent.color = Color.BLACK;
                uncle.color = Color.BLACK;
                grandparent.color = Color.RED;
                
                // check for further properties violations
                validateRBTProperties(grandparent);
            }
            
            
            // case 2: Uncle is null or its color is black
            //         Need to rotate nodes and recolor if necessary
            //         Two subcases follow depending on whether the parent is
            //         left or rightChihld child
            else if (uncle == null || uncle.color == Color.BLACK)
            {
                // case 2.1: If parent is the rightChihld child of grandparent
                //           left rotate is necessary preserving binary search
                //           tree property
                if (parent == grandparent.right)
                {
                    if (node == parent.right)
                    {
                        rotateLeft(grandparent);
                        
                        parent.color = Color.BLACK;
                        grandparent.color = Color.RED;
                    }
                    else 
                    {
                        rotateRight(parent);
                        rotateLeft(grandparent);
                        
                        node.color = Color.BLACK;
                        grandparent.color = Color.RED;
                    }
                }
                // case 2.2: If parent is the left child of grandparent
                //          Left rotate is necessary
                else if (parent == grandparent.left)
                {
                    if (node == parent.left) 
                    {
                        rotateRight(grandparent);
                        parent.color = Color.BLACK;
                        grandparent.color = Color.RED;
                    }
                    else
                    {
                        rotateLeft(parent);
                        rotateRight(grandparent);
                        
                        node.color = Color.BLACK;
                        grandparent.color = Color.RED;
                    }
                }
            }
        } 
    }
    
    // Deletion of a node may lead to double black nodes imbalancing the black height
    // To get rid of double black node, find the closest red sibling and change
    // colors {double black, red} to {black, black}
    private void fixDoubleBlackNode(Node<T> node) {
        Node<T> sibling = null;
        
        if (node.isRoot()) {
            node.color = Color.BLACK;
            return;
        }
        else if (node.isLeftChild()) {
            sibling = node.parent.right;
        }
        else {
            sibling = node.parent.left;
        }
        
        // case: black sibling
        if (sibling.color == Color.BLACK) 
        {
            Node<T> leftNephew = sibling.left;
            Node<T> rightNephew = sibling.right;

            // case 1: black sibling with a right red child; left won't matter
            // restructure and recolor:
            if (rightNephew != null && rightNephew.color == Color.RED) 
            {
                print("---------- case 1: black sibling with a right red child ----------");
                print("[restructure and recolor]:"); 
                
                // case 1a: left node with a right black sibling with a right red child
                //          sibling's right child is red; sibling's left child won't matter
                //          do left rotation on parent
                //          recolor sibling's right child (right nephew) black
                //          recolor node black (extra black absorbed)
                //          recolor sibling to parent color
                if (node.isLeftChild()) {
                    print(" rotate parent [" + node.parent.key + "] left");
                    print(" recolor right nephew, parent and node black;");
                    print(" recolor sibling with parent's previous color");
                    
                    this.rotateLeft(node.parent);
                    rightNephew.color = Color.BLACK;
                    sibling.color = node.parent.color;
                    node.parent.color = Color.BLACK;
                    node.color = Color.BLACK;    // absorbs double black by parent
                }
                
                // case 1b: node is right child
                //          double rotatation: rotate nephew left and parent right
                //          recolor right newphew with parent's color
                //          recolor parent black; recolor node black
                else if (node.isRightChild()) {
                    print(" rotate sibling [" + sibling.key + "] left");
                    print(" rotate parent [" + node.parent.key + "] right");
                    print(" recolor right  nephew with parent's color");
                    print(" recolor parent black, node black");
                    
                    this.rotateLeft(sibling);
                    this.rotateRight(node.parent);
                    rightNephew.color = node.parent.color;
                    node.parent.color = Color.BLACK;    // parent absorbs extra black
                    node.color = Color.BLACK;
                }
                
                if (DEBUG == Debug.YES) BinaryTreePrinter.printLeftToRight(this);
            }
            // case 2: black sibling with left child red (right child won't matter)
            // restructure and recolor: 
            else if (leftNephew != null && leftNephew.color == Color.RED) 
            {
                print("---------- case 2: black sibling with left child red AND right child black/red  ----------");
                print("[restructure and recolor]:");
                    
                // case 2a: double black node is left child
                //          double rotation: rotate sibling's left child right 
                //                 then rotate parent left
                //          recolor sibling's left child to parent color
                //          recolor parent and node black
                if (node.isLeftChild()) {
                    print("rotate sibling's left child (left nephew) [" + sibling.key + "] right\n" + 
                                " rotate parent left;" +
                                " recolor left nephew with parent's color;" + 
                                " recolor parent black and node black");
                        
                    this.rotateRight(sibling);
                    this.rotateLeft(node.parent);
                    leftNephew.color = node.parent.color;
                    node.color = Color.BLACK;   // absorb extra black by parent
                    node.parent.color = Color.BLACK;

                    if (DEBUG == Debug.YES) BinaryTreePrinter.printLeftToRight(this);
                }
                
                // case 2b: double black node is right child
                //          rotate parent right
                //          recolor sibling with parent's color
                //          recolor node black; recolor left nephew black
                //          recolor parent black
                else 
                {
                    print(" rotate parent [" + node.parent.key + "] right");
                    print(" recolor right nephew, parent and node black;");
                    print(" recolor sibling with parent's previous color");
                    
                    this.rotateRight(node.parent);
                    sibling.color = node.parent.color;
                    node.parent.color = Color.BLACK;
                    leftNephew.color = Color.BLACK;
                    node.color = Color.BLACK;
                } 
            }
            
            // case 3: black sibling with black children [null is also considered black]
            //         recolor sibling red and parent black
            //         if parent is red, it absorbs black and terminates; otherwise,
            //         parent becomes double black
            //         if so, other cases applies
            //         terminates if parent is red, otherwise propogates upwards
            else if ((leftNephew == null || leftNephew.color == Color.BLACK) &&
                     (rightNephew == null || rightNephew.color == Color.BLACK))
             {
                print("---------- case 3: black sibling with black children ----------");
                print(" recolor sibling [" + sibling.key + "] red and parent [" +  node.parent.key + "] black;\n");
                print(" if parent was previously black, propogate problem upwards");
                    
                sibling.color = Color.RED;
                node.color = Color.BLACK;   // absorb extra black by parent
                
                if (node.parent.color == Color.BLACK) 
                {
                    node.parent.color = Color.DOUBLEBLACK;
                    
                    if (DEBUG == Debug.YES) BinaryTreePrinter.printLeftToRight(this);
                    
                    this.fixDoubleBlackNode(node.parent);
                }
                else  // terminates as parent absorbs extra black
                {
                    print(" absorb extra black by parent; terminates!");
                    node.parent.color = Color.BLACK;
                    
                    if (DEBUG == Debug.YES) BinaryTreePrinter.printLeftToRight(this);
                }
            }
        }

        // case 4: red sibling
        //         restructure so sibling color is black and use case 1, 2 or 3
        //         to restructure left child: rotate left
        //         or to restructure right child, rotate right
        else if (sibling.color == Color.RED) {
            print("---------- case 4: red sibling ----------\n" + 
                        " recolor sibling [" + sibling.key + "] black and parent [" + node.parent.key + "] red");
                
            if (node.isLeftChild()) {
                print("rotate parent left");
                this.rotateLeft(node.parent);
            }
            else if (node.isRightChild()) {
                print("rotate parent right");
                this.rotateRight(node.parent);
            }
            
            sibling.color = Color.BLACK;
            node.parent.color = Color.RED;
            
            if (DEBUG == Debug.YES) BinaryTreePrinter.printLeftToRight(this);
            
            this.fixDoubleBlackNode(node);
        }
    }
    
    @Override
    public boolean delete(T item) {
        Node<T> node = this.get(item);
        
        // item not found
        if (node == null) {
            print(item + " not found!");
            return false;
        }
        
        print("--- delete " + item + " --->");
        
        // node is leaf, delete it
        if (node.isLeaf()) {
            return this.deleteSingleNode(node);
        }
        // node has one child
        else if (!(node.hasLeft() && node.hasRight())) {
            return this.deleteSingleNode(node);
        }
        
        // node has two children 
        else
        {
            Node<T> inOrderPredecessor = this.predecessor(node);

            // swap node's key with its inorder predecessor and delete its predecessor
            // if node is black and predecessor is red, it just 
            // absorbs the predecessor
            T key = node.key;
            node.key = inOrderPredecessor.key;
            inOrderPredecessor.key = key;

            // delete predecessor
            return this.deleteSingleNode(inOrderPredecessor);
        }
    }
    
    // Node is always a leaf node or a node with a single child
    private boolean deleteSingleNode(Node<T> node) {
        boolean status = false;
        if (DEBUG == Debug.YES) BinaryTreePrinter.printLeftToRight(this);
        
        // node is red, done after deletion!
        if (node.color == Color.RED) {
            print("Deleting red node: [" + node.key + "]; done!");
            
            status = super.delete(node);
            
            if (DEBUG == Debug.YES) BinaryTreePrinter.printLeftToRight(this);
        }
        // node is  black
        else if (node.color == Color.BLACK) {
            if (node.isLeaf()) {
                // node now represents double black null node
                node.color = Color.DOUBLEBLACK;
                //node.key = "\u03A6";

                if (DEBUG == Debug.YES) BinaryTreePrinter.printLeftToRight(this);

                // fix double black node
                this.fixDoubleBlackNode(node);

                // delete node
                status = super.delete(node);
            }
            else if (node.hasLeft()) {
                Node<T> leftChild = node.left;
                
                // delete node
                status = super.delete(node);
                
                if (leftChild.color == Color.BLACK) {
                    leftChild.color = Color.DOUBLEBLACK;
            
                    if (DEBUG == Debug.YES) BinaryTreePrinter.printLeftToRight(this);
                    
                    // fix double black node
                    this.fixDoubleBlackNode(leftChild);
                }
                else {  // color is red
                    // absorb extra blackness
                    leftChild.color = Color.BLACK;
                }
            }
            // child node is right node
            else if (node.hasRight()){
                Node<T> rightChild = node.right;
                
                // delete node
                status = super.delete(node);
                
                if (rightChild.color == Color.BLACK) {
                    rightChild.color = Color.DOUBLEBLACK;
            
                    if (DEBUG == Debug.YES) BinaryTreePrinter.printLeftToRight(this);
                    
                    // fix double black node
                    this.fixDoubleBlackNode(rightChild);
                }
                else {  // color is red
                    // absorb extra blackness
                    rightChild.color = Color.BLACK;
                }
            }
            
            if (DEBUG == Debug.YES) BinaryTreePrinter.printLeftToRight(this);
        }
        
        return status;
    }
    
    private void rotateLeft(Node<T> node)
    {
        Node<T> rightChild = node.right;
        node.right = rightChild.left;
        
        if (rightChild.left != null)
        {
            rightChild.left.parent = node;
        }
        
        rightChild.parent = node.parent;
        
        if (node.parent == null) 
        {
            this.root = rightChild;
        }
        else if (node == node.parent.left) 
        {
            node.parent.left = rightChild;
        }
        else 
        {
            node.parent.right = rightChild;
        }
        
        rightChild.left = node;
        node.parent = rightChild;
    }
    
    private void rotateRight(Node<T> node)
    {
        Node<T> leftChild = node.left;
        node.left = leftChild.right;
        
        if (leftChild.right != null) {
            leftChild.right.parent = node;
        }
        
        leftChild.parent = node.parent;
        
        if (node.parent == null) {
            this.root = leftChild;
        }
        else if (node == node.parent.left) {
            node.parent.left = leftChild;
        }
        else {
            node.parent.right = leftChild;
        }
        
        leftChild.right = node;
        node.parent = leftChild;
    }
    
    
    // print for debugging purposes
    private void print(String text) 
    {
        if (this.DEBUG == Debug.YES)
            System.out.println(text);
    }
    
}
