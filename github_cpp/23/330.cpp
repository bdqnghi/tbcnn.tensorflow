#include <limits.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <pthread.h>
#include "SkipList.h"
#include "SkipListNode.h"

class SkipListNode;

	SkipList::SkipList(){ //Init the skip list
		this->head = new SkipListNode(INT_MIN);
		SkipListNode *right = new SkipListNode(INT_MAX);
		this->head->setRight(right);
		this->depth = 1;
		pthread_mutex_init(&skipListLock, NULL);
		srand (time(NULL));
	}

	SkipList::~SkipList(){
		SkipListNode *curr = this->head;
		
		while(true){
			if(curr->getRight() != NULL)
				curr = curr->getRight();

			if(curr->getDown() != NULL)
				curr = curr->getDown();

			if(curr->getDown() == NULL && curr->getRight() == NULL){
				if(curr->getLeft() != NULL && curr->getUp() != NULL){
					while(curr->getLeft() != NULL)
						curr = curr->getLeft();
					while(curr->getRight() != NULL){
						curr = curr->getRight();
						delete curr->getLeft();
					}
					
					curr = curr->getUp();
					delete curr->getDown();
					curr->setDown(NULL); //Make sure this is NULL otherwise we WILL access freed memory, and bad things will happen
					depth--;
				}

				else{
					delete curr->getLeft(); //We are the onry one reft, so ronery
					delete curr;
					
					pthread_mutex_destroy(&skipListLock);
					return;
				}
			}
		}
	}

	void SkipList::add(int value){
		bool contains = this->contains(value);
		if(contains)
			return; //For right now, don't allow duplicate keys

		SkipListNode *curr = this->head;
		SkipListNode *newNode = new SkipListNode(value);
		while(true){
			
			if(newNode->getValue() > curr->getRight()->getValue() && curr->getRight() != NULL){ //Check our right, if greater than right, move right
				curr = curr->getRight();
				
				continue;
			}

			else if(newNode->getValue() < curr->getRight()->getValue() && curr->getRight() != NULL && curr->getDown() == NULL){ //Check right, if less than and in bottom row, add our node
				newNode->setRight(curr->getRight());
				curr->getRight()->setLeft(newNode);
				curr->setRight(newNode);
				newNode->setLeft(curr);
				
				break; //Exit loop, we've found our spot to add
			}

			else{
				curr = curr->getDown(); //Otherwise move down
				continue;
			}
		}

		bool flip = coinFlip(); //flip our "coin", > 0.5 is true(heads)
		SkipListNode *farLeft = newNode;
		SkipListNode *farRight = newNode;
		
		while(flip == true){ //On a heads flip

				while(farLeft->getUp() == NULL && farLeft->getLeft() != NULL){ //Iterate all the way to the left in the current layer while up is NULL
						farLeft = farLeft->getLeft();
					}

				if(farLeft->getUp() == NULL) //We're at the top layer, so to insert we need to add a new one
					addTopLayer();
				
				SkipListNode *stackedNode = new SkipListNode(value);
				farLeft = newNode;

				stackedNode->setDown(newNode); //Set the node in the higher level's down to the node we added last

				if(newNode->getLeft()->getUp() != NULL)//Make sure we're not grabbing a NULL "up"
					stackedNode->setLeft(newNode->getLeft()->getUp()); 

				else{ //Otherwise
					while(farLeft->getUp() == NULL){ //Iterate all the way to the left in the current layer while up is NULL
						farLeft = farLeft->getLeft();
					}

					stackedNode->setLeft(farLeft->getUp());
				}

				while(farRight->getRight() != NULL){ //iterate from newNode all the way right until it can go up
					if(farRight->getRight()->getUp() == NULL)
						farRight = farRight->getRight();

					farRight = farRight->getRight();
				}

				stackedNode->setRight(farRight->getUp()); //These make sure all the pointers are set to the right nodes
				stackedNode->getLeft()->setRight(stackedNode);
				stackedNode->getRight()->setLeft(stackedNode);
				newNode->setUp(stackedNode);
				newNode = stackedNode; //Set the node we just inserted as the newest node
				farLeft = newNode; //Reset these variables
				farRight = newNode;
				flip = coinFlip(); //Do another flip to see if we need to do this all again
		}
		 //Done adding the new node, give up the lock
		farLeft = newNode; //Reset this guy just to be safe
		while(farLeft->getLeft() != NULL){ //Iterate all the way to the left in the current layer
			farLeft = farLeft->getLeft();
		}

		if(farLeft->getUp() == NULL){ //if the "INT_MIN" node has no up, add a new layer
			 //May not be needed?
			addTopLayer();
			 
		}
		
	}

	bool SkipList::remove(int value){
		if(!this->contains(value)) //It's not here
			return false;

		SkipListNode *curr = this->head;

		while(true){
			
			if(curr->getRight()->getValue() < value && curr->getRight() != NULL){
				curr = curr->getRight();
			
				continue; //Move right
			}

			if(curr->getRight()->getValue() > value && curr->getDown() != NULL){
				curr = curr->getDown();
				
				continue; //Move down
			}

			if(curr->getRight()->getValue() == value){
				curr = curr->getRight();
				while(curr->getDown() != NULL){
					curr->getLeft()->setRight(curr->getRight());
					curr->getRight()->setLeft(curr->getLeft());
					curr = curr->getDown();
					delete curr->getUp(); //Rekt that stack of nodes
					
				}
				
				curr->getLeft()->setRight(curr->getRight());
				curr->getRight()->setLeft(curr->getLeft());
				delete curr; //FINISH HIM
				 //May need to move this up and reacquire?
				return true; 
			}
		}

		std::cout << "Uh oh something went wrong with deleting the node with value " << curr->getValue() << "\n";
		return false; //Well you shouldn't be able to get here, but if you did, good job you broke shit
	}

	bool SkipList::contains(int value){
		SkipListNode *curr = this->head;

		while(curr->getDown() != NULL || curr->getRight() != NULL){
			//
			if(curr->getRight()->getValue() == value){
				//
				return true;
			}

			if(curr->getRight()->getValue() < value && curr->getRight() != NULL){
				curr = curr->getRight();
				//
				continue; //Move right
			}

			if(curr->getRight()->getValue() > value && curr->getDown() != NULL){
				curr = curr->getDown();
				//
				continue; //Move down
			}
			else
				break; //Covers first add case
		}
		//
		return false; //Nope not here
	}

	bool SkipList::coinFlip(){
		double flip = (double)rand()/(double)RAND_MAX;
		//std::cout << "Flip is " << flip << "\n";
		if(flip >= .5)
			return true;
		return false;
	}

	void SkipList::addTopLayer(){

		SkipListNode *newHead = new SkipListNode(INT_MIN);
		SkipListNode *newTail = new SkipListNode(INT_MAX);
		SkipListNode *farRight = this->head;

		newHead->setRight(newTail);
		newHead->setDown(this->head);
		newTail->setLeft(newHead);
		this->head->setUp(newHead);

		while(farRight->getRight() != NULL){ //iterate from head all the way right
			if(farRight->getRight()->getValue() != INT_MAX)
				farRight = farRight->getRight();

			else{
				farRight = farRight->getRight();
				//std::cout << "FarRight is " << farRight->getValue() << "\n";
				farRight->setUp(newTail);
				newTail->setDown(farRight);
			}
		}

		this->head = newHead; //Set our head node to the new one
		this->depth++;
	}
