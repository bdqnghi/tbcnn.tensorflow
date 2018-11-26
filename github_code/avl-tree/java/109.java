import java.util.LinkedList;
import java.util.Queue;

/**
 * @class AVLTree class
 * @brief The AVLTree is a self-balancing generic binary search tree.
 * @description In this data structure the heights of the two 
 * child subtrees of any node differ by at most one; if at any time 
 * they differ by more than one, rebalancing is done to restore this 
 * property. 
 * Lookup, insertion, and deletion all take O(log n) time in both the 
 * average and worst cases, where n is the number of nodes in the tree 
 * prior to the operation. Insertions and deletions may require the 
 * tree to be rebalanced by one or more tree rotations.
 * 
 * @author Christian Kusan
 * @param <R> the generic datatype R
 */
public class AVLTree<R extends Comparable<R>> {
    
    
    // -- attributes --------------------------
    
    /** The root node. */
    private Node<R> _root;
    
    /**
     * @class Node class
     * @brief Describes one single node in generic tree structure.
     * @param <T> the generic datatype T
     */
    private class Node<T extends Comparable<T>> implements Comparable<Node<T>> {
 
	private T _data;
	private int _depth;
        private int _level;
        
        private Node<T> _left;
	private Node<T> _right;
	
	public Node(T data) {
            this(data, null, null);
	}
 
	public Node(T data, Node<T> left, Node<T> right) {
	
            _data = data;
            _left = left;
            _right = right;
	
            if (null == left && null == right)
                _depth = 1;
            else if (null == left)
                _depth = 1 + right._depth;
            else if (null == right)
                _depth = 1 + left._depth;
            else
                _depth = 1 + Math.max(left._depth, right._depth);
	}
 
	@Override
	public int compareTo(Node<T> other) {
            return this._data.compareTo(other._data);
	}
 
	@Override
	public String toString() {
            return "Level " + _level + ": " + _data;
	}
 
    }
    
    
    // -- static ------------------------------
    
    /**
     * @brief Starts the application.
     * @param args the command line arguments
     */
    public static void main(String[] args){
            
        AVLTree<Integer> intTree = new AVLTree<>();
	
        for (int i = 0; 10 > i; ++i)
            intTree.insertData(i);

        intTree.traverse(Order.LEVELORDER);
    }
    
    
    // -- initializer -------------------------
    
    /**
     * @brief The default constructor.
     */
    public AVLTree() {
        _root = null;
    }
    
    
    // -- methods -----------------------------
    
    /**
     * @brief Balances a tree.
     * @param node the head of tree
     * @return the current node
     */
    private Node<R> balance(Node<R> node){
        
        switch (isBalanced(node)) {
            case -1:
                return rotateRight(node);
            case 1:
                return rotateLeft(node);
	    default: 
                return node;
        }
    }
    
    /**
     * @brief Checks whether the tree contains a specific data object.
     * @param data the data object
     * @return true if the tree contains the object, otherwise false
     */
    public boolean contains(R data) {
        
        /* 
        Here we can use the binary search method:
        Recursive division while we arrived at the end of tree 
        or found the data object.
        */
        
        Node<R> node = _root;
		
        while (null != node) 
            if (0 == node._data.compareTo(data))
                return true;
            else if (0 < node._data.compareTo(data))
                node = node._left;
            else
                node = node._right;
        
        return false;
    }
    
    /**
     * @brief Gets the depth of a tree.
     * @param head the root node of the tree
     * @return the tree depth represents by a number
     */
    private int depth(Node<R> head) {
    
        return (null == head) ? 0 : head._depth;
    }
    
    /**
     * @brief Inorder traverse.
     * @param node the current node
     */
    private void inOrderTraverse(Node<R> node){
        
        if(null == node)
            return;
        
        inOrderTraverse(node._left);
        
        System.out.println(node._data);
        
        inOrderTraverse(node._right); 
    }
    
    /**
     * @brief Inserts data.
     * @param data the data object
     * @return the current node
     */
    private Node<R> insert(R data) {
        
        _root = insert(_root, data);
	
        // balancing
        
        switch (isBalanced(_root)) {
            case -1:
                _root = rotateRight(_root);
                break;
            case 1:
                _root = rotateLeft(_root);
                break;
            // default case isn't necessary here    
        }
	
        return _root;
    }
    
    /**
     * @brief Inserts a new node by recursive process.
     * @param node the current node
     * @param data the data object
     * @return the next current node
     */
    private Node<R> insert(Node<R> node, R data) {
        
        if (null == node)
            return new Node<>(data);
	
        /*
        Instead of using the compareTo method of node class we 
        work with compareto of T - its the simplest solution. 
        Otherwise we had to create a new node instance in each 
        iteration: 
                    node.compareTo(new Node(data))
        */
        
        if (0 < node._data.compareTo(data)) 
            node = new Node<>(node._data, insert(node._left, data), node._right);
	else if (0 > node._data.compareTo(data))
            node = new Node<>(node._data, node._left, insert(node._right, data));
	
        // rebalancing
        return balance(node);
    }
    
    /**
     * @brief Inserts data.
     * @param data the data object
     */
    public void insertData(R data){
        
        /* 
        This is the facade method, we don't want to export 
        the non-public type Node<R> (data hiding).
        Try it: Change the access modifier of insert-method to public. 
        Now your IDE at least should give a warning.
        */
        
        insert(data);
    }
    
    /**
     * @brief Checks whether a tree is equals in depth 
     * level on both sides.
     * @param head the root node of the tree
     * @return a number that defines whether the tree is balanced or not.<br />
     * <ul>
     *  <li>0: the tree is balanced</li>
     *  <li>-1: the tree is deeper on the left side</li>
     *  <li>1: the tree is deeper on the right side</li>
     * </ul>
     */
    private int isBalanced(Node<R> head) {
        
        int leftDepth = depth(head._left);
        int rightDepth = depth(head._right);
	
        if(2 <= leftDepth - rightDepth)
            return -1;
	else if (-2 >= leftDepth - rightDepth)
            return 1;
	
        return 0;
    }

    /**
     * @brief Traverses through the tree by using level order.
     */
    private void levelOrderTraverse() {
        
        _root._level = 0;
        Queue<Node<R>> queue = new LinkedList<>();
        queue.add(_root);
	
        while (!queue.isEmpty()) {
	
            Node<R> node = queue.poll();
            System.out.println(node);
            int level = node._level;
            
            Node<R> leftNode = node._left;
            Node<R> rightNode = node._right;
	
            if (null != leftNode) {
                leftNode._level = 1 + level;
                queue.add(leftNode);
            }
	
            if (null != rightNode) {
                rightNode._level = 1 + level;
                queue.add(rightNode);
            }
        }
    }
    
    /**
     * @brief Gets the highest value in tree structure.
     * @return the object of generic type R if the tree is not empty, 
     * otherwise null
     */
    public R maxValue() {
        
        if(null != _root)
            return maxValue(_root);

        return null;
    }
    
    /**
     * @brief Gets the highest value in tree structure by 
     * recursive process.
     * @return the object of generic type R
     */
    private R maxValue(Node<R> node) {
        
        if(null == node._right)
            return node._data;
        
        return maxValue(node._right);
    }
 
    /**
     * @brief Gets the least value in tree structure.
     * @return the object of generic type R if the tree is not empty, 
     * otherwise null
     */
    public R minValue() {
        
        if(null != _root)
            return minValue(_root);
        
        return null;
    }
    
    /**
     * @brief Gets the least value in tree structure 
     * by recursive process.
     * @return the object of generic type R
     */
    private R minValue(Node<R> node) {
        
        if(null == node._left)
            return node._data;
        
        return minValue(node._left);
    }
 
    /**
     * @brief Postorder traverse.
     * @param node the current node
     */
    private void postOrderTraverse(Node<R> node){
    
        if (null == node)
            return;
            
        postOrderTraverse(node._left);
        postOrderTraverse(node._right); 
        
        System.out.println(node._data);
    }
    
    /**
     * @brief Preorder traverse
     * @param node the current node
     */
    private void preOrderTraverse(Node<R> node){
    
        if(null == node)
            return;
        
        System.out.println(node._data);
        
        preOrderTraverse(node._left);
        preOrderTraverse(node._right); 
    }
    
    /**
     * @brief Removes data.
     * @param data the data object
     */
    public void remove(R data) {
        _root = remove(_root, data);
    }
	
    /**
     * @brief Removes a node by recursive process.
     * @param node the root of the tree
     * @param data the data to be deleted
     * @return the current node
     */
    private Node<R> remove(Node<R> node, R data) {
        
        if(null == node)
            return null;
        
        if(0 > data.compareTo(node._data))
            node._left = remove(node._left, data);
        else if(0 < data.compareTo(node._data))
            node._right = remove(node._right, data);
        else {
            
            // no children
            if(null == node._left && null == node._right)
                return null;
	
            // one child - guaranteed to be balanced
            if(null == node._left)
                return node._right;
            
            if(null == node._right)
                return node._left;
			
            // two children
            R smallestValue = minValue(node._right);
            node._data = smallestValue;
            node._right = remove(node._right, smallestValue);
        }
        
        // rebalancing
        return balance(node);
    }
    
    /**
     * @brief Rotates to the left.
     * @param node the current node
     * @return the right node of current
     */
    private Node<R> rotateLeft(Node<R> node) {
        
        Node<R> leftNode = node._left;
        Node<R> rightNode = node._right;
        
        Node<R> rightLeftNode = rightNode._left;
        Node<R> rightrightNode = rightNode._right;
        
        node = new Node<>(node._data, leftNode, rightLeftNode);
        rightNode = new Node<>(rightNode._data, node, rightrightNode);
        
        return rightNode;
    }
    
    /**
     * @brief Rotates to the right.
     * @param node the current node
     * @return the left node of current
     */
    private Node<R> rotateRight(Node<R> node) {

        Node<R> leftNode = node._left;
        Node<R> rightNode = node._right;
        
        Node<R> leftLeftNode = leftNode._left;
        Node<R> leftRightNode = leftNode._right;
        
        node = new Node<>(node._data, leftRightNode, rightNode);
        leftNode = new Node<>(leftNode._data, leftLeftNode, node);
        
        return leftNode;
    }
    
    /**
     * @brief Returns itself as string.
     * @return a string that describes the root node
     */
    @Override
    public String toString() {
        return _root.toString();
    }
    
    /**
     * @brief Traverses through the tree structure.
     * @param order the traverse order
     */
    void traverse(Order order){
        /*
        This method has the access modifier package because the 
        enum is non-public. So this method is only useable in this 
        package or directory.
        Another option would be to write the enum in an extra file 
        with public access modifier. 
        */
        
        switch(order){
            case INORDER:
                inOrderTraverse(_root);
                break;
            case LEVELORDER:
                levelOrderTraverse();
                break;
            case PREORDER:
                preOrderTraverse(_root);
                break;
            case POSTORDER:
                postOrderTraverse(_root);
        }
    }
}

/**
 * @class Order enumeration class
 * @brief An enumeration of possible order types to traverses the 
 * tree structure.
 * @author Christian Kusan
 */
enum Order {
    INORDER, LEVELORDER, PREORDER, POSTORDER;
}