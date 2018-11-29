import java.awt.*;
import java.util.*;

/**
 * Created by D on 5/28/2017.
 */
public class lineSweep {
    public static void main(String[] args) {
        int n = 5;
        Line[] lines = new Line[n];
        lines[0] = new Line(new Point(1, 4), new Point(5, 4));
        lines[1] = new Line(new Point(2, 6), new Point(12, 1));
        lines[2] = new Line(new Point(3, 1), new Point(12, 4));
        lines[3] = new Line(new Point(8, 6), new Point(12, 6));
        lines[4] = new Line(new Point(8, 1), new Point(10, 1));

//    Point[] points = new Point[n * 2];
        PriorityQueue<Point> heap = new PriorityQueue<>(10, new Comparator<Point>() {

            public int compare(Point o1, Point o2) {
                return Double.compare(o1.x, o2.x);
            }
        });

        for (int i = 0; i < lines.length; i++) {
            heap.add(lines[i].left);
            heap.add(lines[i].right);
        }

        ArrayList<Integer> d = new ArrayList<>();
        Iterator<Point> iter = heap.iterator();
        AVLTree avlTree = new AVLTree();
        boolean intersection = false;
        while (iter.hasNext()) {
            Point point = iter.next();
            if (point.left) {

                avlTree.insert(point.line);

                if (avlTree.search(point.line).left != null && doIntersect(point.line.left, point.line.right, ((Line) avlTree.search(point.line).left.element).left, ((Line) avlTree.search(point.line).left.element).right)) {
                    intersection = true;
                    break;
                }
                if (avlTree.search(point.line).right != null && doIntersect(point.line.left, point.line.right, ((Line) avlTree.search(point.line).right.element).left, ((Line) avlTree.search(point.line).right.element).right)) {
                    intersection = true;
                    break;
                }
            } else {
                if (avlTree.search(point.line).left != null && avlTree.search(point.line).right != null && doIntersect(((Line) avlTree.search(point.line).left.element).left, ((Line) avlTree.search(point.line).left.element).right, ((Line) avlTree.search(point.line).right.element).left, ((Line) avlTree.search(point.line).right.element).right)) {
                    intersection = true;
                    break;
                }
                avlTree.delete(point.line);  // Delete from tree
            }
        }
        if (intersection)
            return;
        else
            return;
    }

    static class Point {
        double x, y;
        boolean left;
        Line line;

        Point(double x, double y) {
            this.x = x;
            this.y = y;
        }
    }

    static class Line implements Comparable {
        Point left, right;

        Line(Point left, Point right) {
            left.line = this;
            right.line = this;
            left.left = true;
            right.left = false;
            this.left = left;
            this.right = right;
        }

        public int compareTo(Object otherLine) throws ClassCastException {
            double otherY = ((Line) otherLine).left.y;
            return (int) (this.left.y - otherY);
        }
    }


    // Given three colinear points p, q, r, the function checks if
    // point q lies on line segment 'pr'
    static boolean onSegment(Point p, Point q, Point r) {
        if (q.x <= Math.max(p.x, r.x) && q.x >= Math.min(p.x, r.x) &&
                q.y <= Math.max(p.y, r.y) && q.y >= Math.min(p.y, r.y))
            return true;

        return false;
    }

    // To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
    static int orientation(Point p, Point q, Point r) {
        // See http://www.geeksforgeeks.org/orientation-3-ordered-points/
        // for details of below formula.
        double val = (q.y - p.y) * (r.x - q.x) -
                (q.x - p.x) * (r.y - q.y);

        if (val == 0) return 0;  // colinear

        return (val > 0) ? 1 : 2; // clock or counterclock wise
    }

    // The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
    static boolean doIntersect(Point p1, Point q1, Point p2, Point q2) {
        // Find the four orientations needed for general and
        // special cases
        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);

        // General case
        if (o1 != o2 && o3 != o4)
            return true;

        // Special Cases
        // p1, q1 and p2 are colinear and p2 lies on segment p1q1
        if (o1 == 0 && onSegment(p1, p2, q1)) return true;

        // p1, q1 and p2 are colinear and q2 lies on segment p1q1
        if (o2 == 0 && onSegment(p1, q2, q1)) return true;

        // p2, q2 and p1 are colinear and p1 lies on segment p2q2
        if (o3 == 0 && onSegment(p2, p1, q2)) return true;

        // p2, q2 and q1 are colinear and q1 lies on segment p2q2
        if (o4 == 0 && onSegment(p2, q1, q2)) return true;

        return false; // Doesn't fall in any of the above cases
    }

    public static class AVLTree {

        // Each AVLtree object is (a header of) an AVL-tree.
        // This AVL-tree is represented simply by a reference to its root node (root).
        private Node root;

        public AVLTree() {
            // Construct an empty AVL-tree.
            this.root = null;
        }

        public Node search(Comparable target) {
            // Find which if any node of this AVL-tree contains an element equal to target.
            // Return a link to that node (or null if there is none).
            int direction = 0;  // ... 0 for here, < 0 for left, > 0 for right
            Node curr = this.root;
            for (; ; ) {
                if (curr == null)
                    return null;
                direction = target.compareTo(curr.element);
                if (direction == 0)
                    return curr;
                if (direction < 0)
                    curr = curr.left;
                else  // direction > 0
                    curr = curr.right;
            }
        }

        public void insert(Comparable elem) {
            // Insert the element elem in this AVL-tree.
            Node ins = insertBST(elem);
            if (ins != null)
                rebalance(ins);
        }

        private Node insertBST(Comparable elem) {
            // Insert the element elem in this AVL-tree, treating it as an ordinary
            // binary search tree. Return a link to the newly-inserted leaf node, or null
            // if no node was inserted.
            int direction = 0;  // ... 0 for here, < 0 for left, > 0 for right
            Node parent = null, curr = root;
            for (; ; ) {
                if (curr == null) {
                    Node ins = new Node(elem, parent);
                    if (root == null)
                        root = ins;
                    else {
                        if (direction < 0)
                            parent.left = ins;
                        else  // direction > 0
                            parent.right = ins;
                    }
                    return ins;
                }
                direction = elem.compareTo(curr.element);
                if (direction == 0)
                    return null;
                parent = curr;
                if (direction < 0)
                    curr = curr.left;
                else  // direction > 0
                    curr = curr.right;
            }
        }

        private Node deletee = null;  // link to node just deleted
        // (accessed only by delete and auxiliary methods)

        public void delete(Comparable elem) {
            // Delete the element elem from this AVL-tree.
            deleteBST(elem);
            if (deletee != null) {
                rebalance(deletee);
                deletee = null;
            }
        }

        private void deleteBST(Comparable elem) {
            // Delete the element elem in this AVL-tree, treating it as an ordinary
            // binary search tree.
            int direction = 0;  // ... 0 for here, < 0 for left, > 0 for right
            Node curr = this.root;
            for (; ; ) {
                if (curr == null)
                    return;
                direction = elem.compareTo(curr.element);
                if (direction == 0) {
                    Node modified = deleteTopmost(curr);
                    Node parent = curr.parent;
                    if (curr == this.root)
                        this.root = modified;
                    else if (curr == parent.left)
                        parent.left = modified;
                    else  // curr == parent.right
                        parent.right = modified;
                    if (modified != null) modified.parent = parent;
                    return;
                }
                if (direction < 0)
                    curr = curr.left;
                else  // direction > 0
                    curr = curr.right;
            }
        }

        private Node deleteTopmost(Node top) {
            // Delete the topmost element in the subtree whose topmost node is top.
            // Return a link to the modified subtree.
            if (top.left == null) {
                deletee = top;
                return top.right;
            } else if (top.right == null) {
                deletee = top;
                return top.left;
            } else {  // top has both a left child and a right child
                top.element = top.right.getLeftmost();
                top.right = deleteLeftmost(top.right);
                return top;
            }
        }

        private Node deleteLeftmost(Node top) {
            // Delete the leftmost node of the (nonempty) subtree
            // whose topmost node is top.
            // Return a link to the modified subtree.
            Node curr = top;
            while (curr.left != null)
                curr = curr.left;
            deletee = curr;
            if (curr == top)
                return top.right;
            else {
                curr.parent.left = curr.right;
                return top;
            }
        }

        private void rebalance(Node node) {
            // Rebalance this AVL-tree, following insertion or deletion of node.
            Node ancestor = node;
            while (ancestor != root) {
                ancestor = ancestor.parent;
                ancestor.setHeight();
                if (!ancestor.isHeightBalanced()) {
                    Node greatAncestor = ancestor.parent;
                    Node rotated = rotate(ancestor);
                    if (ancestor == root)
                        setRoot(rotated);
                    else if (ancestor == greatAncestor.left)
                        greatAncestor.setLeft(rotated);
                    else  // ancestor == greatgrandparent.right
                        greatAncestor.setRight(rotated);
                    ancestor = rotated;
                }
            }
        }

        private Node rotate(Node grandparent) {
            // Rotate the node grandparent, the node parent (grandparent's higher child),
            // and the node child (parent's higher child).
            // After an insertion, all three nodes are ancestors of the inserted node.
            // After a deletion, only grandparent is an ancestor of the deleted node.
            Node parent = grandparent.higherChild();
            Node child = parent.higherChild();
            Node a, b, c;
            Node t1, t2, t3, t4;
            if (child == parent.left && parent == grandparent.left) {
                a = child;
                b = parent;
                c = grandparent;
                t1 = child.left;
                t2 = child.right;
                t3 = parent.right;
                t4 = grandparent.right;
            } else if (child == parent.right && parent == grandparent.left) {
                a = parent;
                b = child;
                c = grandparent;
                t1 = parent.left;
                t2 = child.left;
                t3 = child.right;
                t4 = grandparent.right;
            } else if (child == parent.right && parent == grandparent.right) {
                a = grandparent;
                b = parent;
                c = child;
                t1 = grandparent.left;
                t2 = parent.left;
                t3 = child.left;
                t4 = child.right;
            } else {  // child == parent.left && parent == grandparent.right
                a = grandparent;
                b = child;
                c = parent;
                t1 = grandparent.left;
                t2 = child.left;
                t3 = child.right;
                t4 = parent.right;
            }
            a.setLeft(t1);
            a.setRight(t2);
            a.setHeight();
            c.setLeft(t3);
            c.setRight(t4);
            c.setHeight();
            b.setLeft(a);
            b.setRight(c);
            b.setHeight();
            return b;
        }

        private void setRoot(Node newRoot) {
            // Make newRoot this AVL-tree's root node.
            this.root = newRoot;
            newRoot.parent = null;
        }

    }

    public static class Node {

        // Each Node object is an AVL-tree node.
        // This node is represented by its element (element) together with
        // references to its left child (left), its right child (right), and
        // its parent (parent), and its height (height).
        // For every element x stored in the subtree at left:
        //    x.compareTo(element) < 0
        // For every element y stored in the subtree at right:
        //    y.compareTo(element) > 0
        private Comparable element;
        private Node left, right, parent;
        private int height;

        public Node(Comparable elem, Node parent) {
            // Construct an AVL-tree node with element elem and no children.
            this.element = elem;
            this.left = null;
            this.right = null;
            this.parent = parent;
            this.height = 0;
        }

        private Comparable getLeftmost() {
            // Return the element in the leftmost node of the (nonempty) subtree
            // whose topmost node is this.
            Node curr = this;
            while (curr.left != null)
                curr = curr.left;
            return curr.element;
        }

        private static int sizeOfSubtree(Node top) {
            // Return the size of the subtree whose topmost node is top.
            if (top == null)
                return 0;
            else
                return 1 + sizeOfSubtree(top.left) + sizeOfSubtree(top.right);
        }

        private void setLeft(Node child) {
            // Make child the left child of this node.
            left = child;
            if (child != null) child.parent = this;
        }

        private void setRight(Node child) {
            // Make child the right child of this node.
            right = child;
            if (child != null) child.parent = this;
        }

        private void setHeight() {
            // Recompute the height of this node (assuming that the heights of its
            // children are accurate).
            height = Math.max(getHeight(left), getHeight(right)) + 1;
        }

        private static int getHeight(Node node) {
            // Return the height of node.
            return (node == null ? -1 : node.height);
        }

        private Node higherChild() {
            // Return the child of this node with the greater height.
            // If the heights are equal, return either child.
            return (getHeight(left) >= getHeight(right) ? left : right);
        }

        private boolean isHeightBalanced() {
            // Return true if and only if this node is height-balanced, i.e.,
            // the heights of its children differ by at most one.
            int balance = getHeight(left) - getHeight(right);
            return (balance >= -1 && balance <= +1);
        }

    }
}
