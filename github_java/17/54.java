public class RedBlackTree<Key, Value> {

    private static final boolean RED = true;
    private static final boolean BLACK = false;

    private Node root;

    private class Node {
        private Key key;
        private Value val;
        private Node left, right;
        private boolean color;
    }

    private boolean isRed(Node node) {
        return node != null && node.color == RED;
    }

    public boolean isRedBlackTree() {
        return this.isRedBlackTree(this.root);
    }

    private boolean isRedBlackTree(Node node) {
        // Skrifið þessa aðferð!
    }
}