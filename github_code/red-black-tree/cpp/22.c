/*********************************************************
*	Author: xuechenglong --dukanglu@126.com
*	Last modified:19:27 30-07-2014
*	Filename:readblacktree.cpp
*	Description:
**********************************************************/

#include <iostream>
#include <vector>
#include <string>
//enum COLOR_O{"red", "black"};

typedef struct node{
	std::string color;
	int key;
	struct node* leftnode;
	struct node* rightnode;
	struct node* ptr;

	node():color("black"),key(0),leftnode(NULL),rightnode(NULL),ptr(NULL){};
}NODE_S;

NODE_S endFlagNode; //Guard node for end

//bool nodeInsert(int )

int main(){
	if (endFlagNode.color == "black") std::cout << "endFlagNode is right!" << std::endl;
	return 0;
}
