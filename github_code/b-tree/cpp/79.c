#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;



struct node
{
	int key_value;
	node* p_left;
	node* p_right;
};

/*struct pole
{
	int key;
	int level;
	pole* p_next;
};*/

void menu(node* p_tree/*, pole* pol*/);



node* find_max(node* p_tree)
{
	if (p_tree == NULL)
	{
		return NULL;
	}
	if (p_tree->p_right == NULL)
	{
		return p_tree;
	}
	return find_max(p_tree);
}

node* remove_max_node(node* p_tree, node* p_max_node)
{
	if (p_tree == NULL)
	{
		return NULL;
	}
	if (p_tree == p_max_node)
	{
		return p_max_node->p_left;
	}
	p_tree->p_right = remove_max_node(p_tree, p_max_node);
	return p_tree;
}

node* remove(node* p_tree, int key)
{
	if (p_tree == NULL)
	{
		return NULL;
	}
	if (p_tree->key_value == key)
	{
		if (p_tree->p_left == NULL)
		{
			node* p_right_subtree = p_tree->p_right;
			delete p_tree;
			return p_right_subtree;
		}
		if (p_tree->p_right == NULL)
		{
			node* p_left_subtree = p_tree->p_left;
			delete p_tree;
			return p_left_subtree;
		}
		node* p_max_node = find_max(p_tree);
		p_max_node->p_left = remove_max_node(p_tree->p_left, p_max_node);
		p_max_node->p_right = p_tree->p_right;
		delete p_tree;
		return p_max_node;
	}
	else if (key < p_tree->key_value)
	{
		p_tree->p_left = remove(p_tree->p_left, key);
	}
	else
	{
		p_tree->p_right = remove(p_tree->p_right, key);
	}
	return p_tree;
}

node* del(node* p_tree)
{
	int key;
	system("cls");
	cout << "����� ������� ����� ������?\n";
	cin >> key;
	p_tree = remove(p_tree, key);
	return p_tree;
}

node* insert(node* p_tree, int key)
{
	if (p_tree == NULL)
	{
		node* p_new_tree = new node;
		p_new_tree->p_left = NULL;
		p_new_tree->p_right = NULL;
		p_new_tree->key_value = key;
		return p_new_tree;
	}
	if (key < p_tree->key_value)
	{
		p_tree->p_left = insert(p_tree->p_left, key);
	}
	else
	{
		p_tree->p_right = insert(p_tree->p_right, key);
	}
	return p_tree;
}

node* vvod(node* p_tree)
{
	int key;
	system("cls");
	cout << "������� ��������";
	cin >> key;
	p_tree = insert(p_tree, key);
	return p_tree;
}

node* search(node*p_tree, int key)
{
	if (p_tree == NULL)
	{
		return NULL;
	}
	else if (key == p_tree->key_value)
	{
		return p_tree;
	}
	else if (key < p_tree->key_value)
	{
		return search(p_tree->p_left, key);
	}
	else
	{
		return search(p_tree->p_right, key);
	}
}

void poisk(node* p_tree)
{
	int key;
	system("cls");
	cout << "������� ������� ����";
	cin >> key;
	p_tree = search(p_tree, key);
	if (p_tree)
	{
		system("cls");
		cout << "������� ������\n";
		system("pause");
	}
	else
	{
		system("cls");
		cout << "������� �� ������\n";
		system("pause");
	}
}

void destroy_tree(node* p_tree)
{
	if (p_tree != NULL)
	{
		destroy_tree(p_tree->p_left);
		destroy_tree(p_tree->p_right);
		delete p_tree;
	}
}



void output(node* p_tree,int level)
{
	if (p_tree)
	{
		output(p_tree->p_left, level + 1);
		for (int i = 0; i < level; i++)
		{
			cout << "   ";
		}
		cout << p_tree->key_value << "\n";
		output(p_tree->p_right, level + 1);
	}
}

void obhod(node* p_tree,/* pole*& pol*/ int level, int& max_level,int& sch,vector<int>& l, vector<int>& k)
{   
	/*pole* pol_new = new pole;
	pol_new->p_next = pol; 
	pol_new->key = NULL;
	if (p_tree == NULL)
	{
		return NULL;
	}*/
	
	if (p_tree != NULL)
	{
		
		/*pol_new->key = p_tree->key_value;
		pol_new->level = level;
		*/
		l.push_back(level);
		k.push_back(p_tree->key_value);
		sch++;
		if (p_tree->p_left != NULL)
		{
			obhod(p_tree->p_left, /*pol*/ level + 1, max_level, sch,l,k);
		}
		if (p_tree->p_right != NULL)
		{
			obhod(p_tree->p_right, /*pol*/ level + 1, max_level, sch,l,k);
		}
		
		if (level > max_level)
		{
			max_level = level;
		}
		
	}
	
	
/*	return pol_new;*/
}


void output2(node* p_tree/*, pole*& pol*/, int level)
{
	int i;
	int j;
	vector<int> l;
	vector<int> k;
	int max_level=0;
	int sch = 0;
	obhod(p_tree, level, max_level, sch, l, k);
	
	/*pole* buf;
	pol = obhod(p_tree, pol, level, max_level,sch);
	cout << pol->key;
	buf = pol->p_next;
	cout << buf->key;
	buf = pol->p_next;
	cout << buf->key;
	buf = pol;
	for (int i = 0; i < max_level; i++)
	{
		for (int j = 0; j <= sch; j++)
		{   
			
			if (buf != NULL)
			{
				cout << "jg";
				if (buf->level == i)
				{
					cout << "fef";
					cout << buf->key << " ";
				}
				buf = buf->p_next;
				
			}
			

		}
		cout << "\n";
		buf = pol;
	}*/

	for (i = 0; i <=max_level; i++)
	{
		for (j = 0; j < sch; j++)
		{
		
			if (l[j] == i)
			{
				cout << k[j] << " ";
			}
		}
		cout << "\n";
	}

	

}

void menu(node* p_tree/* pole* pol*/)
{
	int cs;
	int level = 0;
	system("cls");
	cout << "1.�������� �������\n" << "2.����� �������\n" << "3.������� ����\n" << "4.���������� ������\n" << "5.������� ������\n" << "6.OUTPUT2\n"<<"7.EXIT\n";
	cin >> cs;
	switch (cs)
	{
	case 1:
	p_tree=vvod(p_tree);

		break;
	case 2:
		poisk(p_tree);

		break;

	case 3:
		p_tree = del(p_tree);
		break;

	case 4:
		destroy_tree(p_tree);
		p_tree = NULL;
		break;

	case 5:
		system("cls");
		output(p_tree,level);
		system("pause");
		break;
	case 6:
		system("cls");
		level = 0;
		output2(p_tree,/* pol*/ level);
		system("pause");
		break;

	case 7:
		goto ex;
		break;

	default:
		system("cls");
		cout << "����������-�� �� ��.";
		system("pause");
		break;
	}
	menu(p_tree/*, pol*/);
ex:;

}

void main()
{	
	setlocale(LC_ALL, "Russian");
	node* p_tree=NULL;
	/*pole* pol=NULL;*/
	menu(p_tree/*,pol*/);
}