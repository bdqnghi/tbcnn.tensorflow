#include "RedBlackTree.h"

RedBlackTree::RedBlackTree()
{
    nil = newNode();
}

Node * RedBlackTree::root()
{
    return nil -> left;
}

void RedBlackTree::inorder()
{
    inorderRec(root());
    cout << endl;
}

void RedBlackTree::inorderRec(Node* node)
{
    if (node != nil)
    {
        inorderRec(node -> left);
        cout << node -> key << " ";
        inorderRec(node -> right);
    }
}

void RedBlackTree::inorderIter()
{
    auto x = root();
    auto prev = nil;
    while (x != nil)
    {
        if (prev == x -> parent)
        {   // coming from up, going to left
            if (x -> left == nil)
            {   // left branch is nil
                prev = x -> left;
            }
            else
            {
                prev = x;
                x = x -> left;
            }
        }
        else if (prev == x -> left)
        {   // coming from left, going to right
            cout << x -> key << " ";
            if (x -> right == nil)
            {  // right branch is nil
                prev = x;
                x = x -> parent;
            }
            else
            {
                prev = x;
                x = x -> right;
            }
        }
        else
        {   // coming from right, going up
            prev = x;
            x = x -> parent;
        }
    }
    cout << endl;
}

void RedBlackTree::preOrder()
{
    preOrderRec(root());
    cout << endl;
}

void RedBlackTree::preOrderRec(Node* x)
{
    if (x != nil)
    {
        cout << x -> key << " ";
        preOrderRec(x -> left);
        preOrderRec(x -> right);
    }
}

void RedBlackTree::postOrder()
{
    postOrderRec(root());
    cout << endl;
}

void RedBlackTree::postOrderRec(Node* x)
{
    if (x != nil)
    {
        postOrderRec(x -> left);
        postOrderRec(x -> right);
        cout << x -> key << " ";
    }
}

Node* RedBlackTree::find(int val)
{
    auto r = root();
    while (r != nil && r -> key != val)
    {
        r = (r -> key > val)
                ? r -> left
                : r -> right;
    }
    return r;
}

Node* RedBlackTree::minimum(Node* root)
{   // return left most leaf in the tree
    while (root -> left != nil)
    {
        root = root -> left;
    }
    return root;
}

Node* RedBlackTree::maximum(Node* root)
{   // return the rightmost leaf in the tree
    while (root -> right != nil)
    {
        root = root -> right;
    }
    return root;
}

Node* RedBlackTree::successor(Node* x)
{  // smallest node that is larger than x
    if (x -> right != nil)
    {   // everything in right branch is larger than x;
        return minimum(x -> right);
    }
    else
    {   // if x is the left branch of its parent, then its parent is larger than it
        auto p = x -> parent;
        while (p != nil && x != p -> left)
        {   // moving up the tree until x becomes left branch
            x = p;
            p = p -> parent;
        }
        return p;
    }
}

Node* RedBlackTree::predecessor(Node* x)
{   // largest node that is smaller than x
    if (x -> left != nil)
    {
        return maximum(x -> left);
    }
    else
    {
        auto p = x -> parent;
        while (p != nil && x != p -> right)
        {   // moving up the tree until x is a right child
            x = p;
            p = p -> parent;
        }
        return p;
    }
}

void RedBlackTree::insert(int k)
{
    Node* node = newNode();
    node -> key = k;
    insert(node);
}

void RedBlackTree::insert(Node* node)
{
    auto x = root();
    node -> left = nil;
    node -> right = nil;
    auto p = x -> parent;

    while (x != nil)
    {
        if (x -> key == node -> key) return;
        p = x;
        x = (x -> key > node -> key)
                ? x -> left
                : x -> right;
    }
    node -> parent = p;

    if (p == nil)
    {   // node is root: node must be both left and right child of nil
        p -> left = node;
        p -> right = node;
    }
    else
    {   // insert node as left/right according to key
        if (node -> key >= p -> key)
        {
            p -> right = node;
        }
        else
        {
            p -> left = node;
        }
    }
}

void RedBlackTree::remove(int key)
{
    remove(find(key));
}

void RedBlackTree::remove(Node* node)
{
    if (node == nil) return; // prevent removal of nil

    if (node -> left  == nil)
    {   // if node -> right is nil, it is still ideal.
        transplant(node, node -> right);
    }
    else if (node -> right == nil)
    {   // only left node exists
        transplant(node, node -> left);
    }
    else
    {   // having two children
        auto s = successor(node);
        if (s != node -> right)
        {   // make s the right chlid of node
            transplant(s, s -> right);  // replace s with its right child
            // make s the parent of node's right child
            s -> right = node -> right;
            s -> right -> parent = node;
        }
        transplant(node, s);
        // transfer node's left to s
        s -> left = node -> left;
        s -> left -> parent = s;
    }
    delete node;
}

void RedBlackTree::transplant(Node* u, Node* v)
{
    // TODO: using reference to simplify the code
    if (u == u -> parent -> left)
    {
        u -> parent -> left = v;
    }
    if (u == u -> parent -> right)
    {   // both could happen at the same time if u is root()
        u -> parent -> right = v;
    }
    v -> parent = u -> parent;
}

bool RedBlackTree::empty()
{
    return (nil -> left == nil);
}

Node* RedBlackTree::newNode()
{
    Node n = new Node();
    n -> left   = nil;
    n -> right  = nil;
    n -> parent = nil;
    n -> key    = 0;
    n -> red    = false;
}
