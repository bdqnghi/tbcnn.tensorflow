/*
	Filename:		AVL.h
	Author:			Emilio Borges
	Course:			EECS 2510 - Non-Linear Data Structures
	Project:		Binary Search Tree - AVL Tree - Red Black Tree
	Date:			April 7, 2015
	Description:	Header file for AVL.cpp
					This includes the public methods to insert and traverse the AVL tree as well as public access to 
					calculated tree parameters. Has private AVL_node template, root pointer, and helper methods.
*/

#ifndef AVL_H	// start of include guard
#define AVL_H

#include <string>
#include <ctime>

class AVL
{

	public:
		AVL();
		void AVL_Insert(const std::string &word);
		void AVL_Traverse();

		// Tree Parameters GET methods
		unsigned int get_key_comparisons_count();
		unsigned int get_left_child_pointer_change_count();
		unsigned int get_right_child_pointer_change_count();
		unsigned int get_Balance_Factor_change_count();
		unsigned int get_distinct_words_count();
		unsigned int get_total_words_count();
		unsigned int get_tree_height();
		float get_traverse_time();

	private:
		
		struct AVL_node
		{
			// AVL node template
			std::string key;
			unsigned int count = 1;
			int BF = 0;
			AVL_node *left_ptr = NULL;
			AVL_node *right_ptr = NULL;
		};

		AVL_node *AVL_root;

		// Tree Parameters
		unsigned int key_comparisons_count = 0;
		unsigned int left_child_pointer_change_count = 0;
		unsigned int right_child_pointer_change_count = 0;
		unsigned int Balance_Factor_change_count = 0;
		unsigned int distinct_words_count = 0;
		unsigned int total_words_count = 0;
		unsigned int tree_height = 0;
		float traverse_time = 0;


		// --- Helper Functions --- //

		void traverse(AVL_node *node, int current_height);	// Performs an in-order tree traversal to calculate the number
															// of distinct words, total words, and the tree's height.

		int compare_strings(const std::string &string1, const std::string &string2);	// Given two strings, returns:
																						//-1 if string1 < string2
																						// 0 if string1 == string2
																						// 1 if string1 > string2
};

#endif	// end of include guard
// No other code should go after this line