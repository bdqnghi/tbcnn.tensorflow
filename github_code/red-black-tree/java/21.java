package chapter13;

/**
 * @Author : jnu_mrc jnu_mrc1990@163.com
 * @Date : Created in 17:04 2018/2/8
 */
public class RedBlackTree<T> {

    public static void main(String[] args) {
        RedBlackTree<Integer> tree = new RedBlackTree<>();

        int[] arr = new int[]{41, 38, 31, 12, 19, 8};
        for (int i : arr) {
            tree.insert(i);
            tree.inOrderTreeWalk(tree.root);
            System.out.println("after insert "+i);
        }
        int[] arr1 = new int[]{8, 12, 19, 31, 38, 41};
        for (int i : arr1) {
            Node<Integer> node = tree.find(i);
            if (node != tree.nil) {
                tree.delete(node);
            } else {
                System.out.println("delete fail key=" + i);
            }
            System.out.println("after delete "+i);
            tree.inOrderTreeWalk(tree.root);
        }
        System.out.println(tree.root == tree.nil);
    }

    private Node<T> nil;
    private Node<T> root;

    public RedBlackTree() {
        nil = new Node<T>();
        nil.color = Color.BLACK;
        root = nil;
    }

    public void inOrderTreeWalk(Node<T> x){
        if (x != nil){
            System.out.print(x.key +", ");
            inOrderTreeWalk(x.left);
            inOrderTreeWalk(x.right);
        }else {
            System.out.print("nil, ");
        }
    }

    private void leftRotate(Node<T> x) {
        Node<T> y = x.right;
        x.right = y.left;
        if (y.left != nil) {
            y.left.p = x;
        }
        y.p = x.p;
        if (x.p == nil) {
            root = y;
        } else if (x == x.p.left) {
            x.p.left = y;
        } else {
            x.p.right = y;
        }
        y.left = x;
        x.p = y;
    }

    private void rightRotate(Node<T> y) {
        Node<T> x = y.left;
        y.left = x.right;
        if (x.right != nil) {
            x.right.p = y;
        }
        x.p = y.p;
        if (y.p == nil) {
            root = x;
        } else if (y == y.p.left) {
            y.p.left = x;
        } else {
            y.p.right = x;
        }
        x.right = y;
        y.p = x;
    }

    public void insert(T z) {
        Node<T> y = nil;
        Node<T> x = root;
        while (x != nil) {
            y = x;
            if (x.key.compareTo(z) > 0) {
                x = x.left;
            } else {
                x = x.right;
            }
        }
        Node<T> newNode = new Node<>();
        newNode.key = (Comparable<T>) z;
        newNode.p = y;
        if (y == nil) {
            root = newNode;
        } else if (y.key.compareTo(z) > 0) {
            y.left = newNode;
        } else {
            y.right = newNode;
        }
        newNode.left = nil;
        newNode.right = nil;
        newNode.color = Color.RED;
        insertFixUp(newNode);
    }

    private void transplant(Node<T> u, Node<T> v) {
        if (u.p == nil) {
            root = v;
        } else if (u == u.p.left) {
            u.p.left = v;
        } else {
            u.p.right = v;
        }
        v.p = u.p;
    }

    private Node<T> find(T z) {
        Node<T> x = root;
        while (x != nil) {
            int r = x.key.compareTo(z);
            if (r == 0) {
                break;
            } else if (r > 0) {
                x = x.left;
            } else {
                x = x.right;
            }
        }
        return x;
    }

    public void delete(T z){
        Node<T> node = find(z);
        if(node != nil){
            delete(node);
        }
    }

    private void delete(Node<T> z) {
        Node<T> y = z, x;
        Color yOriginalColor = y.color;
        if (z.left == nil) {
            x = z.right;
            transplant(z, z.right);
        } else if (z.right == nil) {
            x = z.left;
            transplant(z, z.left);
        } else {
            y = minimum(z.right);
            yOriginalColor = y.color;
            x = y.right;
            if (y.p == z) {
                x.p = y;
            } else {
                transplant(y, y.right);
                y.right = z.right;
                y.right.p = y;
            }
            transplant(z, y);
            y.left = z.left;
            y.left.p = y;
            y.color = z.color;
        }
        if (yOriginalColor == Color.BLACK) {
            deleteFixUp(x);
        }
    }

    private void deleteFixUp(Node<T> x) {
        while (x != root && x.color == Color.BLACK) {
            if (x == x.p.left) {
                Node<T> w = x.p.right;
                if (w.color == Color.RED) {
                    w.color = Color.BLACK;
                    x.p.color = Color.RED;
                    leftRotate(x.p);
                    w = x.p.right;
                }
                if (w.left.color == Color.BLACK && w.right.color == Color.BLACK) {
                    w.color = Color.RED;
                    x = x.p;
                } else {
                    if (w.right.color == Color.BLACK) {
                        w.left.color = Color.BLACK;
                        w.color = Color.RED;
                        rightRotate(w);
                        w = x.p.right;
                    }
                    w.color = x.p.color;
                    x.p.color = Color.BLACK;
                    w.right.color = Color.BLACK;
                    leftRotate(x.p);
                    x = root;
                }
            } else {
                Node<T> w = x.p.left;
                if (w.color == Color.RED) {
                    w.color = Color.BLACK;
                    x.p.color = Color.RED;
                    leftRotate(x.p);
                    w = x.p.left;
                }
                if (w.right.color == Color.BLACK && w.left.color == Color.BLACK) {
                    w.color = Color.RED;
                    x = x.p;
                } else {
                    if (w.left.color == Color.BLACK) {
                        w.right.color = Color.BLACK;
                        w.color = Color.RED;
                        rightRotate(w);
                        w = x.p.left;
                    }
                    w.color = x.p.color;
                    x.p.color = Color.BLACK;
                    w.left.color = Color.BLACK;
                    leftRotate(x.p);
                    x = root;
                }
            }
        }
        x.color = Color.BLACK;
    }

    public Node<T> minimum(Node<T> x) {
        while (x.left != nil) {
            x = x.left;
        }
        return x;
    }

    private enum Color {
        RED, BLACK;
    }

    private void insertFixUp(Node<T> z) {
        while (z.p.color == Color.RED) {
            if (z.p == z.p.p.left) {
                Node<T> y = z.p.p.right;
                if (y.color == Color.RED) {
                    z.p.color = Color.BLACK;
                    y.color = Color.BLACK;
                    z.p.p.color = Color.RED;
                    z = z.p.p;
                } else {
                    if (z == z.p.right) {
                        z = z.p;
                        leftRotate(z);
                    }
                    z.p.color = Color.BLACK;
                    z.p.p.color = Color.RED;
                    rightRotate(z.p.p);
                }
            } else {
                Node<T> y = z.p.p.left;
                if (y.color == Color.RED) {
                    z.p.color = Color.BLACK;
                    y.color = Color.BLACK;
                    z.p.p.color = Color.RED;
                    z = z.p.p;
                } else {
                    if (z == z.p.left) {
                        z = z.p;
                        rightRotate(z);
                    }
                    z.p.color = Color.BLACK;
                    z.p.p.color = Color.RED;
                    leftRotate(z.p.p);
                }
            }
        }
        root.color = Color.BLACK;
    }

    private static class Node<T> {
        private Color color;
        private Comparable<T> key;
        private Node<T> p;
        private Node<T> left;
        private Node<T> right;
    }
}
