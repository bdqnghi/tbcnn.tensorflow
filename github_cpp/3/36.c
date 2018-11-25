#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "avl-tree.h"


AVLTree& AVLTree::insert(int val)
{
    rec_insert(root,val);
    return *this;
}




void AVLTree::rec_insert(node*& curr, int val)
{
    if (curr == nullNode) {
        curr = new node(val, nullNode,nullNode); 
        return;
    }
    
    int oppNodeHt = 0;
    
    
    
    node* node::*compNode=nullptr;
    node* node::*oppNode=nullptr;
    
    
    
    if (curr->val > val) {
        rec_insert(curr->left,val);
        compNode = &node::left;
        oppNodeHt = curr->right->ht;
        oppNode = &node::right;
    }
    else if (curr->val < val) {
        rec_insert(curr->right,val);
        compNode = &node::right;
        oppNodeHt = curr->left->ht;
        oppNode = &node::left;
    } else {
        return; 
    }
    if ((curr->*compNode)->ht >= curr->ht) {
        
        if ((curr->*compNode)->ht - oppNodeHt > 1) {
            
            
            
            int compOppNodeHt = (curr->*compNode->*oppNode)->ht;
            int compCompNodeHt =  (curr->*compNode->*compNode)->ht;
            node *tmp = nullNode;
            
            
            
            if ( compCompNodeHt < compOppNodeHt ) {
                
                
                --curr->ht;
                --(curr->*compNode)->ht;
                ++(curr->*compNode->*oppNode)->ht;
                
                node *tmp = curr->*compNode;
                curr->*compNode = curr->*compNode->*oppNode;
                tmp->*oppNode = curr->*compNode->*compNode;
                curr->*compNode->*compNode = tmp;
                
                
            } else if (compCompNodeHt > compOppNodeHt) {
                --curr->ht;
            } 
            tmp = curr;
            curr = curr->*compNode;
            tmp->*compNode = curr->*oppNode;
            curr->*oppNode = tmp;
            
            
        } else {
            ++curr->ht;
        }
    }
}

const int & AVLTree::binary_index(int level, unsigned index) const
{
    node *curr = binary_index_unchecked(level, index);
    if (curr == nullNode) {
        throw item_not_found();
    }
    return curr->val;
}

node *AVLTree::binary_index_unchecked(int level, unsigned index) const
{
    node *curr = root;
    unsigned mask = 1 << (level-1);
    for (int i=0; i< level; i++) {
        curr = index & mask ? curr->right : curr->left; 
        mask >>=1;
    }
    return curr == nullNode? nullptr : curr; 
}




void AVLTree::level_order(std::ostream & os) const
{
for (int level = 0; level < root->ht; level++) {
        for ( int i = 0; i < (1<<level); i++) {
            node *curr = binary_index_unchecked(level,i);
            if (curr) os << curr->val << ' ';
        }
    }
}

int AVLTree::find_max() const
{
    node *n = binary_index_unchecked(0, 0);
    int maxVal=0;
    while (n != nullNode) {
        maxVal = n->val;
        n=n->right;
    }
    return maxVal;
}
