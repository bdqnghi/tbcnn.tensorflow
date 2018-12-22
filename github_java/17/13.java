package at.fhv.itb3.redBlackTree;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 * A basic class to represent a Red-Black-Tree. The available methods are restricted to: insertion, red-black
 * height determination and a method to print the tree in a tree like manner.
 * @author ske2577
 * <p>Created on: 22.11.17</p>
 * @version 1
 *
 */
public class RBTree<T extends Comparable<T>> {
	
	private final Node _nil = new Node(); //represents an external node
	private Node _root;
	
	/**
	 * Class to represent a red-black-tree node. A node without any specific relationships will have the nil node as
	 * parent, left and right child. Each node has a colour (black = true, red = false)
	 * @author ske2577
	 * <p>Created on: 22.11.17</p>
	 * @version 1
	 *
	 */
	private class Node {
		private T _value;
		private Node _left;
		private Node _right;
		private Node _parent;
		private boolean _isBlack;

		private Node(T value) {
			_value = value;
			_isBlack = false; // red
			_parent = _nil;
			_left = _nil;
			_right = _nil;
		}

		/**
		 * Constructor used to initialize the nil node.
		 */
		private Node() {
			_isBlack = true;
		}
	}
	
	/**
	 * Method used to test
	 * @return Root
	 */
	public Node getRoot() {
		return _root;
	}
	
	/**
	 * Method used to test
	 * @return Root value
	 */
	public T getRootValue() {
		return _root._value;
	}
	
	/**
	 * Method used to test
	 * @return a list of all tree values
	 */
	public List<T> getTreeValuesLevelByLevel() {
		LinkedList<T> out = new LinkedList<>();
		LinkedList<Node> q = new LinkedList<>();

		q.add(_root);
		while (!q.isEmpty()) {
			Node el = q.removeFirst();
			out.add(el._value);
			if (el != _nil) {

				q.add(el._left);
				q.add(el._right);
			}
		}

		return out;
	}
	
	/**
	 * Method used to test
	 * @return a list of all tree colours
	 */
	public List<Boolean> getTreeColoursLevelByLevel() {
		LinkedList<Boolean> out = new LinkedList<>();
		LinkedList<Node> q = new LinkedList<>();

		q.add(_root);
		while (!q.isEmpty()) {
			Node el = q.removeFirst();
			out.add(el._isBlack);
			if (el != _nil) {

				q.add(el._left);
				q.add(el._right);
			}
		}

		return out;
	}
	
	/**
	 * Method to compare two values.
	 * @param n is the node(value) to be compared
	 * @param nodeValue is the value to insert
	 * @return The comparison result of the comparator (1, 0, -1)
	 */
	public int compareValues(Node n, T nodeValue) {
		return n._value.compareTo(nodeValue);
	}
	
	/**
	 * Method to insert a new node into the tree. Value must be comparable with a comparator.
	 * @param value
	 */
	public void insert(T value){
		if (_root == null) {
			_root = new Node(value);
			_root._isBlack = true;
		} else {
			Node n = _root;
			Node parent = null;

			while (n != _nil) {
				parent = n;

				if (compareValues(n, value) < 0) {
					n = n._right;
				} else {
					n = n._left;
				}
			}

			n = new Node(value);

			if (parent != null) {
				if (compareValues(parent, value) < 0) {
					parent._right = n;
				} else {
					parent._left = n;
				}

				n._parent = parent;
			}

			rebalance(n);
		}
	}
	
	/**
	 * Method to re-balance the tree according to the RBTree rules.
	 * @param n is the current node
	 */
	public void rebalance(Node n){
		while((n._parent != null) && (!n._parent._isBlack)){
			if(n._parent ==  n._parent._parent._left){ //case: parent is on the left of grandparent
				if(!n._parent._parent._right._isBlack){ //case: uncle and parent are red
					if(n._parent._parent != _root){
						n._parent._parent._isBlack = false;
					}
					n._parent._isBlack = true;
					n._parent._parent._right._isBlack = true;
					
					n = n._parent._parent;
					
				}else{ //case: parent is red, but uncle black
					//case: parent is on the left of the grandparent and n is on the right of the parent
					if(n == n._parent._right){
						rotateLeft(n._parent);
						n = n._left;
					}else{ //case:n is on the left
						n._parent._isBlack = true;
						n._parent._parent._isBlack = false;
						rotateRight(n._parent._parent);
					}
				}
				
				
			}else{ //case: parent is on the right of grandparent
				if(!n._parent._parent._left._isBlack){ //case: uncle and parent are red
					if(n._parent._parent != _root){
						n._parent._parent._isBlack = false;
					}
					n._parent._isBlack = true;
					n._parent._parent._left._isBlack = true;
					
					n = n._parent._parent;
				}else{ //case: parent is red, but uncle black
					if(n == n._parent._right){ //case: parent is on the right and n is on the right
						n._parent._isBlack = true;
						n._parent._parent._isBlack = false;
						rotateLeft(n._parent._parent);
					}else{ //case: n is on the left
						rotateRight(n._parent);
						n = n._right;
					}
				}
			}
		}
		
	}
	
	/**
	 * Method to re-balance the tree to make it a valid RBTree. Rotates a subtree. 
	 * @param n is the current node 
	 */
	private void rotateRight(Node n){
		Node y = n._left;

		n._left = y._right;
		if (y._right != _nil) {
			y._right._parent = n;
		}

		y._parent = n._parent;

		if (n._parent == _nil) {
			y._parent = _nil;
			_root = y;
		} else if (n == n._parent._left) {
			n._parent._left = y;
		} else {
			n._parent._right = y;
		}

		y._right = n;
		n._parent = y;
		
	}
	
	/**
	 * Method to re-balance the tree to make it a valid RBTree. Rotates a subtree. 
	 * @param n is the current node 
	 */
	private void rotateLeft(Node n){
		Node y = n._right;

		n._right = y._left;
		if (y._left != _nil) {
			y._left._parent = n;
		}

		y._parent = n._parent;

		if (n._parent == _nil) {
			y._parent = _nil;
			_root = y;
		} else if (n == n._parent._left) {
			n._parent._left = y;
		} else {
			n._parent._right = y;
		}

		y._left = n;
		n._parent = y;
	}
	
	/**
	 * Public method to determine the RBHeight of the tree.
	 * @return The number of black nodes
	 */
	public int getRBHeight() {
		return getRBHeight(_root);
	}
	
	/**
	 * Private method to determine the RBHeight of the tree.
	 * @param n is the node to start from
	 * @return The number of black nodes
	 */
	private int getRBHeight(Node n) {
		int count = 0;
		while (n != null && n != _nil) {
			if (n._isBlack) {
				count++;
			}

			n = n._left;
		}

		return count;
	}


	/**
	 * Method to print the tree in a tree-like manner. Format is NODE_VALUE : COLOUR
	 */
	public void printTree(){		
		List<List<String>> treeLines = new ArrayList<>(); //complete tree split up in individual lines
        List<Node> level = new ArrayList<>();
        List<Node> nextLevel = new ArrayList<>();

        level.add(_root);
        boolean nodesAvailable = true;
        
        int maxTextLength = 0;
        
        while (nodesAvailable) {
            List<String> line = new ArrayList<>();

            nodesAvailable = false;

            for (Node n : level) {
                if (n == null || n == _nil) {
                    line.add(null);

                    nextLevel.add(null);
                    nextLevel.add(null);
                } else {
                    String text = n._value + ":";
                    
                    if(n._isBlack){
                    	text = text + "B";
                    }else{
                    	text = text + "R";
                    }
                    
                    line.add(text);
                    
                    if (text.length() > maxTextLength){
                    	maxTextLength = text.length();
                    }

                    nextLevel.add(n._left);
                    nextLevel.add(n._right);
                    
                    
                    if (n._left != null || n._right != null){
                    	nodesAvailable = true;
                    }

                }
            }

            //for esthetic reasons
            if (maxTextLength % 2 == 1){
            	maxTextLength++;
            }

            treeLines.add(line);

            level = nextLevel;
            nextLevel = new ArrayList<>();
        }
        
        
        //format + print extracted tree text
        int charsPerNode = treeLines.get(treeLines.size() - 1).size() * (maxTextLength + 4);
        char lineChar = '_';
        char separatorChar = '|';
        char borderChar = '|';
        
        for (int i = 0; i < treeLines.size(); i++) {
            List<String> line = treeLines.get(i);
            
            int midPerNode = (int) Math.floor(charsPerNode / 2) - 1;

            if (i > 0) { //if not root level
                for (int j = 0; j < line.size(); j++) {

                    //add separator beneath parent
                	char c = ' ';
                    if (j % 2 == 1) {
                    	if(line.get(j - 1) != null){
                    		if(line.get(j) != null) {
                    			c = separatorChar;
                    		}else{
                    			c = separatorChar;
                    		}
                    	}else{
                    		 if (j < line.size() && line.get(j) != null){
                    			 c = separatorChar;
                    		 }
                    	}
                    }
                    
                    System.out.print(c);

                    // lines and spaces
                    if (line.get(j) == null) {
                        for (int k = 0; k < charsPerNode - 1; k++) {
                            System.out.print(" ");
                        }
                    } else {

                        for (int k = 0; k < midPerNode; k++) {
                        	if(j % 2 == 0){
                        		System.out.print(' ');
                        	}else{
                        		System.out.print(lineChar);
                        	}
                        }
                        
                        System.out.print(borderChar);
                        
                        for (int k = 0; k < midPerNode; k++) {
                        	if(j % 2 == 0){
                        		System.out.print(lineChar);
                        	}else{
                        		System.out.print(' ');
                        	}
                        }
                    }
                }
                System.out.println();
            }

            // print line of numbers
            for (int j = 0; j < line.size(); j++) {
            	
                String lineText = line.get(j);
                if (lineText == null){
                	lineText = ""; 
                }
                
                int spaceLeft = (int) Math.ceil(charsPerNode / 2 - lineText.length() / 2);
                int spaceRight = (int) Math.floor(charsPerNode / 2 - lineText.length() / 2);

                for (int k = 0; k < spaceLeft; k++) {
                    System.out.print(" ");
                }
                
                System.out.print(lineText);
                
                for (int k = 0; k < spaceRight; k++) {
                    System.out.print(" ");
                }
            }
            
            System.out.println();

            charsPerNode = charsPerNode / 2;
        }
    
	}
	
}
