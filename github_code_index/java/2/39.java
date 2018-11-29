package AVLTree;

/* Implementacja drzew AVL.

 */

public class AvlTree<T extends Comparable<T>> implements Tree<T> {

    public Node<T> root;

    public Node<T> getRoot() {
        return root;
    }

    public int findHeight(Node<T> root){
        if ( root == null) return -1;

        int leftH = findHeight(root.getLeftChild());
        int rightH = findHeight(root.getRightChild());

        if(leftH > rightH){
            return leftH + 1;
        } else {
            return rightH + 1;
        }
    }

    @Override
    public void insert(T data) {
        root = insert(root, data);
    }

    private Node<T> insert(Node<T> node, T data) {

        if( node == null) {
            return new Node<>(data);
        }

        if(data.compareTo(node.getData()) < 0){
            node.setLeftChild( insert(node.getLeftChild(), data) );
        } else {
            node.setRightChild( insert(node.getRightChild(), data) );
        }

        node.setHeight( Math.max( height(node.getLeftChild()), height(node.getRightChild())) + 1);

        node = settleViolation(data, node);

        return node;
    }

    private Node<T> settleViolation(T data, Node<T> node) {

        int balance = getBalance(node);

        // Case I:
        if(balance > 1 && data.compareTo(node.getLeftChild().getData()) < 0){
            return rightRotation(node);
        }

        // Case II:
        if(balance < -1 && data.compareTo(node.getRightChild().getData()) > 0){
            return leftRotation(node);
        }

        // Case III - left-right heavy situation
        if(balance > 1 && data.compareTo(node.getLeftChild().getData()) > 0){
            node.setLeftChild(leftRotation(node.getLeftChild()));
            return rightRotation(node);
        }

        // Case IV - right left heavy situation
        if(balance < -1 && data.compareTo(node.getLeftChild().getData()) < 0){
            node.setRightChild(rightRotation(node.getRightChild()));
            return leftRotation(node);
        }

        return node;
    }

    private Node<T> rightRotation(Node<T> node){

        //System.out.println("Rotating to the right on node: " + node.toString());

        Node<T> tempLeftNode = node.getLeftChild();
        Node<T> t = tempLeftNode.getRightChild();

        tempLeftNode.setRightChild(node);
        node.setLeftChild(t);

        node.setHeight( Math.max( height(node.getLeftChild()), height(node.getRightChild())) + 1);
        tempLeftNode.setHeight( Math.max( height(tempLeftNode.getLeftChild()), height(tempLeftNode.getRightChild())) + 1);

        return tempLeftNode;
    }

    private Node<T> leftRotation(Node<T> node){

        //System.out.println("Rotating to the left on node: " + node.toString());

        Node<T> tempRightNode = node.getRightChild();
        Node<T> t = tempRightNode.getLeftChild();

        tempRightNode.setLeftChild(node);
        node.setRightChild(t);

        node.setHeight( Math.max( height(node.getLeftChild()), height(node.getRightChild())) + 1);
        tempRightNode.setHeight( Math.max( height(tempRightNode.getLeftChild()), height(tempRightNode.getRightChild())) + 1);

        return tempRightNode;
    }


    private int height(Node<T> node){
        if(node == null){
            return -1;
        }

        return node.getHeight();

    }
    // calculating the "balance" of the given node
    // meaning the difference between left and right paths
    private int getBalance(Node<T> node){

        if( node == null) return 0;

        return height(node.getLeftChild()) - height(node.getRightChild());
    }

    @Override
    public void traverse() {

        if( root == null) return;

        inOrderTraversal(root);

    }

    private void inOrderTraversal(Node<T> node) {

        if(node.getLeftChild() != null){
            inOrderTraversal(node.getLeftChild());
        }

        System.out.print(node+" ");

        if(node.getRightChild() != null){
            inOrderTraversal(node.getRightChild());
        }
    }
}
