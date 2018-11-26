#include <iostream>
#include "AVL_templfunc.h"

using namespace std;

template <class T>
//������� ��� ������ �������� � �������:
void ActionsWithAVLTree(Tree<T> *root)
{
	bool high = false;//������ �� ����������� ���������
	int action_ch;

	do
	{
		system ("cls");
		cout << "Choose the actions: \ n";
		cout << "0 - Quit the AVL tree \ n";
		cout << "1 - Add element / s to the tree \ n";
		cout << "2 - Remove an element from the tree \ n";
		cout << "3 - Output the tree to the screen \ n";
		cout << ">";

		cin >> action_ch;
		system("cls");

		switch (action_ch)
		{
		case 1:
		{
			int count;//���-�� ��������� � ������
			cout << "Enter the number of elements to add to the tree:";
			cin >> count;
			cout << endl;

			T add_el;//����������� ������� ���� T

			//����������� ������ �������� � ������:
			for (int i = 0; i < count; i++)
			{
				cout << "Enter the element to add to the AVL tree:";
				cin >> add_el;
				SearchAndInsert(add_el, &root, high);//������� ��������� ��. � ������ �����
			}
			system("pause");
			break;
		}
		case 2:
		{
			T del_el;//��������� ������� ���� T
			cout << "Enter the element you want to delete:";
			cin >> del_el;
			Delete(del_el, &root, high);//�������� ��������� ��������
			cout << endl;
			system("pause");
			break;
		}
		case 3:
		{
			cout << "����� ����������������� AVL-������: " << endl;
			PrintTree(root, 0);//����� ����������� ������
			system("pause");
			break;
		}
		}
	} while (action_ch != 0);
}

/ * ------------------------------------------------ -------------------------------------------------- ----- *
Task: implementation of building a balanced tree (AVL-tree).
| | ------------------------------------------------- - ------------------------------------------------- - -----
The purpose of main_10.h: demonstration of the program (testing the AVL-tree).
| | ------------------------------------------------- - ------------------------------------------------- - -----
| | Assignment AVL_templfunc.h: create the necessary functions for building an AVL-tree:
| | `search function to insert this element into the desired place in the tree;
| | `function for balancing the left side of the tree;
| | `function for balancing the right side of the tree;
| | `helper function to delete a node;
| | `function to delete a node;
| | `function for outputting a tree (bypassing it). | | | | | | | |
| | ------------------------------------------------- - ------------------------------------------------- - -----
Note: in main_10.h there is a function for calling all necessary program functions with the selected
| | type of user data (built on templates).
* ------------------------------------------------- -------------------------------------------------- ---- * /
int main_10()
{
	setlocale(LC_ALL, "Russian");

	int tchoice;//����� ���� ������ �������������
	cout << "Select the data type for the tree elements: \ n";
	cout << "1 - int; 2 - float; 3 - double; 4 - char: ";
	cin >> tchoice;

	//�� ������ ������������ ���������� ������������ ��� ������:
	switch (tchoice)
	{
	case 1://��� ���� int:
	{
		//������ (��� � ��� �������� ������) ����� ���� int:
		Tree<int>* root = (Tree<int>*)NULL;

		//�������� ������� � ����� ��������� int:
		ActionsWithAVLTree(root);
		break;
	}
	case 2://��� ���� float:
	{
		//������ (��� � ��� �������� ������) ����� ���� float:
		Tree<float>* root = (Tree<float>*)NULL;

		//�������� ������� � ����� ��������� float:
		ActionsWithAVLTree(root);
		break;
	}
	case 3://��� ���� double:
	{
		//������ (��� � ��� �������� ������) ����� ���� double:
		Tree<double>* root = (Tree<double>*)NULL;

		//�������� ������� � ����� ��������� double:
		ActionsWithAVLTree(root);
		break;
	}
	case 4://��� ���� char:
	{
		//������ (��� � ��� �������� ������) ����� ���� char:
		Tree<char>* root = (Tree<char>*)NULL;

		//�������� ������� � ����� ��������� char:
		ActionsWithAVLTree(root);
		break;
	}
	default://����� ��������� ��� ��������!
	{
		cout << "Invalid type ... \ n";
		break;
	}
	}

	cout << endl;
	system("pause");
	return 0;
}