package fdu.qhf.mytree;
import java.util.ArrayList;

/*
 * class Red-Black-Tree
 */
public class RedBlackTree {
	/*
	 * structure method, get data and initial the tree
	 */
	public RedBlackTree(ArrayList<String> arrayList1, ArrayList<String> arrayList2) {
		initial(arrayList1, arrayList2);
	}
	
	/*
	 * initial the tree
	 */
	private void initial(ArrayList<String> arrayList1, ArrayList<String> arrayList2) {
		int length = arrayList1.size();
		for (int i=0;i<length;i++) {
			insert(arrayList1.get(i), arrayList2.get(i));
		}
	}
	
	/*
	 * get the minimum node start at x
	 */
	private TreeNode treeMinimum(TreeNode x) {
		while (x.leftChild != null) {
			x = x.leftChild;
		}
		return x;
	}
	
	/*
	 * get node x's successor
	 */
	private TreeNode treeSuccessor(TreeNode x) {
		if (x.rightChild != null) {
			return treeMinimum(x.rightChild);
		}
		TreeNode y = x.father;
		while (y != null && !x.isLeftChild()) {
			x = y;
			y = x.father;
		}
		return y;
	}
	
	/*
	 * search node key, start at x
	 */
	private TreeNode searchNode(TreeNode x, TreeNode key) {
		if (x != null && x.compare(key) == 0) {
			return x;
		}
		if (x != null && x.compare(key) == -1) {
			return searchNode(x.rightChild, key);
		}
		if (x != null && x.compare(key) == 1) {
			return searchNode(x.leftChild, key);
		}
		return null;
	}
	
	/*
	 * left rotate at x
	 */
	private void leftRotate(TreeNode x) {
		TreeNode y = x.rightChild;
		if (y.leftChild != null) {
			x.rightChild = y.leftChild;
			y.leftChild.father = x;
		} else {
			x.rightChild = null;
		}
		y.father = x.father;
		if (x.father == null) {
			root = y;
		} else {
			if (x.isLeftChild()) {
				x.father.leftChild = y;
			} else {
				x.father.rightChild = y;
			}
		}
		y.leftChild = x;
		x.father = y;
	}
	
	/*
	 * right rotate at x
	 */
	private void rightRotate(TreeNode x) {
		TreeNode y = x.leftChild;
		if (y.rightChild != null) {
			x.leftChild = y.rightChild;
			y.rightChild.father = x;
		} else {
			x.leftChild = null;
		}
		y.father = x.father;
		if (x.father == null) {
			root = y;
		} else {
			if (x.isLeftChild()) {
				x.father.leftChild = y;
			} else {
				x.father.rightChild = y;
			}
		}
		y.rightChild = x;
		x.father = y;
		
	}
	
	/*
	 * insert node z
	 */
	private void insertNode(TreeNode z) {
		if (searchNode(root, z) != null) return;
		TreeNode x = root;
		TreeNode y = x;
		
		while (x != null) {
			y = x;
			if (z.compare(x) == 0) return;
			if (z.compare(x) == -1) {
				x = x.leftChild;
			} else {
				x = x.rightChild;				
			}
		}
		z.father = y;
		if (y == null) {
			root = z;
		} else {
			if (z.isLeftChild()) {
				y.leftChild = z;
			} else {
				y.rightChild = z;
			}
		}
		insertFixup(z);
		return;
	}
	
	/*
	 * fix up the tree after insert, start at z
	 */
	private void insertFixup(TreeNode z) {
		TreeNode y;
		while (z.father != null && z.father.isRed) {
			if (z.father.isLeftChild()) {
				y = z.father.father.rightChild;
				if (y != null && y.isRed) {
					z.father.isRed = false;
					y.isRed = false;
					z.father.father.isRed = true;
					z = z.father.father;
				} else {
					if (!z.isLeftChild()) {
						z = z.father;
						leftRotate(z);
					} 
					z.father.isRed = false;
					z.father.father.isRed = true;
					rightRotate(z.father.father);
					
				}
			} else {
				y = z.father.father.leftChild;
				if (y != null && y.isRed) {
					z.father.isRed = false;
					y.isRed = false;
					z.father.father.isRed = true;
					z = z.father.father;
				} else {
					if (z.isLeftChild()) {
						z = z.father;
						rightRotate(z);
					} 
					z.father.isRed = false;
					z.father.father.isRed = true;				
					leftRotate(z.father.father);
					
				}
			}
		}
		root.isRed = false;
	}
	
	/*
	 * delete node z
	 */
	private TreeNode deleteNode(TreeNode z) {
		z = searchNode(root, z);
		if (z == null) return null;
		TreeNode x,y;
		if (z.leftChild == null || z.rightChild == null) {
			y = z;
		} else {
			y = treeSuccessor(z);
		}
		if (y.leftChild != null) {
			x = y.leftChild;
		} else {
			x = y.rightChild;
		}
		if (x != null) {
			x.father = y.father;
		}
		if (y.father == null) {
			root = x;			
		} else {
			if (y.isLeftChild()) {
				y.father.leftChild = x;
			} else {
				y.father.rightChild = x;
			}
		}
		if (z.compare(y) != 0) {
			z.changeValue(y);
		}
		if (!y.isRed) {
			if (x != null) {
				deleteFixup(x);
			} else {
				if (y.father == null) {
					return y;
				}
				x = y;
				deleteFixup(x);
				if (y.isLeftChild()) {
					y.father.leftChild = null;
				} else {
					y.father.rightChild = null;
				}
			}
		}
		return y;
	}
	
	/*
	 * fix up the tree after delete, start at x
	 */
	private void deleteFixup(TreeNode x) {
		TreeNode w;
		// now node is not root and is black
		while (x.father != null && !x.isRed) {
			// now node is left child
			if (x.isLeftChild()) {
				w = x.father.rightChild;
				// sibling is red, case 1      
				if (w != null && w.isRed) {
					w.isRed = false;
					x.father.isRed = true;
					leftRotate(x.father);
					w = x.father.rightChild;
				}
				// sibling is black and sibling's two son is black, case 2
				if ((w.leftChild == null || !w.leftChild.isRed) && (w.rightChild ==null || !w.rightChild.isRed)) {
					w.isRed = true;
					x = x.father;
				} else {
					// the same side nephew is red, case 3
					if (w.rightChild == null || !w.rightChild.isRed) {
						w.leftChild.isRed = false;
						w.isRed = true;
						rightRotate(w);
						w = x.father.rightChild;
					}
					// the different side nephew is red, case 4
					w.isRed = x.father.isRed;
					x.father.isRed = false;
					if (w.rightChild != null) {
						w.rightChild.isRed = false;
					}
					leftRotate(x.father);
				
					x = root;
				}
			} else {
			// now node is right child
				w = x.father.leftChild;
				// sibling is red, case 1
				if (w != null && w.isRed) {
					w.isRed = false;
					x.father.isRed = true;
					rightRotate(x.father);
					w = x.father.leftChild;
				} 
				// sibling is black and sibling's two son is black, case 2
				if ((w.leftChild == null || !w.leftChild.isRed) && (w.rightChild ==null || !w.rightChild.isRed)) {
					w.isRed = true;
					x = x.father;
				} else {
					// the same side nephew is red, case 3
					if (w.leftChild == null || !w.leftChild.isRed) {					
						w.rightChild.isRed = false;
						w.isRed = true;
						leftRotate(w);
						w = x.father.leftChild;
					}
					// the different side nephew is red, case 4
					w.isRed = x.father.isRed;
					x.father.isRed = false;
					if (w.leftChild != null) {
						w.leftChild.isRed = false;
					}
					rightRotate(x.father);
					x = root;
				}
			}
		}
		if (x != null) {
			x.isRed = false;
		}
	}
	
	/*
	 * show the whole node, start at node
	 */
	private String show(TreeNode node, int level, int childNum) {
		String ans = "";
		if (node != null) {
			ans += "level=" + level + " child=" + childNum + " " + node.value;
			if (node.isRed) {
				ans += "(RED)"+System.getProperty("line.separator");
			} else {
				ans += "(BLACK)"+System.getProperty("line.separator");
			}
			ans += show(node.leftChild, level + 1, 0);
			ans += show(node.rightChild, level + 1, 1);
		} else {
			ans += "level=" + level + " child=" + childNum + " null"+System.getProperty("line.separator");
		}
		return ans;
	}
	
	/*
	 * show node from x to y
	 */
	private String show(TreeNode node, TreeNode x, TreeNode y) {
		String ans = "";
		if (node == null) return "";
		if (node.compare(x)>=0) {
			ans += show(node.leftChild, x, y);		
		}
		if (node.compare(x)>=0 && (node.compare(y)<=0 || "".equals(y.value.trim()))) {		
			ans += node.value + " " + node.chineseValue + "\n";
		}
		if (node.compare(y)<=0 || "".equals(y.value.trim())) {
			ans += show(node.rightChild, x, y);
		}
		return ans;
	}
	
	/*
	 * insert a word, English is x, Chinese is y
	 */
	public void insert(String x, String y) {
		insertNode(new TreeNode(x,y));
	}
	
	/*
	 * delete a word, English is x
	 */
	public String delete(String x) {
		TreeNode node = deleteNode(new TreeNode(x,""));
		if (node != null) {
			return node.value; 
		} else {
			return null;
		}
	}	
	
	/*
	 * search a word, English is x
	 */
	public String search(String x) {
		TreeNode node = searchNode(root, new TreeNode(x,""));
		if (node != null) {
			return node.chineseValue; 
		} else {
			return null;
		}
	}
	
	/*
	 * show the whole tree
	 */
	public String show() {
		return show(root, 0, 0);
	}
	
	/*
	 * show the tree from x to y
	 */
	public String show(String x, String y) {
		return show(root, new TreeNode(x,""), new TreeNode(y,""));
	}
	
	/*
	 * member variable, the root of red-black-tree.
	 */
	private TreeNode root = null;
	
	/*
	 * inner class, offer the data structure for every node.
	 */
	private static class TreeNode {
		private TreeNode() {
			this.father = null;
			this.leftChild = null;
			this.rightChild = null;
		}
		private TreeNode(String x, String y) {
			this.value = x;
			this.chineseValue =y;
			this.leftChild = null;
			this.rightChild = null;
			this.isRed = true;
		}
		private TreeNode father;
		
		private TreeNode leftChild;
		private TreeNode rightChild;
		private String value;
		private String chineseValue;
		private boolean isRed;
		
		private boolean isLeftChild() {
			if (this.compare(this.father) == -1) {
				return true;
			} else {
				return false;
			}
		}
		
		private int compare(TreeNode x) {
			String str1 = this.value;
			String str2 = x.value;
			if (str1.equals(str2)) {
				return 0;
			}
			if (str1.compareTo(str2) < 0) return -1;
			return 1;
		}
		private void changeValue(TreeNode x) {
			this.value = x.value;
			this.chineseValue = x.chineseValue;
		}
	}
}
