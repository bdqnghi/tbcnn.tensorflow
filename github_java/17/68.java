package algorithm.sourcecode;
// RedBlackTree class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// boolean contains( x )  --> Return true if x is found
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print all items
// ******************ERRORS********************************
// Throws UnderflowException as appropriate

/**
 * Implements a red-black tree. Note that all "matching" is based on the compareTo method.
 *
 * @author Mark Allen Weiss
 */
public class RedBlackTree<AnyType extends Comparable<? super AnyType>> {

    /**
     * Construct the tree.
     */
    public RedBlackTree() {
        nullNode = new RedBlackNode<>(null);
        nullNode.left = nullNode.right = nullNode;
        header = new RedBlackNode<>(null);
        header.left = header.right = nullNode;
    }

    /**
     * Compare item and t.element, using compareTo, with caveat that if t is header, then item is
     * always larger. This routine is called if is possible that t is header. If it is not possible
     * for t to be header, use compareTo directly.
     */
    private int compare(AnyType item, RedBlackNode<AnyType> t) {
        if (t == header) {
            return 1;
        } else {
            return item.compareTo(t.element);
        }
    }

    /**
     * Insert into the tree.
     *
     * @param item the item to insert.
     */
    public void insert(AnyType item) {
        current = parent = grand = header;
        nullNode.element = item;

        while (compare(item, current) != 0) {
            great = grand;
            grand = parent;
            parent = current;
            current = compare(item, current) < 0 ?
                    current.left : current.right;

            // Check if two red children; fix if so
            if (current.left.color == RED && current.right.color == RED) {
                handleReorient(item);
            }
        }

        // Insertion fails if already present
        if (current != nullNode) {
            return;
        }
        current = new RedBlackNode<>(item, nullNode, nullNode);

        // Attach to parent
        if (compare(item, parent) < 0) {
            parent.left = current;
        } else {
            parent.right = current;
        }
        handleReorient(item);
    }

    /**
     * Remove from the tree.
     *
     * @param x the item to remove.
     * @throws UnsupportedOperationException if called.
     */
    public void remove(AnyType x) {
        throw new UnsupportedOperationException();
    }

    /**
     * Find the smallest item  the tree.
     *
     * @return the smallest item or throw UnderflowExcepton if empty.
     */
    public AnyType findMin() {
        if (isEmpty()) {
            throw new UnderflowException();
        }

        RedBlackNode<AnyType> itr = header.right;

        while (itr.left != nullNode) {
            itr = itr.left;
        }

        return itr.element;
    }

    /**
     * Find the largest item in the tree.
     *
     * @return the largest item or throw UnderflowExcepton if empty.
     */
    public AnyType findMax() {
        if (isEmpty()) {
            throw new UnderflowException();
        }

        RedBlackNode<AnyType> itr = header.right;

        while (itr.right != nullNode) {
            itr = itr.right;
        }

        return itr.element;
    }

    /**
     * Find an item in the tree.
     *
     * @param x the item to search for.
     * @return true if x is found; otherwise false.
     */
    public boolean contains(AnyType x) {
        nullNode.element = x;
        current = header.right;

        for (; ; ) {
            if (x.compareTo(current.element) < 0) {
                current = current.left;
            } else if (x.compareTo(current.element) > 0) {
                current = current.right;
            } else if (current != nullNode) {
                return true;
            } else {
                return false;
            }
        }
    }

    /**
     * Make the tree logically empty.
     */
    public void makeEmpty() {
        header.right = nullNode;
    }

    /**
     * Print the tree contents in sorted order.
     */
    public void printTree() {
        if (isEmpty()) {
            System.out.println("Empty tree");
        } else {
            printTree(header.right);
        }
    }

    /**
     * Internal method to print a subtree in sorted order.
     *
     * @param t the node that roots the subtree.
     */
    private void printTree(RedBlackNode<AnyType> t) {
        if (t != nullNode) {
            printTree(t.left);
            System.out.println(t.element);
            printTree(t.right);
        }
    }

    /**
     * Test if the tree is logically empty.
     *
     * @return true if empty, false otherwise.
     */
    public boolean isEmpty() {
        return header.right == nullNode;
    }

    /**
     * Internal routine that is called during an insertion if a node has two red children. Performs
     * flip and rotations.
     *
     * @param item the item being inserted.
     */
    private void handleReorient(AnyType item) {
        // Do the color flip
        current.color = RED;
        current.left.color = BLACK;
        current.right.color = BLACK;

        if (parent.color == RED)   // Have to rotate
        {
            grand.color = RED;
            if ((compare(item, grand) < 0) !=
                    (compare(item, parent) < 0)) {
                parent = rotate(item, grand);  // Start dbl rotate
            }
            current = rotate(item, great);
            current.color = BLACK;
        }
        header.right.color = BLACK; // Make root black
    }

    /**
     * Internal routine that performs a single or double rotation. Because the result is attached to
     * the parent, there are four cases. Called by handleReorient.
     *
     * @param item the item in handleReorient.
     * @param parent the parent of the root of the rotated subtree.
     * @return the root of the rotated subtree.
     */
    private RedBlackNode<AnyType> rotate(AnyType item, RedBlackNode<AnyType> parent) {
        if (compare(item, parent) < 0) {
            return parent.left = compare(item, parent.left) < 0 ?
                    rotateWithLeftChild(parent.left) :  // LL
                    rotateWithRightChild(parent.left);  // LR
        } else {
            return parent.right = compare(item, parent.right) < 0 ?
                    rotateWithLeftChild(parent.right) :  // RL
                    rotateWithRightChild(parent.right);  // RR
        }
    }

    /**
     * Rotate binary tree node with left child.
     */
    private RedBlackNode<AnyType> rotateWithLeftChild(RedBlackNode<AnyType> k2) {
        RedBlackNode<AnyType> k1 = k2.left;
        k2.left = k1.right;
        k1.right = k2;
        return k1;
    }

    /**
     * Rotate binary tree node with right child.
     */
    private RedBlackNode<AnyType> rotateWithRightChild(RedBlackNode<AnyType> k1) {
        RedBlackNode<AnyType> k2 = k1.right;
        k1.right = k2.left;
        k2.left = k1;
        return k2;
    }

    private static class RedBlackNode<AnyType> {

        // Constructors
        RedBlackNode(AnyType theElement) {
            this(theElement, null, null);
        }

        RedBlackNode(AnyType theElement, RedBlackNode<AnyType> lt, RedBlackNode<AnyType> rt) {
            element = theElement;
            left = lt;
            right = rt;
            color = RedBlackTree.BLACK;
        }

        AnyType element;    // The data in the node
        RedBlackNode<AnyType> left;       // Left child
        RedBlackNode<AnyType> right;      // Right child
        int color;      // Color
    }

    private RedBlackNode<AnyType> header;
    private RedBlackNode<AnyType> nullNode;

    private static final int BLACK = 1;    // BLACK must be 1
    private static final int RED = 0;

    // Used in insert routine and its helpers
    private RedBlackNode<AnyType> current;
    private RedBlackNode<AnyType> parent;
    private RedBlackNode<AnyType> grand;
    private RedBlackNode<AnyType> great;


    // Test program
    public static void main(String[] args) {
        RedBlackTree<Integer> t = new RedBlackTree<>();
        final int NUMS = 400000;
        final int GAP = 35461;

        System.out.println("Checking... (no more output means success)");

        for (int i = GAP; i != 0; i = (i + GAP) % NUMS) {
            t.insert(i);
        }

        if (t.findMin() != 1 || t.findMax() != NUMS - 1) {
            System.out.println("FindMin or FindMax error!");
        }

        for (int i = 1; i < NUMS; i++) {
            if (!t.contains(i)) {
                System.out.println("Find error1!");
            }
        }
    }
}
