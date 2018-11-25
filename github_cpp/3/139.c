#include "AVLTree.h"



namespace UsmaanSahak {


void AVLTree::leftRotationRoot(node* oldRoot, node* newRoot, node* subtree) {




	oldRoot->setRight(nullptr);
	raiseHeight(oldRoot);
	oldRoot->setRight(newRoot->getLeft());

	newRoot->setLeft(nullptr);
	lowerHeight(newRoot);
	newRoot->setLeft(oldRoot);
	root = newRoot;

}
void AVLTree::leftRotation(int dir, node* witness, node* oldRoot, node* newRoot, node* subchild) {





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


}


void AVLTree::rightRotationRoot(node* oldRoot, node* newRoot, node* subtree) {





	oldRoot->setLeft(nullptr);
	raiseHeight(oldRoot);
	oldRoot->setLeft(newRoot->getRight());

	newRoot->setRight(nullptr);
	lowerHeight(newRoot);
	newRoot->setRight(oldRoot);
	root = newRoot;



}

void AVLTree::rightRotation(int dir, node* witness, node* oldRoot, node* newRoot, node* subchild) {




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
	

}



void AVLTree::leftRightRotationRoot(int dir, node* witness, node* prevNode, node* subtree, node* subchild) {






	rightRotation(-2,witness,prevNode, subtree, subchild);
	
	leftRotationRoot(witness, subtree, prevNode);
}


void AVLTree::rightLeftRotationRoot(int dir, node* witness, node* prevNode, node* subtree, node* subchild) {






	leftRotation(2, witness, prevNode, subtree, nullptr);
	
	rightRotationRoot(witness, subtree, subtree->getLeft());
}


void AVLTree::rightLeftRotation(int dir, node* witness, node* prevNode, node* subtree, node* subchild) {



leftRotation(2, prevNode, subtree, subchild, subchild->getRight());
	
	rightRotation(dir, witness, prevNode, subchild, subtree); 
	
	
}





void AVLTree::leftRightRotation(int dir, node* witness, node* prevNode, node* subtree, node* subchild) {



	rightRotation(-2, prevNode, subtree, subchild, subchild->getLeft());
	
	leftRotation(dir, witness, prevNode, subchild, subtree);
}














void AVLTree::iterate(node* s) {
	
	std::cout <<  s->getValue() << std::endl;
	if (s->getLeft() != nullptr) { iterate(s->getLeft()); }
	else { std::cout << "left nullptr\n"; }

	if (s->getRight() != nullptr) { iterate(s->getRight()); }
	else { std::cout << "right nullptr\n"; }
}
	



int AVLTree::gsh() {
	
	
	gshRoot(root);
}

int AVLTree::gshRoot(node* s) {
	if (s == nullptr) { return -1; } 
	
	if ((s->getLeft() == nullptr) && (s->getRight() == nullptr)) {

		return 0; 
	}

	
	int cLeft = 1 + gsh(s,s->getLeft());
	int cRight = 1 + gsh(s,s->getRight());
	int d = cLeft - cRight;
	
	
	if ((d < -1) || (d > 1)) {
		
		
		node* prevNode;
		node* subtree;
		node* subchild;
		int dir1 = 0; 
		int dir2 = 0;
		
		if (d < -1) {
			
			prevNode = s->getRight();
			dir1 = 1;

			
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

			
			if (subtree->getLeft() == nullptr) {
				subchild = subtree->getRight();
				dir2 = 1;
			} else if (subtree->getRight() == nullptr) {
				subchild = subtree->getLeft();
				
			}
			else if (gsh(subtree,subtree->getLeft()) > gsh(subtree,subtree->getRight())) {
			subchild = subtree->getLeft();
			
			} 
			else {
				subchild = subtree->getRight();
				dir2 = 1;
			}
		} else if (d > 1) {

			prevNode = s->getLeft();
			dir1 = 2;


			
			int prev = 0; 
			
			if (prevNode->getLeft() == nullptr && prevNode->getRight() == nullptr) {

				return 1; 
			} else if (prevNode->getLeft() == nullptr) {

				subtree = prevNode->getRight();

				dir2 = 1;
			} else if (prevNode->getRight() == nullptr) {

				subtree = prevNode->getLeft();
				dir2 = 2;
			}
			else if (gsh(prevNode,prevNode->getLeft()) > gsh(prevNode,prevNode->getRight())) {


				subtree = s->getLeft()->getLeft();
				dir2 = 2;
			} 
			else {

				subtree = s->getLeft()->getRight();
				dir2 = 1;
			}



			

			if (subtree->getLeft() == nullptr && subtree->getRight() == nullptr) {

				return 2;
			} else if (subtree->getLeft() == nullptr) {
				subchild = subtree->getRight();
				
			} else if (subtree->getRight() == nullptr) {
				subchild = subtree->getLeft();
				
				
			}
			else if (gsh(subtree,subtree->getLeft()) > gsh(subtree,subtree->getRight())) {
			subchild = subtree->getLeft();
			
			} 
			else {
				subchild = subtree->getRight();
				
			}
		}
		
		
			
			
		if (dir1 == 1 && dir2 == 1) {

			leftRotationRoot(s, prevNode, subtree);
		}
		if (dir1 == 1 && dir2 == 2) {
		
			leftRightRotationRoot(d, s, prevNode, prevNode->getLeft(), prevNode->getLeft()->getLeft());
		}
		if (dir1 == 2 && dir2 == 2) {







			rightRotationRoot(s, prevNode, subtree);
		}
		if (dir1 == 2 && dir2 == 1) {


			rightLeftRotationRoot(d, s, prevNode, subtree, subchild);
		}
		
		
		return -99;
	}
	
	return -99; 
}
	

int AVLTree::gsh(node* witness, node* s) {
	if (s == nullptr) { return -1; } 

	if ((s->getLeft() == nullptr) && (s->getRight() == nullptr)) {

		return 0; 
	}
	int wChild = 0;
	if (witness->getRight() != nullptr && witness->getRight()->getValue() == s->getValue()) { wChild = -2;
	} else { wChild = 2; }
	
	int cLeft = 1 + gsh(s,s->getLeft());
	int cRight = 1 + gsh(s,s->getRight());
	int d = cLeft - cRight;

	
	if ((d < -1) || (d > 1)) {
		
		
		node* prevNode;
		node* subtree;
		node* subchild;
		int dir1 = 0; 
		int dir2 = 0;
		
		if (d < -1) {
			
			prevNode = s->getRight();
			dir1 = 1;

			
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


			
			if (subtree->getLeft() == nullptr) {
				subchild = subtree->getRight();
				
			} else if (subtree->getRight() == nullptr) {
				subchild = subtree->getLeft();
				
			}
			else if (gsh(subtree,subtree->getLeft()) > gsh(subtree,subtree->getRight())) {
			subchild = subtree->getLeft();
			
			} 
			else {
				subchild = subtree->getRight();
				
			}


		} else if (d > 1) {
			dir1 = 2;
			prevNode = s->getLeft();


			
			int prev = 0; 
			
			if (prevNode->getLeft() == nullptr && prevNode->getRight() == nullptr) {

				return 1; 
			} else if (prevNode->getLeft() == nullptr) {

				subtree = prevNode->getRight();

				dir2 = 1;
			} else if (prevNode->getRight() == nullptr) {

				subtree = prevNode->getLeft();
				dir2 = 2;
			}
			else if (gsh(prevNode,prevNode->getLeft()) > gsh(prevNode,prevNode->getRight())) {


				subtree = s->getLeft()->getLeft();
				dir2 = 2;
			} 
			else {

				subtree = s->getLeft()->getRight();
				dir2 = 1;
			}



			

			if (subtree->getLeft() == nullptr && subtree->getRight() == nullptr) {

				return 2;
			} else if (subtree->getLeft() == nullptr) {
				subchild = subtree->getRight();
				
			} else if (subtree->getRight() == nullptr) {
				subchild = subtree->getLeft();
				
				
			}
			else if (gsh(subtree,subtree->getLeft()) > gsh(subtree,subtree->getRight())) {
			subchild = subtree->getLeft();
			
			} 
			else {
				subchild = subtree->getRight();
				
			}
		}
		
		
			
			
		if (dir1 == 1 && dir2 == 1) {

			leftRotation(wChild, witness, s, prevNode, subtree);
		}
		if (dir1 == 1 && dir2 == 2) {

			leftRightRotation(wChild, witness, s, prevNode, subtree);
		}
		if (dir1 == 2 && dir2 == 2) {


			rightRotation(wChild, witness, s, prevNode, subtree);
		}
		if (dir1 == 2 && dir2 == 1) {
			rightLeftRotation(wChild, witness, s, prevNode, subtree);
		}
		
		
		
		cLeft = 1 + gsh(prevNode,prevNode->getLeft());
		cRight = 1 + gsh(prevNode,prevNode->getRight());

		return cRight > cLeft ? cRight : cLeft;
	}
	return cRight > cLeft ? cRight : cLeft; 
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



  	if (num > subtree->getValue()) {

  		if (subtree->getRight() == nullptr) { return false; }
  	  else if (subtree->getRight()->getValue() == num) {

  	  	if ((subtree->getRight()->getLeft() == nullptr) && (subtree->getRight()->getRight() == nullptr)) {
  	  		

  	  		delete subtree->getRight();
  	  		size--;
  	  		node* temp = nullptr;
  	  		subtree->setRight(temp);

  	  		return true;
  	  	}
  	  	else if ((subtree->getRight()->getLeft() == nullptr) && (subtree->getRight()->getRight() != nullptr)) {
  	  		



  	  		node* temp = subtree->getRight();

  	  		subtree->setRight(subtree->getRight()->getRight());
  	  		temp->setRight(nullptr);
  	  		lowerHeight(subtree->getRight());
  	  		delete temp;
  	  		size--;
  	  		temp = nullptr;


  	  		return true;
  	  	} else if ((subtree->getRight()->getLeft() != nullptr) && (subtree->getRight()->getRight() == nullptr)) {
  	  		

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
  				

  				node* temp = subtree->getRight()->getRight();
  				while (temp->getLeft() != nullptr && temp->getLeft()->getLeft() != nullptr) {
  					temp = temp->getLeft();
  				}
					if (temp->getLeft() == nullptr) { 
					
					
						node* deleteThis = subtree->getRight();
						subtree->setRight(temp);

						lowerHeight(subtree->getRight());
						temp->setLeft(deleteThis->getLeft());
						deleteThis->setRight(nullptr);
						deleteThis->setLeft(nullptr);
						delete deleteThis;
						size--;
						deleteThis = nullptr;
						temp = nullptr;

					} else { 

						subtree->getRight()->setValue(temp->getLeft()->getValue());
						if (!helperDeleteTree(temp->getLeft()->getValue(),temp)) { return false; }
					}

					return true;
				}
  		} else {
  			
  			if (!helperDeleteTree(num, subtree->getRight())) { return false;}
  			return true;
  		}
  		
  		
  		
  	} else if (num < subtree->getValue()) {

  		if (subtree->getLeft() == nullptr) { return false; }
  	  else if (subtree->getLeft()->getValue() == num) {

  	  	if ((subtree->getLeft()->getLeft() == nullptr) && (subtree->getLeft()->getRight() == nullptr)) {
  	  		

  	  		
  	  		delete subtree->getLeft();
  	  		size--;
  	  		subtree->setLeft(nullptr);

  	  		return true;
  	  	}
  	  	else if ((subtree->getLeft()->getLeft() == nullptr) && (subtree->getLeft()->getRight() != nullptr)) {
  	  		

  	  		node* temp = subtree->getLeft()->getRight();
  	  		subtree->getLeft()->setRight(nullptr);
  	  		delete subtree->getLeft();
  	  		size--;
  	  		subtree->setLeft(temp);
  	  		lowerHeight(subtree->getLeft());
  	  		temp = nullptr;
  	  		return true;
  	  	} else if ((subtree->getLeft()->getLeft() != nullptr) && (subtree->getLeft()->getRight() == nullptr)) {
  	  		

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
  					

  				node* temp = subtree->getLeft()->getRight();
  				while (temp->getLeft() != nullptr && temp->getLeft()->getLeft() != nullptr) {
  					temp = temp->getLeft();
  				}
					if (temp->getLeft() == nullptr) { 
					
					

						node* deleteThis = subtree->getLeft();
						subtree->setLeft(temp);
						lowerHeight(subtree->getLeft());
						temp->setLeft(deleteThis->getLeft());
						

						
						deleteThis->setRight(nullptr);
						deleteThis->setLeft(nullptr);
						delete deleteThis;	
						size--;
						deleteThis = nullptr;
						temp = nullptr;

					} else { 

						subtree->getLeft()->setValue(temp->getLeft()->getValue());
						if (!helperDeleteTree(temp->getLeft()->getValue(),temp)) { return false; }
					}

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
    
    if (root == nullptr) {
      return false;
    } else if (root->getValue() == num) {


			
			
			
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
			else { 
				node* it = root->getRight();
				
				
				while ((it->getLeft() != nullptr) && (it->getLeft()->getLeft() != nullptr)) {
				it = it->getLeft();
			}
			if (it->getLeft() == nullptr) { 
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
			else { 
				
				root->setValue(it->getLeft()->getValue());
				if (!helperDeleteTree(it->getLeft()->getValue(),it)) { return false; }
				}
				it = nullptr;
				return true;
			}
    } else { 
      node* it = root;
      if (num < it->getValue()) {
        if (it->getLeft() == nullptr) {
          

          return false;
        } else {
        
        

        	
        	
        	if (((it->getLeft() != nullptr) && (it->getLeft()->getValue() == num)) || ((it->getRight() != nullptr) && (it->getRight()->getValue() == num))) {
        		if(!helperDeleteTree(num, it)) { return false; }
        		return true;
        	}
        	

        	
          
          if (!helperDeleteTree(num, it->getLeft())) { return false;}
          return true;
        }
      } else if (num > it->getValue()) {
        if (it->getRight() == nullptr) {
          
          return false;
        } else {
          
          if (!helperDeleteTree(num, it)) { return false; }
        }
      } else { std::cout << "This is impossible, we already checked for root.\n"; return false;  } 
    }
    return true;
  }


















	bool AVLTree::helperWriteTree(int64_t num, node* witness, node* prevNode, node* subtree) {

  

    
    if (num > subtree->getValue()) {

      if (subtree->getRight() == nullptr) {
        node* temp = new node(num);
        subtree->setRight(temp);

        temp->height = subtree->height+1;
        temp = nullptr;
        size++;
        
        
        
        
        
        
       	gsh();
        
        
        
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
        if (!helperWriteTree(num, subtree, subtree->getLeft())) { return false; }
      }
    }
    else { return false; }
    return true;
  }
  
  
  
  
  
  
  

  bool AVLTree::helperWriteTree(int64_t num, node* prevNode, node* subtree) {


  

    
    if (num > subtree->getValue()) {
      if (subtree->getRight() == nullptr) {
        node* temp = new node(num);
        subtree->setRight(temp);
        temp->height = subtree->height+1;
        temp = nullptr;
        size++;
        
        
        
        gsh();
        
        
        
        
        
        
        
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
  
  
  
  
  
    
    if (size == capacity) { 
    	
    	return false; 
    }
    
    if (getRoot() == nullptr) {
      node* temp = new node(num);
      setRoot(temp);
      temp->height = 1;
      size++;
      gsh();
      temp = nullptr;
    } else { 
      node* it = getRoot();
      if (num < it->getValue()) {
        if (it->getLeft() == nullptr) {
          
          node* temp = new node(num);
          it->setLeft(temp);
          temp->height = 2;
          size++;
          gsh();
          temp = nullptr;
        } else {
          
          if (!helperWriteTree(num, root, it->getLeft())) { return false; }
        }
      } else if (num > it->getValue()) {
        if (it->getRight() == nullptr) {
          
          node* temp = new node(num);
          it->setRight(temp);
          temp->height = 2;
          temp = nullptr;
          size++;
          gsh();
        } else {
          
          if (!helperWriteTree(num, root,it->getRight())) { return false; }
        }
      } else { return false;  } 
    }
    
    return true;
  }
  

    
    
    
    
    
    
    
 

  bool AVLTree::helperReadTree(int64_t num, node* subtree) { 
    
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

    
    if (getRoot() == nullptr) {
      return false;
    } else { 
      node* it = getRoot();
      if (num < it->getValue()) {
        if (it->getLeft() == nullptr) {
          
          return false;
        } else {
          
          if (!helperReadTree(num, it->getLeft())) { return false;}
        }
      } else if (num > it->getValue()) {
        if (it->getRight() == nullptr) {
          
          return false;
        } else {
          
          if (!helperReadTree(num, it->getRight())) {return false;}
        }
      } else { return true;  } 
    }
    return true;
  }
  
  
  
  static int count = 0;
  void AVLTree::outputTree() {
  	totalHeight = 0;
  	
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
  	
  	file << "\nOutputting AVL tree:\n";
  	if (root == nullptr) { std::cout << "root is boot\n"; return;}
  	if (root->getLeft() != nullptr) {
  		helperOutputTree(root->getLeft(),file);
  	}
  	if (root->getRight() != nullptr) {
  		helperOutputTree(root->getRight(),file);
  	}
  	file << root->getValue() << " height: " << root->height << std::endl;
  	
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
