import java.util.ArrayList;


public class bPlusTree {

	public genericNode rootNode;
	public static int O;

	/**
	 * takes order input from the file and initialize that tree.
	 * @param order
	 */

	static void Initialize(int order){
		O = order-1;
	}

	/**searchValue method to find value corresponding to a single key
	 * @return null if the tree or the key is empty
	 * @return value otherwise
	 * @param key
	 */

	public String searchValue(Double key) {


		if(key == null || rootNode == null) {
			return null;
		}
		// Find a leaf the input key is pointing at
		leaf leafNode = (leaf) fetchTree(rootNode, key);

		// Look for the corresponding value

		for(int i = 0; i<leafNode.keyList.size(); i++) {
			if(key.compareTo(leafNode.keyList.get(i)) == 0) {
				return leafNode.valueList.get(i);
			}
		}
		return null;
	}

	/**searchValue method to find values corresponding to a range of keys
	 * @return null if the tree or the key is empty
	 * @return ArrayList of key value pair otherwise
	 * @param key1
	 * @param key2
	 */

	public ArrayList<String> searchValue(Double key1, Double key2) {

		ArrayList<String> values_range = new ArrayList<String>();
		if(key1 == null || rootNode == null || key2 == null) {
			return null;
		}
		// Find a leaf the input key1 is pointing at
		leaf leafNode = (leaf) fetchTree(rootNode, key1);
		int j=0;
		while(key1.compareTo(leafNode.keyList.get(j)) >= 0 && leafNode.leafNext !=null){
			if(j==leafNode.keyList.size()-1){
				leafNode=leafNode.leafNext;
				j=0;
			}
			else {j++;}
		}


		for(int i = 0; i<leafNode.keyList.size(); i++) {

			if(key1.compareTo(leafNode.keyList.get(i)) <= 0 && key2.compareTo(leafNode.keyList.get(i))>=0) {

				if(leafNode.valueList.get(i).contains(",")){
					String[] parts = leafNode.valueList.get(i).split(",");
					for(String s: parts){
						values_range.add("("+leafNode.keyList.get(i) + "," + s + ")");
					}

				}
				else{
					values_range.add("("+leafNode.keyList.get(i) + "," + leafNode.valueList.get(i) + ")");

					if(i==leafNode.keyList.size()-1&&leafNode.leafNext !=null){

						leafNode=leafNode.leafNext;
						i=-1;
					}
				}

			}

		}
		//returns an arraylist of valueList
		return values_range;
	}


	/**
	 * Inserting key value pairs in the tree.
	 * @param key
	 * @param value
	 */
	public void insertData(Double key, String value) {

		if(searchValue(key)==null){
			leaf newLeaf = new leaf(key, value);
			myDict entry = new myDict(key, newLeaf);
			// insertData entry into the subtree with pointer to the rootNode node
			if(rootNode == null || rootNode.keyList.size() == 0) {
				rootNode = entry.getNode();
			}


			myDict newChildPair = fetchChild(rootNode, entry, null);
			if(newChildPair == null) {
				return;
			} else {
				innerNode newRoot = new innerNode(newChildPair.getKey(), rootNode,
						newChildPair.getNode());
				rootNode = newRoot;
				return;
			}
		}
		else{

			leaf leaf = (leaf) fetchTree(rootNode, key);

			for(int i = 0; i<leaf.keyList.size(); i++) {
				if(key.compareTo(leaf.keyList.get(i)) == 0) {
					leaf.valueList.set(i, leaf.valueList.get(i) + "," + value) ;
				}
			}


		}
	}


	/**
	 *
 	 * @param node
	 * @param key
	 * @return genericNode
	 */
	private genericNode fetchTree(genericNode node, Double key) {
		if(node.LeafNodeCheck) {
			return node;
		} 
		// If the node is an index node
		else {
			innerNode index = (innerNode)node;
			
			// Double < Key1, return fetchTree(P0, Double)
			if(key.compareTo(index.keyList.get(0)) < 0) {
				return fetchTree(index.childList.get(0), key);
			}
			// Double >= Keym, return fetchTree(Pm, K), m = #entries
			else if(key.compareTo(index.keyList.get(node.keyList.size()-1)) >= 0) {
				return fetchTree(index.childList.get(index.childList.size()-1), key);
			}
			// searchValue for i such that Keyi <= Key < Key(i+1), return fetchTree(Pi,K)
			else {
				// Searching Linearly
				for(int i = 0; i<index.keyList.size()-1; i++) {
					if(key.compareTo(index.keyList.get(i)) >= 0 && key.compareTo(index.keyList.get(i+1)) < 0) {
						return fetchTree(index.childList.get(i+1), key);
					}
				}
 			}
			return null;
		}
	}


	/**
	 *
	 * @param node
	 * @param Pair
	 * @param newChildPair
	 * @return
	 */
	private myDict fetchChild(genericNode node, myDict Pair,
							  myDict newChildPair) {
		if(!node.LeafNodeCheck) {

			innerNode inner = (innerNode) node;
			int i = 0;
			while(i < inner.keyList.size()) {
				if(Pair.getKey().compareTo(inner.keyList.get(i)) < 0) {
					break;
				}
				i++;
			}
			//  insertData entry, recursively
			newChildPair = fetchChild( inner.childList.get(i), Pair, newChildPair);
			

			if(newChildPair == null) {
				return null;
			} 

			else {
				int j = 0;
				while (j < inner.keyList.size()) {
					if(newChildPair.getKey().compareTo(inner.keyList.get(j)) < 0) {
						break;
					}
					j++;
				}
				
				inner.InsertAndSort(newChildPair, j);

				if(!inner.OverflowCheck()) {
					return null;
				} 
				else{
					newChildPair = splitInnerNode(inner);
					
					// When rootNode is split
					if(inner == rootNode) {
						innerNode newRoot = new innerNode(newChildPair.getKey(), rootNode,
								newChildPair.getNode());
						rootNode = newRoot;
						return null;
					}
					return newChildPair;
				}
			}
		}
		// genericNode pointer is a leaf node
		else {
			leaf leaf = (leaf)node;
			leaf newLeaf = (leaf)Pair.getNode();
			
			leaf.InsertAndSort(Pair.getKey(), newLeaf.valueList.get(0));
			

			if(!leaf.OverflowCheck()) {
				return null;
			}
			// When the leaf is full
			else {
				newChildPair = splitLeaf(leaf);
				if(leaf == rootNode) {
					innerNode newRoot = new innerNode(newChildPair.getKey(), leaf,
							newChildPair.getNode());
					rootNode = newRoot;
					return null;
				}
				return newChildPair;
			}
		}
	}

	/**
	 * This method splits a leaf
	 * @param leafNode
	 * @return key/node pair as a myDict object
	 */
	public myDict splitLeaf(leaf leafNode) {

		ArrayList<Double> newKeyList = new ArrayList<Double>();
		ArrayList<String> newValueList = new ArrayList<String>();
		

		for(int i = O /2; i<= O; i++) {
			newKeyList.add(leafNode.keyList.get(i));
			newValueList.add(leafNode.valueList.get(i));
		}
		

		for(int i = O /2; i<= O; i++) {
			leafNode.keyList.remove(leafNode.keyList.size()-1);
			leafNode.valueList.remove(leafNode.valueList.size()-1);
		}
		
		Double splitKeyNode = newKeyList.get(0);
		leaf rightNode = new leaf(newKeyList, newValueList);
		

		leaf tmp = leafNode.leafNext;
		leafNode.leafNext = rightNode;
		leafNode.leafNext.leafPrevious = rightNode;
		rightNode.leafPrevious = leafNode;
		rightNode.leafNext = tmp;
        

		myDict newChildPair = new myDict(splitKeyNode, rightNode);
		return newChildPair;
	}

	/**
	 * This method splits an innerNode
	 * @param inner
	 * @return key/node pair (splitting key and RightNode) as myDict object
	 */
	public myDict splitInnerNode(innerNode inner) {

		ArrayList<Double> newKeyList = new ArrayList<Double>();
		ArrayList<genericNode> newChildList = new ArrayList<genericNode>();
		

		Double splitKeyNode = inner.keyList.get(O /2);
		inner.keyList.remove(O /2);
		
		// The First (O/2) key valueList and (O/2)+1 node pointers don't move
		// Last (O/2) keyList and (O/2)+1 pointers move into new node
		newChildList.add(inner.childList.get((O /2)+1));
		inner.childList.remove((O /2)+1);
		
		while(inner.keyList.size() > O /2) {
			newKeyList.add(inner.keyList.get(O /2));
			inner.keyList.remove(O /2);
			newChildList.add(inner.childList.get((O /2)+1));
			inner.childList.remove((O /2)+1);
		}

		innerNode rightNode = new innerNode(newKeyList, newChildList);
		myDict newChildPair = new myDict(splitKeyNode, rightNode);
		return newChildPair;
	}

}