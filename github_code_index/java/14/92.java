package bTree;

import static gdi.MakeItSimple.closeInputFile;
import static gdi.MakeItSimple.isEndOfInputFile;
import static gdi.MakeItSimple.isFilePresent;
import static gdi.MakeItSimple.openInputFile;
import static gdi.MakeItSimple.print;
import static gdi.MakeItSimple.println;
import static gdi.MakeItSimple.readInt;
import static gdi.MakeItSimple.readLine;

import java.io.Serializable;

import queue.Queue;


/**
 * 
 * @author Wolfgang Schramm
 * @date 20.4.2016
 * @version 2.0
 * 
 */

public class BTree implements Cloneable, Serializable {
	private BNode root; 
	private int degree;
	
	/**
	 * 
	 * @param degree of B-tree
	 * @returns new emtpy B-tree
	 * 
	 */
	
	public BTree(int degree) {
	}
	
	/**
	 * @returns true when tree is empty
	 */
	
	public boolean isEmpty () {
	}

	/**
	 * @returns height of b-tree
	 */
	
	public int height () {
	}
	
	/**
	 * @returns the biggest element in b-tree
	 */
	
	public Object getMax () {
	}
	
	/**
	 * @returns the smallest element in b-tree
	 */
	
	public Object getMin () {
	}
	
	/**
	 * @param other b-tree who's elements are inserted in B-tree
	 * duplicate keys are ignored
	 * there is no insertion order guaranteed 
	 */
	
	public void addAll (BTree other) {
	}
	
	
	/**
	 * @returns true when building of a B-Tree with keys from a file
	 * was successful
	 * The filename is asked in the method
	 * possible improvement: pass filename as parameter
	 */
	
	public boolean build() {
	}

	
	/**
	 * @return a deep clone of this B-Tree
	 * makes a deep clone of this B-Tree
	 */
	
	@Override
	public Object clone () throws CloneNotSupportedException {
	}
	
	/**
	 * prints B-Tree in levelorder on console
	 */
	
	public void levelOrder () {
	}
	
	/**
	 * prints B-Tree in preorder on console
	 */
	
	public void preOrder () {
	}

	/**
	 * prints B-Tree in inorder on console
	 */
	
	public void inOrder () {
	}
	
	/**
	 * prints B-Tree in postorder on console
	 */
	

	public void postOrder () {
	}
	
	/**
	 * @returns number of objects stored in B-Tree
	 */
	
	public int size () {	
	}
	
	/**
	 * @returns true when obj is in B-Tree else false
	 */
	
	boolean contains (Integer obj) {
	}
	
	
	/**
	 * @param obj to be deleted
	 */
	
	public void delete (Integer obj) {
	}
	
	
	/**
	 * @param obj to be inserted in B-Tree
	 */
	
	public void insert (Integer obj) {
	}
	
	/**
	 * @param obj to be inserted in B-Tree
	 * @return leaf-Node where obj has to be inserted
	 *         null, when obj already in tree
	 */
	
	private BNode searchInsPage (Integer obj) {
	}
}