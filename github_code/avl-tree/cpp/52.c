// 09/07/2017 - CS 5460 - Meine, Joel
// Homework #0 - AVL Tree

#include <iostream> // std::cout, std::cin, system()
#include <string> // std::getline()
#include <conio.h> // _getch()
#include "avl-tree.h"

Tree tree;
unsigned int action;
unsigned int node;
signed int factor;

void main_menu();
char key = ' ';

void output_message(unsigned int message)
{
	if (message == 1)
	{
		std::cout << "Type number of action to run: ";
	}
	else if (message == 2)
	{
		std::cout << "Enter Number: ";
	}
	else if (message == 3)
		std::cout << "Error! Non-Valid Input" << std::endl;
	else if (message == 4)
	{
		std::cout << "Completed! Press ENTER to continue...";
		key = _getch();
		system("cls");
		main_menu();
	}
}

void run_action()
{
	output_message(1);
	std::cin >> action;
}

void check_input()
{
	output_message(2);
	std::cin >> node;
	std::cout << std::endl;
}

void actions()
{
	std::cout << std::endl;
	if (action == 1) // create
	{
		tree.create();
	}
	else if (action == 2) // insert
	{
		check_input();
		tree.insert(node);
	}
	else if (action == 3) // remove
	{
		check_input();
		tree.remove(node);
	}
	else if (action == 4) // search
	{
		check_input();
		tree.search(node);
	}
	else if (action == 5) // traverse
	{
		std::cout << "1. Pre-Order" << std::endl;
		std::cout << "2. Post-Order" << std::endl;
		std::cout << "3. In-Order" << std::endl;
		std::cout << std::endl;
		run_action();
		std::cout << std::endl;
		if (action == 1) // pre-order
			tree.traverse("Pre-Order");
		else if (action == 2) // post-order
			tree.traverse("Post-Order");
		else if (action == 3) // in-order
			tree.traverse("In-Order");
	}
	else if (action == 6) // clear
	{
		tree.clear();
	}
	else if (action == 7) // balance
	{
		tree.balance();
	}
	std::cout << std::endl;
	output_message(4);
}

void main_menu()
{
	std::cout << "AVL Tree" << std::endl;
	std::cout << std::endl;
	std::cout << "1. Create" << std::endl;
	std::cout << "2. Insert" << std::endl;
	std::cout << "3. Remove" << std::endl;
	std::cout << "4. Search" << std::endl;
	std::cout << "5. Traverse" << std::endl;
	std::cout << "6. Clear" << std::endl;
	std::cout << "7. Balance" << std::endl;
	std::cout << std::endl;
	run_action();
	actions();
}

int main()
{
	main_menu();

	system("pause");
	return 0;
}