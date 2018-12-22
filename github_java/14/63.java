package lab;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;

import frame.*;

/*
 * Implements a B-Tree structure as introduced in the 
 * lecture to store the information read by the RFID 
 * readers in the library.
 *
 * Make sure that you have tested all the given test cases
 * given on the homepage before you submit your solution.
 *
 */



public class B_Tree {

    B_TreeNode root;
    int minDeg;



    /**
	 * The constructor
	 *
	 * @param t minimum degree of the B-tree.
     * 			t can not be changed once a new B Tree object is created.
     *
	 */

    public B_Tree(int t) {
        minDeg = t;
        B_TreeNode node = new B_TreeNode(t);
        node.leaf = true;
        this.root = node;
    }

    /**
	 * This method takes as input the name of a file containing a sequence of
     * entries that should be inserted to the B-Tree in the order they appear in
     * the file. You cannot make any assumptions on the order of the entries nor
     * is it allowed to change the order given in the file. You can assume that the
     * file is located in the same directory as the executable program. The input
     * file is similar to the input file for lab 1. The return value is the number of
     * entries successfully inserted in the B-Tree.
	 *
	 * @param filename name of the file containing the entries
	 * @return returns the number of entries successfully inserted in the B-Tree.
	 */


    public int constructB_TreeFromFile (String filename) {
        try {
            Scanner s = new Scanner(new FileInputStream(filename));
            int c = 0;
            while (s.hasNextLine()) {
                String[] data = s.nextLine().split(";");
                Entry e = new Entry(data[0], data[1], data[2]);
                if (this.insert(e)) c++;
            }

            return c;
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return -1;
        }

    }

    /**
	 * This method inserts the entry insertEntry into the B-Tree. Note that you
     * have to deal with overflows if you want to insert an entry into a leaf which
     * already contains 2t - 1 entries. This method returns true if the insertion
     * of the entry insertEntry is successful and false if the key of this entry
     * already exists in the B-Tree.
     *
	 * @param insertEntry entry to insert into the B-Tree
	 * @return returns true if the entry insertEntry is successfully inserted
     *                 false if the entry already exists in the B-Tree
	 */


    public boolean insert(Entry insertEntry) {
        if (root.entries.size() == 2*minDeg - 1) {
            B_TreeNode s = new B_TreeNode(minDeg);
            s.leaf = false;
            s.children.add(this.root);
            s.splitChild(0, root);
            this.root = s;
            this.insertNonfull(s, insertEntry);
        } else {
            this.insertNonfull(this.root, insertEntry);
        }
        return true;
    }

    private boolean insertNonfull(B_TreeNode x, Entry k) {
        int i = x.entries.size() - 1;
        if (x.leaf) {
            while (i >= 0 && k.compareTo(x.entry(i)) < 0) {
                i = i - 1;
            }
            if (x.entries.size() > 0 && i>-1 && k.compareTo(x.entry(i)) == 0) return false;
            x.entries.add(i+1, k);
            return true;
        } else {
            while (i >= 0 && k.compareTo(x.entry(i)) < 0) {
                i = i - 1;
            }
            i++;
            //DISK-READ()
            if (x.child(i).entries.size() == 2*minDeg - 1) {
                x.splitChild(i, x.child(i));
                if (k.compareTo(x.entry(i)) > 0) {
                    i = i + 1;
                }
            }
            return insertNonfull(x.child(i), k);
        }
    }

    /**
	 * This method deletes the entry from the B-Tree structure, having deleteKey
     * as key. In this method you have to distinguish between two cases:
     *     1. The entry, having deleteKey as key, is located in an internal node.
     *     2. The entry, having deleteKey as key, is located in a leaf.
     * This method returns the entry, having deleteKey as key if the deletion is
     * successful and null if the key deleteKey is not found in any entry of the
     * B-Tree.
     *
	 * @param deleteKey key of the entry to delete from the B-Tree
	 * @return returns the deleted entry if the deletion ends successfully
     *                 null if the entry is not found in the B-Tree
	 */


    public Entry delete(String deleteKey) {
        if (root == null) {
            return null;
        } else {
            printNode(root);
            System.out.println("Deleting "+deleteKey);
            Entry deleted = root.treeDeleteByKey(deleteKey);
            if (root.children.size() == 1) {
                root = root.child(0);
            }
            printNode(root);
            return deleted;
        }
    }


    /**
	 * This method searches in the B-Tree for the entry with key searchKey. It
     * returns the entry, having searchKey as key if such an entry is found, null
     * otherwise.
     *
	 * @param searchKey key of the entry to find in the B-Tree
	 * @return returns the entry having searchKey as key if such an entry exists
     *                 null if the entry is not found in the B-Tree
	 */


    public Entry find(String searchKey) {
        if (root == null)
            return null;
        else
            return root.treeSearch(searchKey);
    }

    /**
	 * This method returns a ArrayList<String> containing the output B-Tree.
     * The output should be directly interpretable dot code.
     * Each item in the ArrayList corresponds to one line of the output
     * tree. The nodes of the output tree should only
     * contain the keys of the entries and not the data.
     *
     * @return returns the output B-Tree in directly interpretable dot code
     */
    public ArrayList<String> getB_Tree() {
        return getB_Tree_Cutted(Integer.MAX_VALUE);
    }
    public ArrayList<String> getB_Tree_Cutted(int label_maxlen) {
        //pfff
        numerateTree_counter = 0;
        numerateTree(root);
        root.id = "root";

        ArrayList<String> out =  new ArrayList<>();
        out.add("Digraph{");
        out.add("node[shape=record];");

        Stack<B_TreeNode> nodes = new Stack<>();
        if (root != null) nodes.push(root);

        while (!nodes.empty()) {
            B_TreeNode node = nodes.pop();

            out.add(node.toDotRep(label_maxlen));

            for(int i = 0; i < node.children.size(); i++) {
                B_TreeNode child = node.child(i);
                nodes.push(child);
                out.add(String.format("%s:f%d->%s;",
                        node.id, i*2, child.id));
            }
        }

        out.add("}");
        return out;
    }
    int numerateTree_counter;
    private void numerateTree(B_TreeNode el) {
        for(B_TreeNode child:el.children) {
            child.setId(++numerateTree_counter);
            numerateTree(child);
        }

    }
    /**
	 * This method returns the height of the B-Tree
     * If the B-Tree is empty this method should return 0.
     *
	 * @return returns the height of the B-Tree
	 */


    public int getB_TreeHeight() {
        if (root == null)
    	    return 0;
        else
            return root.getMaxDepth() - 1;
    }



    /**
	 * This method traverses the B-Tree in inorder and adds each entry to a
     * ArrayList<Entry>. The returned ArrayList contains the entries of the B-Tree
     * in ascending order.
     *
	 * @return returns the entries stored in the B-Tree in ascending order
	 */

    
    public ArrayList<Entry> getInorderTraversal() {
        ArrayList<Entry> list = new ArrayList<>();
        if (root != null)
            root.treeTraverse(list);
        return list;
    }

    /**
	 * This method returns the number of entries in the B-Tree (not the number
     * of nodes).
     *
     *
	 * @return returns the size of the B-Tree, i.e., the number of entries stored in the B-Tree
	 */

    
    public int getB_TreeSize() {
        if (root == null)
    	    return 0;
        else
            return root.getEntryCount();
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder();
        if (this.root != null)
            prn(this.root, "  ", b);
        return "B_Tree(\n" + b.toString() + "\n)";
    }

    private Entry prnlast = null;
    private void checkorder(String prefix , Entry o , StringBuilder out) {
        out.append(prefix + o);
        if (prnlast != null) {
            if (o.compareTo(prnlast) < 0) {
                out.append(" \t !!!!! WRONG ORDER !!!!!");
            }
        }
        out.append("\n");
        prnlast = o;
    }
    private void printNode(B_TreeNode n) {
        prnlast = null;
        StringBuilder b = new StringBuilder();
        prn(n, "#", b);
        System.out.println(b.toString());
    }
    private void prn(B_TreeNode n, String prefix, StringBuilder out) {
        try {
            out.append(prefix + "o " + n + "\n");
            int i;
            if (n.leaf) {
                for (i = 0; i < n.entries.size(); i++)
                    checkorder(prefix + "   | ", n.entry(i), out);
            } else {
                for (i = 0; i < n.entries.size(); i++) {
                    prn(n.child(i), prefix + "   ", out);
                    checkorder(prefix + "   | ", n.entry(i), out);
                }
                prn(n.child(i), prefix + "   ", out);
            }
        } catch(Exception ex) {
            out.append(prefix + "!!!!!!! " + ex.getMessage() + "\n");
        }
    }
}