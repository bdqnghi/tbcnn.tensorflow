import java.util.Vector;

public class SplaySymbolTable <K extends Comparable<K>,V> implements SymbolTable<K,V>{

	public int rotations;
	public int comparaisons;
	
	private class Node{
		public Node left;
		public Node right;
		public Node parent;
		public K key;
		public V val;
		
		Node(K k, V v){
			this.key = k;
			this.val = v;
			left = right = parent = null;
		}
	}
	private Node root = null;
	public SplaySymbolTable(){root = null;}
	
	public Vector<String> serialize() {	
		Vector<String> vec = new Vector<String>();
		serializeAux(root, vec);
		return vec;
	}
	
	private void serializeAux(Node tree, Vector<String> vec){
		if(tree == null)
			vec.addElement(null);
		else{
			vec.addElement(tree.key.toString() + ":black");
			serializeAux(tree.left, vec);
			serializeAux(tree.right, vec);
		}
	}
	private void rotateRight(Node tree){
		assert tree !=null;
		assert tree.left != null;
		Node root = tree.left;
		tree.left = root.right;
		if(tree.left != null)
			tree.left.parent = tree;
		
		root.right =tree;
		if(tree == this.root){
			root.parent = null;
			this.root = root;
		}
		else{
			root.parent = tree.parent;			
			if(tree.parent.left == tree)
				tree.parent.left = root;
			else
				tree.parent.right = root;
		}
		tree.parent = root;
		rotations++;
	}
	
	private void rotateLeft(Node tree){
		assert tree != null;
		assert tree.right != null;
		Node root = tree.right;
		tree.right = root.left;
		if(tree.right != null)
			tree.right.parent = tree;
		
		root.left = tree;
		if(tree == this.root){
			root.parent = null;
			this.root = root;
		}
		else{
			root.parent = tree.parent;
			if(tree.parent.right == tree)
				tree.parent.right = root;
			else
				tree.parent.left = root;
		}
		tree.parent = root;
		rotations++;
	}
	
	public void insert(K key, V val) {	
		if(root == null){
			root = new Node(key, val);
			return;
		}
		insertAux(root, key, val);
	}
	
	void insertAux(Node tree, K key, V val){
		while(true){
			int cmp = key.compareTo(tree.key);
			comparaisons++;
			if(cmp == 0){
				 tree.key = key;
				 tree.val = val;	
				 break;
			}
			else if(cmp < 0){
				if(tree.left == null){
					tree.left = new Node(key, val);
					tree.left.parent = tree;
					tree = tree.left;
					break;
				}
				else
					tree = tree.left;
			}
			else{
				if(tree.right == null){
					tree.right = new Node(key,val);
					tree.right.parent = tree;
					tree = tree.right;
					break;
				}
				else
					tree = tree.right;
			}
		}
		splayTree(tree);
	}

	@Override
	public V search(K key) {
		
		if(root == null)
			return null;
		Node previousTree = null;
		Node tree = root;
		
		while(tree != null){
			int cmp = key.compareTo(tree.key);
			if(cmp == 0){
				splayTree(tree);
				return tree.val;
			}
			else if(cmp > 0){
				previousTree = tree;
				tree = tree.right;
			}
			else{
				previousTree = tree;
				tree = tree.left;
			}
		}
		splayTree(previousTree);
		return null;
	}

	void splayTree(Node tree){

		assert tree != null;
		assert tree.parent != null;

		Node parent;
		Node gparent;

		while((parent = tree.parent) != null && (gparent = parent.parent) != null)
		{
			if(gparent.left == parent){ 
				if(parent.left == tree){  // zig-zig
					rotateRight(gparent);
					rotateRight(parent);
				}
				else { // if(parent.right == tree){ // zig-zag
					rotateLeft(parent);
					rotateRight(gparent);
				}
			}
			else { //if (gparent.right == parent){
				if(parent.right == tree){ // zag-zag
					rotateLeft(gparent);
					rotateLeft(parent);
				}
				else{ //if(parent.left == tree){ // zag-zig
					rotateRight(parent);
					rotateLeft(gparent);
				}
			}
		
		}

		if(parent != null)
		{
			if(parent.left == tree)
				rotateRight(parent); // zig
			else
				rotateLeft(parent);  //zag
		}
	}
}
