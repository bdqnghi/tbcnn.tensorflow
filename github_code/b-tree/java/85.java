/** B-tree is a search tree in which each node contains n data items where 
    (order-1)/2 < n < order-1 
    The tree is always balanced in that all leaves are on the same level 
    -> the length of the path from the root to a leaf is contant */

public class BTree<T extends Comparable<T>> {
        /** A node represents a node in a B-tree */
        private static class Node<T> {
                /** The number of data items in this node */
                private int size = 0; 
                /** The information */
                private Node<T>[] child;

                /** Create an empty node of size order 
                    @param order The size of a node 
                */
                @SuppressWarnings("unchecked")
                public Node (int order) {
                        data = (T[]) new Comparable[order - 1];
                        child = (Node<T>[]) new Node[order];
                        size = 0;
                }
        }
        /** Root node */ 
        private Node<T> root = null;
        /** The maximum number of children of a node */
        private int order;

        /** Contruct a B-tree with node size order 
            @param order the size of a node 
        */
        public BTree(int order) {
                this.order = order;
                root = null;
        }
                
        /** Method to insert a new value into a node 
            pre: node.data[index-1] < item < node.data[index]
            post: node.data[index] == item and old values are moved right one position
            @param node The node to insert the value into 
            @param index The index where the inserted item is to be placed
            @param item The value to be inserted
            @param child The right child of the value to be inserted 
        */
        private void insertIntoNode(Node<T> node, int index, T obj, Node<T> child) {
                for (int i = node.size; i > index; i--) {
                        node.data[i] = node.data[i-1];
                        node.child[i+1] = node.child[i];
                }
                node.data[index] = obj;
                node.child[index+1] = child;
                node.size++;
        }

        private void splitNode(Node<T> node, int index, T item, Node<T> child) {
                // Create new child
                newChild = new Node<T>(order);
                // Determine number of times to move
                int numToMove = (order - 1) - ((order - 1) / 2);
                // If insertion point is in the right, move one less item
                if (index > (order - 1) / 2) {
                        numToMove--;
                }
                // arraycopy(Object src, int srcPos, Object dest, int destPos, int length)
                // Move items and their children
                System.arraycopy(node.data, order - numToMove - 1, newChild.data, 0, numToMove);
                System.arraycopy(node.child, order - numToMove, newChild.child, 1, numToMove);
                node.size = order - numToMove - 1;
                newChild.size = numToMove;
                
                // Insert new item
                if (index == ((order - 1) / 2)) { // Insert as middle item 
                        newParent = item; 
                        newChild.child[0] = child;
                } else {
                        if (index < ((order - 1) / 2)) { // Insert into the left 
                                insertIntoNode(node, index, item, child);
                        } else {
                                insertIntoNode(newChild, index - ((order - 1) / 2) - 1, item, child);
                        }
                        // The rightmost item of the node is the new parent
                        newParent = node.data[node.size - 1];
                        // Its child is the left child of the split-off node
                        newChild.child[0] = node.child[node.size];
                        node.size--;
                }

                // Remove items and refereces to moved items
                for (int i = node.size; i < node.data.length; i++) {
                        node.data[i] = null;
                        node.child[i + 1] = null;
                }
        }
}
