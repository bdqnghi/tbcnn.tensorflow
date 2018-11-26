package trees;

/**
 * Node.java
 * Purpose: represent a node in a Red-Black-Tree
 */
public class Node {
	
	//possible node colors
	public enum Colors{BLACK, RED};
	
	protected String _key;
	protected Colors _color; //color of the node can only be red or black
	protected Node _left, _right;
	protected Node _parent;
	
	/** Class Constructor (default) */
	public Node(String key){
		setKey(key);
		setColor(Colors.RED); //default color
	}
	
	/** 
	 * Class Constructor (default)
	 * @param other the node to be copied from
	 */
	public Node(Node other){
		if(other!=null)
			setKey(other.getKey());
		else 
			setKey("");
		setColor(Colors.RED); //default color
	}
	
	/** 
	 * copy the satellite data from another node 
	 * @param other the node to be copied from
	 */
	public void copyData(Node other) {
		_key = other.getKey();	
	}
	
	//Getters
	/** @return the key of this node */
	public String getKey(){
		return _key;
	}
	
	/** @return the color of this node */
	public Colors getColor(){
		return _color;
	}
	
	/** @return the parent node */
	public Node getParent() {
		return _parent;
	}
	
	/** @return the left node */
	public Node getLeft() {
		return _left;
	}
	
	/** @return the right node */
	public Node getRight() {
		return _right;
	}
	
	//Setters
	/**
	 * set a new key for this node
	 * @param key the new key
	 */
	public void setKey(String key){
		_key = key;
	}
	
	/**
	 * set a new color for this node
	 * @param color the new color
	 */
	public void setColor(Colors color){
		_color = color;
	}

	/**
	 * set a new parent for this node
	 * @param parent new the parent to set 
	 */
	public void setParent(Node parent) {
		_parent = parent;
	}

}
