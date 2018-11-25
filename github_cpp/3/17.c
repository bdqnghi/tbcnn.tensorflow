

#ifndef AVL_H	
#define AVL_H

#include <string>
#include <ctime>

class AVL
{

	public:
		AVL();
		void AVL_Insert(const std::string &word);
		void AVL_Traverse();

		
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
			
			std::string key;
			unsigned int count = 1;
			int BF = 0;
			AVL_node *left_ptr = NULL;
			AVL_node *right_ptr = NULL;
		};

		AVL_node *AVL_root;

		
		unsigned int key_comparisons_count = 0;
		unsigned int left_child_pointer_change_count = 0;
		unsigned int right_child_pointer_change_count = 0;
		unsigned int Balance_Factor_change_count = 0;
		unsigned int distinct_words_count = 0;
		unsigned int total_words_count = 0;
		unsigned int tree_height = 0;
		float traverse_time = 0;


		

		void traverse(AVL_node *node, int current_height);	
															

		int compare_strings(const std::string &string1, const std::string &string2);	
																						
																						
																						
};

#endif	
