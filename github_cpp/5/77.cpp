#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "avl-tree.h"


AVLTree& AVLTree::insert(int val)
{
    rec_insert(root,val);
    return *this;
}

//void in_order(node*);
//void in_order_bf(node*);

void AVLTree::rec_insert(node*& curr, int val)
{
    if (curr == nullNode) {
        curr = new node(val, nullNode,nullNode); // use the constructor
        return;
    }
    
    int oppNodeHt = 0;
    
    // pointers to members: one will be left, the other will be right, but we don't know which one
    // this is like the differential pseudoform approach... LOLOLOL
    node* node::*compNode=nullptr;
    node* node::*oppNode=nullptr;
    
    // "compnode" stands for "computed node", that is, the node we just inserted into
    
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
        return; // they are equal, so stop
    }
    if ((curr->*compNode)->ht >= curr->ht) {
        
        if ((curr->*compNode)->ht - oppNodeHt > 1) {
            // AVL property. All that pointer to member gymnastics is to avoid
            // having to repeat code for rotations
            
            int compOppNodeHt = (curr->*compNode->*oppNode)->ht;
            int compCompNodeHt =  (curr->*compNode->*compNode)->ht;
            node *tmp = nullNode;
            
            // if compNode's compNode is the larger, rotate once in the opposite direction
            
            if ( compCompNodeHt < compOppNodeHt ) {
                // compNode's oppNode is the larger, so rotate BASED AT COMPNODE
                // once in the SAME direction, then rotate (based at (new) curr)
                --curr->ht;
                --(curr->*compNode)->ht;
                ++(curr->*compNode->*oppNode)->ht;
                
                node *tmp = curr->*compNode;
                curr->*compNode = curr->*compNode->*oppNode;
                tmp->*oppNode = curr->*compNode->*compNode;
                curr->*compNode->*compNode = tmp;
                
                // now rotate based at new current
            } else if (compCompNodeHt > compOppNodeHt) {
                --curr->ht;
            } // if they're equal, maintain current height
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
        curr = index & mask ? curr->right : curr->left; // select the right or left depending on mask
        mask >>=1;
    }
    return curr == nullNode? nullptr : curr; // note: this has to be fixed -- obviously it's not unchecked if it's still using a conditional
}

//class unbalanced_exception{};

/*void in_order_bf(node* curr)
{
    if (curr == nullNode) return;
    
    in_order_bf(curr->left);
    int leftHt=0, rightHt=0;
    if(curr->left) leftHt = curr->left->ht;
    if(curr->right) rightHt = curr->right->ht;
    std::cout << curr->val << "(BF=" << leftHt -rightHt << ") ";
    if (abs(leftHt-rightHt) > 1) throw unbalanced_exception();
    in_order_bf(curr->right);
}
*/
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
