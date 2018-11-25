#include<iostream>

using namespace std;


class AVLTreeNode {
public:
    int val;
    AVLTreeNode* left;
    AVLTreeNode* right;
    int height;

    AVLTreeNode(int v) {
        val = v;
        left = NULL;
        right = NULL;
        height = 1; 
    }
};


int max(int a, int b);


int height(AVLTreeNode* node) {
    if(node == NULL) return 0;
    return node->height;
}


int max(int a, int b) {
    return (a > b)? a : b;
}





AVLTreeNode* rightRotate(AVLTreeNode* y) {
    AVLTreeNode* x = y->left;
    AVLTreeNode* T2 = x->right;

    
    x->right = y;
    y->left = T2;

    
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    
    return x;
}



AVLTreeNode* leftRotate(AVLTreeNode* x) {
    AVLTreeNode* y = x->right;
    AVLTreeNode* T2 = y->left;

    
    y->left = x;
    x->right = T2;

    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    
    return y;
}


int getBalance(AVLTreeNode* node) {
    if(node == NULL) return 0;
    return height(node->left) - height(node->right);
}

AVLTreeNode* insert(AVLTreeNode* node, int val) {
    
    if(node == NULL) return(new AVLTreeNode(val));

    if(val < node->val) {
        node->left = insert(node->left, val);
    } else {
        node->right = insert(node->right, val);
    }

    
    node->height = max(height(node->left), height(node->right)) + 1;

    
    int balance = getBalance(node);

    

    
    if(balance > 1 && val < node->left->val) {
        return rightRotate(node);
    }

    
    if(balance < -1 && val > node->right->val) {
        return leftRotate(node);
    }

    
    if(balance > 1 && val > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    
    if(balance < -1 && val < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    
    return node;
}


AVLTreeNode* minValueNode(AVLTreeNode* node) {
    AVLTreeNode* current = node;

    
    while(current->left != NULL) {
        current = current->left;
    }

    return current;
}

AVLTreeNode* deleteNode(AVLTreeNode* root, int val) {
    
    if(root == NULL) return root;

    
    
    if(val < root->val) {
        root->left = deleteNode(root->left, val);
    } else if(val > root->val) {
        
        
        root->right = deleteNode(root->right, val);
    } else {
        
        
        
        if((root->left == NULL) || (root->right == NULL)) {
            AVLTreeNode* temp = root->left ? root->left : root->right;

            
            if(temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                
                *root = *temp; 
            }
            delete(temp);
        } else {
            
            
            AVLTreeNode* temp = minValueNode(root->right);

            
            root->val = temp->val;

            
            root->right = deleteNode(root->right, temp->val);
        }
    }

    
    if(root == NULL) return root;

    
    root->height = max(height(root->left), height(root->right)) + 1;

    
    
    int balance = getBalance(root);

    

    
    if(balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    
    if(balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    
    if(balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    
    if(balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}



void preOrder(AVLTreeNode*root) {
    if(root != NULL) {
        cout<<root->val<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
}


int main() {
    AVLTreeNode* root = NULL;

    
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    

    cout<<"Pre order traversal of the constructed AVL tree is "<<endl;
    preOrder(root);

    root = deleteNode(root, 10);

    

    cout<<"\nPre order traversal after deletion of 10 "<<endl;
    preOrder(root);

    return 0;
}
