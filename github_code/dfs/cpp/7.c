//g++ -g -Wall -o assignment1 main.cpp xml_parse.cpp node_class.cpp

#include "node_class.h"
#include "tree_node.h"
#include "xml_parse.h"
#include <cassert>
#include <stdlib.h> 
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std;
using namespace steffen_space;

tree_node<node_class>* tree = new tree_node<node_class>();
void call_user();
node_class* random_child(tree_node<node_class>* parent);
void debug_tree(vector<string> search_test);

void debug_tree_random(vector<string> search_test, int num_of_test);

int main()
{
	srand(time(NULL));
	vector<string> search_test {"ROOT",
								"Idle",
								"Use Computer",
								"Patrol",
								"Incoming Projectile",
								"Evade",
								"Combat",
								"Melee",
								"Flee",
								"Attack",
								"Ranged",
								"Weapon 1",
								"Weapon 2",
								"Weapon 3"};
	
	vector<string> search_balanced {"ROOT",
									"branch1",
									"branch2",
									"branch3",
									"branch11",
									"branch12",
									"branch21",
									"branch22",
									"branch31",
									"branch32",
									"leaf1",
									"leaf2",
									"leaf3",
									"leaf4",
									"leaf5",
									"leaf6",
									"leaf7",
									"leaf8",
									"leaf9",
									"leaf10"};
	
	vector<string> search_bottom_heavy {"ROOT",
										"branch1",
										"branch2",
										"branch3",
										"branch11",
										"branch21",
										"branch31",
										"leaf1",
										"leaf2",
										"leaf3",
										"leaf4",
										"leaf5",
										"leaf6",
										"leaf7",
										"leaf8",
										"leaf9",
										"leaf10"};

	vector<string> search_top_heavy {"ROOT",
									"branch1",
									"branch2",
									"branch3",
									"branch11",
									"branch12",
									"branch21",
									"branch22",
									"branch31",
									"branch32",
									"leaf1",
									"leaf2",
									"leaf3",
									"leaf4",
									"leaf5",
									"leaf6"};

	// Left and Right heavy trees use the same nodes as balanced
	//****** pass the xml tree here ******
	tree = parse_into_tree("/home/stoplime/ai_class/xml_parser/test.xml");
	
	cout << "Searches each element once" << endl;
	debug_tree(search_test);

	cout << "------------------------------------" << endl;
	cout << "Random searches with 100,000 iterations" << endl;
	debug_tree_random(search_test, 100000);
	cout << "------------------------------------" << endl;

	print(tree);
	cout << "------------------------------------" << endl;
	call_user();

	return 0;
}

void call_user(){
	while(true){
		cout << "Event ('quit' to exit) : ";
		string user_input = "";
		getline(cin, user_input);
		//cout << user_input << endl;
		if(user_input == "quit"){
			return;
		}
		int count = 0;
		tree_node<node_class>* search = breadth_search(user_input, tree, count);
		if(search == NULL){
			cout << "Search not found!" << endl;
		}
		else{
			node_class* leaf = random_child(search);
			cout << leaf->to_string() << endl;
		}
	}
}

node_class* random_child(tree_node<node_class>* parent){
	if(parent->get_num_children() == 0){
		return &parent->get_data();
	}
	else{
		int rand_num = rand() % parent->get_num_children();
		return random_child(parent->get_child(rand_num));
	}
}

void debug_tree(vector<string> search_test){
	vector< vector< int* > > depth_count;
	vector< vector< tree_node< node_class >* > > search_result;
	for(int i=0; i < 3; i++){
		depth_count.push_back(vector< int* >());
		search_result.push_back(vector< tree_node< node_class >* >());
		for(size_t j=0; j < search_test.size(); j++){
			depth_count[i].push_back(new int(0));
			if(i==0){
				// i == 0 is the non-recursive depth-first search
				search_result[i].push_back(depth_search(search_test[j], tree, *depth_count[i][j]));
			}
			else if(i==1){
				// i == 1 is the recursive depth-first search
				search_result[i].push_back(depth_search_recursive(search_test[j], tree, *depth_count[i][j]));
			}
			else{
				// i == 2 is the breadth-first search
				search_result[i].push_back(breadth_search(search_test[j], tree, *depth_count[i][j]));
			}
		}
	}
	
	vector< float > sum;
	vector< int > num_found;
	for(int i=0; i < 3; i++){
		sum.push_back(0);
		num_found.push_back(0);
		if(i==0){
			// i == 0 is the non-recursive depth-first search
			cout << "For the non-recursive depth-first search: " << endl;
		}
		else if(i==1){
			// i == 1 is the recursive depth-first search
			cout << "For the recursive depth-first search: " << endl;
		}
		else{
			// i == 2 is the breadth-first search
			cout << "For the breadth-first search: " << endl;
		}
		for (size_t j=0; j < search_test.size(); j++){
			if(search_result[i][j] == NULL){
				cout << "search[" << j << "] == null" << endl;
			}
			else{
				cout << "search[" << j << "] \ttook " << *depth_count[i][j] << " steps to search\t'" << search_test[j] << "'" << endl;
				sum[i] += *depth_count[i][j];
				num_found[i]++;
				//print(search_result[i][j]);
			}
		}
		cout << endl;
	}
	cout << "total number of loops:" << endl;
	cout << "depth non-recursive:\t" << sum[0] << endl;
	cout << "depth recursive:\t" << sum[1] << endl;
	cout << "breadth:\t\t" << sum[2] << endl;

	cout << endl;
	cout << "average number of loops:" << endl;
	cout << "depth non-recursive:\t" << sum[0]/num_found[0] << endl;
	cout << "depth recursive:\t" << sum[1]/num_found[0] << endl;
	cout << "breadth:\t\t" << sum[2]/num_found[0] << endl;
	cout << endl;
}

void debug_tree_random(vector<string> search_test, int num_of_test){
	vector< vector< int* > > depth_count;
	vector< vector< tree_node< node_class >* > > search_result;
	for(int i=0; i < 3; i++){
		depth_count.push_back(vector< int* >());
		search_result.push_back(vector< tree_node< node_class >* >());
		for(int j=0; j < num_of_test; j++){
			int random_index = rand() % search_test.size();
			depth_count[i].push_back(new int(0));
			if(i==0){
				// i == 0 is the non-recursive depth-first search
				search_result[i].push_back(depth_search(search_test[random_index], tree, *depth_count[i][j]));
			}
			else if(i==1){
				// i == 1 is the recursive depth-first search
				search_result[i].push_back(depth_search_recursive(search_test[random_index], tree, *depth_count[i][j]));
			}
			else{
				// i == 2 is the breadth-first search
				search_result[i].push_back(breadth_search(search_test[random_index], tree, *depth_count[i][j]));
			}
		}
	}
	vector< float > sum;
	vector< int > num_found;
	for(int i=0; i < 3; i++){
		sum.push_back(0);
		num_found.push_back(0);
		if(i==0){
			// i == 0 is the non-recursive depth-first search
			cout << "For the non-recursive depth-first search: " << endl;
		}
		else if(i==1){
			// i == 1 is the recursive depth-first search
			cout << "For the recursive depth-first search: " << endl;
		}
		else{
			// i == 2 is the breadth-first search
			cout << "For the breadth-first search: " << endl;
		}
		for (int j=0; j < num_of_test; j++){
			if(search_result[i][j] == NULL){
				cout << "search[" << j << "] == null" << endl;
			}
			else{
				//cout << "search[" << j << "] \ttook " << *depth_count[i][j] << " steps to search\t'" << search_test[j] << "'" << endl;
				sum[i] += *depth_count[i][j];
				num_found[i]++;
				//print(search_result[i][j]);
			}
		}
	}
	cout << endl;

	cout << "total number of loops:" << endl;
	cout << "depth non-recursive:\t" << sum[0] << endl;
	cout << "depth recursive:\t" << sum[1] << endl;
	cout << "breadth:\t\t" << sum[2] << endl;

	cout << endl;
	cout << "average number of loops:" << endl;
	cout << "depth non-recursive:\t" << sum[0]/num_found[0] << endl;
	cout << "depth recursive:\t" << sum[1]/num_found[0] << endl;
	cout << "breadth:\t\t" << sum[2]/num_found[0] << endl;
	cout << endl;

	ofstream myfile;
	myfile.open ("results.txt");
	myfile << sum[0]/num_found[0] << endl;
	myfile << sum[1]/num_found[1] << endl;
	myfile << sum[2]/num_found[2] << endl;
	myfile.close();
}
