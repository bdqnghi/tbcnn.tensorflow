package interval;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Optional;
import java.util.Queue;
import java.util.function.Consumer;

/**
 * This class augments left-leaning <strong>Red-Black-Tree</strong> with interval search operations.
 * The class uses left endpoint in an {@link Interval} to navigate search and insert,
 * and optimizes searches with the following two facts:
 * <ul>
 *  <li>left subtree can contain overlap <strong>only</strong> if max endpoint for that subtree is greater  than low endpoint of a key</li>
 *  <li>if the search went left and didn't find any overlaps, there <strong>cannot</strong> be any overlaps in the right subtree either.</li>
 * </ul>
 * 
 * <p>
 * The class offers following methods in Θ(log(N)): {@link #put(Interval, Object)} to insert new interval and associated value,
 * {@link #find(Interval)} to find value associated with the interval, {@link #findAnyOverlap(Interval)} to find any interval
 * in the tree overlapping passed interval.
 * The class also supports {@link #findAllOverlaps(Interval)} in Θ(R*log(N)) where R is the number of overlapping intervals.
 * </p>
 *
 * The class also supports pre-order iteration with {@link Iterable} over interval-value 
 * pairs and breadth-first iteration {@link #visit} that may apply an action on each node, 
 * in linear time.
 * Finally, it supports {@link #size()} in constant time.
 * 
 * <p>Delete method is <strong>not</strong> supported in this version and may be added at a later date.<p>
 * 
 * <strong> Notes: </strong>
 * <ul>
 *  <li> Null keys/values -> not allowed, will result with an {@link IllegalArgumentException} </li>
 *  <li> Duplicates  -> value is overridden on insert </li>
 * </ul>
 *
 *
 * @author dtemraz
 *
 * @param <K> comparable interval key
 * @param <V> type of value
 */
public class IntervalTree<K extends Comparable<? super K>, V> implements Iterable<IntervalValuePair<K, V>> {
    
    private static final byte RED = 1;    // newly inserted nodes are always referenced with red links
    private static final byte BLACK = 0;  // null links(including link to root) are by convention black
    
    private int size = 0; // number of nodes in tree
    private Node root;
    
    /**
     * Adds interval and value pair to this interval search tree, overriding values for duplicate keys.
     * 
     * @param interval key to add in the tree
     * @param value associated with the key to add in the tree
     * @return <em>true</em> if interval was not in the tree, <em>false</em> otherwise
     * @throws IllegalArgumentException if interval or value is null
     */
    public boolean put(Interval<K> interval, V value) {
        if (interval == null) {
            throw new IllegalArgumentException("interval must not be null");
        }
        if (value == null) {
            throw new IllegalArgumentException("value must not be null");
        }
        int sizeBefore = size(); // change in size will indicate that this was a new key
        root = put(interval, value, root);
        root.color = BLACK; // by convention, root nodes are black
        return sizeBefore < size();
    }
    
    /**
     * Adds all {@link IntervalValuePair} pairs from <em>intervals</em>in this tree, overriding values for duplicate keys.
     * 
     * @param intervals of interval-value pairs to add into Interval Search Tree
     * @throws NullPointerException if intervals are null
     */
    public void putAll(List<IntervalValuePair<K, V>> intervals) {
        if (intervals == null) {
            throw new IllegalArgumentException("intervals must not be null");
        }
        intervals.forEach(item -> put(item.getInterval(), item.getValue()));
    }

    /**
     * Returns value for the given interval if there is an exact match, empty optional otherwise.
     * 
     * @param interval key for which to find value in the tree
     * @return Optional value if interval exists, empty Optional otherwise
     * @throws NullPointerException if interval is null
     */
    public Optional<V> find(Interval<K> interval) {
        if (interval == null) {
            throw new IllegalArgumentException("interval must not be null");
        }
        return Optional.ofNullable(find(interval, root));
    }
    
    /**
     * Returns first found overlapping interval if there are any overlaps, empty Optional otherwise.
     *
     * @param interval key for which to find overlapping interval
     * @return Optional overlapping interval if it exists, empty Optional otherwise
     * @throws NullPointerException if interval is null
     */
    public Optional<IntervalValuePair<K, V>> findAnyOverlap(Interval<K> interval) {
        if (interval == null) {
            throw new IllegalArgumentException("interval must not be null");
        }
        return Optional.ofNullable(findAnyOverlap(interval, root));
    }
    
    /**
     * Returns all overlapping interval for the interval if there are any overlaps, empty list otherwise.
     *
     * @param interval key for which to find overlapping interval
     * @return List of overlapping intervals
     * @throws NullPointerException if interval is null
     */
    public List<IntervalValuePair<K, V>> findAllOverlaps(Interval<K> interval) {
        if (interval == null) {
            throw new IllegalArgumentException("interval must not be null");
        }
        List<IntervalValuePair<K, V>> overlaps = new ArrayList<>();
        findAllOverlaps(interval, root, overlaps);
        return overlaps;
    }
    
    /**
     * Visits each node in breadth-first order and applies action on interval-value
     * pair.
     * 
     * @param action to apply on each interval-value
     * @throws NullPointerException if interval is null
     */
    public void visit(Consumer<IntervalValuePair<K, V>> action) {
        if (action == null) {
            throw new IllegalArgumentException("action must not be null");
        }
        Queue<Node> nodes = new LinkedList<>();
        nodes.add(root);
        visit(action, nodes);
    }
    
    /**
     * Returns pre-order iterator over all intervals and their values in the tree.
     * 
     * @return pre-order iterator over all intervals and their values in the tree
     */
    @Override
    public Iterator<IntervalValuePair<K, V>> iterator() {
        List<IntervalValuePair<K, V>> items = new ArrayList<>();
        preOrder(root, items);
        return items.iterator();
    }
    
    /**
     * Returns number of intervals in this tree.
     * 
     * @return number of intervals in this tree
     */
    public int size() {
        return size;
    }
    
    // recursively adds key-value in the tree, maintaining the red black tree balance
    private Node put(Interval<K> key, V value, Node node) {
        // base case - found a place for new leaf
        if (node == null) { 
            size++;
            return new Node(key, value);
        }

        int comparison = key.compareTo(node.key);
        // value for duplicate key is overridden with new value
        if (comparison == 0) {
            node.value = value;
        }
        // try to find free leaf in the left subtree
        else if (comparison < 0) {
            node.left = put(key, value, node.left);
        }
        // otherwise check right subtree
        else {
            node.right = put(key, value, node.right);
        }
        // base case - balance subtree bottom up
        return balance(node);
    }
    
    // recursively searches for value that corresponds to a key
    private V find(Interval<K> key, Node node) {
        // base case - interval not found
        if (node == null) {
            return null;
        }
        int comparison = key.compareTo(node.key);
        // base case - interval found
        if (comparison == 0) {
            return node.value;
        }
        // since key is less than node key, check left subtree
        if (comparison < 0) {
            return find(key, node.left);
        }
        // otherwise check right subtree
        return find(key, node.right);
    }
   
    private IntervalValuePair<K, V> findAnyOverlap(Interval<K> key, Node node) {
        // base case - no overlapping node
        if (node == null) {
            return null;
        }
        // base case - found an overlap
        if (key.overlaps(node.key)) {
            return node;
        }
        // max right endpoint in left subtree should be greater than left endpoint in the key,
        // otherwise there can be no overlaps on the left
        if (node.leftCandidates(key)) {
            return findAnyOverlap(key, node.left);
        }
        
        return findAnyOverlap(key, node.right);
    }
    
    // recursively finds all overlapping intervals for the key interval
    private boolean findAllOverlaps(Interval<K> key, Node node, List<IntervalValuePair<K, V>> overlaps) {
        // base case - finished exploring a path
        if (node == null) {
            return false;
        }
        // found overlap
        boolean isOverlap = false;
        if (key.overlaps(node.key)) {
            overlaps.add(node);
            isOverlap = true;
        }
        
        // Fact 1. we go left if the max high endpoint is greater than or equal to key's low endpoint
        // max = 5, key = (7-15) -> skip, max = 10 -> check
        boolean leftSubtreeOverlaps = false;
        if (node.leftCandidates(key)) {
            leftSubtreeOverlaps = findAllOverlaps(key, node.left, overlaps);
        }
        
        // Fact 2. if we went left but there were no hits, than there can be no overlaps on the right either
        // this holds since right subtree has low endpoints which are greater than low endpoints in left subtree
        boolean rightSubtreeOverlaps = false;
        if (leftSubtreeOverlaps || !node.leftCandidates(key)) {
            rightSubtreeOverlaps = findAllOverlaps(key, node.right, overlaps);
        }
        
        return isOverlap || leftSubtreeOverlaps || rightSubtreeOverlaps;
    }
    
    // adds nodes in pre-order to items list
    private void preOrder(Node node, List<IntervalValuePair<K, V>> items) {
        if (node != null) {
            items.add(node);
            preOrder(node.left, items);
            preOrder(node.right, items);
        }
    }
    
    /// visits all nodes and applies action on each of them
    private void visit(Consumer<IntervalValuePair<K, V>> action, Queue<Node> nodes) {
        Node node = nodes.poll();
        // base case - no more nodes
        if (node == null) {
            return;
        }
        
        action.accept(node);
        
        // add child nodes if they exist
        if (node.left != null) {
            nodes.add(node.left);
        }
        if (node.right != null) {
            nodes.add(node.right);
        }
        
        visit(action, nodes);
    }

    /*
     * Red-Black-Tree balancing operations
     */
    
    private Node balance(Node node) {
        if (node.rightLeaning()) {
            node = leftRotation(node);
        }
        if (node.doubleRedLink()) {
            node = rightRotation(node);
        }
        if (node.hasRedChildren()) {
            flipColors(node);
        }
        node.subtreeMax = subtreeMax(node);
        return node;
    }

    private K max(K max1, K max2) {
        return max1.compareTo(max2) >= 0 ? max1 : max2;
    }

    // calculates subtreeMax for a node
    private K subtreeMax(Node node) {
        // must use value of right endpoint instead of previous max since rotation might move the child node which held previous max
        K localMax = node.key.getTo();
        // no children nodes so return own right endpoint
        if (node.left == null && node.right == null) {
            return localMax;
        }
        // both left and right subtree exists, find best max
        if (node.left != null && node.right != null) {
            return max(localMax, max(node.left.subtreeMax, node.right.subtreeMax));
        }
        // only right subtree exists
        if (node.left == null) {
            return max(localMax, node.right.subtreeMax);
        }
        // only left subtree exists
        return max(localMax, node.left.subtreeMax);
    }
    
    // applied on right-leaning red link
    private Node leftRotation(Node node) {
        
        /* fix(A)-> A                   B
         *           \                 / \
         *            B      ---->    A   C
         *           / \               \
         *     subtree  C             subtree   
         */        
        Node newRoot = node.right;
        node.right = newRoot.left;
        newRoot.left = node;
        
        newRoot.color = node.color;
        node.color = RED;
        
        fixMaxEndpoints(node, newRoot);
        return newRoot;
    }
    
    // applied on two successive left red links
    private Node rightRotation(Node node) {
        
        /* fix(C)-> C                 B
         *    red  /                 / \
         *        B         ---->   A   C
         *  red  / \                   /
         *      A   subtree        subtree  
         */
        Node newRoot = node.left;
        node.left = newRoot.right;
        newRoot.right = node;

        newRoot.color = node.color;
        node.color = RED;

        fixMaxEndpoints(node, newRoot);
        return newRoot;
    }
    
    private void flipColors(Node node) {
        
        /*          B.                R.   
         *          C                 C
         *      R. / \ R.  ---->  B. / \ B.     
         *        B   D             B   D
         */
        
        node.color = RED;
        node.left.color = BLACK;
        node.right.color = BLACK;
    }
    
    // nodes must retain max endpoints in it's subtree after rotations
    private void fixMaxEndpoints(Node node, Node root) {
        root.subtreeMax = subtreeMax(root);
        node.subtreeMax = subtreeMax(node);
    }
        
    private class Node implements IntervalValuePair<K, V> {
        
        private final Interval<K> key;
        private V value;
        
        private Node left;
        private Node right;

        private K subtreeMax;
        private byte color = RED;
        
        private Node(Interval<K> key, V value) {
            this.key = key;
            this.value = value;
            subtreeMax = key.getTo();
        }
        
        @Override
        public Interval<K> getInterval() {
            return key;
        }
        
        @Override
        public V getValue() {
            return value;
        }
        
        @Override
        public String toString() {
            String linkType = color == RED ? "RED" : "BLACK";
            return String.format("[key: %s, value: %s, max: %s, color: %s]", key, value, subtreeMax, linkType);
        }
        
        // returns true if the tree could contain overlapping nodes in the left subtree
        private boolean leftCandidates(Interval<K> key) {
            return left != null && left.subtreeMax.compareTo(key.getFrom()) >= 0;
        }
        
        /*
         *  Red-Black-Tree states that require balancing
         */
        
        // fixed with left rotation
        private boolean rightLeaning() {
            return isRed(right) && !isRed(left);
        }

        // fixed with right rotation
        private boolean doubleRedLink() {
            return isRed(left) && isRed(left.left);
        }
        
        // fixed with color flip of node and it's children
        private boolean hasRedChildren() {
            return isRed(left) && isRed(right);
        }
        
        private boolean isRed(Node node) {
            return node != null && node.color == RED;
        }
    }   
}
