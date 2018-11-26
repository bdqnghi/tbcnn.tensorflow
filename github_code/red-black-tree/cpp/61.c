#include <bits/stdc++.h>

using namespace std;

#define RED 0
#define BLACK 1

struct RBNode {
    RBNode *left, *right, *parent;
    int key, color;
};

// left rotate
/*
 *   |                |
 *  node             right
 *  / \      ==>      / \
 * a  right        node  c
 *     / \         / \
 *    b   c       a   b
 *
 */
static RBNode *leftRotate(RBNode *node, RBNode *root) {
    RBNode *right = node->right;

    if ((node->right = right->left)) {
        right->left->parent = node;
    }
    right->left = node;

    if ((right->parent = node->parent)) {
        if (node == node->parent->left) {
            node->parent->left = right;
        } else {
            node->parent->right = right;
        }
    } else {
        root = right;
    }
    node->parent = right;
    return root;
}

//right rotate

/*
 *       |              |
 *      node           left
 *      / \     ==>    / \
 *   left  c          a  node
 *    / \                / \
 *   a   b              b   c
 */

static RBNode *rightRotate(RBNode *node, RBNode *root) {
    RBNode *left = node->left;
    if ((node->left = left->right)) {
        left->right->parent = node;
    }
    left->right = node;
    if ((left->parent = node->parent)) {
        if (node == node->parent->left) {
            node->parent->left = left;
        } else {
            node->parent->right = left;
        }
    } else {
        root = left;
    }
    node->parent = left;
    return root;
}

static RBNode *search(int key, RBNode *root, RBNode **save) {
    RBNode *node = root, *parent = NULL;
    while (node) {
        parent = node;
        if (key < node->key) {
            node = node->left;
        } else if (node->key < key) {
            node = node->right;
        } else {
            return node;
        }
    }
    if (save) {
        *save = parent;
    }
    return NULL;
}

static RBNode *search(int key, RBNode *root) {
    return search(key, root, NULL);
}

static RBNode *insertFixUp(RBNode *root, RBNode *node) {

    RBNode *parent = NULL, *gparent = NULL, *uncle = NULL;
    while ((parent = node->parent) && parent->color == RED) {
        gparent = parent->parent;
        if (parent == gparent->left) {
            uncle = gparent->right;
            //case 1
            if (uncle && uncle->color == RED) {
                parent->color = uncle->color = BLACK;
                gparent->color = RED;
                node = gparent;
            } else {
                //case 2
                if (node == parent->right) {
                    node = parent;
                    root = leftRotate(node, root);
                    parent = node->parent;
                }
                //case 3
                parent->color = BLACK;
                gparent->color = RED;
                root = rightRotate(gparent, root);
            }
        } else {
            uncle = gparent->left;
            if (uncle && uncle->color == RED) {
                parent->color = uncle->color = BLACK;
                gparent->color = RED;
                node = gparent;
            } else {
                if (node == parent->left) {
                    node = parent;
                    root = rightRotate(node, root);
                    parent = node->parent;
                }
                parent->color = BLACK;
                gparent->color = RED;
                root = leftRotate(gparent, root);
            }
        }
    }
    root->color = BLACK;
}

static RBNode *insert(int key, RBNode *root) {
    RBNode *parent = NULL, *node;

    if (search(key, root, &parent)) {
        return root;
    }

    node = new RBNode();
    node->key = key;
    node->left = node->right = NULL;
    node->color = RED;
    node->parent = parent;

    if (parent) {
        if (parent->key > key) {
            parent->left = node;
        } else {
            parent->right = node;
        }
    } else {
        root = node;
    }
    root = insertFixUp(root, node);
    return root;
}

static RBNode *transplant(RBNode *root, RBNode *oldNode, RBNode *newNode) {
    if (!oldNode->parent)return newNode;
    if (oldNode == oldNode->parent->left) {
        oldNode->parent->left = newNode;
    } else {
        oldNode->parent->right = newNode;
    }
    if (newNode)
        newNode->parent = oldNode->parent;
    return root;
}

static RBNode *minimum(RBNode *root) {
    if (!root)return NULL;
    while (root->left)root = root->left;
    return root;
}

static RBNode *maximum(RBNode *root) {
    if (!root)return NULL;
    while (root->right)root = root->right;
    return root;
}

static RBNode *seccessor(RBNode *node) {
    if (node->right)return minimum(node->right);
    RBNode *parent = node->parent;
    while (parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

static RBNode *predecessor(RBNode *node) {
    if (node->left)return maximum(node->left);
    RBNode *parent = node->parent;
    while (parent && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

static RBNode *removeFixUp(RBNode *root, RBNode *node) {
    RBNode *brother, *parent;
    while (node != root && node->color == BLACK) {
        parent = node->parent;
        if (node == parent->left) {
            brother = parent->right;
            //case 1
            if (brother->color == RED) {
                brother->color = BLACK;
                parent->color = RED;
                root = leftRotate(parent, root);
            }
            //case 2
            if (brother->left->color == BLACK && brother->right->color == BLACK) {
                brother->color = RED;
                node = node->parent;
            }//case 3
            else if (brother->color == BLACK) {
                brother->left->color = BLACK;
                brother->color = RED;
                root = rightRotate(root, brother);
                brother = parent->right;
            }
            //case 4
            brother->color = parent->color;
            parent->color = BLACK;
            brother->right->color = BLACK;
            root = leftRotate(root, parent);
            node = root;
        } else {
            brother = parent->left;
            //case 1
            if (brother->color == RED) {
                brother->color = BLACK;
                parent->color = RED;
                root = rightRotate(parent, root);
            }
            //case 2
            if (brother->right->color == BLACK && brother->left->color == BLACK) {
                brother->color = RED;
                node = node->parent;
            }//case 3
            else if (brother->color == BLACK) {
                brother->right->color = BLACK;
                brother->color = RED;
                root = leftRotate(root, brother);
                brother = parent->left;
            }
            //case 4
            brother->color = parent->color;
            parent->color = BLACK;
            brother->left->color = BLACK;
            root = rightRotate(root, parent);
            node = root;
        }
    }
    node->color = BLACK;
    return root;
}

static RBNode *remove(int key, RBNode *root) {
    RBNode *node, *realDelete, *child;
    int color;
    if (!(node = search(key, root)))return root;

    realDelete = node;
    color = realDelete->color;

    if (!node->left) {
        child = node->right;
        root = transplant(root, node, node->right);
    } else if (!node->right) {
        child = node->left;
        root = transplant(root, node, node->left);
    } else {
        realDelete = minimum(node->right);
        color = realDelete->color;
        child = realDelete->right;
        root = transplant(root, realDelete, child);
        node->key = realDelete->key;
    }
    free(realDelete);

    if (color == BLACK) {
        root = removeFixUp(root, child);
    }
    return root;
}

static void traverse(RBNode *root) {
    if (!root)return;
    traverse(root->left);
    printf("%d ", root->key);
    traverse(root->right);
}


int main() {

    RBNode *root = NULL;
    root = insert(2, root);
    traverse(root);
    printf("\n");
    root = insert(3, root);
    traverse(root);
    printf("\n");
    root = insert(3, root);
    traverse(root);
    printf("\n");
    root = insert(5, root);
    traverse(root);
    printf("\n");
    root = insert(6, root);
    traverse(root);
    printf("\n");
    root = insert(7, root);
    traverse(root);
    printf("\n");
    root = insert(1, root);
    traverse(root);
    printf("\n");
    root = remove(5, root);
    traverse(root);
    printf("\n");
    root = insert(11, root);
    traverse(root);
    printf("\n");
    root = insert(13, root);
    traverse(root);
    printf("\n");
    root = insert(26, root);
    traverse(root);
    printf("\n");
    root = insert(16, root);
    traverse(root);
    printf("\n");


    return 0;
}














