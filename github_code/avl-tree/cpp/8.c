#pragma once

#include <string>
#include <sstream>

namespace tg
{
	enum colorType
	{
		RBTREE_RED,
		RBTREE_BLACK
	};

	enum traversalModel
	{
		PREORDER,
		INORDER,
		POSTORDER
	};

	typedef struct treeNode
	{
		size_t _key;
		colorType _nodeType;
		treeNode * _parent;
		treeNode * _lChild;
		treeNode * _rChild;

		treeNode(const int& value) :_key(value) 
		{
			_parent = nullptr;
			_lChild = nullptr;
			_rChild = nullptr;
		}

		~treeNode()
		{
			printf("destory.. %d\r\n", _key);
		}

		std::string to_string()
		{
			std::stringstream ss;
			ss << "key : " << _key << " -- clrtype : " << (_nodeType == RBTREE_BLACK ? "RBTREE_BLACK" : "RBTREE_RED") << "\r\n";
			return ss.str();
		}
	} Node;

	typedef void(*__process)(Node* node);
	
	class RBTree
	{
	public:
		RBTree();
		~RBTree();

		void insertNode(const int& value);			// ����ڵ�
		void findNode(const int& value);			// ���ҽڵ�
		void removeNode(const int& value);			// ɾ���ڵ�
		std::string to_string();					// �ڵ��ӡ
		size_t size() { return _Tree_Size; }		// �����size

	private:
		void init();								// ��ʼ�������
		void color(Node * node, colorType type_c);	// ���ý����ɫ

		Node * makeHead();							// ����ͷ���
		Node * createNode(const int& value);		// �����½ڵ�
		Node * parent(Node* node);					// ��ȡ�ڵ�ĸ��ڵ�

		void leftMost(Node* node, Node* child);		// �������ӽڵ�
		void rightMost(Node* node, Node* child);	// �������ӽڵ�
		void parentMost(Node* node, Node* parent);	// ���ø��ڵ�

		void treeLeftRotate(Node* node);			// ����
		void treeRightRotate(Node* node);			// ����
		void balanceRBTree(Node* node);				// ƽ�⻯

		bool clrType(Node* node, colorType type);					// ʶ��ڵ���ɫ
		void traversalTree(traversalModel type, __process func);	// ���������

		void preorderTraversal(Node * node);									// �������
		void inorderTraversal(Node * node, __process func = nullptr);			// �������
		void postorderTraversal(Node * node);									// �������

		static void free_node(Node* node) { delete node; node = nullptr; }

	private:
		Node * _Head;
		Node * _Root;
		std::stringstream _SS;
		size_t _Tree_Size;
	};
}

//////////////////////////////////////////////////////////////////////////
/**
	note:
	�����ڶ�̬���ҷ�Χ���

	RB-tree : ������� ƽ������������һ�֣���׼��STL�У�set��map���Ѻ����Ϊ�ײ�洢���ݽṹ�� �������������
		�� �Ҳ���Ԫ��Ѹ��

	* �� RB-tree ͬ���Ļ��� AVL-tree (Adelson-velskii-landis) 

	RB-tree definition : 
		1. �������������������������
		2. ���нڵ㲻�Ǻ�ɫ���Ǻ�ɫ
		3. ���ڵ�Ϊ��ɫ
		4. ����ڵ�Ϊ��ɫ����ô���ӽڵ����Ϊ��ɫ
		5. ��һ�ڵ���nil(��ɫ)���κ�·���������ĺ�ɫ�ڵ���������ͬ

	AVL-tree definition :
		1. ����������������������
		2. ÿ���ڵ�����������߶����ܳ���1

	* �ص㣺

		ƽ�⻯�����壺 ʹÿ�β���Ԫ�ص�ƽ�����ҳ���ΪO(nlogn)
		���������ƽ�⻯ �� ����RB-tree �� AVL-tree��������ʣ������벻����������avl�����ʵĽڵ㣬��������ƽ�⻯��ת����
		��ת������Ϊ �� ���� - ˫��

		ƽ�ⱻ�ƻ��ļ�������� (RB-tree �� AVL-tree ��ʹ�ô˷�����ƽ�ⱻ�ƻ��Ķ����������ƽ�⻯)
		1. ����ڵ���X�ڵ�����ӽڵ���������� -- ���� ---- ���� ���� ����				# ������
		2. ����ڵ���x�ڵ�����ӽڵ���������� -- ���� ---- ˫�� ���� ������ �� ����		# �ڲ����
		3. ����ڵ���x�ڵ�����ӽڵ���������� -- ���� ---- ˫�� ���� ������ �� ����		# �ڲ����
		4. ����ڵ���x�ڵ�����ӽڵ���������� -- ���� ---- ���� ���� ����				# ������


	* ��ת
		case 1 : ����ڵ�Nλ�����ĸ��ϣ�û�и��ڵ�
		case 2 : ����ڵ�N�ĸ��ڵ�Ϊ��ɫ��ֱ�Ӳ���
		case 3 : ����ڵ�N�ĸ��ڵ㣬����ڵ��Ϊ��ɫ	���ڵ㣬����ڵ��Ϊ��ɫ�����游�ڵ㵱���²���ڵ���е�������
		case 4 : ����ڵ�N�ĸ��ڵ�Ϊ��ɫ������ڵ�Ϊ��ɫ����NIL
			(1) ����ڵ�N�ڸ��ڵ���������ϣ����ڵ����游�ڵ���������� (������)	�Ը��ڵ�Ϊ��������
			(2) ����ڵ�N�ڸ��ڵ���������ϣ����ڵ����游�ڵ���������� (������)	�Ը��ڵ�Ϊ��������
			(3) ����ڵ�N�ڸ��ڵ���������ϣ����ڵ����游�ڵ���������� (�ڲ����)	�Ը��ڵ�Ϊ��������������NΪ��������
			(4) ����ڵ�N�ڸ��ڵ���������ϣ����ڵ����游�ڵ���������� (�ڲ����)	�Ը��ڵ�Ϊ��������������NΪ��������
*/