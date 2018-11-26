#include "AVLTree.h"



namespace UsmaanSahak {


void AVLTree::leftRotationRoot(node* oldRoot, node* newRoot, node* subtree) {
//outputTree();
//std::cout << "LEFT ROTATION ROOT\n";
//std::cout << oldRoot->getValue() << " is oldRoot " << newRoot->getValue() << " is newRoot"<< subtree->getValue() << " is subtree" << std::endl;

	oldRoot->setRight(nullptr);
	raiseHeight(oldRoot);
	oldRoot->setRight(newRoot->getLeft());

	newRoot->setLeft(nullptr);
	lowerHeight(newRoot);
	newRoot->setLeft(oldRoot);
	root = newRoot;
//outputTree();
}
void AVLTree::leftRotation(int dir, node* witness, node* oldRoot, node* newRoot, node* subchild) {
//outputTree();
//std::cout << "LEFT ROTATION\n";
//std::cout << dir << " is dir " << witness->getValue() << " is wit\n";
//std::cout << witness->getValue() << " is witness " << oldRoot->getValue() << " is oldroot " << newRoot->getValue() <<" is newRoot" << std::endl;
//std::cout << witness->getRight()->getValue() << " " << witness->getRight()->getRight()->getValue() << " " << witness->getRight()->getRight()->getRight()->getValue() << std::endl;
	if (dir < -1) {
		witness->setRight(newRoot);
	} else {
		witness->setLeft(newRoot);
	}
	oldRoot->setRight(nullptr);
	raiseHeight(oldRoot);
	oldRoot->setRight(newRoot->getLeft());
	newRoot->setLeft(nullptr);
	lowerHeight(newRoot);
	newRoot->setLeft(oldRoot);

//outputTree();
}


void AVLTree::rightRotationRoot(node* oldRoot, node* newRoot, node* subtree) {
//outputTree();
//std::cout << "RIGHT ROTATION ROOT\n";

//std::cout << oldRoot->getValue() << " " << oldRoot->getLeft()->getValue() << " " << oldRoot->getLeft()->getLeft()->getValue() << std::endl;
//std::cout << oldRoot->getValue() << " " << newRoot->getValue() << " " << subtree->getValue() << std::endl;
	oldRoot->setLeft(nullptr);
	raiseHeight(oldRoot);
	oldRoot->setLeft(newRoot->getRight());

	newRoot->setRight(nullptr);
	lowerHeight(newRoot);
	newRoot->setRight(oldRoot);
	root = newRoot;
//	std::cout << oldRoot->getValue() << " " << oldRoot->getLeft()->getValue() << std::endl;
//	std::cout << "after right rotation root>\n";
//outputTree();
}

void AVLTree::rightRotation(int dir, node* witness, node* oldRoot, node* newRoot, node* subchild) {
//outputTree();
//std::cout << "RIGHT ROTATION\n";
//std::cout << dir << " is dir.\n";
//std::cout << witness->getValue() << " " << oldRoot->getValue() << " " << newRoot->getValue() << std::endl;
	if (dir < -1) {
		witness->setRight(newRoot);
	} else {
		witness->setLeft(newRoot);
	}
	oldRoot->setLeft(nullptr);
	raiseHeight(oldRoot);
	oldRoot->setLeft(newRoot->getRight());
	newRoot->setRight(nullptr);
	lowerHeight(newRoot);
	newRoot->setRight(oldRoot);
	//std::cout << "rotation done!\n";
//outputTree();
}



void AVLTree::leftRightRotationRoot(int dir, node* witness, node* prevNode, node* subtree, node* subchild) {
//std::cout << witness->getValue() << " is w " << prevNode->getValue() << " is p " << subtree->getValue() << " is su\n";
//std::cout << "LEFTRIGHT ROTATION ROOT\n";
//std::cout << prevNode->getValue() << " " << subtree->getValue() << " " << subchild->getValue() << std::endl;



	rightRotation(-2,witness,prevNode, subtree, subchild);
	//subtree and prevNode switch since they get rotated above
	leftRotationRoot(witness, subtree, prevNode);
}


void AVLTree::rightLeftRotationRoot(int dir, node* witness, node* prevNode, node* subtree, node* subchild) {
//std::cout << witness->getValue() << " is w " << prevNode->getValue() << " is p " << subtree->getValue() << " is su\n";
//std::cout << "RIGHTLEFT ROTATION ROOT\n";
//std::cout << prevNode->getValue() << " " << subtree->getValue() << " " << subchild->getValue() << std::endl;



	leftRotation(2, witness, prevNode, subtree, nullptr);
	//subtree and prevNode switch since they get rotated above
	rightRotationRoot(witness, subtree, subtree->getLeft());
}


void AVLTree::rightLeftRotation(int dir, node* witness, node* prevNode, node* subtree, node* subchild) {
//std::cout << witness->getValue() << " is w " << prevNode->getValue() << " is p " << subtree->getValue() << " is su\n";
//std::cout << "RIGHTLEFT ROTATION\n";

leftRotation(2, prevNode, subtree, subchild, subchild->getRight());
	//rotate on subtree instead of prevNode. right rotation.
	rightRotation(dir, witness, prevNode, subchild, subtree); 
	//afterwards, rotate left like normal, but account for the previous rotation in parameter.
	
}





void AVLTree::leftRightRotation(int dir, node* witness, node* prevNode, node* subtree, node* subchild) {
//std::cout << witness->getValue() << " is w " << prevNode->getValue() << " is p " << subtree->getValue() << " is su\n";
//std::cout << "LEFTRIGHT ROTATION\n";
//std::cout << prevNode->getValue() << " " << subtree->getValue() << " " << subchild->getValue() << std::endl;
	rightRotation(-2, prevNode, subtree, subchild, subchild->getLeft());
	//subtree and prevNode switch since they get rotated above
	leftRotation(dir, witness, prevNode, subchild, subtree);
}











//I need these two below so if the rotation is near node it will still work!
/*
void AVLTree::leftRightRotation(node* grandNode, direction) {
	leftRotation(2, prevNode, subtree, subchild, subchild-getLeft());
	rightRotation(dir, witness, prevNode, subtree, subchild);
}
*/

void AVLTree::iterate(node* s) {
	//Put stuff you want to do to each node here.
	std::cout <<  s->getValue() << std::endl;
	if (s->getLeft() != nullptr) { iterate(s->getLeft()); }
	else { std::cout << "left nullptr\n"; }

	if (s->getRight() != nullptr) { iterate(s->getRight()); }
	else { std::cout << "right nullptr\n"; }
}
	



int AVLTree::gsh() {
	//Pre-order
	//outputTree();
	gshRoot(root);
}
//s here would be root. The regular gsh would then hold s as a witness node. 
int AVLTree::gshRoot(node* s) {
	if (s == nullptr) { return -1; } //So cBlah turns 0 if no child.
	//std::cout << "Running gsh " << s->getValue() << std::endl;
	if ((s->getLeft() == nullptr) && (s->getRight() == nullptr)) {
//std::cout << "Is leaf.\n";
		return 0; //Is leaf.
	}

	
	int cLeft = 1 + gsh(s,s->getLeft());
	int cRight = 1 + gsh(s,s->getRight());
	int d = cLeft - cRight;
	//std::cout << "Comparing " << cLeft << " and " << cRight << " for " << s->getValue() <<  std::endl;
	
	if ((d < -1) || (d > 1)) {
		//rotate appropriately
		//node* s is the witness
		node* prevNode;
		node* subtree;
		node* subchild;
		int dir1 = 0; //left is 2, right is 1. 
		int dir2 = 0;
		//Lets fill the above variables.
		if (d < -1) {
			//prevNode
			prevNode = s->getRight();
			dir1 = 1;
//std::cout << "getting subtree\n";
			//subtree
			if (prevNode->getLeft() == nullptr) {
				subtree = s->getRight()->getRight();
				dir2 = 1;
			} else if (s->getRight()->getRight() == nullptr) {
				subtree = s->getRight()->getLeft();
				dir2 = 2;
			}
			else if (gsh(s->getRight(),s->getRight()->getLeft()) > gsh(s->getRight(),s->getRight()->getRight())) {
			subtree = s->getRight()->getLeft();
			dir2 = 2;
			} 
			else {
				subtree = s->getRight()->getRight();
				dir2 = 1;
			}
//std::cout << "getting subchild\n";
			//subchild
			if (subtree->getLeft() == nullptr) {
				subchild = subtree->getRight();
				dir2 = 1;
			} else if (subtree->getRight() == nullptr) {
				subchild = subtree->getLeft();
				//dir2 = 2;
			}
			else if (gsh(subtree,subtree->getLeft()) > gsh(subtree,subtree->getRight())) {
			subchild = subtree->getLeft();
			//dir2 = 2;
			} 
			else {
				subchild = subtree->getRight();
				dir2 = 1;
			}
		} else if (d > 1) {
//		std::cout << "d > 1\n";
			prevNode = s->getLeft();
			dir1 = 2;
//std::cout << "getting d>1 subtree, prevNode is " << prevNode->getValue() << std::endl;

			//subtree
			int prev = 0; //If previous node messed up then set as 1.
			//Lets add this here, debug. Is it a leaf?
			if (prevNode->getLeft() == nullptr && prevNode->getRight() == nullptr) {
//std::cout << s->getValue() <<  "'s prevNode is a leaf! returning 1?\n";
				return 1; //I think we should return 1, since we went down once after all.
			} else if (prevNode->getLeft() == nullptr) {
//std::cout << "we now access prevNode->getRight()\n";
				subtree = prevNode->getRight();
//std::cout << "accessed!\n";
				dir2 = 1;
			} else if (prevNode->getRight() == nullptr) {
//std::cout << "accessing the right instead\n";
				subtree = prevNode->getLeft();
				dir2 = 2;
			}
			else if (gsh(prevNode,prevNode->getLeft()) > gsh(prevNode,prevNode->getRight())) {
//std::cout << "HERE\n";
//std::cout << "lets list them all! " << s->getValue() << " " << s->getLeft()->getValue() << " " << s->getLeft()->getLeft()->getValue() << std::endl;
				subtree = s->getLeft()->getLeft();
				dir2 = 2;
			} 
			else {
//std::cout << "NO HERE\n";
				subtree = s->getLeft()->getRight();
				dir2 = 1;
			}
//std::cout << s->getValue() << " getting d>1 subchild\n";


			//subchild
//std::cout << "Making sure... subtree: " << subtree->getValue() << std::endl;
			if (subtree->getLeft() == nullptr && subtree->getRight() == nullptr) {
//std::cout << s->getValue() << "'s subtree is leaf! returning 2?\n";
				return 2;
			} else if (subtree->getLeft() == nullptr) {
				subchild = subtree->getRight();
				//dir2 = 1;
			} else if (subtree->getRight() == nullptr) {
				subchild = subtree->getLeft();
				
				//dir2 = 2;
			}
			else if (gsh(subtree,subtree->getLeft()) > gsh(subtree,subtree->getRight())) {
			subchild = subtree->getLeft();
			//dir2 = 2;
			} 
			else {
				subchild = subtree->getRight();
				//dir2 = 1;
			}
		}
		
		//Now, using the dir1 and dir2 values, determine which of the four rotation functions you will use, and fill it with the nodes you filled in.
			
			//In each, check to see if near root first so you know which overrided rotation prototype to call.
		if (dir1 == 1 && dir2 == 1) {

			leftRotationRoot(s, prevNode, subtree);
		}
		if (dir1 == 1 && dir2 == 2) {
		//Later switch this with leftRightRotationRoot
			leftRightRotationRoot(d, s, prevNode, prevNode->getLeft(), prevNode->getLeft()->getLeft());
		}
		if (dir1 == 2 && dir2 == 2) {

//std::cout << s->getValue() << " " << prevNode->getValue() << " "  << subtree->getValue() << " " << subchild->getValue() << " is here." <<  std::endl;
//std::cout << s->getValue() << " " << s->getLeft()->getValue() << " " << s->getLeft()->getLeft()->getValue() << " " << s->getLeft()->getLeft()->getLeft()->getValue() << std::endl;

//outputTree();
//std::cout << "We are comparing  " << cLeft << " and " << cRight << " for the value " << s->getValue() << std::endl;
/*
if (s->getRight()->getValue() && s->getLeft()->getValue()) {
	std::cout << s->getRight()->getValue() << " <right and left> " << s->getLeft()->getValue() << std::endl;
	}
*/
			rightRotationRoot(s, prevNode, subtree);
		}
		if (dir1 == 2 && dir2 == 1) {
//outputTree();
//std::cout << "We are comparing  " << cLeft << " and " << cRight << " for the value " << s->getValue() << std::endl;
			rightLeftRotationRoot(d, s, prevNode, subtree, subchild);
		}
		//Actually shouldn't be needed if root
		/*
		//Recalculate cRight and cLeft
		//cLeft = 1 + gsh(root,root->getLeft());
		//cRight = 1 + gsh(root,root->getRight());
std::cout << "For " << s->getValue() << ": from d:" << d << " to e:" << cLeft - cRight << std::endl;
		return cRight > cLeft ? cRight : cLeft;
		*/
		return -99;
	}
	//return cRight > cLeft ? cRight : cLeft; //Return larger of two.
	return -99; //Its root, no need.
}
	
/*
rType = 0 means single left
rType = 1 means single right
rType = 2 means right-left
rType = 3 means left-right
*/
int AVLTree::gsh(node* witness, node* s) {
	if (s == nullptr) { return -1; } //So cBlah turns 0 if no child.
//std::cout << "Running gsh " << s->getValue() << std::endl;
	if ((s->getLeft() == nullptr) && (s->getRight() == nullptr)) {
//std::cout << "Is leaf.\n";
		return 0; //Is leaf.
	}
	int wChild = 0;
	if (witness->getRight() != nullptr && witness->getRight()->getValue() == s->getValue()) { wChild = -2;
	} else { wChild = 2; }
	
	int cLeft = 1 + gsh(s,s->getLeft());
	int cRight = 1 + gsh(s,s->getRight());
	int d = cLeft - cRight;
//std::cout << "Comparing " << cLeft << " and " << cRight << " for " << s->getValue() <<  std::endl;
	
	if ((d < -1) || (d > 1)) {
		//rotate appropriately
		//node* s is the witness
		node* prevNode;
		node* subtree;
		node* subchild;
		int dir1 = 0; //left is 2, right is 1. 
		int dir2 = 0;
		//Lets fill the above variables.
		if (d < -1) {
			//prevNode
			prevNode = s->getRight();
			dir1 = 1;
//std::cout << "getting subtree\n";
			//subtree
			if (prevNode->getLeft() == nullptr) {
				subtree = s->getRight()->getRight();
				dir2 = 1;
			} else if (s->getRight()->getRight() == nullptr) {
				subtree = s->getRight()->getLeft();
				dir2 = 2;
			}
			else if (gsh(s->getRight(),s->getRight()->getLeft()) > gsh(s->getRight(),s->getRight()->getRight())) {
			subtree = s->getRight()->getLeft();
			dir2 = 2;
			} 
			else {
				subtree = s->getRight()->getRight();
				dir2 = 1;
			}

//std::cout << "getting subchild\n";
			//subchild
			if (subtree->getLeft() == nullptr) {
				subchild = subtree->getRight();
				//dir2 = 1;
			} else if (subtree->getRight() == nullptr) {
				subchild = subtree->getLeft();
				//dir2 = 2;
			}
			else if (gsh(subtree,subtree->getLeft()) > gsh(subtree,subtree->getRight())) {
			subchild = subtree->getLeft();
			//dir2 = 2;
			} 
			else {
				subchild = subtree->getRight();
				//dir2 = 1;
			}

//std::cout <<"s: " << s->getValue() << " " << dir1 << " <dir1 I dir2>" << dir2 << std::endl;
		} else if (d > 1) {
			dir1 = 2;
			prevNode = s->getLeft();
//std::cout << "getting d>1 subtree, prevNode is " << prevNode->getValue() << std::endl;

			//subtree
			int prev = 0; //If previous node messed up then set as 1.
			//Lets add this here, debug. Is it a leaf?
			if (prevNode->getLeft() == nullptr && prevNode->getRight() == nullptr) {
//std::cout << s->getValue() <<  "'s prevNode is a leaf! returning 1?\n";
				return 1; //I think we should return 1, since we went down once after all.
			} else if (prevNode->getLeft() == nullptr) {
//std::cout << "we now access prevNode->getRight()\n";
				subtree = prevNode->getRight();
//std::cout << "accessed!\n";
				dir2 = 1;
			} else if (prevNode->getRight() == nullptr) {
//std::cout << "accessing the right instead\n";
				subtree = prevNode->getLeft();
				dir2 = 2;
			}
			else if (gsh(prevNode,prevNode->getLeft()) > gsh(prevNode,prevNode->getRight())) {
//std::cout << "HERE\n";
//std::cout << "lets list them all! " << s->getValue() << " " << s->getLeft()->getValue() << " " << s->getLeft()->getLeft()->getValue() << std::endl;
				subtree = s->getLeft()->getLeft();
				dir2 = 2;
			} 
			else {
//std::cout << "NO HERE\n";
				subtree = s->getLeft()->getRight();
				dir2 = 1;
			}
//std::cout << s->getValue() << " getting d>1 subchild\n";


			//subchild
//std::cout << "Making sure... subtree: " << subtree->getValue() << std::endl;
			if (subtree->getLeft() == nullptr && subtree->getRight() == nullptr) {
//std::cout << s->getValue() << "'s subtree is leaf! returning 2?\n";
				return 2;
			} else if (subtree->getLeft() == nullptr) {
				subchild = subtree->getRight();
				//dir2 = 1;
			} else if (subtree->getRight() == nullptr) {
				subchild = subtree->getLeft();
				
				//dir2 = 2;
			}
			else if (gsh(subtree,subtree->getLeft()) > gsh(subtree,subtree->getRight())) {
			subchild = subtree->getLeft();
			//dir2 = 2;
			} 
			else {
				subchild = subtree->getRight();
				//dir2 = 1;
			}
		}
		
		//Now, using the dir1 and dir2 values, determine which of the four rotation functions you will use, and fill it with the nodes you filled in.
			
			//In each, check to see if near root first so you know which overrided rotation prototype to call.
		if (dir1 == 1 && dir2 == 1) {
//std::cout << s->getValue() << "thes line\n";
			leftRotation(wChild, witness, s, prevNode, subtree);
		}
		if (dir1 == 1 && dir2 == 2) {
//std::cout << witness->getValue() << " is witness\n" << s->getValue() << " is s.\n";
			leftRightRotation(wChild, witness, s, prevNode, subtree);
		}
		if (dir1 == 2 && dir2 == 2) {
//std::cout << s->getValue() << " " << prevNode->getValue() << " "  << subtree->getValue() << " " << subchild->getValue() << "hi" << std::endl;
//std::cout << s->getValue() << " " << s->getLeft()->getValue() << " " << s->getLeft()->getLeft()->getValue() << " " << s->getLeft()->getLeft()->getLeft()->getValue() << "rye" << std::endl;
			rightRotation(wChild, witness, s, prevNode, subtree);
		}
		if (dir1 == 2 && dir2 == 1) {
			rightLeftRotation(wChild, witness, s, prevNode, subtree);
		}
		
		//Recalculate cRight and cLeft
		//prevNode should be the new local root after rotations, not s
		cLeft = 1 + gsh(prevNode,prevNode->getLeft());
		cRight = 1 + gsh(prevNode,prevNode->getRight());
//std::cout << "for " << s->getValue() << " from d:" << d << " to e:" << cLeft - cRight << std::endl;
		return cRight > cLeft ? cRight : cLeft;
	}
	return cRight > cLeft ? cRight : cLeft; //Return larger of two.
}
	
	
	
	
	
	
	









	void AVLTree::raiseHeight(node* subtree) {
		subtree->height = subtree->height+1;
	  if (subtree->getLeft() != nullptr) {
			raiseHeight(subtree->getLeft());
		}
		if (subtree->getRight() != nullptr) {
			raiseHeight(subtree->getRight());
		}
	}
	void AVLTree::lowerHeight(node* subtree) {
		subtree->height = subtree->height-1;
	  if (subtree->getLeft() != nullptr) {
			lowerHeight(subtree->getLeft());
		}
		if (subtree->getRight() != nullptr) {
			lowerHeight(subtree->getRight());
		}
	}
	
  bool AVLTree::helperDeleteTree(int64_t num, node* subtree) {
//  std::cout << subtree->getValue() << "helper\n";
//  std::cout << num << "number\n";
//outputTree();
  	if (num > subtree->getValue()) {
//  	std::cout << "More than.\n";
  		if (subtree->getRight() == nullptr) { return false; }
  	  else if (subtree->getRight()->getValue() == num) {
//std::cout << "We found a match!\n";
  	  	if ((subtree->getRight()->getLeft() == nullptr) && (subtree->getRight()->getRight() == nullptr)) {
  	  		//Is leaf, delete node.
//  	  		std::cout << "LEEAF\n";
  	  		delete subtree->getRight();
  	  		size--;
  	  		node* temp = nullptr;
  	  		subtree->setRight(temp);
//  	  		std::cout << "bye line 105 AVLTree.cpp\n";
  	  		return true;
  	  	}
  	  	else if ((subtree->getRight()->getLeft() == nullptr) && (subtree->getRight()->getRight() != nullptr)) {
  	  		//Connect parent of node to right child of node
//std::cout << "connect right\n";
//std::cout << "before\n";
//outputTree();
  	  		node* temp = subtree->getRight();

  	  		subtree->setRight(subtree->getRight()->getRight());
  	  		temp->setRight(nullptr);
  	  		lowerHeight(subtree->getRight());
  	  		delete temp;
  	  		size--;
  	  		temp = nullptr;
//std::cout << "after\n";
//outputTree();
  	  		return true;
  	  	} else if ((subtree->getRight()->getLeft() != nullptr) && (subtree->getRight()->getRight() == nullptr)) {
  	  		//Connect parent of node to left child of node
//std::cout << "connect left\n";
  	  		node* temp = subtree->getRight();
  	  		subtree->setRight(subtree->getRight()->getLeft());
  	  		temp->setLeft(nullptr);
  	  		lowerHeight(subtree->getRight());
  	  		delete temp;
  	  		size--;
  	  		temp = nullptr;
  	  		return true;
  			}
  			else if ((subtree->getRight()->getLeft() != nullptr) && (subtree->getRight()->getRight() != nullptr)) {
  				//Find minimum, then recursively call helperDeleteTree in an if statement on it so all cases are considered.
//std::cout << "find min etc\n";
  				node* temp = subtree->getRight()->getRight();
  				while (temp->getLeft() != nullptr && temp->getLeft()->getLeft() != nullptr) {
  					temp = temp->getLeft();
  				}
					if (temp->getLeft() == nullptr) { //If the right node has no left child... (The above loop did not iterate once)
					//temp is subtree->getRight()->getRight().
					//node to be deleted is subtree->getRight().
						node* deleteThis = subtree->getRight();
						subtree->setRight(temp);
//Note: lowerHeight() before setLeft, because the getleft is already correct height.
						lowerHeight(subtree->getRight());
						temp->setLeft(deleteThis->getLeft());
						deleteThis->setRight(nullptr);
						deleteThis->setLeft(nullptr);
						delete deleteThis;
						size--;
						deleteThis = nullptr;
						temp = nullptr;
//std::cout << "no u\n";
					} else { //The while loop iterated at least once.
//std::cout << "Iterate >1\n";
						subtree->getRight()->setValue(temp->getLeft()->getValue());
						if (!helperDeleteTree(temp->getLeft()->getValue(),temp)) { return false; }
					}
//outputTree();
					return true;
				}
  		} else {
  			//if more than, right is not nullptr nor the value we want, then keep iterating down.
  			if (!helperDeleteTree(num, subtree->getRight())) { return false;}
  			return true;
  		}
  		
  		
  		
  	} else if (num < subtree->getValue()) {
//std::cout << "Less than\n"; 
  		if (subtree->getLeft() == nullptr) { return false; }
  	  else if (subtree->getLeft()->getValue() == num) {
//std::cout << "Match, " << num << std::endl;
  	  	if ((subtree->getLeft()->getLeft() == nullptr) && (subtree->getLeft()->getRight() == nullptr)) {
  	  		//Is leaf, delete node.
//std::cout << "should have been here. line 156.\n";
  	  		//delete subtree->getLeft()->getRight();
  	  		delete subtree->getLeft();
  	  		size--;
  	  		subtree->setLeft(nullptr);
//outputTree();
  	  		return true;
  	  	}
  	  	else if ((subtree->getLeft()->getLeft() == nullptr) && (subtree->getLeft()->getRight() != nullptr)) {
  	  		//Connect parent of node to right child of node
//std::cout << "connect right\n";
  	  		node* temp = subtree->getLeft()->getRight();
  	  		subtree->getLeft()->setRight(nullptr);
  	  		delete subtree->getLeft();
  	  		size--;
  	  		subtree->setLeft(temp);
  	  		lowerHeight(subtree->getLeft());
  	  		temp = nullptr;
  	  		return true;
  	  	} else if ((subtree->getLeft()->getLeft() != nullptr) && (subtree->getLeft()->getRight() == nullptr)) {
  	  		//Connect parent of node to left child of node 
//std::cout << "connect left\n";
  	  		node* temp = subtree->getLeft()->getLeft();
  	  		subtree->getLeft()->setLeft(nullptr);
  	  		delete subtree->getLeft();
  	  		size--;
  	  		subtree->setLeft(temp);
  	  		lowerHeight(subtree->getLeft());
  	  		temp = nullptr;
  	  		return true;
  			}
  			else if ((subtree->getLeft()->getLeft() != nullptr) && (subtree->getLeft()->getRight() != nullptr)) {
  					//Find minimum, then recursively call helperDeleteTree in an if statement on it so all cases are considered.
//std::cout << "get min etc\n";
  				node* temp = subtree->getLeft()->getRight();
  				while (temp->getLeft() != nullptr && temp->getLeft()->getLeft() != nullptr) {
  					temp = temp->getLeft();
  				}
					if (temp->getLeft() == nullptr) { //If the right node has no left child... (The above loop did not iterate once)
					//temp is subtree->getLeft()->getRight().
					//node to be deleted is subtree->getLeft().
//std::cout << "no iteration\n";
						node* deleteThis = subtree->getLeft();
						subtree->setLeft(temp);
						lowerHeight(subtree->getLeft());
						temp->setLeft(deleteThis->getLeft());
						
//outputTree();
						
						deleteThis->setRight(nullptr);
						deleteThis->setLeft(nullptr);
						delete deleteThis;	
						size--;
						deleteThis = nullptr;
						temp = nullptr;

					} else { //The while loop iterated at least once.
//std::cout << "iterated\n";
						subtree->getLeft()->setValue(temp->getLeft()->getValue());
						if (!helperDeleteTree(temp->getLeft()->getValue(),temp)) { return false; }
					}
//outputTree();
					return true;
  			}
  			else { std::cout << "This is impossible.\n"; }
  		} else {
  			if (helperDeleteTree(num, subtree->getLeft())) { return true; }
  			else { return false; }
  		}
  	}
  }
  		
  			
  bool AVLTree::deleteTree(int64_t num) {
    //iterate through tree, find value. If not found, return false.
    if (root == nullptr) {
      return false;
    } else if (root->getValue() == num) {
//    std::cout << "deleting the root node.\n";
//Delete the root node
			//If right node, then iterate down the left most of that right node until reach leaf. Make the 'to be deleted' node's value into that, and delete that leaf node that you just copied.
			//if no right node, then check for left 
			
			if ((root->getRight() == nullptr) && (root->getLeft() == nullptr)) {
			delete root;
			root = nullptr;
			size--;
			}
			else if ((root->getRight() == nullptr) && (root->getLeft() != nullptr)) {
				node* temp = root;
				root = root->getLeft();
				temp->setLeft(nullptr);
				delete temp;
				temp = nullptr;
				lowerHeight(root);
				size--;
			}
			else if ((root->getRight() != nullptr) && (root->getLeft() == nullptr)) {
				node* temp = root;
				root = root->getRight();
				temp->setRight(nullptr);
				delete temp;
				temp = nullptr;
				lowerHeight(root);
				size--;
			}
			else { //has two children
				node* it = root->getRight();
				
				//Short circuit so second statement will not segfault us.
				while ((it->getLeft() != nullptr) && (it->getLeft()->getLeft() != nullptr)) {
				it = it->getLeft();
			}
			if (it->getLeft() == nullptr) { //If the right node has no left child... (The above loop did not iterate once)
				lowerHeight(it);
				it->setLeft(root->getLeft());
				node* temp = root;
				root = it;
				temp->setLeft(nullptr);
				temp->setRight(nullptr);
				delete temp;
				temp = nullptr;
				size--;
			}
			else { //The while loop iterated at least once.
				
				root->setValue(it->getLeft()->getValue());
				if (!helperDeleteTree(it->getLeft()->getValue(),it)) { return false; }
				}
				it = nullptr;
				return true;
			}
    } else { //Iterate down tree, find position.
      node* it = root;
      if (num < it->getValue()) {
        if (it->getLeft() == nullptr) {
          //num will be on left of root.
//std::cout << "line 260\n";
          return false;
        } else {
        
        
//std::cout << "Modified code to eliminate root child nodes here. Line 265.\n";
        	//If one of the root's child nodes is the one, do this instead.
        	//Shortcircuit if there is no respective child node.
        	if (((it->getLeft() != nullptr) && (it->getLeft()->getValue() == num)) || ((it->getRight() != nullptr) && (it->getRight()->getValue() == num))) {
        		if(!helperDeleteTree(num, it)) { return false; }
        		return true;
        	}
        	//Otherwise, just keep iterating down.
//std::cout << "keep iterating down\n";
        	
          //recursive helper function.
          if (!helperDeleteTree(num, it->getLeft())) { return false;}
          return true;
        }
      } else if (num > it->getValue()) {
        if (it->getRight() == nullptr) {
          //num will be on right of root.
          return false;
        } else {
          //same recursive helper function, like above.
          if (!helperDeleteTree(num, it)) { return false; }
        }
      } else { std::cout << "This is impossible, we already checked for root.\n"; return false; /*Already present. */ } 
    }
    return true;
  }

















//Maybe override the helperWriteTree() so it also takes a witness that is run inside the helperWriteTree() below this one?
	bool AVLTree::helperWriteTree(int64_t num, node* witness, node* prevNode, node* subtree) {
//std::cout << "running 3 node writer\n";
  //prevNode is always root in this version of the function.
//outputTree();
    //base case; see if spot is as a left or right of current node.
    if (num > subtree->getValue()) {
//std::cout << "adding " << num << " to node " << subtree->getValue() << "'s right.\n";
      if (subtree->getRight() == nullptr) {
        node* temp = new node(num);
        subtree->setRight(temp);
//std::cout << subtree->getValue() << "'s height is " << subtree->height << std::endl;
        temp->height = subtree->height+1;
        temp = nullptr;
        size++;
        
        
        
        
        //We are adding to right of subtree
        //call gsh()
       	gsh();
        
        
        
      } else {
//std::cout << "What why is it not null?\n";
        if (!helperWriteTree(num, prevNode, subtree, subtree->getRight())) { return false; }
      }
    } else if (num < subtree->getValue()) {
//std::cout << "why less? " << subtree->getValue() << std::endl;
      if (subtree->getLeft() == nullptr) {
        node* temp = new node(num);
        subtree->setLeft(temp);
        temp->height = subtree->height+1;
        size++;
        
        //We are adding to the left of subtree
        //check if subtree is at right or left of prevNode.
        //if left left, do our single left rotation
//leftRotate(witness, prevNode, subtree, subtree->left);
        //if right left, do our double right-left rotation
        
        
      gsh();
      } else {
        if (!helperWriteTree(num, subtree, subtree->getLeft())) { return false; }
      }
    }
    else { return false; }
    return true;
  }
  
  
  
  
  
  
  

  bool AVLTree::helperWriteTree(int64_t num, node* prevNode, node* subtree) {
//outputTree();
//std::cout << "Running 2 node writer, " << subtree->getValue() << std::endl;
  //prevNode is always root in this version of the function.
//outputTree();
    //base case; see if spot is as a left or right of current node.
    if (num > subtree->getValue()) {
      if (subtree->getRight() == nullptr) {
        node* temp = new node(num);
        subtree->setRight(temp);
        temp->height = subtree->height+1;
        temp = nullptr;
        size++;
        
        
        
        gsh();
        //We are adding to right of subtree
        
        
        
        
        
        
      } else {
        if (!helperWriteTree(num, prevNode, subtree, subtree->getRight())) { return false; }
      }
    } else if (num < subtree->getValue()) {
      if (subtree->getLeft() == nullptr) {
        node* temp = new node(num);
        subtree->setLeft(temp);
        temp->height = subtree->height+1;
        size++;
        gsh();
      } else {
        if (!helperWriteTree(num, prevNode, subtree, subtree->getLeft())) { return false; }
      }
    }
    else { return false; }
    return true;
  }
  
  
  
  
  
  
  
  
  
  
  bool AVLTree::writeTree(int64_t num) {
  /*
  difference from binary:
  1 - After adding, check height of the opposite subtree to see if you need rebalancing.
  2 - Find out which of the four cases this is, and rotate accordingly.
  */
  
  
  
  
    //Check if we have room.
    if (size == capacity) { 
    	//std::cout << "Capacity reached\n"; 
    	return false; 
    }
    //Check to see if tree is empty or not.
    if (getRoot() == nullptr) {
      node* temp = new node(num);
      setRoot(temp);
      temp->height = 1;
      size++;
      gsh();
      temp = nullptr;
    } else { //Iterate down tree, find position.
      node* it = getRoot();
      if (num < it->getValue()) {
        if (it->getLeft() == nullptr) {
          //num will be on left of root.
          node* temp = new node(num);
          it->setLeft(temp);
          temp->height = 2;
          size++;
          gsh();
          temp = nullptr;
        } else {
          //recursive helper function.
          if (!helperWriteTree(num, root, it->getLeft())) { return false; }
        }
      } else if (num > it->getValue()) {
        if (it->getRight() == nullptr) {
          //num will be on right of root.
          node* temp = new node(num);
          it->setRight(temp);
          temp->height = 2;
          temp = nullptr;
          size++;
          gsh();
        } else {
          //same recursive helper function, like above.
          if (!helperWriteTree(num, root,it->getRight())) { return false; }
        }
      } else { return false; /*Already present. */ } 
    }
    //outputTree();//Debugging
    return true;
  }
  

    
    
    
    
    
    
    
 

  bool AVLTree::helperReadTree(int64_t num, node* subtree) { 
    //base case; see if spot is as a left or right of current node.
    if (num > subtree->getValue()) {
      if (subtree->getRight() == nullptr) {
        return false;
      } else if (subtree->getRight()->getValue() == num) {
        return true;
      } else {
        if (!helperReadTree(num, subtree->getRight())) { return false;}
      }
    } else if (num < subtree->getValue()) {
      if (subtree->getLeft() == nullptr) {
        return false;
      } else if (subtree->getLeft()->getValue() == num) {
        return true;
      } else {
        if (!helperReadTree(num, subtree->getLeft())) { return false; }
      }
    }
    else { return false; }
    return true;
  }
  
  
  
  
  bool AVLTree::readTree(int64_t num) {
//outputTree();
    //iterate through tree, find value. If not found, return false.
    if (getRoot() == nullptr) {
      return false;
    } else { //Iterate down tree, find position.
      node* it = getRoot();
      if (num < it->getValue()) {
        if (it->getLeft() == nullptr) {
          //num will be on left of root.
          return false;
        } else {
          //recursive helper function.
          if (!helperReadTree(num, it->getLeft())) { return false;}
        }
      } else if (num > it->getValue()) {
        if (it->getRight() == nullptr) {
          //num will be on right of root.
          return false;
        } else {
          //same recursive helper function, like above.
          if (!helperReadTree(num, it->getRight())) {return false;}
        }
      } else { return true; /*Already present. */ } 
    }
    return true;
  }
  
  
  
  static int count = 0;
  void AVLTree::outputTree() {
  	totalHeight = 0;
  	//post order
  	std::cout << "\nOutputting AVL tree:\n";
  	if (root == nullptr) { std::cout << "root is boot\n"; return;}
  	if (root->getLeft() != nullptr) {
  		helperOutputTree(root->getLeft());
  	}
  	if (root->getRight() != nullptr) {
  		helperOutputTree(root->getRight());
  	}
  	std::cout << root->getValue() << " height: " << root->height << std::endl;
  	std::cout << "Count: (delete later) " << ++count << std::endl;
  	std::cout << "Size: " << size << std::endl;
  	count = 0;
  }
  
  
  
  void AVLTree::helperOutputTree(node* subtree) {
  
  	if (subtree->getLeft() != nullptr) {
  		helperOutputTree(subtree->getLeft());
  	}
  	
  	if (subtree->getRight() != nullptr) {
  		helperOutputTree(subtree->getRight());
  	}
  	std::cout << subtree->getValue() << " height: " << subtree-> height << std::endl;
  	if (subtree->height > totalHeight) {
  		totalHeight = subtree->height;
  	}
  	count++;
  }
  
  void AVLTree::outputTree(std::ofstream& file) {
  	totalHeight = 0;
  	//post order
  	file << "\nOutputting AVL tree:\n";
  	if (root == nullptr) { std::cout << "root is boot\n"; return;}
  	if (root->getLeft() != nullptr) {
  		helperOutputTree(root->getLeft(),file);
  	}
  	if (root->getRight() != nullptr) {
  		helperOutputTree(root->getRight(),file);
  	}
  	file << root->getValue() << " height: " << root->height << std::endl;
  	//std::cout << "Count: (delete later) " << ++count << std::endl;
  	file << "Size: " << size << std::endl;
  	count = 0;
  }
  
  
  
  void AVLTree::helperOutputTree(node* subtree, std::ofstream& file) {
  
  	if (subtree->getLeft() != nullptr) {
  		helperOutputTree(subtree->getLeft(),file);
  	}
  	
  	if (subtree->getRight() != nullptr) {
  		helperOutputTree(subtree->getRight(),file);
  	}
  	file << subtree->getValue() << " height: " << subtree-> height << std::endl;
  	if (subtree->height > totalHeight) {
  		totalHeight = subtree->height;
  	}
  	count++;
  }
  
  
  
  AVLTree::~AVLTree() {
  	delete root;
  }
}
