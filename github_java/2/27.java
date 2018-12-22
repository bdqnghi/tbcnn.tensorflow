import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
import java.util.function.Function;

public class AVL {

    public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException {
        // ArrayLists for 3 input lines
        ArrayList<Integer> data_add = new ArrayList<Integer>();
        ArrayList<Integer> data_del = new ArrayList<Integer>();
        ArrayList<Integer> data_out = new ArrayList<Integer>();

        //Block of reading input data
        StringBuffer sb = null;
        Scanner in = new Scanner(new File("data.in"));
        sb = new StringBuffer();

        //1st line
        sb.append(in.nextLine()).append("\n");
        String[] numbers = sb.toString().split("\\s+");
        for (int i = 0; i < numbers.length; i++)
            data_add.add(i, Integer.valueOf(numbers[i]));
        sb = sb.delete(0, sb.length());

        AVLTree<Point> avl_tree = new AVLTree<Point>();
        BinarySearchTreeNode<Point> avl_node = null;

        for (int i = 0; i < data_add.size(); i = i + 2) {
            Point p = new Point();
            p.x = data_add.get(i);
            p.y = data_add.get(i + 1);
            avl_node = avl_tree.insert(avl_node, p);
        }

        avl_tree.BFS(avl_node);

        BinarySearchTreeNode<Point> temp = avl_node;
        while (temp.left != null) {
            temp = temp.left;
        }
        System.out.println(avl_tree.dist(temp.data));

        temp = avl_node;
        while (temp.right != null) {
            temp = temp.right;
        }
        System.out.println(avl_tree.dist(temp.data));

        Point p = new Point();
        p.x = data_add.get(data_add.size() - 2);
        p.y = data_add.get(data_add.size() - 1);

        temp = avl_tree.find(avl_node, p);
        System.out.println(temp + " " + temp.data.x);
        Point min = null;
//        System.out.println(min);
        if (temp.parent != null)
            min = temp.parent.data;
        if (temp.right != null){
            if (min == null)
                min = temp.right.data;
            else if (avl_tree.dist(min)>avl_tree.dist(temp.data))
                    min = temp.data;
        }

        if (temp.left != null){
            if (min == null)
                min = temp.left.data;
            else if (avl_tree.dist(min)>avl_tree.dist(temp.data))
                min = temp.data;
        }

        System.out.println("f"+min.x);
    }

    public static class BinarySearchTreeNode<E> {
        protected Point data;
        protected String data_out;
        protected BinarySearchTreeNode<E> parent;
        protected BinarySearchTreeNode<E> left;
        protected BinarySearchTreeNode<E> right;
        protected int height;

        //constructor
        public BinarySearchTreeNode(Point data) {
            this.data = data;
            this.parent = null;
            this.left = null;
            this.right = null;
        }

        public BinarySearchTreeNode(String data) {
            this.data_out = data;
            this.parent = null;
            this.left = null;
            this.right = null;
        }

        //constructor
        public BinarySearchTreeNode(Point data, BinarySearchTreeNode<E> parent, BinarySearchTreeNode<E> left, BinarySearchTreeNode<E> right) {
            this.data = data;
            this.parent = null;
            this.left = null;
            this.right = null;
            this.height = 1;
        }


//        public E getData(){
//            return data;
//        }
//
//        public void setData(E data){
//            this.data = data;
//        }

        public BinarySearchTreeNode<E> getParent() {
            return parent;
        }

        public void setParent(BinarySearchTreeNode<E> parent) {
            this.parent = parent;
        }

        public BinarySearchTreeNode<E> getLeft() {
            return left;
        }

        public void setLeft(BinarySearchTreeNode<E> childNode) {
            for (BinarySearchTreeNode<E> n = this; n != null; n = n.parent) {
                if (n == childNode) {
                    throw new IllegalArgumentException();
                }
            }

            if (this.left != null) {
                left.parent = null;
            }
            if (childNode != null) {
                childNode.parent = this;
            }
            this.left = childNode;
        }

        public BinarySearchTreeNode<E> getRight() {
            return right;
        }

        public void setRight(BinarySearchTreeNode<E> childNode) {
            for (BinarySearchTreeNode<E> n = this; n != null; n = n.parent) {
                if (n == childNode) {
                    throw new IllegalArgumentException();
                }
            }

            if (right != null) {
                right.parent = null;
            }
            if (childNode != null) {
                childNode.parent = this;
            }
            this.right = childNode;
        }

        public void removeFromParent() {
            if (parent != null) {
                if (parent != null) {
                    if (parent.left == this) {
                        parent.left = null;
                    } else if (parent.right == this) {
                        parent.right = null;
                    }
                    this.parent = null;
                }
            }
        }

        public int numChildren() {
            int count = 0;
            if (this.getLeft() != null)
                count++;
            if (this.getRight() != null)
                count++;
            return count;
        }

    }

    public static class AVLTree<E> {

        //function to compare values of objects
        Function<Object, Comparable> map = new Function<Object, Comparable>() {
            @Override
            public Comparable apply(Object t) {
                return (Comparable) t;
            }
        };

        public int dist(Point p) {
            int dist = (int) Math.round(Math.sqrt(Math.pow(p.getX(), 2) + Math.pow(p.getY(), 2)));
            return dist;
        }

        //add element to avl tree
        public BinarySearchTreeNode<E> insert(BinarySearchTreeNode<E> node, Point e) {
            if (node == null)
                return new BinarySearchTreeNode(e);
            else if (dist(node.data) > dist(e))
                node.left = insert(node.left, e);
            else if (dist(node.data) < dist(e))
                node.right = insert(node.right, e);
            else if (node.data.x > e.x)
                node.left = insert(node.left, e);
            else if (node.data.x < e.x)
                node.right = insert(node.right, e);
            else if (node.data.y > e.y)
                node.left = insert(node.left, e);
            else
                node.right = insert(node.right, e);

            return balance(node);
        }

        private BinarySearchTreeNode<E> balance(BinarySearchTreeNode<E> node) {
            fixheight(node);
            if (bfactor(node) == 2) {
                if (bfactor(node.right) < 0)
                    node.right = rightRotate(node.right);
                return leftRotate(node);
            }
            if (bfactor(node) == -2) {
                if (bfactor(node.left) > 0)
                    node.left = leftRotate(node.left);
                return rightRotate(node);
            }

            return node;
        }

        public int getHeight(BinarySearchTreeNode<E> node) {
            if (node != null)
                return node.height;
            else return -1;
        }

        private int bfactor(BinarySearchTreeNode<E> node) {
            return getHeight(node.right) - getHeight(node.left);
        }

        private void fixheight(BinarySearchTreeNode<E> node) {
            int hl = getHeight(node.left);
            int hr = getHeight(node.right);
            node.height = (hl > hr ? hl : hr) + 1;
        }

        private BinarySearchTreeNode<E> findmax(BinarySearchTreeNode<E> node) {
            while (node.right != null)
                node = node.right;
            return node;
        }

        //looking for predecessor in the avl tree
        private BinarySearchTreeNode<E> predecessor(BinarySearchTreeNode<E> node) {
            if (node.right == null)
                return node.right;
            node.right = predecessor(node.right);
            return balance(node);
        }


        public BinarySearchTreeNode<E> remove(BinarySearchTreeNode<E> node, E e) {
            if (node == null)
                return null;
            if (map.apply(node.data).compareTo(e) > 0)
                node.left = remove(node.left, e);
            else if (map.apply(node.data).compareTo(e) < 0)
                node.right = remove(node.right, e);
            else {
                BinarySearchTreeNode<E> r = node.left;
                BinarySearchTreeNode<E> q = node.right;
                if (r == null)
                    return q;
                BinarySearchTreeNode<E> max = findmax(r);
                max.left = predecessor(r);
                max.right = q;

                return balance(max);
            }
            return balance(node);
        }

        private BinarySearchTreeNode<E> rightRotate(BinarySearchTreeNode<E> node) {
            BinarySearchTreeNode<E> temp = node.left;
            node.left = temp.right;
            temp.right = node;
            fixheight(node);
            fixheight(temp);
            return temp;
        }

        private BinarySearchTreeNode<E> leftRotate(BinarySearchTreeNode<E> node) {
            BinarySearchTreeNode<E> temp = node.right;
            node.right = temp.left;
            temp.left = node;
            fixheight(node);
            fixheight(temp);
            return temp;
        }

        //visualisation of the avl tree
        public void BFS(BinarySearchTreeNode<E> node) {
            Queue<BinarySearchTreeNode<E>> q = new LinkedList<BinarySearchTreeNode<E>>();
            if (node == null)
                return;
            q.add(node);
            int level = 1;
            int h = -2;
            String null_s = "@"; // definition of null node;
            for (int i = 0; i < Math.pow(2, getHeight(node) + 1) - 1; i++) {
                BinarySearchTreeNode<E> n = (BinarySearchTreeNode<E>) q.remove();
                if (Math.log(level) / Math.log(2) % 1 == 0) {
                    System.out.println();
                    h++;
                    for (int j = (int) (Math.pow(2, getHeight(node) - Math.log(level)
                            / Math.log(2))) - 1; j > 0; j--) {
                        System.out.print(" ");
                    }
                } else {
                    for (int j = 0; j < (Math.pow(2, getHeight(node) - h)) - 1; j++)
                        System.out.print(" ");
                }
                if (n != null) {
                    System.out.print(n.data);
                    level++;
                }
                if (n.left != null)
                    q.add(n.left);
                else
                    q.add(new BinarySearchTreeNode(null_s));
                if (n.right != null)
                    q.add(n.right);
                else
                    q.add(new BinarySearchTreeNode(null_s));
            }
            System.out.println();
        }

        public BinarySearchTreeNode<E> find(BinarySearchTreeNode<E> n, Point e) {
            BinarySearchTreeNode<E> current = recursiveSearch(n, e);
            if (current != null)
                return current;
            else
                return null;
        }

        public BinarySearchTreeNode<E> recursiveSearch(BinarySearchTreeNode<E> node, Point e) {

            if (node == null)
                return null;


            if (node.data.x == e.x && node.data.y == e.y) {
                System.out.println("Here" + node.data.x + " " + node.data.y);
                return node;
            }

            BinarySearchTreeNode<E> temp = null;
            if (dist(node.data) > dist(e))
                temp = recursiveSearch(node.left, e);
            else if (dist(node.data) < dist(e))
                temp = recursiveSearch(node.right, e);
            else if (node.data.x > e.x)
                temp = recursiveSearch(node.left, e);
            else if (node.data.x < e.x)
                temp = recursiveSearch(node.right, e);
            else if (node.data.y > e.y)
                temp = recursiveSearch(node.left, e);
            else if (node.data.y < e.y)
                temp = recursiveSearch(node.right, e);
            else if (node.data.y > e.y)
                temp = recursiveSearch(node.left, e);


            return temp;
        }
    }

}