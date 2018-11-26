#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>
#include <iterator>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode(int val) : val(val), left(nullptr), right(nullptr), height(1) {}
};

int balance(TreeNode* root) {
    return (root->left ? root->left->height : 0) - (root->right ? root->right->height : 0); 
}

void updateHeight(TreeNode* root) {
    root->height = max(root->left ? root->left->height : 0, root->right ? root->right->height : 0) + 1; 
};

TreeNode* leftRotate(TreeNode* root) {
    TreeNode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

TreeNode* rightRotate(TreeNode* root) {
    TreeNode* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

TreeNode* rebalance(TreeNode* root) {
    int b = balance(root);
    if (b > 1) {
        if (balance(root->left) < 0)
            root->left = leftRotate(root->left);
        return rightRotate(root);
    } else if (b < -1) {
        if (balance(root->right) > 0)
            root->right = rightRotate(root->right);
        return leftRotate(root);
    } else {
        return root;
    }
}

TreeNode* insert(TreeNode* root, int val) {
    if (!root)
        return new TreeNode(val);

    if (val < root->val) {
        root->left = insert(root->left, val);
    } else if (val > root->val) {
        root->right = insert(root->right, val);
    } else {
        throw "key exists";
    }
    updateHeight(root);
    return rebalance(root);
}

TreeNode* remove(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (val < root->val) {
        root->left = remove(root->left, val);
    } else if (val > root->val) {
        root->right = remove(root->right, val);
    } else {
        if (!root->left || !root->right) {
            TreeNode* t = root->left ? root->left : root->right;
            delete root;
            return t;
        } else { 
            TreeNode* max = root->left;
            while (max->right) max = max->right; // max in left sub tree
            root->val = max->val;
            root->left = remove(root->left, max->val);
        }
    }

    updateHeight(root);
    return rebalance(root);
}

TreeNode* lookup(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (val < root->val)
        return lookup(root->left, val);
    else if (val > root->val)
        return lookup(root->right, val);
    else
        return root;
}

void print(TreeNode* root, bool isTail, string indent) {
    if (!root) return;
    if (root->right)
        print(root->right, false, indent + (isTail ? "|     " : "      "));
    cout << indent << (isTail ? "\\--- " : "/--- ") << root->val << endl;
    if (root->left)
        print(root->left, true, indent + (isTail ? "      " : "|     "));
}

int main() {
    vector<int> keys = { 13, 2, 10, 3, 1, 12, 8, 4, 5, 7, 9, 6, 15, 14, 11 }; // 1-15

    TreeNode* root = nullptr;
    for (int key : keys) {
        root = insert(root, key);
        cout << "insert( " << key << ")" << endl;
        print(root, false, "");
        cout << endl;
    }

    for (int key = 1; key <= 15; ++key) {
        if (!lookup(root, key)) {
            cout << key << " not found!" << endl;
            return 1;
        }
    }

    for (int key = 1; key <= 15; ++key) {
        root = remove(root, key);
        cout << "remove(" << key << ")" << endl;
        print(root, false, "");
        cout << endl;
    }

}

