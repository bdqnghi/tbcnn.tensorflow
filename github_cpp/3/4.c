#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include "nvm0avltree.h"


tree_node*
search_tree_node(
    tree_root* tree,
    uint32_t lbn)
{
    tree_node* local_root = tree->root;

    while(local_root != NULL) 
    {
        if(lbn == local_root->lbn)
            return local_root;

        else if(lbn < local_root->lbn) 
            local_root = local_root->left;

        else if(lbn > local_root->lbn)
            local_root = local_root->right;
    }

    return nullptr;
}

void
insert_tree_node(
    tree_root* tree,
    tree_node* node)
{
    tree->root = insert_tree_node(tree->root, node);
    tree->count_total++;
}   


tree_node*
insert_tree_node(
    tree_node* root,
    tree_node* node)
{
    if (root == nullptr)
    {
        root = node;
        return root;
    }

    if (node->lbn < root->lbn)
    {
        root->left = insert_tree_node(root->left, node);
    }
    
    else
    {
        root->right = insert_tree_node(root->right, node);
    }

    
    root->height = max_height(get_height(root->left), get_height(root->right)) + 1;

    
    int balance = get_balance(root);
    
    
    if (balance > 1 && node->lbn < root->left->lbn)
    {
        return right_rotate(root);
    }
    
    
    if (balance > 1 && node->lbn > root->left->lbn)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }   
    
    
    if (balance < -1 && node->lbn > root->right->lbn)
    {
        return left_rotate(root);
    }
    
    
    if (balance < -1 && node->lbn < root->right->lbn)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

void
logical_delete_tree_node(
    tree_root* tree,
    tree_node* node)
{
    tree_node* local_root = tree->root;

    while(local_root != NULL) 
    {
        if(node->lbn == local_root->lbn)
        {
            if(local_root->valid == TREE_VALID)
            {
                local_root->valid = TREE_INVALID;
                tree->count_invalid++;
            }

            break;
        }
        else if(node->lbn < local_root->lbn) 
        {
            local_root = local_root->left;
        }
        else if(node->lbn > local_root->lbn)
        {
            local_root = local_root->right;
        }
    }
}


tree_node*
physical_delete_tree_node(
        tree_node* root,
        tree_node* node)
{
    if (root == nullptr)
    {
        return root;
    }
    
    if (node->lbn < root->lbn)
    {
        root->left = physical_delete_tree_node(root->left, node);
    }
    else if (node->lbn > root->lbn)
    {
        root->right = physical_delete_tree_node(root->right, node);
    }
    else
    {
        
        if ((root->left == nullptr) || (root->right == nullptr))
        {
            tree_node* temp = root->left ? root->left : root->right;
            
            if (temp == nullptr)
            { 
                temp = root;
                root = nullptr;
            }
            else 
            { 
                *root = *temp;
            }

            free(temp);
        }

        else
        {
            
            tree_node* temp =  min_value_node(root->right);
            
            
            root->inode = temp->inode;
            root->lbn = temp->lbn;
            root->valid = temp->valid;
            
            
            root->right = physical_delete_tree_node(root->right, temp);
        }
    }
    
    if (root == nullptr)
    {
        return root;
    }
    
    
    root->height = max_height(get_height(root->left),get_height(root->right)) + 1;
    
    
    int balance = get_balance(root);
    
    
    if (balance > 1 && get_balance(root->left) >= 0)
    {
        return right_rotate(root);
    }
    
    
    if (balance > 1 && get_balance(root->left) < 0)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    
    
    if (balance < -1 && get_balance(root->right) <= 0)
    {
        return left_rotate(root); 
    }
    
    
    if (balance < -1 && get_balance(root->right) > 0)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    
    return root;
}

void
rebalance_tree_node(
    tree_root* tree)
{
    while(tree->count_invalid > 0)
    {
        printf("total: %5d, invalid: %5d, ratio: %3.0f%%\r", tree->count_total, tree->count_invalid, get_invalid_ratio(tree)* 100);
        tree_node *invalid_node = find_invalid_tree_node(tree->root);
        tree->root = physical_delete_tree_node(tree->root, invalid_node);
        tree->count_total--;
        tree->count_invalid--;
    }

    printf("total: %5d, invalid: %5d, ratio: %3.0f%%\n", tree->count_total, tree->count_invalid, get_invalid_ratio(tree)* 100);
    printf("\n");
}

tree_node*
find_invalid_tree_node(
    tree_node* node)
{
    std::stack<tree_node*> tnode_stack;
    tnode_stack.push(node);

    while (!tnode_stack.empty() && tnode_stack.top() != nullptr) 
    {
        tree_node *tnode = tnode_stack.top();
        tnode_stack.pop();

        if(tnode->valid == TREE_INVALID)
            return tnode;

        if(tnode->right != nullptr)
        {
            tnode_stack.push(tnode->right);
        }

        if(tnode->left != nullptr)
        {
            tnode_stack.push(tnode->left);
        }
    }
    
    return NULL;
}


tree_node*
min_value_node(
    tree_node* node)
{
    tree_node* current = node;
    
    while (current->left != nullptr)
    {
        current = current->left;
    }
    
    return current;
}

tree_node*
init_tree_node(
    inode_entry* inode)
{
    tree_node* t = (tree_node*)malloc(sizeof(tree_node));
    t->inode = inode;
    t->lbn = inode->lbn;
    t->valid = TREE_VALID;
    t->left = nullptr;
    t->right = nullptr;
    t->height = 1;
    
    return t;
}


int
get_height(
    tree_node* node)
{
    if (node == NULL) 
    {
        return 0;
    }
    return node->height;
}

int
max_height(
    int a,
    int b)
{
    return a > b ? a : b;
}

int
get_balance(
    tree_node* node)
{
    if (node == NULL)
    {
        return 0;
    }

    return get_height(node->left) - get_height(node->right);
}

tree_node*
right_rotate(
    tree_node* y)
{
    tree_node* x = y->left;
    tree_node* T2 = x->right;

    
    x->right = y;
    y->left = T2;

    
    y->height = max_height(get_height(y->left), get_height(y->right)) + 1;
    x->height = max_height(get_height(x->left), get_height(x->right)) + 1;

    
    return x;
}

tree_node*
left_rotate(
    tree_node* x)
{
    tree_node* y = x->right;
    tree_node* T2 = y->left;

    
    y->left = x;
    x->right = T2;

    
    x->height = max_height(get_height(x->left), get_height(x->right)) + 1;
    y->height = max_height(get_height(y->left), get_height(y->right)) + 1;

    
    return y;
}

double
get_invalid_ratio(
        tree_root *tree)
{
    if(tree->count_total == 0)
        return 0;

    return (double)tree->count_invalid/(double)tree->count_total; 
}

