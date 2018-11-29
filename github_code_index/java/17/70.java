import java.util.Iterator;

/**
 * Created by uditmehrotra on 29/12/14.
 */
public class RedBlackTree<Key extends Comparable<Key>, Value>
{

    private Node root = null;
    private final static boolean RED = true;
    private final static boolean BLACK = false;

    private class Node
    {
        Key key;
        Value value;
        Node left;
        Node right;
        boolean color;

        public Node(Key key, Value value, boolean color)
        {
            this.key = key;
            this.value = value;
            this.color = color;
        }
    }

    private void put(Key key, Value value)
    {
        root = put(root, key, value);
    }

    private Node put(Node node, Key key, Value value)
    {
        if(node == null)
        {
            return new Node(key, value, RED);
        }
        else if(key.compareTo(node.key) < 0)
        {
            node.left = put(node.left, key, value);
        }
        else if(key.compareTo(node.key) > 0)
        {
            node.right = put(node.right, key, value);
        }
        else if(key.compareTo(node.key) == 0)
        {
            node.value = value;
        }

        if(!isRed(node.left) && isRed(node.right)) node = rotateLeft(node);

        if(isRed(node.left) && isRed(node.left.left)) node = rotateRight(node);

        if(isRed(node.left) && isRed(node.right)) flipColors(node);
        return node;
    }

    private boolean isRed(Node node)
    {
        if(node == null) return false;

        return node.color == RED;
    }

    private Node rotateLeft(Node node)
    {
        //Orient a temporarily right leaning Red link, and make it left leaning

        assert isRed(node.right);
        Node t = node.right;
        node.right = t.left;
        t.left = node;
        t.color = node.color;
        node.color = RED;
        return t;

    }

    private Node rotateRight(Node node)
    {
        //Orient a left leaning Red link, and make it temporarily right leaning

        assert isRed(node.left);
        Node t = node.left;
        node.left = t.right;
        t.right = node;
        t.color = node.color;
        node.color = RED;
        return t;

    }

    private void flipColors(Node node)
    {
        assert !isRed(node);
        assert isRed(node.left);
        assert isRed(node.right);

        node.left.color = BLACK;
        node.right.color = BLACK;
        node.color = RED;
    }

    private Value get(Key key)
    {

        Node node = root;
        while(node != null)
        {
            if(node.key.compareTo(key) == 0)
            {
                return node.value;
            }
            else if(key.compareTo(node.key) < 0)
            {
                node = node.left;
            }
            else
            {
                node = node.right;
            }
        }

        return null;

    }

    private Node floor(Node node, Key key)
    {
        if(node == null) return null;

        if(node.key.compareTo(key) == 0)
            return node;

        if(key.compareTo(node.key) < 0)
            return floor(node.left, key);

        Node temp = floor(node.right, key);
        if(temp != null) return temp;
        return node;
    }

    private Key floor(Key key)
    {
        Node x = floor(root, key);

        if(x == null) return null;

        return x.key;
    }

    private Node ceiling(Node node, Key key)
    {
        if(node == null) return null;

        if(node.key.compareTo(key) == 0)
            return node;

        if(key.compareTo(node.key) > 0)
            return ceiling(node.right, key);

        Node temp = ceiling(node.left, key);
        if(temp != null) return temp;
        return node;
    }

    private Key ceiling(Key key)
    {
        Node x = ceiling(root, key);

        if(x == null) return null;

        return x.key;
    }

    private void preorder(Node node)
    {
        if(node != null)
        {
            System.out.print(node.key + "," + node.value + "   ");
            preorder(node.left);
            preorder(node.right);
        }
    }

    private Iterable<Key> keys()
    {
        QueueLinkedList<Key> q = new QueueLinkedList<Key>();
        inorder(q, root);
        return q;
    }

    private void inorder(QueueLinkedList<Key> q, Node node)
    {
        if(node == null) return;
        inorder(q, node.left);
        q.enqueue(node.key);
        inorder(q, node.right);
    }

    private Key min()
    {
        return min(root).key;
    }

    private Node min(Node node)
    {
        if(node == null) return null;
        if(node.left == null) return node;

        return min(node.left);
    }


    public static void main(String[] args)
    {
        RedBlackTree<String,Integer> rbt = new RedBlackTree<String, Integer>();
        rbt.put("udit", 10);
        rbt.put("jaya", 80);
        rbt.put("neeraj", 56);
        rbt.put("ujjwal", 67);
        rbt.put("suchitra", 45);
        rbt.put("ankit", 34);
        rbt.put("akshat", 99);
        rbt.put("shikha", 56);
        rbt.put("neeraj", 156);
        rbt.put("ujjwal", 267);
        rbt.preorder(rbt.root);

        System.out.println("\nGot : " + rbt.get("udit"));
        System.out.println("Got : " + rbt.get("ankit"));
        System.out.println("Got : " + rbt.get("neeraj"));
        System.out.println("Got : " + rbt.get("suchitra"));


        RedBlackTree<String,Integer> rbt_2 = new RedBlackTree<String, Integer>();
        rbt_2.put("S", 10);
        System.out.println("\nKeys Iterator : ");
        rbt_2.preorder(rbt_2.root);

        rbt_2.put("E", 10);
        System.out.println("\nKeys Iterator : ");
        rbt_2.preorder(rbt_2.root);

        rbt_2.put("A", 10);
        System.out.println("\nKeys Iterator : ");
        rbt_2.preorder(rbt_2.root);

        rbt_2.put("R", 10);
        System.out.println("\nKeys Iterator : ");
        rbt_2.preorder(rbt_2.root);

        rbt_2.put("C", 10);
        System.out.println("\nKeys Iterator : ");
        rbt_2.preorder(rbt_2.root);

        rbt_2.put("H", 10);
        System.out.println("\nKeys Iterator : ");
        rbt_2.preorder(rbt_2.root);

        rbt_2.put("X", 10);
        System.out.println("\nKeys Iterator : ");
        rbt_2.preorder(rbt_2.root);

        rbt_2.put("M", 10);
        System.out.println("\nKeys Iterator : ");
        rbt_2.preorder(rbt_2.root);

        rbt_2.put("P", 10);
        System.out.println("\nKeys Iterator : ");
        rbt_2.preorder(rbt_2.root);
    }
}
