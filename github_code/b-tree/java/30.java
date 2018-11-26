package myPackage;

import java.util.Random;


/********************************************************************************/
public class B_tree {
	final int EMPTY = -200;
	final int ROOT_DISK_POS = 0;
	final int ROOT = -1;
	final int NO_ROOT = 1;
	final int ROOT_LEVEL = 0;
	final int EXISTS = -9;
	final int NO_OVERFLOW = -8;
	final int OVERFLOW = -7;
	final int RIGHT = 1;
	final int LEFT = -1;
	final int SPLIT_SUCCESS = 1;
	final int INSERT_SUCCESS = 2;
	
	private boolean keyExists;
	private Node root;
	private Node foundNode;
	private int order;
	private int nodeCounter;
	private int nodeAccesses;


/********************************************************************************/
	public B_tree(){     // Constructor of the class
		//root = null;
		root = new Node();
		root.setLevelOfNode(ROOT_LEVEL);
		root.setDiskPosition(ROOT_DISK_POS);
		foundNode = new Node();
		order = root.getOrder();
		this.setNodeCounter(0);
		this.setNodeAccesses(0);
		System.out.println("Order:"+root.getOrder());
	}
	
/********************************************************************************/	
	public void RandomizeTree(int numOfKeys, int rangeOfKeys){
		// This method generates a new Btree with random numOfKeys numbers.
		// Those numbers are in the range from zero to rangeOfKeys.
		
		
		Random rand = new Random();
		int min = 1, max = rangeOfKeys;
		int key = 0;
		
		for (int i=0; i<numOfKeys; i++){
			key = rand.nextInt(max - min + 1) + min;
			this.insert(key);
		}
		
		this.fixDiskPositions(this.getRoot());
	}
	
/********************************************************************************/	
	public void insert(int key){
		// Insert method is used to insert a new key in the tree.
		
		findNode(this.getRoot(), key);
		if (!this.getFoundNode().isFull()){
			nonFullInsert(this.getFoundNode(), key);
		}
		else{
			split(this.getFoundNode());
			insert(key);
		}
	}
	
/********************************************************************************/	
	public int nonFullInsert(Node auxNode, int key){
		//Inserts a key to a non-full node
		
		int position = 0;
		if (auxNode.getKeyCounter() == this.getOrder()-1){
			// Case that node is full. 
			return OVERFLOW;
		}
		
		for (int i=0; i<auxNode.getKeyCounter(); i++){
			if (auxNode.getKey(i) == key){
				return EXISTS;    //Case that the key already exists
			}
		}
		
		int i = 0;
		while ((i<this.getOrder()-1) && (key>auxNode.getKey(i))&&
				                               (auxNode.getKey(i)!=EMPTY)){
			i++;
			//Looking for the proper place
		}
		
		for (int j=auxNode.getKeyCounter(); j>i; j--){
			// Moving the existing keys to the right
			auxNode.setKey(auxNode.getKey(j-1), j);
			//auxNode.setChild(auxNode.getChild(j), j+1);
		}
		auxNode.setKey(key, i);
		auxNode.setKeyCounter(auxNode.getKeyCounter()+1);
		
		position = i;
		return position;
	}
	
/********************************************************************************/	
	public void findNode(Node auxNode, int key){
		// This method is looking for the proper node for the new 
		// key to be inserted
		
		this.setNodeAccesses(this.getNodeAccesses()+1);
		if (auxNode.isLeaf()){
			this.setFoundNode(auxNode);
			// We attach a node that is leaf => node found
			return;
		}
		else{
			int i=0;
			while ((i<this.getOrder()-1) && (key>auxNode.getKey(i))&&
                                                  (auxNode.getKey(i)!=EMPTY)){
				i++;
			}
			for (int j=0; j<auxNode.getKeyCounter(); j++){
				if (key == auxNode.getKey(i)){
					// Key exists => node found
					this.setFoundNode(auxNode);
					return;
				}
			}
			if ((key>auxNode.getKey(i)) && (auxNode.isFull())){
				if (auxNode.getChild(i+1) != null){
					// Recursive call to attach child
					findNode(auxNode.getChild(i+1), key);
				}
				else{
					this.setFoundNode(auxNode);
					return;
				}
			}
			else{
				if (auxNode.getChild(i) != null){
					// Recursive call to attach child
					findNode(auxNode.getChild(i), key);
				}
				else{
					this.setFoundNode(auxNode);
					return;
				}
			}
		}
	}
	
/********************************************************************************/	
	public void split(Node nodeToSplit){
		// Split function splits a node if it's needed 
		if (nodeToSplit.isRoot()){
			// Case that root must be splitted
			splitRoot();
		}
		else{
			Node newChild = new Node();
			Node parent = new Node();
			parent = nodeToSplit.getParentPtr();
			int splitPoint = this.getOrder()/2;
			if (!parent.isFull()){
				System.out.println("Parent node is not full. Yeah!");
				int i = 0;
				// Parent node is not full. Looking for the right place to parent 
				// node, for the key to be inserted.
				while ((i<this.getOrder()-1) && 
					(nodeToSplit.getKey(splitPoint)>
						       parent.getKey(i)) && (parent.getKey(i)!=EMPTY)){
					i++;
				}
				
				for (int j=parent.getKeyCounter(); j>i; j--){
					parent.setKey(parent.getKey(j-1), j);
					parent.setChild(parent.getChild(j), j+1);
				}
				parent.setKey(nodeToSplit.getKey(splitPoint), i);
				parent.setKeyCounter(parent.getKeyCounter()+1);
				
				// Setting the new child that came from splitting
				for (int j=splitPoint+1; 
				                j<nodeToSplit.getKeyCounter()+1; j++){
					//System.out.println("J: "+j);
					newChild.setKey(nodeToSplit.getKey(j),
							                          j-splitPoint-1);
					newChild.setKeyCounter(newChild.getKeyCounter()+1);
					nodeToSplit.setKeyCounter(nodeToSplit.getKeyCounter()-1);
					newChild.setChild(nodeToSplit.getChild(j),
							                           j-splitPoint-1);
				}
				
				// Deleting the moved elements from the splitted node
				for (int j=splitPoint; 
				                 j<nodeToSplit.getKeyCounter()+2; j++){
					nodeToSplit.setKey(EMPTY, j);
					nodeToSplit.setChild(null, j);
				}
				
				parent.setChild(nodeToSplit, i);
				//nodeToSplit.setDiskPosition(i+1+parent.getDiskPosition());
				parent.setChild(newChild, i+1);
				//newChild.setDiskPosition(i+2+parent.getDiskPosition());
				nodeToSplit.setParentPtr(parent);
				newChild.setParentPtr(parent);
				
				nodeToSplit.setLevelOfNode(nodeToSplit.
						                   getParentPtr().getLevelOfNode()+1);
				newChild.setLevelOfNode(newChild.
		                                   getParentPtr().getLevelOfNode()+1);
			}
			else{
				split(parent);
			}
		}
	}
	
/********************************************************************************/
	public void splitRoot(){
		
		// Split root function looks like the split method.
		
		fixLevel(this.getRoot());
		System.out.println("Splitting root...");
		Node newRoot = new Node();
		Node newChild = new Node();
		
		int splitPoint = this.getOrder()/2;
		newRoot.setKey(this.getRoot().getKey(splitPoint), 0);
		newRoot.setKeyCounter(newRoot.getKeyCounter()+1);
		
		for (int i=splitPoint+1; i<this.getRoot().getKeyCounter()+1; i++){
			//System.out.println("I: "+i);
			newChild.setKey(this.getRoot().getKey(i), i-splitPoint-1);
			//this.getRoot().setKey(EMPTY, i-1);
			this.getRoot().setKeyCounter(this.getRoot().getKeyCounter()-1);
			newChild.setChild(this.getRoot().getChild(i), i-splitPoint-1);
			//this.getRoot().setChild(null, i);
		}
		for (int i=splitPoint; i<this.getRoot().getKeyCounter()+1; i++){
			this.getRoot().setKey(EMPTY, i);
			this.getRoot().setChild(null, i);
		}
		
		newRoot.setChild(this.getRoot(), 0);
		//this.getRoot().setDiskPosition(1);
		this.getRoot().setParentPtr(newRoot);
		newRoot.setChild(newChild, 1);
		//newChild.setDiskPosition(2);
		newChild.setParentPtr(newRoot);
		
		this.setRoot(newRoot);
		//this.getRoot().setDiskPosition(0);
	}

/********************************************************************************/
	public void fixLevel(Node auxNode){
		auxNode.setLevelOfNode(auxNode.getLevelOfNode()+1);
		for (int i=0; i<this.getOrder(); i++){
			if (auxNode.getChild(i) != null){
				fixLevel(auxNode.getChild(i));
			}
		}
	}
	
/********************************************************************************/	
	public void fixDiskPositions(Node auxNode){
		for (int i=0; i<this.getOrder(); i++){
			if (auxNode.getChild(i) != null){
				//System.out.println("Hello..............");
				auxNode.getChild(i).setDiskPosition(
					                   4*auxNode.getDiskPosition()+i+1);
			}
		}
		for (int i=0; i<this.getOrder(); i++){
			if (auxNode.getChild(i) != null){
				fixDiskPositions(auxNode.getChild(i));
			}
		}
	}
	
/********************************************************************************/
	public void printTree(Node auxNode){
		System.out.println();
		System.out.println("Tree:");
		System.out.println("---------------------------------");
		auxPrintTree(auxNode);
		System.out.println();
		System.out.println("Nodes: "+this.getNodeCounter());
		System.out.println("---------------------------------");
		System.out.println();
	}
	
/********************************************************************************/
	public void auxPrintTree(Node auxNode){
		auxNode.printNode();
		for (int i=0; i<this.getOrder(); i++){
			if (auxNode.getChild(i) != null){
				this.setNodeCounter(this.getNodeCounter()+1);
				auxPrintTree(auxNode.getChild(i));
			}
		}
	}
	
/********************************************************************************/
	public int getOrder() {
		return order;
	}

	public void setOrder(int order) {
		this.order = order;
	}

	public Node getRoot() {
		return root;
	}

	public void setRoot(Node root) {
		this.root = root;
	}
	
	public boolean isKeyExists() {
		return keyExists;
	}

	public void setKeyExists(boolean keyExists) {
		this.keyExists = keyExists;
	}

	public Node getFoundNode() {
		return foundNode;
	}

	public void setFoundNode(Node foundNode) {
		this.foundNode = foundNode;
	}
	

	public int getNodeCounter() {
		return nodeCounter;
	}

	public void setNodeCounter(int nodeCounter) {
		this.nodeCounter = nodeCounter;
	}

	public int getNodeAccesses() {
		return nodeAccesses;
	}

	public void setNodeAccesses(int nodeAccesses) {
		this.nodeAccesses = nodeAccesses;
	}
	
}
