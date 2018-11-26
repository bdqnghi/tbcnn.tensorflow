#ifndef __LIST_CPP
#define __LIST_CPP
#include <cstdlib>
#include "avl.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
int flag;

template <class A, class B>
tree<A,B>::tree()
{

    root=NULL;
}

template <class A, class B>
tree<A,B>::~tree()
{

}

//<------------------------------------------------->
// make new node.
template <class A, class B>
treeNode<A,B> *tree<A,B>::newNode(A v, B k){
	treeNode<A,B> *toInsert = new treeNode<A,B>(v,k);
	toInsert->left=NULL;
	toInsert->right=NULL;
	return toInsert;
}
//<------------------------------------------------->
// toInsert

template <class A, class B>
treeNode<A,B> *tree<A,B>::insert(A v, B k){
	if (root==NULL){
		root=newNode(v,k);
	}
	else{
		return insert(root,v,k);
	}
}

//<------------------------------------------------->
// insert
template <class A, class B>
treeNode<A,B> *tree<A,B>::insert( treeNode<A,B> *&trav, A v, B k)
{

	if (trav==NULL){			
		trav = newNode(v,k);
		return trav;	
	}//if....
	else{ 
    	if (k < trav->key){
			insert(trav->left,v,k);
			if (flag==2){
				checkLeftBalance(trav, k);}
		}//if....			
		
		if (k > trav->key){
			insert(trav->right, v ,k);
			if (flag==2){
				checkRightBalance(trav, k);}
		}//if....	
	}//else	 		
	
}// insert func.
//<-------------------------------------------------------------------------------------------------->

template <class A, class B>
void tree<A,B>::checkLeftBalance( treeNode<A,B> *&node, B k){
	treeNode<A,B> *nL = node->left; 
	treeNode<A,B> *nR = node->right;
	 if( height(nL) - height(nR) >= 2){
	 	if( k < nL->key){
          	rotateLeftOnce(node);
       	}
       else{
          	rotateLeftTwice(node);		
 	 }	
 	 }

}

template <class A, class B>
void tree<A,B>::checkRightBalance( treeNode<A,B> *&node, B k){
	treeNode<A,B> *nL = node->left;
	treeNode<A,B> *nR = node->right;
	if( height(nR) - height(nL) == 2){
	 	if(k > nR->key){
        	rotateRightOnce(node);
    	}   
    	else{
        	rotateRightTwice(node);
   		}
	}
}
//<-------------------------------------------------------------------------------------------------->
// Rotation function.
template <class A, class B>
void tree<A,B>::rotateLeftOnce( treeNode<A,B> *&node ){
	 treeNode<A,B> *nL;
     nL = node->left;
     node->left = nL->right;
     nL->right = node;
     node = nL;	
}// leftOnce.
template <class A, class B>
void tree<A,B>::rotateLeftTwice( treeNode<A,B> *&node){
	rotateRightOnce(node->left);
	rotateLeftOnce(node);
} //lefttwice.

template <class A, class B>
void tree<A,B>::rotateRightOnce( treeNode<A,B> *&node){
	 treeNode<A,B> *nR;
     nR = node->right;
     node->right = nR->left;
     nR->left = node;
     node = nR;
}//Right Once.

template <class A, class B>
void tree<A,B>:: rotateRightTwice(treeNode<A,B> *&node){
	rotateLeftOnce(node->right);
	rotateRightOnce(node);
}
//RightTwice.
//<-------------------------------------------------------------------------------------------------->	
// Update Height.

template <class A, class B>
void tree<A,B>::updateHeight( treeNode<A,B> *&trav, B item){

	if (trav==NULL){
		return;
	}	
	B hL = height(trav->left);
	B hR = height(trav->right);
	if (trav->left==NULL)
		hL = 0;
	if(trav->left==NULL)
		hR = 0;
	// Now calculte the differe.

	if (hR-hL >= 2){
	    treeNode<A,B> *nL = trav->left;
        treeNode<A,B> *nR = trav->right;
        if( item > nR->key)
          rotateRightTwice(trav);
       else
          rotateRightOnce(trav);
    }  
    else if(hL-hR>=2){
    	treeNode<A,B> *nL = trav->left;
    	treeNode<A,B> *nR = trav->right;   
 	    if( item < nL->key)
           rotateLeftTwice(trav);
       	else
           rotateLeftOnce(trav);
	}
		
	treeNode<A,B> *retParent = parent(trav->key);
//	cout<<"parents values: "<< retParent->key <<endl;
	updateHeight(retParent, item);
}
//<-------------------------------------------------------------------------------------------------->

template <class A, class B>
void tree<A,B>::assignHeights( treeNode<A,B> *&trav){
		if (trav!=NULL){
			trav->nodeHeight = height(trav);
//			cout<< trav->nodeHeight<< " is for "<< trav->value <<endl;
		}
		else if (trav==NULL){	
			return;
		}
		assignHeights(trav->left);
		assignHeights(trav->right);
		
}// assignHeights.
//<------------------------------------------------------------------------------------------------->

template <class A, class B>
treeNode<A,B> *tree<A,B>::search( treeNode<A,B> *&trav, B item)
{
	if(root!=NULL){
		treeNode<A,B> *trav = root;
		while (trav!=NULL){
		// Go left if item is less than or equal.
			if (item <= trav->key){
				if (item==trav->key){
					return trav;
				}//if.	
				else
				trav = trav->left;	
			}//if..
			else if(item >= trav->key){
				if (item==trav->key){
					return trav;
				}	
				else
					trav = trav->right;
			}//else if.
		}//while.
		return NULL; 
	}//if.
}// search func.

//<------------------------------------------------>
template <class A, class B>
treeNode<A,B> *tree<A,B>::parent(B item)
{
if (item==root->key)
	return NULL;
else{
    if(root!=NULL){
        treeNode<A,B> *trav = root;
		treeNode<A,B> *pre = trav;
        while (trav!=NULL){
        // Go left if item is less than or equal.
            if (item <= trav->key){
                if (item==trav->key){ 
                    return pre;
                }
                else{
                	pre = trav;
                	trav = trav->left;
                }
            }//if..
            else if(item >= trav->key){
                if (item==trav->key){
                    return pre;
                }    
                else{
                	pre = trav;
                    trav = trav->right;
                }  
            }//else if.
        }//while.
    }//if.
}
}// search func.

//<-------------------------------------------------------------------------------------------->
template <class A, class B>
treeNode<A,B> *tree<A,B>::deleteNode(B item)
{
	treeNode<A,B> *retNode = search( root, item);
if (retNode!=NULL){	
	treeNode<A,B> *retParent = parent(item);
	treeNode<A,B> *parentLeft = retParent->left;
	treeNode<A,B> *parentRight = retParent->right;

	// If node has no subtree.
	if (retNode->left==NULL && retNode->right==NULL){

		if (parentLeft!=NULL && parentLeft->key==retNode->key){ // Node at the left of parent.
			retParent->left=NULL;
			delete(retNode);
			retNode=NULL;
			return retParent;
		}//if.	
		else if(parentRight!=NULL && parentRight->key==retNode->key){ // Node is at the right of parent.
			retParent->right=NULL;
			delete(retNode);
			retNode=NULL;
			return retParent;	
			
		}//else if.	
	}//if.
	// if Node deleted has only one subtree.
	else if (retNode->left==NULL){
		if (parentLeft!=NULL && parentLeft->key==retNode->key){ // Node is at the left of parent.
			retParent->left = retNode->right; 
		}
		else if(parentRight!=NULL && parentRight->key==retNode->key){ // Node is at the right of parents.
			retParent->right= retNode->right;
		}			
		delete(retNode);
		retNode=NULL;
		return retParent;
	}
	else if(retNode->right==NULL){
		if (parentLeft!=NULL && parentLeft->key==retNode->key){ // Node is at the left of parent	
			retParent->left = retNode->left;
		}
		else if(parentRight!=NULL && parentRight->key==retNode->key){ // node is at the right of parent.
			retParent->right = retNode->left;
		}
		delete(retNode);
		retNode=NULL;
		return retParent;
	}		
	// if Node has both subtree.
	else if(retNode->left!=NULL && retNode->right!=NULL){
		treeNode<A,B> *nodeRight = retNode->right;
		treeNode<A,B> *preN=nodeRight;
		while (nodeRight->left!=NULL){
			preN = nodeRight;
			nodeRight = nodeRight->left;
		}//while.
		A a1 = nodeRight->value;
		B b1 = nodeRight->key;
		preN->left=NULL;
		delete(nodeRight);
		nodeRight=NULL;
		retNode->value = a1;
		retNode->key = b1;
		return retParent;
	}//else if.
}
	else
		return NULL;
}// delete func.
//<----------------------------------------------------------------------->
template <class A, class B>
treeNode<A,B> *tree<A,B>::getRoot(){
	return root;
}
//<------------------------------------------------------------------------>

template <class A, class B>
int tree<A,B>::height( treeNode<A,B> *&h){
	  
    if(h==NULL)
 		return -1;
    else{

        int leftH=height(h->left);

        int rightH=height(h->right);

        if (leftH>rightH)
        	return leftH+1;

        else
            return rightH+1;
    }//else.

}
#endif
