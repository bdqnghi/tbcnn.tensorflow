#include "redblacktree.h"
#include <iostream>

using namespace std;


RedBlackTree::RedBlackTree()
{
    Nil=new node;
    Nil->color=black;
    Nil->left=0;
    Nil->right=0;
    Nil->parent=0;
    root=Nil;
    numberOfElements=0;
}

RedBlackTree::RedBlackTree(Data x)
{
    Nil=new node;
    root=new node;
    Nil->color=black;
    Nil->left=0;
    Nil->right=0;
    Nil->parent=0;
    root->left=Nil;
    root->right=Nil;
    root->parent=Nil;
    root->color=black;
    root->element=x;
    numberOfElements=1;
}

RedBlackTree::~RedBlackTree()
{
    del_RBtree(root);
    Nil=0;
    numberOfElements=0;
}

void RedBlackTree::del_RBtree(node *nd)
{
    if(Nil==nd)return;
    del_RBtree(nd->left);
    del_RBtree(nd->right);
    delete nd;
    nd=0;
}

void RedBlackTree::copy_RBtree(node *&newn,node *old, node *newNil, node *oldNil)
{
    if(old==oldNil)
    {
        newn=newNil;
        return;
    }
    newn=new node;
    newn->element=old->element;
    copy_RBtree(newn->left,old->left, newNil, oldNil);
    copy_RBtree(newn->right,old->right, newNil, oldNil);
}

RedBlackTree::RedBlackTree(const RedBlackTree& other)
{
    copy_RBtree(root,other.root,Nil, other.Nil);
}

RedBlackTree& RedBlackTree::operator = (const RedBlackTree &t)
{

    if(this==&t) return *this;
    del_RBtree(root);
    copy_RBtree(root, t.root, Nil, t.Nil);
    return *this;
}

void RedBlackTree::left_Rotate(node *x)
{
    if(x->right!=Nil)
    {
        node *y=x->right;
        x->right=y->left;
        if(y->left!=Nil)
            y->left->parent=x;
        y->parent=x->parent;
        if(x->parent==Nil)
            root=y;
        else
        {
            if(x==x->parent->left)
                x->parent->left=y;
            else
                x->parent->right=y;
        }
        y->left=x;
        if(x!=Nil)
            x->parent=y;
        y=0;
    }
}

void RedBlackTree::right_Rotate(node *x)
{
    if(x->left!=Nil)
    {
        node *y=x->left;
        x->left=y->right;
        if(y->right!=Nil)
            y->right->parent=x;
        if(y!=Nil)
            y->parent=x->parent;
        if(x->parent==Nil)
            root=y;
        else
        {
            if(x==x->parent->left)
                x->parent->left=y;
            else
                x->parent->right=y;
        }
        y->right=x;
        if(x!=Nil)
            x->parent=y;
        y=0;
    }
}

void RedBlackTree::insertFixup(node *z)
{
    node *y=Nil;
    while(z->parent->color==red)
    {
        if(z->parent==z->parent->parent->left)
        {
            y=z->parent->parent->right;
            if(y->color==red)
            {
                y->color=black;
                z->parent->color=black;
                z->parent->parent->color=red;
                z=z->parent->parent;
            }
            else
            {
                if(z==z->parent->right)
                {
                    z=z->parent;
                    left_Rotate(z);
                }
                z->parent->color=black;
                z->parent->parent->color=red;
                right_Rotate(z->parent->parent);
            }
        }
        else
        {
            y=z->parent->parent->left;
            if(y->color==red)
            {
                y->color=black;
                z->parent->color=black;
                z->parent->parent->color=red;
                z=z->parent->parent;
            }
            else
            {
                if(z==z->parent->left)
                {
                    z=z->parent;
                    right_Rotate(z);
                }
                z->parent->color=black;
                z->parent->parent->color=red;
                left_Rotate(z->parent->parent);
            }
        }
    }
    root->color=black;
    y=0;
}

void RedBlackTree::insertElement(node *y, node *nd, Data d)
{
    if(!isFinded(d))
    {
        if(nd==Nil)
        {
            nd=new node;
            nd->element=d;
            nd->color=red;
            nd->left=nd->right=Nil;
            nd->parent=y;
            if(nd->parent==Nil)
            {
                root=nd;
            }
            else
            {
                if(nd->element<y->element)
                    y->left=nd;
                if(nd->element>y->element)
                    y->right=nd;
            }
            insertFixup(nd);
            ++numberOfElements;
            return;
        }
        if(d<=nd->element) insertElement(nd, nd->left, d);
        else insertElement(nd, nd->right, d);
    }
}

void RedBlackTree::insertElement(Data d)
{
    node *y=Nil;
    insertElement(y, root, d);
    y=0;
}

RedBlackTree::node *RedBlackTree::findElement(node *t, Data x)
{
    if(t==Nil) return Nil;
    if(x<t->element) return findElement(t->left,x);
    if(x>t->element) return findElement(t->right,x);
    return t;
}

bool RedBlackTree::isFinded(Data x)
{
    if(findElement(root, x)==Nil)
        return false;
    else
        return true;
}

Data RedBlackTree::findMinimal()
{
    node *y=root;
    if(y==Nil)
        throw minimumE();
    else
    {
        while(y->left!=Nil)
            y=y->left;
        return y->element;
    }
}

RedBlackTree RedBlackTree::operator +(RedBlackTree &x)
{
    RedBlackTree z=x;
    conjunction(root, z);
    return z;
}

void RedBlackTree::conjunction(node *p, RedBlackTree &x)
{
    if(p!=Nil)
    {
        conjunction(p->left, x);
        if(!x.isFinded(p->element))
            x.insertElement(p->element);
        conjunction(p->right, x);
    }
}


RedBlackTree RedBlackTree::operator -(RedBlackTree &x)
{
    RedBlackTree z;
    difference(root, z, x);
    return z;
}

void RedBlackTree::difference(node *p, RedBlackTree &z, RedBlackTree x)
{
    if(p!=Nil)
    {
        difference(p->left, z, x);
        if(!x.isFinded(p->element))
            z.insertElement(p->element);
        difference(p->right, z, x);
    }
}


void RedBlackTree::disjunction(node *p, RedBlackTree &z, RedBlackTree x)
{
    if(p!=Nil)
    {
        disjunction(p->left, z, x);
        if(x.isFinded(p->element))
            z.insertElement(p->element);
        disjunction(p->right, z, x);
    }
}

RedBlackTree RedBlackTree::disjunction(RedBlackTree x)
{
    RedBlackTree z;
    disjunction(root, z, x);
    return z;
}


void RedBlackTree::output(node* nd)
{
    if(nd!=Nil)
    {
        output(nd->left);
        cout << nd->element << ' ';
        output(nd->right);
    }
}

void RedBlackTree::output()
{
    output(root);
}
