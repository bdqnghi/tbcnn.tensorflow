package avl.tree;

import bsearch.tree.BTreeSearch;
import bsearch.tree.LDR;
import bsearch.tree.TreeNode;

public class AVLLeftRotate {

	public static void main(String[] args) {
		AVLTreeRootNode rootNode = new AVLTreeRootNode();
		LDR.LDRShow(rootNode.root);
		TreeNode rotateNode = BTreeSearch.searchNodeByKey(rootNode.root, 4);
		leftRotate(rotateNode);
		LDR.LDRShow(rootNode.root);
	}

	// AVL-Tree                                          
	//                    7                      
	//              4            11                 
	//           3     6     9        18            
	//        2                   14      19      
	//						   12    17       22
	//                                      20        
	//
	//		  2,3,4,6,7,9,11,12,14,17,18,19,22
	// TODO ��ȷ����֤
	
	// 1. ��ת�ڵ�������ָ����ת�ڵ㸸�ڵ�
	// 2. ������ת�ڵ�λ�ã�Ϊ����������������������ת�ڵ�ĸ��ڵ�ָ����ת�ڵ�������
	// 3. ��ת�ڵ�ĸ��ڵ�ָ���Լ����Һ���
	// 4. ��ת�ڵ��������Ϊ��ת�ڵ�������������
	// 5. ��ת�ڵ���������� ������ Ϊ�Լ�
	public static void leftRotate(TreeNode rotationNode){
		rotationNode.rightChild.parent = rotationNode.parent;// �������������ڵ�ָ��
		if(rotationNode.parent == null){
			AVLTreeRootNode.root = rotationNode.rightChild;
		}
		else{
			if(rotationNode == rotationNode.parent.leftChild){
				rotationNode.parent.leftChild = rotationNode.rightChild;// �����Լ�����Ϊ������
			}
			else if(rotationNode == rotationNode.parent.rightChild){
				rotationNode.parent.rightChild = rotationNode.rightChild;// �����Լ�����Ϊ������
			}
		}
		rotationNode.parent = rotationNode.rightChild;// ����ԭ�ڵ�ĸ��ڵ�Ϊԭ�ڵ��Һ���
		// ��ת����ڵ�Ϊԭ���������ҽڵ�
		// �����ϵ���ȣ�������ٿ�ָ����ж϶�ֱ�Ӹ�ֵ
		rotationNode.rightChild = rotationNode.parent.leftChild;
		rotationNode.parent.leftChild = rotationNode;// ԭ���������Һ����������Լ�
		// AVL-Tree                                          
		//                      7                      
		//             3                 18                 
		//          2     4          11        19            
		//                  6      9     14        22      
		//					           12   17   20
		// 
		//			2,3,4,6,7,9,11,12,14,17,18,19,20,22
	}
	
	// 1. ��ת�ڵ��������Ϊ��ת�ڵ�������������
	// 2. ��ת�ڵ�������ָ����ת�ڵ㸸�ڵ�
	// 3. ������ת�ڵ�λ�ã�Ϊ����������������������ת�ڵ�ĸ��ڵ�ָ����ת�ڵ�������
	// 4. ��ת�ڵ���������� ������ Ϊ�Լ�
	// 5. ��ת�ڵ�ĸ��ڵ�ָ���Լ����Һ���
	public static TreeNode leftRotate2(TreeNode rotationNode){
		TreeNode rightChild = rotationNode.rightChild;
		rotationNode.rightChild = rightChild.leftChild;// �ƶ�ԭ�ڵ������������ӵ�ԭ�ڵ���Һ���λ��
		if (rightChild.leftChild != null) {
			rightChild.leftChild.parent = rotationNode;
		}
		// �����ת���Ǹ��ڵ�
		rightChild.parent = rotationNode.parent;
		if (rotationNode.parent == null) {
			//AVLTreeRootNode.root = rightChild;
			AVLTreeRootNode.avlRoot = rightChild;
		}
		// ����������֧���Ҵ��֧������������Ҫ�ж���ת�ڵ������ӻ����Һ���
		else if (rotationNode == rotationNode.parent.leftChild) {
			rotationNode.parent.leftChild = rightChild;
		} else {
			rotationNode.parent.rightChild = rightChild;
		}
		rightChild.leftChild = rotationNode;
		rotationNode.parent = rightChild;
		
		// ���¶�������߶ȣ���������!!!!!
		((AVLTreeNode)rotationNode).height 
			= AVLInsert.max(AVLInsert.getHeight(rotationNode.leftChild),
					AVLInsert.getHeight(rotationNode.rightChild)) + 1;
		((AVLTreeNode)rightChild).height 
			= AVLInsert.max(AVLInsert.getHeight(rotationNode.leftChild),
					AVLInsert.getHeight(rotationNode.rightChild)) + 1;
		return rightChild;
	}
}
