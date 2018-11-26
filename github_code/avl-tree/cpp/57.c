#include "avltree.h"
#include <stack>
#include <Windows.h>
using namespace std;

//������ ��´�
//������ ��� ���� ����, ������ �Ͼ ����̴�
void AVLTree::reBalance(AVLNODE *n)
{
	SetBalance(n);

	if (n->balance == -2)
	{
		if (height(n->left->left) >= height(n->left->right))
			n = rotateRight(n);
		else
			n = rotateLeftThenRight(n);
	}
	else if (n->balance == 2)
	{
		if (height(n->right->right) >= height(n->right->left))
			n = rotateLeft(n);
		else
			n = rotateRightThenLeft(n);
	}

	if (n->parent != NULL)
		reBalance(n->parent);
	else
		root = n;
}

//
void AVLTree::SetBalance(AVLNODE *n)
{
	n->balance = height(n->right) - height(n->left);
}

int AVLTree::height(AVLNODE *n)
{
	if (n == NULL)
		return -1;

	int leftHeight = height(n->left);
	int rightHeight = height(n->right);

	if (leftHeight > rightHeight)
		return leftHeight + 1;

	return rightHeight + 1;

}

///////////////////////////////////
//ȸ��
AVLNODE* AVLTree::rotateLeft(AVLNODE *a)
{
	AVLNODE *b = a->right;
	b->parent = a->parent;
	a->right = b->left;

	if (a->right != NULL)
		a->right->parent = a;

	b->left = a;
	a->parent = b;

	if (b->parent != NULL) {
		if (b->parent->right == a) {
			b->parent->right = b;
		}
		else {
			b->parent->left = b;
		}
	}

	SetBalance(a);
	SetBalance(b);
	return b;
}

AVLNODE* AVLTree::rotateRight(AVLNODE *a) {
	AVLNODE *b = a->left;
	b->parent = a->parent;
	a->left = b->right;

	if (a->left != NULL)
		a->left->parent = a;

	b->right = a;
	a->parent = b;

	if (b->parent != NULL) {
		if (b->parent->right == a) {
			b->parent->right = b;
		}
		else {
			b->parent->left = b;
		}
	}

	SetBalance(a);
	SetBalance(b);
	return b;
}

//LRȸ��
AVLNODE* AVLTree::rotateLeftThenRight(AVLNODE *n)
{
	n->left = rotateLeft(n->left);
	return rotateRight(n);
}

AVLNODE* AVLTree::rotateRightThenLeft(AVLNODE *n)
{
	n->right = rotateRight(n->right);
	return rotateLeft(n);
}

//insert������ ��� ����� ��ȿ���̹Ƿ� �ٸ� �Լ��� ��ü�Ѵ�.
bool AVLTree::insert(int key, carArgument data)
{
	access.lock();
	if (root == NULL)
		root = new AVLNODE(key, data, NULL);

	else
	{
		AVLNODE *parentNode = NULL;
		AVLNODE *curNode = root;

		while (true)
		{
			//�� �ߺ��ϰ�� 
			if (curNode->key == key)
			{
				//������
				access.unlock();
				return false;
			}

			parentNode = curNode;

			bool goLeft = curNode->key > key;
			curNode = goLeft ? curNode->left : curNode->right;

			//���� ��尡 NULL�̶��
			if (curNode == NULL)
			{
				if (goLeft)
					parentNode->left = new AVLNODE(key, data, parentNode);
				else
					parentNode->right = new AVLNODE(key, data, parentNode);

				//������ ��´�.
				reBalance(parentNode);
				break;
			}
		}
	}

	access.unlock();
	return true;
}

//Ʈ���� ��������� ��������
//�Ǵ� ã�� Ű���� ���� ���� ����
bool AVLTree::remove(int key) {
	bool r = false;

	if (root == NULL)
		return r;

	access.lock();

	AVLNODE *n = root,
			*parentNode = root,
			*delNode = NULL,
			*childNode = root;

	while (childNode != NULL) {
		parentNode = n;
		n = childNode;
		childNode = key >= n->key ? n->right : n->left;
		if (key == n->key)
			delNode = n;
	}

	if (delNode != NULL) {
		delNode->key = n->key;

		childNode = n->left != NULL ? n->left : n->right;

		if (root->key == key) {
			root = childNode;
		}
		else {
			if (parentNode->left == n) {
				parentNode->left = childNode;
			}
			else {
				parentNode->right = childNode;
			}
			reBalance(parentNode);
		}
		r = true;
	}
	
	access.unlock();

	return r;
}

//Ž��
AVLNODE* AVLTree::search(int key)
{
	AVLNODE *searchNode = root;
	access.lock();

	if (root != NULL)
	{
		while (true)
		{
			if (searchNode == NULL) //ã�°��� ���ٸ�
			{
				searchNode = NULL;
				break;
			}

			if (searchNode->key == key) //ã�°��̶��
				break;
			else if (searchNode->key > key)
				searchNode = searchNode->left;
			else
				searchNode = searchNode->right;
		}
	}

	access.unlock();
	return searchNode;
}

void AVLTree::update(AVLNODE* updateNode, int operate, void* data)
{
	switch (operate)
	{
	case 1: //������
		updateNode->Data.sortOfcar = std::stoi(*static_cast<std::string *>(data)); break;
	case 2: //���ұݾ� �߰�
		updateNode->Data.totalPrice += std::stoi(*static_cast<std::string *>(data)); break;
	case 3: //�湮��¥ ����
		updateNode->Data.lastVisit = (*static_cast<std::string *>(data)); break;
	case 4: //��ȭ �߰�
		updateNode->Data.movieName.push_back((*static_cast<std::string *>(data))); break;
	case 5: //��ȭ ��û �ð� �߰�
		updateNode->Data.totalmovieTime += std::stoi(*static_cast<std::string *>(data)); break;
	case 6:
		updateNode->Data.visitCount += std::stoi(*static_cast<std::string *>(data)); break;
	}
}

void AVLTree::save(FILE *fp)
{
	access.lock();

	if (root == NULL)
		return;

	char saveBuf[1024] = { 0, };
	stack<AVLNODE*> nodestack;
	nodestack.push(root);

	while (nodestack.empty() == false)
	{
		AVLNODE* node = nodestack.top();

		//����ȣ, ������, �ѱݾ�, ��ȭ���ð�, �������湮��¥, ����ȭ���
		fwrite(&node->Data.carnumber, 1, sizeof(int), fp);
		fwrite(&node->Data.sortOfcar, 1, sizeof(int), fp);
		fwrite(&node->Data.totalPrice, 1, sizeof(int), fp);
		fwrite(&node->Data.visitCount, 1, sizeof(int), fp);
		fwrite(&node->Data.totalmovieTime, 1, sizeof(int), fp);
		const char *lastvisit = node->Data.lastVisit.c_str();
		int lastvisitlen = strlen(lastvisit);
		fwrite(&lastvisitlen, 1, sizeof(int), fp);
		fwrite(lastvisit, 1, lastvisitlen, fp);

		//��ȭ ���� ���
		int movielist = node->Data.movieName.size();
		fwrite(&movielist, 1, sizeof(int), fp);
		list<string>::iterator End = node->Data.movieName.end();
		for (list<string>::iterator iterPos = node->Data.movieName.begin();
			iterPos != End; iterPos++)
		{
			const char* movie = iterPos->c_str();
			int movielen = strlen(movie);
			fwrite(&movielen, 1, sizeof(int), fp);
			fwrite(movie, 1, movielen, fp);
		}
				
		nodestack.pop();

		if (node->right)
			nodestack.push(node->right);
		if (node->left)
			nodestack.push(node->left);
	}
	access.unlock();
}


//����
void AVLTree::load(FILE *fp)
{
	int carnumber;

	while (fread(&carnumber, 1, sizeof(int), fp) > 0)
	{
		carArgument readArgument;
		readArgument.carnumber = carnumber;

		fread(&readArgument.sortOfcar, 1, sizeof(int), fp);
		fread(&readArgument.totalPrice, 1, sizeof(int), fp);
		fread(&readArgument.visitCount, 1, sizeof(int), fp);
		fread(&readArgument.totalmovieTime, 1, sizeof(int), fp);
		

		//�ֱ� �湮 ��¥
		int lastvisitlen;
		char lastvisit[1024] = { 0, };
		fread(&lastvisitlen, 1, sizeof(int), fp);
		fread(lastvisit, 1, lastvisitlen, fp);
		readArgument.lastVisit = lastvisit;

		//��ȭ ����
		int movienumber;
		fread(&movienumber, 1, sizeof(int), fp);
		for (int i = 0; i < movienumber; i++)
		{
			int movielen; char movie[1024] = { 0, };
			fread(&movielen, 1, sizeof(int), fp);
			fread(movie, 1, movielen, fp); 			
			readArgument.movieName.push_back(movie);
		}
		
		this->insert(carnumber, readArgument);
	}
	
}

//������
AVLTree::AVLTree()
{
	root = NULL;
}

//�Ҹ���
AVLTree::~AVLTree()
{
	delete root;
}

AVLNODE* AVLTree::getRoot()
{
	return root;
}

//////////////////////////////////////
//������ ���

int AVLTree::getvisitCount()
{
	return root->Data.visitCount;
}