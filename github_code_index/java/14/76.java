package b_Tree;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;

//degree must be greater than 2
public class B__Tree implements Serializable{
	private static int degree = 4;
	public Node root;
	private int height = 1;
	private int size=0;

	public B__Tree(int degree) {
		this.degree = degree;
		root = new Node(degree);
	}
	
	public static int getDegree() {
		return degree;
	}

	public int getHeight() {
		return height;
	}


	public int getSize() {
		return size;
	}

	public ArrayList<String> search(Comparable key) {
		if (key == null)
			return new ArrayList<>();
		ArrayList<String> list = new ArrayList<>();
		String toRet = search(key, root, height, false);
		if(toRet!=null)
		list.add(toRet);
		return list;
	}

	public String search(Comparable key, Node node, int height, boolean delete) {
		if (height == 1) {
			ArrayList<Entry> leafEntries = node.nodeData;
			for (int i = 0; i < leafEntries.size(); i++) 
				if (key.compareTo(leafEntries.get(i).key) == 0){ 
					if(delete){
						((LeafEntry) leafEntries.get(i)).setDeleted(true);
					}
					if(!((LeafEntry) leafEntries.get(i)).isDeleted())
					return ((LeafEntry) leafEntries.get(i)).getValue();
				}
		} else {
			for (int i = 0; i < node.nodeData.size(); i++) 
				if (key.compareTo(node.nodeData.get(i).key) < 0) 
					return search(key, node.nodeData.get(i).leftChild, --height, delete);	
			 // key greater go to right child of node
			return search(key, node.rightChild, --height, delete);
		}
		return null;
	}

	public void insert(Comparable key, String value) {
		if (key == null)
			throw new NullPointerException("key is nul or value is null");
		Node x = insert(key, value, root, height);
		if (x != null) { // case 4 new Root
			ArrayList<Entry> newRootEntry = new ArrayList<Entry>();
			newRootEntry.add(new Entry(x.nodeData.get(0).key));
			if (height != 1)
				x.nodeData.remove(0);
			Node newRoot = new Node(degree, newRootEntry);
			newRoot.rightChild = x;
			newRoot.nodeData.get(0).leftChild = root;
			this.root = newRoot;
			height++;
		}
		size++;
	}

	private Node insert(Comparable key, String value, Node node, int height) {
		if (height == 1) { // leaves
			LeafEntry toInsert = new LeafEntry(key, value);
			node.nodeData.add(toInsert);
			Collections.sort(node.nodeData); // malhash right child
			if (!node.isOverFlow())// case 1
				return null;
			else // return new splitted node, leave old one case 2
				return node.splitLeaf();
		}
		/* Now to the Inner Nodes */
		Node prevSplit = null;
		boolean called = false;
		for (int i = 0; i < node.nodeData.size(); i++) {
			if (key.compareTo(node.nodeData.get(i).key) < 0) {
				called = true;
				prevSplit = insert(key, value, node.nodeData.get(i).leftChild, --height);
				break;
			}
		}
		if (!called)
			prevSplit = insert(key, value, node.rightChild, --height);

		if (prevSplit == null)
			return null; // inserted

		Entry toInsertNonLeaf = new Entry(prevSplit.nodeData.get(0).key); // smallest
		if (!(prevSplit.nodeData.get(0) instanceof LeafEntry))
			prevSplit.nodeData.remove(0);// remove to make sparse
		toInsertNonLeaf.leftChild = node.rightChild;
		node.nodeData.add(toInsertNonLeaf);
		node.rightChild = prevSplit;
		Collections.sort(node.nodeData);
		if (!node.isOverFlow()) // case 2
			return null;
		else
			return node.split();
	}

	public void delete(Comparable key) {
		search(key, root, height,true);
	}	
}