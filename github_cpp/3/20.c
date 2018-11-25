









#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;


typedef struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
}node;


int max(int a, int b);


int height(node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}


int max(int a, int b)
{
    return (a > b)? a : b;
}


node* newNode(int key)
{
    node* tmp = new node();
    tmp->key   = key;
    tmp->left   = NULL;
    tmp->right  = NULL;
    tmp->height = 1;  
    return(tmp);
}



node *rightRotate(node *y)
{
    node *x = y->left;
    node *T2 = x->right;
    
    
    x->right = y;
    y->left = T2;
    
    
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
    
    
    return x;
}



node *leftRotate(node *x)
{
    node *y = x->right;
    node *T2 = y->left;
    
    
    y->left = x;
    x->right = T2;
    
    
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
    
    
    return y;
}


int getBalance(node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

node* insert(node* node, int key)
{
    
    if (node == NULL)
        return(newNode(key));
    
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    
    
    node->height = max(height(node->left), height(node->right)) + 1;
    
    
    int balance = getBalance(node);
    
    
    
    
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    
    
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    
    
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    
    
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    
    return node;
}



node * minValueNode(node* t)
{
    node* current = t;
    
    
    while (current->left != NULL)
        current = current->left;
    
    return current;
}

node* deleteNode(node* root, int key)
{
    
    
    if (root == NULL)
        return root;
    
    
    
    if ( key < root->key )
        root->left = deleteNode(root->left, key);
    
    
    
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
    
    
    
    else
    {
        
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct node *temp = root->left ? root->left : root->right;
            
            
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else 
                *root = *temp; 
            
            free(temp);
        }
        else
        {
            
            
            node* temp = minValueNode(root->right);
            
            
            root->key = temp->key;
            
            
            root->right = deleteNode(root->right, temp->key);
        }
    }
    
    
    if (root == NULL)
        return root;
    
    
    root->height = max(height(root->left), height(root->right)) + 1;
    
    
    
    int balance = getBalance(root);
    
    
    
    
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    
    
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
    
    
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    
    
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}


void preOrder(node *root)
{
    if(root != NULL)
    {
        cout << root->key << " " ;
        preOrder(root->left);
        preOrder(root->right);
    }
}



int main()
{
    struct node *root = NULL;
    
    
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);
    
    
    
    cout << "Pre order traversal of the constructed AVL tree is \n";
    preOrder(root);
    
    return 0;
}