package TREE;

/**
 * Project name: HomeWork
 * Created by pavel on 06.10.2017.
 */
public class RedBlackTree<K,V>{
    private Node root;
    private static final boolean RED = true;
    private static final boolean BLACK = false;



    /**
     * Search for key. Update value if found; grow table if new.
     * @param key
     * @param value
     */
    public void add(K key, V value)
    {
        root = add(root, key, value);
        root.color = BLACK;
    }

    private Node add(Node node, K key, V value)
    {
        // Change key’s value to val if key in subtree rooted at x.
        // Otherwise, add new node to subtree associating key with val.

        if (node == null) return new Node(key, value, 1, RED);

        if (node.compareTo(key) < 0) node.left  = add(node.left,  key, value);
        else if (node.compareTo(key) > 0) {
            node.right = add(node.right, key, value);
        } else node.value = value;

        if (isRed(node.right) && !isRed(node.left))    node = rotateLeft(node);
        if (isRed(node.left) && isRed(node.left.left)) node = rotateRight(node);
        if (isRed(node.left) && isRed(node.right))     flipColors(node);

        node.nodes = size(node.left) + size(node.right) + 1;

        return node;
    }



    /**
     *
     * @param key
     * @return
     */
    public V get(K key)
    {  return get(root, key);  }

    private V get(Node node, K key)
    {   // Return value associated with key in the subtree rooted at x;
        // Return null if key not present in subtree rooted at x.
        if (node == null) return null;
        if      (node.compareTo(key) < 0) return get(node.left, key);
        else if (node.compareTo(key) > 0) return get(node.right, key);
        else return (V) node.value;
    }



    /**
     *
     * @param key
     */
    public void delete(K key)
    {  root = delete(root, key);  }

    private Node delete(Node node, K key)
    {
        if (node == null) return null;
        if (node.compareTo(key) < 0) node.left  = delete(node.left,  key);
        else if (node.compareTo(key) > 0) node.right = delete(node.right, key);
        else
        {
            if (node.right == null) return node.left;
            if (node.left == null) return node.right;
            Node min = node;
            node = min(min.right);
            node.right = deleteMin(min.right);
            node.left = min.left;
        }
        node.nodes = size(node.left) + size(node.right) + 1;
        return node;
    }




    private Node deleteMin(Node node)
    {
        if (node.left == null) return node.right;
        node.left = deleteMin(node.left);
        node.nodes = size(node.left) + size(node.right) + 1;
        return node;
    }


    private Node min(Node node)
    {
        if (node.left == null) return node;
        return min(node.left);
    }





    private Node rotateLeft(Node node)
    {
        Node newentry = node.right;
        node.right = newentry.left;
        newentry.left = node;
        newentry.color = node.color;
        node.color = RED;
        newentry.nodes = node.nodes;
        node.nodes = 1 + size(node.left) + size(node.right);
        return newentry;
    }

    private Node rotateRight(Node node)
    {
        Node newentry = node.left;
        node.left = newentry.right;
        newentry.right = node;
        newentry.color = node.color;
        node.color = RED;
        newentry.nodes = node.nodes;
        node.nodes = 1 + size(node.left) + size(node.right);
        return newentry;
    }

    void flipColors(Node node)
    {
        node.color = RED;
        node.left.color = BLACK;
        node.right.color = BLACK;
    }

    private boolean isRed(Node node)
    {
        if (node == null) return false;
        return node.color == RED;
    }


    public int size()
    {  return size(root);  }

    private int size(Node node)
    {
        return (node == null) ? 0 : node.nodes;
    }


    public void display(){
        display(root);
    }

    private void display(Node root){
        if(root != null){
            display(root.left);
            System.out.println("key: " + root.key + " value: " + root.value);
            display(root.right);
        }
    }



    private class Node<K,V>{
        private K key;
        private V value;
        boolean color;
        int nodes;
        Node<K, V> left;
        Node<K, V> right;


        Node(K key, V value, int nodes, boolean color) {
            this.key = key;
            this.value = value;
            this.color = color;
            this.nodes = nodes;
        }



        public int compareTo(K key){
            try
            {
                return compareTo(Integer.parseInt(key.toString()), (Integer.parseInt(this.key.toString())));
            }
            catch (java.lang.NumberFormatException e)
            {
                try
                {
                    return compareTo(key.toString(), this.key.toString());
                }
                catch (java.lang.NumberFormatException h)
                {
                    return -1;
                }
            }
        }

        public int compareTo(int a, int b){
            return a - b;
        }

        public int compareTo(String a, String b){
            return a.compareTo(b);
        }

    }

}
