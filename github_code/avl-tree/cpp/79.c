//
// Created by 11570 on 2018/4/18.
//

//
// Created by 11570 on 2018/4/11.
//
#include <iostream>
#include "avltree.h"

//Node constructor and definition of NIL
Node nil(0,0);
Node * NIL=&nil;
Node::Node(int k)
:key(k),h(1),p(NIL),left(NIL),right(NIL)
{}
Node::Node(int k,int height)
:key(k),h(height),p(NIL),left(NIL),right(NIL)
{}


void TransPlant (Node * n1,Node * n2)//take n2 to replace the place of n1
{
    if(n2== NIL)
    {
        if(n1==n1->p->right)
            n1->p->right=n2;
        else if(n1==n1->p->left)
            n1->p->left=n2;
        return ;
    }
    if(n1->p== NIL)
        n1=n2;
    if(n1==n1->p->right)
        n1->p->right=n2;
    else if(n1==n1->p->left)
        n1->p->left=n2;
    n2->p=n1->p;
}
Node * AVLTree::Search (int k)
{
    Node * cur=root;
    while(cur->key!=k&&cur!= NIL)
    {
        if(cur->key<k)
            cur=cur->right;
        else cur=cur->left;
    }
    if(cur->key==k)
        return cur;
    else return NIL;
}
void AVLTree::InorderTreeWalk(Node * n)
{
    if(n== NIL)
        return ;
    InorderTreeWalk(n->left);
    std::cout<<n->key<<'('<<n->h<<')'<<' ';
    InorderTreeWalk(n->right);
}
Node * AVLTree::Minimum()
{
    if(root->left== NIL)
        return root;
    Node * cur=root;
    while(cur->left!= NIL)
        cur=cur->left;
    return cur;
}
Node * AVLTree::Maximum()
{
    if(root->right== NIL)
        return root;
    Node * cur=root;
    while(cur->right!= NIL)
        cur=cur->right;
    return cur;
}
Node * AVLTree::Predecessor(Node * n)
{
    if(n->left!= NIL)
    {
        return AVLTree(n->left).Maximum();
    }
    else if(n->p!= NIL)
        return n->p;
    else return NIL;
}
Node * AVLTree::Successor(Node *n)
{
    if(n->right!= NIL)
    {
        return AVLTree(n->right).Minimum();
    }
    else if(n->p!= NIL)
        return n->p;
    else return NIL;
}
Node * AVLTree::Insert(int k)
{
    Node * cur=root;
    Node * prev= NIL;
    while(cur!= NIL)
    {
        prev=cur;
        if(k<cur->key)
            cur=cur->left;
        else if(k>cur->key)
            cur=cur->right;
        else
        {
            std::cerr<<k<<" already in tree.\n";
            return NIL;
        }
    }
    Node * toInsert=new Node(k);
    toInsert->p=prev;
    if(k<prev->key)
        prev->left=toInsert;
    else
        prev->right=toInsert;
    InsertHeightFixup(toInsert);
    if(!IsAVL(root))
        Balance(toInsert);
}
bool AVLTree::Delete(int k)
{
    Node * toDelete=Search(k);
    if(toDelete== NIL)
    {
        std::cerr<<"Delete failed.\n";
        return false;
    }
    if(toDelete->left== NIL)
    {
        Node * fix_point=toDelete->p;//Where you should fix the height
        TransPlant(toDelete,toDelete->right);
        if(fix_point->right!=NIL)
        {
            InsertHeightFixup(fix_point->right);
            Balance(fix_point->right);
        }
        else if(fix_point->left!=NIL)
        {
            InsertHeightFixup(fix_point->left);
            Balance(fix_point->left);
        }
        else
        {
            fix_point->h=1;
            Balance(fix_point);
        }

    }
    else if(toDelete->right==NIL)
    {
        Node * fix_point=toDelete->p;
        TransPlant(toDelete,toDelete->left);
        if(fix_point->right!=NIL)
        {
            InsertHeightFixup(fix_point->right);
            Balance(fix_point->right);
        }
        else if(fix_point->left!=NIL)
        {
            InsertHeightFixup(fix_point->left);
            Balance(fix_point->right);
        }
        else
        {
            InsertHeightFixup(fix_point->left);
            Balance(fix_point);
        }
    }
    else
    {
        Node * toReplace=AVLTree(toDelete->right).Maximum();
        if(toReplace==toDelete->right)
        {
            toReplace->left=toDelete->left;
            toDelete->left->p=toReplace;
            TransPlant(toDelete,toReplace);
            InsertHeightFixup(toReplace->right);
            Balance(toReplace->right);
        }
        else
        {
            Node * fix_point1=toReplace->p;
            Node * fix_point2=toDelete->p;
            TransPlant(toReplace,toReplace->right);
            TransPlant(toDelete,toReplace);
            toReplace->left=toDelete->left;
            toReplace->right=toDelete->right;
            toDelete->right->p=toReplace;
            toDelete->left->p=toReplace;
            if(fix_point1->right!=NIL)
            {
                InsertHeightFixup(fix_point1->right);
                Balance(fix_point1->right);
            }
            else if(fix_point1->left!=NIL)
            {
                InsertHeightFixup(fix_point1->left);
                Balance(fix_point1->right);
            }
            else {
                fix_point1->h=1;
                Balance(fix_point1);
            }
            if(fix_point2->right!=NIL)
                InsertHeightFixup(fix_point2->right);
            else if(fix_point2->left!=NIL)
                InsertHeightFixup(fix_point2->left);
            else fix_point2->h=1;
        }
    }


}
//private method
void AVLTree::LeftRotate(Node * n)
{
    if(n==root)
        root=n->right;
    Node * y=n->right;
    n->right=y->left;
    y->left->p=n;
    y->p=n->p;
    y->left=n;
    if(n==n->p->right)
        n->p->right=y;
    else
        n->p->left=y;
    n->p=y;
    if(y->left->left!=NIL)
        InsertHeightFixup(y->left->left);
    else if(y->left->right!=NIL)
        InsertHeightFixup(y->left->right);
    else{
        y->left->h=1;
        InsertHeightFixup(y->left);
    }



}
void AVLTree::RightRotate(Node * n)
{
    if(n==root)
        root=n->left;
    Node * y=n->left;
    n->left=y->right;
    y->right->p=n;
    y->p=n->p;
    y->right=n;
    if(n==n->p->right)
        n->p->right=y;
    else
        n->p->left=y;
    n->p=y;
    if(y->right->left!=NIL)
        InsertHeightFixup(y->right->left);
    else if(y->right->right!=NIL)
        InsertHeightFixup(y->right->right);
    else{
        y->right->h=1;
        InsertHeightFixup(y->right);
    }

}

void AVLTree::Balance(Node * n)
{
    if(n->p==NIL)
        return;
    n=n->p;
    while(n->left->h-n->right->h<2&&n->left->h-n->right->h>-2&&n!=NIL)
        n=n->p;
    if(n==NIL)
        return;
    if(n->left->h-n->right->h==2)
    {
        Node * top=n->p;
        n=n->left;
        while((n->left->h-n->right->h)*(n->p->left->h-n->p->right->h)<0)
        {
            if(n->left->h>n->right->h)
                n=n->left;
            else n=n->right;
        }
        if(n->left==NIL&&n->right==NIL)
        {
            if(n->p==n->p->right)
            {
                n->p->right=n;
                n->p->left=NIL;

            }
            else
            {
                n->p->left=n;
                n->p->right=NIL;
            }
        }
        while(n!=top->left&&n!=top->right)
        {
            if(n==root)
                break;
            if(n->right->h>n->left->h)
                LeftRotate(n->p);
            else
                RightRotate(n->p);
        }
    }
    else if(n->right->h-n->left->h==2)
    {
        Node * top=n->p;
        n=n->right;
        while((n->left->h-n->right->h)*(n->p->left->h-n->p->right->h)<0)
        {
            if(n->left->h>n->right->h)
                n=n->left;
            else
                n=n->right;
        }
        while(n!=top->left&&n!=top->right)
        {
            if(n==root)
                break;
            if(n->right->h>=n->left->h)
                LeftRotate(n->p);
            else
                RightRotate(n->p);

        }
    }
}
/*void AVLTree::HeightPlus(Node * n)
{
    if(n==NIL)
        return;
    HeightPlus(n->left);
    n->h++;
    HeightPlus(n->right);

}
void AVLTree::HeightMinus(Node * n)
{
    if(n==NIL)
        return;
    HeightMinus(n->left);
    n->h--;
    HeightMinus(n->right);
}*/
void AVLTree::InsertHeightFixup(Node * n)//muti-functional!
{
    Node * up=n->p;

    while(up->left->h!=up->right->h&&up!=NIL)
    {
        if(up->left->h>up->right->h)
            up->h=up->left->h+1;
        else
            up->h=up->right->h+1;
        up=up->p;
    }
    if(up!=NIL)
        up->h=up->left->h+1;
}
bool AVLTree::IsAVL(Node * n)
{
    if(n==NIL)
        return true;
    return (IsAVL(n->left)&&IsAVL(n->right))&&((n->left->h-n->right->h<=1)&&(n->right->h-n->left->h<=1));
}

