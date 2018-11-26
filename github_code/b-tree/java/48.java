package lab;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.stream.Collectors;

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
	
	private final int t;
	private B_TreeNode root;

    /**
	* The constructor
	* 
	* @param t minimum degree of the B-tree.
    *		 t can not be changed once a new B Tree object is created.
    *
	*/

    public B_Tree(int t) {
    	this.t = t;
        this.root = new B_TreeNode(t);
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
    	try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
		    String line;
		    String[] parts;
		    int insertionCount = 0;
		    
		    // Read all lines
		    while ((line = br.readLine()) != null) {
		    	// Create new entry from line parts separated by a semicolon
		    	parts = line.split(";");
		    	Entry entry = new Entry(parts[0], parts[1], parts[2]);

		    	if(this.insert(entry))
		    		insertionCount += 1;
		    }
		    
		    return insertionCount;
		} catch (FileNotFoundException e) {
			System.out.println("File not found");
			return 0;
		} catch (IOException e) {
			System.out.println("IO Exception");
			return 0;
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
   
    	if(root.isFull()) {
    		B_TreeNode newRoot = new B_TreeNode(this.t);
    		newRoot.makeNonLeaf();
    		newRoot.setPointer(0, root);
    		newRoot.splitChild(root);
    		this.root = newRoot;
    	}
    
    	return root.insert(insertEntry);
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
    	// delete operates on entries, not strings, therefore we create a dummy entry with the key we're deleting
    	Entry dummy = new Entry(deleteKey, "", "");

    	Entry res = root.delete(dummy);
    	// If the root is empty, but there are still values in the tree, redefine the root
    	if(root.getCurrentLoad() == 0 && !root.isLeaf()) {
    		this.root = root.getPointer(0);
    	}

    	return res;
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
    	// find operates on entries, not strings, therefore we create a dummy entry with the key we're searching
    	Entry dummy = new Entry(searchKey, "", "");
        return root.find(dummy);
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
        ArrayList<String> res = new ArrayList<String>();
        res.add("digraph{");
        res.add("node[shape=record];");
        root.getDotCode(1, true, res);
        res.add("}");
        //System.out.println(res.stream().map(Object::toString).collect(Collectors.joining("\n")));
    	return res;
    }

    /**
	 * This method returns the height of the B-Tree
     * If the B-Tree is empty this method should return 0.
     *
	 * @return returns the height of the B-Tree
	 */
    public int getB_TreeHeight() {
    	return root.getHeight();
    }

    /**
	 * This method traverses the B-Tree in inorder and adds each entry to a
     * ArrayList<Entry>. The returned ArrayList contains the entries of the B-Tree
     * in ascending order.
     *
	 * @return returns the entries stored in the B-Tree in ascending order
	 */
    public ArrayList<Entry> getInorderTraversal() {
    	return root.inorderTraversal();
    }

    /**
	 * This method returns the number of entries in the B-Tree (not the number
     * of nodes).
     *
	 * @return returns the size of the B-Tree, i.e., the number of entries stored in the B-Tree
	 */
    public int getB_TreeSize() {
    	return root.getSize();
    }
}