/*
	Filename:		AVL.h
	Author:			Emilio Borges
	Course:			EECS 2510 - Non-Linear Data Structures
	Project:		B-Trees - AVL Tree - Disk-based Comparison
	Date:			April 25, 2015
	Description:	Header file for AVL.cpp
					This includes the public methods to create and delete an AVL .tree file, insert and traverse 
					the AVL tree, and get calculated tree parameters. Has private file stream, AVL_node template, 
					root pointer, tree parameters, and helper methods (read from/write to file, traverse, compare).

*/

#ifndef AVL_H	// start of include guard
#define AVL_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class AVL
{
	public:
		AVL();
		void AVL_Insert(const std::string &word);
		void AVL_Traverse();
		void AVL_Close();	// Closes the avl tree fstream and resets values/parameters for a new tree.
		void AVL_New();		// Same as constructor, used when running multiple texts.
		void AVL_Delete();	// Deletes the avl.tree file

		// Tree Parameters GET methods
		int get_key_comparisons_count();
		int get_left_child_pointer_change_count();
		int get_right_child_pointer_change_count();
		int get_Balance_Factor_change_count();
		int get_distinct_words_count();
		int get_total_words_count();
		int get_tree_height();
		int get_disk_read_count();
		int get_disk_write_count();
		int get_node_size();
		float get_traverse_time();

	private:

		std::fstream file;

		struct AVL_node
		{
			// AVL node template

			int id;				// Holds this node's I.D. number.

			char key[50];		// Max word length is 50 chars.

			int count = 1;
			int BF = 0;

			int left = 0;		// Left and right "pointers".
			int right = 0;		// Node #0 does not exist. 0 is a null pointer.

		} n1, n2, n3;			// The three nodes we're allowed to keep in memory.

		int AVL_root_id;		// Holds the I.D. number of the root node.

		int id_count = 1;		// Any new node's id will be this.
								// After a new node is created, id_count is incremented.

		// Tree Parameters
		int key_comparisons_count = 0;
		int left_child_pointer_change_count = 0;
		int right_child_pointer_change_count = 0;
		int Balance_Factor_change_count = 0;
		int distinct_words_count = 0;
		int total_words_count = 0;
		int tree_height = 0;
		int disk_read_count = 0;
		int disk_write_count = 0;
		float traverse_time = 0;


		// --- Helper Functions --- //

		void traverse(int root, int current_height);	// Performs an in-order tree traversal to calculate the number
														// of distinct words, total words, and the tree's height.

		int compare_strings(const std::string &string1, const std::string &string2);	// Given two strings, returns:
																						//-1 if string1 < string2
																						// 0 if string1 == string2
																						// 1 if string1 > string2

		void write_node_to_file(AVL_node node);		// Takes a node and writes its contents to the tree file.
													// If that node already exists, overwrite its contents with 
													// the new data.

		AVL_node read_node_from_file(int id);	// Given a node I.D., return that node's contents from the tree file.
												// If node I.D. doesn't exist, return NULL node.
};

#endif	// end of include guard
// No other code should go after this line