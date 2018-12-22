package prova;

import btree.BTreeNode;

public class Questao2 extends BTreeNode<String>{

	public Questao2(String element) {
		super(element);
		
		BTreeNode<String> btreeNodeB = new BTreeNode<String>("B");
		BTreeNode<String> btreeNodeC = new BTreeNode<String>("C");
		BTreeNode<String> btreeNodeD = new BTreeNode<String>("D");
		BTreeNode<String> btreeNodeE = new BTreeNode<String>("E");
		BTreeNode<String> btreeNodeF = new BTreeNode<String>("F");
		BTreeNode<String> btreeNodeG = new BTreeNode<String>("G");
		BTreeNode<String> btreeNodeH = new BTreeNode<String>("H");
		
		this.addLeftChild(btreeNodeB);
		this.addRightChild(btreeNodeC);
			btreeNodeC.addRightChild(btreeNodeD);
				btreeNodeD.addLeftChild(btreeNodeE);
					btreeNodeE.addLeftChild(btreeNodeH);
				btreeNodeD.addRightChild(btreeNodeF);
					btreeNodeF.addRightChild(btreeNodeG);
	}

}
