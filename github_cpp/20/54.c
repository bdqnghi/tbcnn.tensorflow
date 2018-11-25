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
        {   
            if (x -> left == nil)
            {   
                prev = x -> left;
            }
            else
            {
                prev = x;
                x = x -> left;
            }
        }
        else if (prev == x -> left)
        {   
            cout << x -> key << " ";
            if (x -> right == nil)
            {  
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
        {   
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
{   
    while (root -> left != nil)
    {
        root = root -> left;
    }
    return root;
}

Node* RedBlackTree::maximum(Node* root)
{   
    while (root -> right != nil)
    {
        root = root -> right;
    }
    return root;
}

Node* RedBlackTree::successor(Node* x)
{  
    if (x -> right != nil)
    {   
        return minimum(x -> right);
    }
    else
    {   
        auto p = x -> parent;
        while (p != nil && x != p -> left)
        {   
            x = p;
            p = p -> parent;
        }
        return p;
    }
}

Node* RedBlackTree::predecessor(Node* x)
{   
    if (x -> left != nil)
    {
        return maximum(x -> left);
    }
    else
    {
        auto p = x -> parent;
        while (p != nil && x != p -> right)
        {   
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
    {   
        p -> left = node;
        p -> right = node;
    }
    else
    {   
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
    if (node == nil) return; 

    if (node -> left  == nil)
    {   
        transplant(node, node -> right);
    }
    else if (node -> right == nil)
    {   
        transplant(node, node -> left);
    }
    else
    {   
        auto s = successor(node);
        if (s != node -> right)
        {   
            transplant(s, s -> right);  
            
            s -> right = node -> right;
            s -> right -> parent = node;
        }
        transplant(node, s);
        
        s -> left = node -> left;
        s -> left -> parent = s;
    }
    delete node;
}

void RedBlackTree::transplant(Node* u, Node* v)
{
    
    if (u == u -> parent -> left)
    {
        u -> parent -> left = v;
    }
    if (u == u -> parent -> right)
    {   
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
