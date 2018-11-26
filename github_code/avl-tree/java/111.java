package avl.tree;

import bsearch.tree.BTreeSearch;
import bsearch.tree.LDR;
import bsearch.tree.TreeNode;

public class AVLRightRotate {

	public static void main(String[] args) {
		AVLTreeRootNode rootNode = new AVLTreeRootNode();
		LDR.LDRShow(rootNode.root);
		TreeNode rotateNode = BTreeSearch.searchNodeByKey(rootNode.root, 4);
		rightRotate(rotateNode);
		LDR.LDRShow(rootNode.root);
	}

	// AVL-Tree                                          
	//                    7                      
	//              4            11                 
	//           3     6     9        18            
	//        2                   14      19      
	//						   12    17       22
	//                                      20    
	
	@Deprecated
	//    18
	//  14
	// 12
	// ���������̫�У�39�б���ָ��
	public static void rightRotate(TreeNode rotationNode){
//		if(rotationNode.leftChild != null && rotationNode.parent != null){
//			rotationNode.leftChild.parent = rotationNode.parent;// �������������ڵ�ָ��
//			rotationNode.parent.leftChild = rotationNode.leftChild;// ���ĸ��ڵ�������ָ��
//			rotationNode.parent = rotationNode.leftChild;// �����Լ�����Ϊ������
//			rotationNode.leftChild = rotationNode.parent.rightChild;// ��ת����ڵ�Ϊԭ���������ҽڵ�
//			rotationNode.parent.rightChild = null;// ԭ���������ҽڵ����
//			rotationNode.parent.rightChild = rotationNode;// ԭ���������Һ����������Լ�
//		}
		rotationNode.leftChild.parent = rotationNode.parent;// �������������ڵ�ָ��
		if(rotationNode.parent == null){
			AVLTreeRootNode.root = rotationNode.leftChild;
		}
		else{
			if(rotationNode == rotationNode.parent.leftChild){
				rotationNode.parent.leftChild = rotationNode.leftChild;// �����Լ�����Ϊ������
			}
			else if(rotationNode == rotationNode.parent.rightChild){
				rotationNode.parent.rightChild = rotationNode.leftChild;// �����Լ�����Ϊ������
			}
		}
		rotationNode.parent = rotationNode.leftChild;// ����ԭ�ڵ�ĸ��ڵ�Ϊԭ�ڵ��Һ���
		// ��ת����ڵ�Ϊԭ���������ҽڵ�
		// �����ϵ���ȣ�������ٿ�ָ����ж϶�ֱ�Ӹ�ֵ
		rotationNode.leftChild = rotationNode.parent.rightChild;
		rotationNode.parent.rightChild = rotationNode;// ԭ���������Һ����������Լ�
		// AVL-Tree                                          
		//                    7                      
		//              3            11                 
		//           2     4     9        18            
		//                   6        14      19      
		//						   12    17       22
		// 
	}
	
	// 1. ��ת�ڵ��������Ϊ��ת�ڵ�������������
		// 2. ��ת�ڵ�������ָ����ת�ڵ㸸�ڵ�
		// 3. ������ת�ڵ�λ�ã�Ϊ����������������������ת�ڵ�ĸ��ڵ�ָ����ת�ڵ�������
		// 4. ��ת�ڵ���������� ������ Ϊ�Լ�
		// 5. ��ת�ڵ�ĸ��ڵ�ָ���Լ����Һ���
		public static TreeNode rightRotate2(TreeNode rotationNode){
			TreeNode leftChild = rotationNode.leftChild;
			rotationNode.leftChild = leftChild.rightChild;// �ƶ�ԭ�ڵ������������ӵ�ԭ�ڵ���Һ���λ��
			if(leftChild.rightChild != null){
				leftChild.rightChild.parent = rotationNode;
			}
			// �����ת���Ǹ��ڵ�
			leftChild.parent = rotationNode.parent;
			if(rotationNode.parent == null){
				//AVLTreeRootNode.root = leftChild;
				AVLTreeRootNode.avlRoot = leftChild;
			}
			// ����������֧���Ҵ��֧������������Ҫ�ж���ת�ڵ������ӻ����Һ���
			else if(rotationNode == rotationNode.parent.leftChild){
				rotationNode.parent.leftChild = leftChild;
			}
			else{
				rotationNode.parent.rightChild = leftChild;
			}
			leftChild.rightChild = rotationNode;
			rotationNode.parent = leftChild;
			
			// ���¶�������߶ȣ���������!!!!!
			((AVLTreeNode)rotationNode).height 
				= AVLInsert.max(AVLInsert.getHeight(rotationNode.leftChild),
						AVLInsert.getHeight(rotationNode.rightChild)) + 1;
			((AVLTreeNode)leftChild).height 
				= AVLInsert.max(AVLInsert.getHeight(rotationNode.leftChild),
						AVLInsert.getHeight(rotationNode.rightChild)) + 1;
			return leftChild;
		}
}
