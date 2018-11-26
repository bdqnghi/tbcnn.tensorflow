// Authors: Yu Liao Peng, Ana Chiu
public class AvlTree <T extends Comparable> extends BinarySearchTree<T> {
	
	private static final int ALLOWED_BALANCE = 1;
	private BinaryNode<T> root;

	public AvlTree() {
		root = null;
	}
	
	public void insert(T element) {
		root = insert(element, root);
	}
	
	public T rootValue() {
		return root.data;
	}
	
	public void remove(T element) {
		root = remove(element, root);
	}
	
	protected BinaryNode<T> insert(T element, BinaryNode<T> node){
		return balance(super.insert(element, node));	
	}
	
	protected BinaryNode<T> remove(T element, BinaryNode<T> node){
		return balance(super.remove(element, node));
	}
	
	private BinaryNode<T> balance(BinaryNode<T> node){
		if(node == null)
			return node;
		
		if(height(node.left) - height(node.right) > ALLOWED_BALANCE)
			if(height(node.left.left) >= height(node.left.right))
				node = singleRightRotation(node);
			else
				node = doubleLeftRightRotation(node);
		else
			if(height(node.right) - height(node.left) > ALLOWED_BALANCE)
				if( height(node.right.right) >= height(node.right.left) )
					node = singleLeftRotation(node);
				else
					node = doubleRightLeftRotation(node);
		
		node.height = Math.max(height(node.left), height(node.right)) + 1;
		return node;	
	}

	private BinaryNode<T> singleRightRotation(BinaryNode<T> k2){
		BinaryNode<T> k1 = k2.left;
		k2.left = k1.right;
		k1.right = k2;
		k2.height = (Math.max(height(k2.left), height(k2.right)) +1);
		k1.height = (Math.max(height(k1.left), k2.height) +1) ;
		System.out.println("Single right rotate: " + k2.getData());

		return k1;
	}
	
	private BinaryNode<T> singleLeftRotation(BinaryNode<T> k1){
		BinaryNode<T> k2 = k1.right;
		k1.right = k2.left;
		k2.left = k1;
		k1.height = (Math.max(height(k1.left), height(k1.right))+1);
		k2.height = (Math.max(height(k2.right), k1.height)+1);	
		System.out.println("Single left rotate: " + k1.getData());
		return k2;	
	}
	
	private BinaryNode<T> doubleLeftRightRotation(BinaryNode<T> k3){
		k3.left = singleLeftRotation(k3.left);
		System.out.println("Double left right rotation: " + k3.getData());
		return singleRightRotation(k3);
	}
	
	private BinaryNode<T> doubleRightLeftRotation(BinaryNode<T> k1){
		k1.right = singleRightRotation(k1.right);
		System.out.println("Double right left rotation: " + k1.getData());
		return singleLeftRotation(k1);
	}
	
	private int checkBalance(BinaryNode<T> node) throws Exception{
		if(node == null) return -1;
		
		if(node != null) {
			int leftHeight = checkBalance(node.left);
			int rightHeight = checkBalance(node.right);
			if( (Math.abs(height(node.left) - height(node.right) )) > 1  
				|| (height(node.left) != leftHeight)
				|| (height(node.right) != rightHeight) )
			{
				throw new Exception("Unbalanced Tree");
			}
		}
		return height(node);
	}
	
	private int height(BinaryNode<T> node) {
		return node == null ? -1 : node.height;
	}
	
	public BinaryNode<T> getRoot(){
		return root;
	}
	

}
