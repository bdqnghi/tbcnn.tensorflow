#include <iostream>
using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
};

int heigthOf(Node* node) {
    if (!node) return 0;
    return node->height;
}

Node* getMinNode(Node* root) {
    Node* node = root;
    while(node->left != nullptr) {
        node =  node->left;
    }
    return node;
}

int getBalanceFactor(Node* node) { 
    if (!node) return 0;
    return heigthOf(node->left) - heigthOf(node->right);
}

Node* rotateLeft(Node* root) {
    Node* newRootNode = root->right;
    Node* oldRootNodeRight = newRootNode->left;
    newRootNode->left = root;
    root->right = oldRootNodeRight;
    root->height = max(heigthOf(root->left), heigthOf(root->right)) + 1;
    newRootNode->height = max(heigthOf(newRootNode->left), heigthOf(newRootNode->right)) + 1;
    return newRootNode;
}

Node* rotateRight(Node* root) {
    Node* newRootNode = root->left;
    Node* oldRootNodeLeft = newRootNode->right;
    newRootNode->right = root;
    root->left = oldRootNodeLeft;
    root->height = max(heigthOf(root->left), heigthOf(root->right)) + 1;
    newRootNode->height = max(heigthOf(newRootNode->left), heigthOf(newRootNode->right)) + 1;
    return newRootNode;
}

    
Node* insert(int key, Node* root) {
    if (!root) {
        return new Node { key, 1, nullptr, nullptr };
    }
    if (key < root->key) {
        root->left = insert(key, root->left);
    } else if (key > root->key) {
        root->right = insert(key, root->right);
    } else {
        printf("Duplicates keys are not allowed");
        return root;
    }
    root->height = max(heigthOf(root->left), heigthOf(root->right)) + 1;
    int balanceFactor = getBalanceFactor(root);
    if (2 <= balanceFactor && key < root->left->key) { 
                                                       
        return rotateRight(root);
    } else if (2 <= balanceFactor && key > root->left->key) { 
                                                              
        root->left = rotateLeft(root->left);
        return rotateRight(root);

    } else if (-2 >= balanceFactor && key > root->right->key) { 
                                                                
        return rotateLeft(root);
    } else if (-2 >= balanceFactor && key < root->right->key) { 
                                                                
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

Node* deleteNode(int key, Node* root) {
    if (!root) return nullptr;
    if (key == root->key) {
        if (root->left && root->right) { 
                                         
            Node* minRightNode = getMinNode(root->right);
            root->key = minRightNode->key;
            root->right = deleteNode(minRightNode->key, root->right);
        } else {
            Node* tempNode = root->left ? root->left : root->right;
            delete root;
            return tempNode;
        }
    } else if (key < root->key) {
        root->left = deleteNode(key, root->left);
    } else {
        root->right = deleteNode(key, root->right);
    }
    if (!root) return nullptr;
    root->height = max(heigthOf(root->left), heigthOf(root->right)) + 1;
    int balanceFactor = getBalanceFactor(root);
    int leftBalanceFactor = getBalanceFactor(root->left);
    int rightBalanceFactor = getBalanceFactor(root->right);
    if (2 <= balanceFactor && leftBalanceFactor >= 0) { 
                                                        
        return rotateRight(root);
    } else if (2 <= balanceFactor && leftBalanceFactor < 0) { 
                                                              
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    } else if (-2 >= balanceFactor && rightBalanceFactor <= 0) { 
                                                                 
        return rotateLeft(root);
    } else if (-2 >= balanceFactor && rightBalanceFactor > 0) { 
                                                                
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

void traverseTree(Node* root) {
    if (!root) {
        return;
    }
    Node* node = root;
    printf(" %d ", node->key);
    traverseTree(node->left);
    traverseTree(node->right);
}

int main() {
    Node* root = nullptr;
    root = insert(4, root);
    root = insert(7, root);
    root = insert(17, root);
    root = insert(10, root);
    root = insert(5, root);
    root = insert(14, root);
    root = insert(15, root);
    traverseTree(root);
    printf("\n");
    root = deleteNode(7, root);
    traverseTree(root);
    printf("\n");
    root = deleteNode(15, root);
    traverseTree(root);
    printf("\n");
    root = deleteNode(5, root);
    traverseTree(root);
    printf("\n");
    root = deleteNode(10, root);
    traverseTree(root);
    printf("\n");
    root = insert(10, root);
    root = insert(5, root);
    root = insert(7, root);
    root = insert(15, root);
    traverseTree(root);
    printf("\n");
}
