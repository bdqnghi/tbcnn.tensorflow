/**
 * 
 */
package de.tuberlin.ise.prog1winf.btree;

/**
 * @author Dave
 *
 */
public class BTree {

	private BTreeNode root;

	public void insert(int value){
		if(root==null){
			this.root = new BTreeNode(value);
			return;
		}
		insert(root,value);
	}
	
	private void insert(BTreeNode node, int value) {
		if (node.value > value) {
			// links
			if (node.left == null) {
				// hier einfuegen
				node.left = new BTreeNode(value);
				return;
			} else {
				// an Kindknoten delegieren
				insert(node.left, value);
			}

		} else if (node.value < value) {
			// rechts
			if (node.right == null) {
				node.right = new BTreeNode(value);
				return;
			} else {
				insert(node.right, value);
			}
		} else {
			return;
		}
	}

}
