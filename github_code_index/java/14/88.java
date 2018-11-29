package prova;

import org.junit.Test;
import btree.BTreeNode;

public class Questao4 {
	
	@Test
	public void testQuestao2(){
		
		BTreeNode<String> btreeNodeA = new BTreeNode<String>("A");
		BTreeNode<String> btreeNodeB = new BTreeNode<String>("B");
		BTreeNode<String> btreeNodeC = new BTreeNode<String>("C");
		BTreeNode<String> btreeNodeD = new BTreeNode<String>("D");
		BTreeNode<String> btreeNodeE = new BTreeNode<String>("E");
		BTreeNode<String> btreeNodeF = new BTreeNode<String>("F");
		BTreeNode<String> btreeNodeG = new BTreeNode<String>("G");
		BTreeNode<String> btreeNodeH = new BTreeNode<String>("H");
		
		btreeNodeA.addLeftChild(btreeNodeB);
		btreeNodeA.addRightChild(btreeNodeC);
			btreeNodeC.addRightChild(btreeNodeD);
				btreeNodeD.addLeftChild(btreeNodeE);
					btreeNodeE.addLeftChild(btreeNodeH);
				btreeNodeD.addRightChild(btreeNodeF);
					btreeNodeF.addRightChild(btreeNodeG);
		
		System.out.println(btreeNodeA.toString());	
		percorrer(btreeNodeA);
	}
	
	private void percorrer(BTreeNode<String> btreeNode){
		
		//Percorrer primeiro elementos do lado direito
		if (btreeNode.getRightChild() != null) {
			System.out.println(btreeNode.getRightChild().toString());
			percorrer(btreeNode.getRightChild());
		}
		
		if (btreeNode.getLeftChild() != null) {
			System.out.println(btreeNode.getLeftChild().toString());
			percorrer(btreeNode.getLeftChild());
		}
		
	}
}