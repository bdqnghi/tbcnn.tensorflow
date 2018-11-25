

#ifndef AVL_H	
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
		void AVL_Close();	
		void AVL_New();		
		void AVL_Delete();	

		
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
			

			int id;				

			char key[50];		

			int count = 1;
			int BF = 0;

			int left = 0;		
			int right = 0;		

		} n1, n2, n3;			

		int AVL_root_id;		

		int id_count = 1;		
								

		
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


		

		void traverse(int root, int current_height);	
														

		int compare_strings(const std::string &string1, const std::string &string2);	
																						
																						
																						

		void write_node_to_file(AVL_node node);		
													
													

		AVL_node read_node_from_file(int id);	
												
};

#endif	
