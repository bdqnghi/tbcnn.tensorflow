/**
 * Initialize, Insert, Search and Range Search operations on B+ Tree
 * Implemented by: Akash Barve
 * UFID: 5546-6983
 * email: akash.barve@ufl.edu
 */

import java.io.*;
import java.util.*;

//Definition of class b_plus_tree
public class b_plus_tree {

    public node root;
    public static int tree_degree;

    /**
     * Method to insert a key-value pair into respective positions
     * @param key
     * @param value
     */
    public void tree_insert(Double key, String value) {
        if (root != null && value_search(key) != null ){
            // Search for the leaf node that key points to
            leaf_node leaf = (leaf_node)tree_search(root, key);
            // Look for value that the leaf holds
            for(int i=0; i<leaf.keys.size(); i++) {
                if(key.compareTo(leaf.keys.get(i)) == 0) {
                    leaf.update(i,value);
                }
            }

            return;
        }
        leaf_node newLeaf = new leaf_node(key, value);
        key_node_map entry = new key_node_map(key, newLeaf);

        // Insert entry in respective subtree with the root node pointer
        if(root == null || root.keys.size() == 0) {
            root = entry.getValue();
        }

        // new_child set to null initially
        key_node_map new_child = get_child(root, entry, null);

        //new_child null on return unless child is split
        if(new_child == null) {
            return;
        } else {
            index_node newRoot = new index_node(new_child.getKey(), root,
                    new_child.getValue());
            root = newRoot;
            return;
        }
    }

    /**
     * Method to handle insertion if it was not done at a leaf node
     * @param node
     * @param entry
     * @param new_child
     * @return key_node_map
     */
    private key_node_map get_child(node node, key_node_map entry, key_node_map new_child) {
        if(!node.is_leaf) {
            // Choose subtree, find i such that Ki <= entry's key value < J(i+1)
            index_node index = (index_node) node;
            int i = 0;
            while(i < index.keys.size()) {
                if(entry.getKey().compareTo(index.keys.get(i)) < 0) {
                    break;
                }
                i++;
            }
            // tree_insert entry is done recursively
            new_child = get_child((node) index.children.get(i), entry, new_child);

            // No  child split case
            if(new_child == null) {
                return null;
            }
            // Split child case
            else {
                int j = 0;
                while (j < index.keys.size()) {
                    if(new_child.getKey().compareTo(index.keys.get(j)) < 0) {
                        break;
                    }
                    j++;
                }

                index.ordered_insert(new_child, j);

                // Usual case, put new_child on it, set new_child to null, return
                if(!index.overflow()) {
                    return null;
                }
                else{
                    new_child = split_index(index);

                    // Root was just split
                    if(index == root) {
                        // Create new node and make tree's root-node pointer point to newRoot
                        index_node newRoot = new index_node(new_child.getKey(), root,
                                new_child.getValue());
                        root = newRoot;
                        return null;
                    }
                    return new_child;
                }
            }
        }
        // node pointer is a leaf node
        else {
            leaf_node leaf = (leaf_node)node;
            leaf_node newLeaf = (leaf_node)entry.getValue();

            leaf.ordered_insert(entry.getKey(), newLeaf.values.get(0));

            // Usual case: leaf has space, put entry and set new_child to null and return
            if(!leaf.overflow()) {
                return null;
            }
            // Once in a while, the leaf is full
            else {
                new_child = split_leaf(leaf);
                if(leaf == root) {
                    index_node newRoot = new index_node(new_child.getKey(), leaf,
                            new_child.getValue());
                    root = newRoot;
                    return null;
                }
                return new_child;
            }
        }
    }

    /**
     * Handles the splitting of a leaf node
     * Returns new right node and splitting key
     * @param leaf
     * @return key_node_map
     */
    public key_node_map split_leaf(leaf_node leaf) {
        ArrayList<Double> new_keys = new ArrayList<Double>();
        ArrayList<ArrayList<String>> newValues = new ArrayList<ArrayList<String>>();

        // Rest of the tree_degree entries are moved to a new node
        for(int i=tree_degree/2; i<=tree_degree; i++) {
            new_keys.add(leaf.keys.get(i));
            newValues.add(leaf.values.get(i));
        }

        // Initial tree_degree entries are kept
        for(int i=tree_degree/2; i<=tree_degree; i++) {
            leaf.keys.remove(leaf.keys.size()-1);
            leaf.values.remove(leaf.values.size()-1);
        }

        Double splitKey = new_keys.get(0);
        leaf_node rightNode = new leaf_node(new_keys, newValues);

        // Sibling pointers are set
        leaf_node tmp = leaf.leaf_next;
        leaf.leaf_next = rightNode;
        leaf.leaf_next.leaf_previous = rightNode;
        rightNode.leaf_previous = leaf;
        rightNode.leaf_next = tmp;

        key_node_map new_child = new key_node_map(splitKey, rightNode);

        return new_child;
    }

    /**
     * Handles splitting of the index node
     * Return new right node and splitting key
     * @param index
     * @return key_node_map
     */
    public key_node_map split_index(index_node index) {
        ArrayList<Double> new_keys = new ArrayList<Double>();
        ArrayList<node> newChildren = new ArrayList<node>();

        // Splitting leaf page note: 2(tree_degree)+1 key values, 2(tree_degree)+2 node pointers
        Double splitKey = index.keys.get(tree_degree/2);
        index.keys.remove(tree_degree/2);

        // First tree_degree key values and tree_degree+1 node pointers stay while last tree_degree keys and tree_degree+1 pointers move to new node
        newChildren.add(index.children.get(tree_degree/2+1));
        index.children.remove(tree_degree/2+1);

        while(index.keys.size() > tree_degree/2) {
            new_keys.add(index.keys.get(tree_degree/2));
            index.keys.remove(tree_degree/2);
            newChildren.add(index.children.get(tree_degree/2+1));
            index.children.remove(tree_degree/2+1);
        }

        index_node rightNode = new index_node(new_keys, newChildren);
        key_node_map new_child = new key_node_map(splitKey, rightNode);

        return new_child;
    }

    /**
     * Search for the key and return either value of the leaf node or return null
     * @param key
     * @return ArrayList<String>
     */
    public ArrayList<String> value_search(Double key) {
        // Check whether tree is empty or key exists
        if(key == null || root == null) {
            return null;
        }
        // Find the leaf node the key points to
        leaf_node leaf = (leaf_node)tree_search(root, key);

        // Find the value in the leaf
        for(int i=0; i<leaf.keys.size(); i++) {
            if(key.compareTo(leaf.keys.get(i)) == 0) {
                return leaf.values.get(i);
            }
        }

        return null;
    }

    /**
     * Search if the key value is at an index node and return the value using a linear search
     * @param node
     * @param key
     * @return node
     */
    private node tree_search(node node, Double key) {
        if(node.is_leaf) {
            return node;
        }
        // For index node
        else {
            index_node index = (index_node)node;

            // when key < key0, return tree_search(P0, Double)
            if(key.compareTo(index.keys.get(0)) < 0) {
                return tree_search((node)index.children.get(0), key);
            }
            // m is the number of entries
            // When key >= keym, return tree_search(Pm, Double)
            else if(key.compareTo(index.keys.get(node.keys.size()-1)) >= 0) {
                return tree_search((node)index.children.get(index.children.size()-1), key);
            }
            // Get i for keyi <= key < key(i+1), return tree_search(Pi, Double)
            else {
                // Perform linear searching
                for(int i=0; i<index.keys.size()-1; i++) {
                    if(key.compareTo(index.keys.get(i)) >= 0 && key.compareTo(index.keys.get(i+1)) < 0) {
                        return tree_search((node)index.children.get(i+1), key);
                    }
                }
            }
            return null;
        }
    }

    /**
     * Generate a string of the keys in between key1 and key2 for the range search operation
     * @param key1
     * @param key2
     * @return StringBuilder
     */
    public StringBuilder range_search(Double key1, Double key2) {
        // Return a key or whether empty tree
        StringBuilder builder = new StringBuilder();
        if(key1 == null || key2 == null || root == null) {
            return builder.append("");
        }
        // Find leaf node key is pointing to
        leaf_node leaf = (leaf_node)tree_search(root, key1);

        int j=0;
        while(key1.compareTo(leaf.keys.get(j)) >= 0 && leaf.leaf_next != null){
            if(j==leaf.keys.size()-1){
                leaf=leaf.leaf_next;
                j=0;
            }
            else {
                j++;
            }
        }

        // get value in the leaf
        for(int i=0; i<leaf.keys.size(); i++){
            if(key1.compareTo(leaf.keys.get(i)) <= 0){
                while(i<leaf.keys.size() && key2.compareTo(leaf.keys.get(i)) >= 0){

                    if(leaf.values.get(i).size() > 0){
                        Double key = leaf.keys.get(i);
                        for (String value:leaf.values.get(i)){

                            builder.append("("+key+","+value+"), ");
                        }
                    }
                    i++;
                    if(i==leaf.keys.size() && key2.compareTo(leaf.keys.get(i-1)) >= 0){
                        i=0;
                        leaf=leaf.leaf_next;
                    }
                }
            }
        }
        return builder;
    }




}