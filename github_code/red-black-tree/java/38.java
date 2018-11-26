/**
 * Created by rober on 7/4/2017.
 * A good method to represent a 2-3 tree as Binary Search Tree
 * B-tree is of the same form, but now each node can hold more items,
 * sitll once full, split into 2 and pop up the mediate key, e.g.
 * abced -> ab cde e. Used for external memeory access and system.
 */
public class RedBlackTree<Key extends Comparable<Key>, Value> {
    /**
     *  Every left lining red line represents an internal link
     *  for three node, from root to any node, the number of black
     *  links are equal.
     *  Many operations does not need to be changed, because the old
     *  operations do not check color of links, but enjoy more balanced
     *  architecture.
     */

    private Node root;
    private static final boolean RED = true;
    private static final boolean BLACK = false;

    public void put(Key key, Value value) {
        root = put(root, key, value);
    }

    /**
     * same as get procedure in BST
     * @param key
     * @return
     */
    public Value get(Key key) {
        Node current = root;
        while (current != null) {
            if (key.compareTo(current.key) < 0) current = current.left;
            else  if (key.compareTo(current.key) > 0) current = current.right;
            else return current.value;
        }
        return null;
    }

    /**
     * put procedure: 1. standard BST insertion, color new link red
     * 2. rotate to balance 4-node. 3. filp color to pass red link up one
     * level. 4. rotate to make lean left. 5. repeat 1-4 if needed.
     */
    private Node put(Node current, Key key, Value value) {
        if (current == null) return new Node(RED, value, key);
        else if (key.compareTo(current.key) < 0) current.left = put(current.left, key, value);
        else if (key.compareTo(current.key) > 0) current.right = put(current.right, key, value);
        else current.value = value;

        //rotate to maintain left lean structure
        if (!isRed(current.left) && isRed(current.right)) rotateLeft(current);
        if (isRed(current.left.left) && isRed(current.left)) rotateRight(current);
        if (isRed(current.left) && isRed(current.right)) flipColors(current);

        current.count = 1 + size(current.left) + size(current.right);
        return current;

    }

    /**
     * Convert temporary 4-child nodes to split inner-most node upper
     * and flip colors
     * @param current
     */
    private void flipColors(Node current) {
        assert (isRed(current.left));
        assert (isRed(current.right));
        assert (!isRed(current));
        current.color = RED;
        current.left.color = BLACK;
        current.right.color = BLACK;
    }

    private int size(Node curr) {
        return curr.count;
    }

    /**
     * if right lining tree, rotate left, maintain height and
     * the portion of child (right, left, between)
     * @param current
     * @return
     */
    private Node rotateLeft(Node current) {
        assert (isRed(current.right));
        Node rightChild = current.right;
        rightChild.color = current.color;
        current.color = RED;
        current.right = rightChild.left;
        rightChild.left = current;
        return rightChild;
    }

    /**
     * if left lining tree, rotate right, maintain height and
     * the portion of child (right, left, between)
     * @param current
     * @return
     */
    private Node rotateRight(Node current) {
        assert (isRed(current.left));
        Node leftChild = current.left;
        leftChild.color = current.color;
        current.color = RED;
        current.left = leftChild.right;
        leftChild.right = current;
        return leftChild;
    }

    private class Node {
        private Key key;
        private Value value;
        private Node left, right;
        private int count;
        private boolean color;          //every node is pointed by 1 link

        public Node(boolean color, Value value, Key key) {
            this.color = color;
            this.value = value;
            this.key = key;
        }
    }

    private boolean isRed(Node x) {
        if (x == null) return false;
        return x.color == RED;
    }

    public static void main(String[] args) {

    }
}
