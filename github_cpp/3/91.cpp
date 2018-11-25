







#include "avl.hpp"



int avlTree::height(avlNode *temp)
{
    int max_height = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        max_height = max (l_height, r_height);
        
    }
    return max_height + 1;;
}




int avlTree::diff(avlNode *temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}




avlNode *avlTree::rr_rotation(avlNode *parent)
{
    avlNode *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}



avlNode *avlTree::ll_rotation(avlNode *parent)
{
    avlNode *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}




avlNode *avlTree::lr_rotation(avlNode *parent)
{
    avlNode *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}




avlNode *avlTree::rl_rotation(avlNode *parent)
{
    avlNode *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);
}




avlNode *avlTree::balance(avlNode *temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}




avlNode *avlTree::insert(avlNode *root, int value, string data)
{
    if (root == NULL)
    {
        root = new avlNode;
        root->avlKey = value;
        root->name = data;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (value < root->avlKey)
    {
        root->left = insert(root->left, value, data);
        root = balance (root);
    }
    else if (value >= root->avlKey)
    {
        root->right = insert(root->right, value, data);
        root = balance (root);
    }
    return root;
}




void avlTree::display(avlNode *ptr, int level, int var)
{
    int i;
    if (ptr!=NULL)
    {
        display(ptr->right, level + 1, var);
        printf("\n");
        if (ptr == root)
            cout<< var<<" -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<ptr->name;
        display(ptr->left, level + 1, var);
    }
}





void avlTree::inorder(avlNode *tree)
{
    if (tree == NULL)
        return;
    inorder (tree->left);
    cout<<tree->avlKey<<"  ";
    inorder (tree->right);
}
void avlTree::preorder(avlNode *tree)
{
    if (tree == NULL)
        return;
    cout<<tree->avlKey<<"  ";
    preorder (tree->left);
    preorder (tree->right);
    
}


void avlTree::postorder(avlNode *tree)
{
    if (tree == NULL)
        return;
    postorder ( tree ->left );
    postorder ( tree ->right );
    cout<<tree->avlKey<<"  ";
}
