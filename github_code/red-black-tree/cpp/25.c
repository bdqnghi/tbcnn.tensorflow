//
//  red_black_tree.cpp
//  ADS Project
//
//  Created by Abhinav Rathi on 3/22/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

#include <iostream>

#include "red_black_tree.hpp"           // // Including red_black_tree Header File

using namespace std;

//Function Definitions of Red-Black-Tree Follows:

/*
 Constructor : Initializes the root to NULL
*/
red_black_tree::red_black_tree(){
    root=NULL;
};

/*
 Insert_from_sorted_list : Tree Initialization
    Calls to Function sorted_insert with arrays "id" and "count" to build the tree
    "start" & "end" indicate the length of list to be put in the tree
    "height" represnts the maximum height of the tree
*/
void red_black_tree::insert_from_sorted_list(int id[],int count[],int start,int end,int height){
    root=sorted_insert(id,count,start,end,height);
    
    // Explicitly making root black (since for 1 node tree root would be the last level and hence will be colored red by above function
    if(root)
        root->color='b';
};

/*
 Sorted_insert : Recursice function to build tree and return its root
*/
node* red_black_tree::sorted_insert(int i[],int c[],int s,int e,int h){
    node *t=NULL;
    if(s<=e){
        int m=(s+e)/2;                      // Find middle index of list
        t=new node(i[m],c[m]);              // Make root with the elements of middle index (Color->black)
        if(h==1)                            // If at last level, change color to red
            t->color='r';
        t->l=sorted_insert(i,c,s,m-1,h-1);  // Recursive call with left part of list as left subtree
        if(t->l)                            // If left child exists, make "t" its parent
            t->l->p=t;
        t->r=sorted_insert(i,c,m+1,e,h-1);  // Recursive call with right part of list as right subtree
        if(t->r)                            // If right child exists, make "t" its parent
            t->r->p=t;
    }
    return t;
};

/*
 User Command : Increase count of "id" by "m", if present else insert
*/
int red_black_tree::increase(int id,int m){
    node *t=search(id);             // Search for node with given id
    int count=m;                    // Initialize temporary variable count with m
    if(t){                          // If node found
        t->count+=m;                // Increase it's count by m
        count=t->count;             // Save this value in variable count
    }
    else{                           // Else if node is not found
        node *temp=new node(id,m);  // Create a node "temp" with "id" and "m" values
        temp->color='r';            // Make it's color red
        insert(temp);               // Use function "insert" to insert into red-black-tree
    }
    return count;                   // Return the value of variable count
};

/*
 Insert : Insert single node "t" into Red-Black-Tree with "root"
 All cases discussed are exactly what was discussed in class. The appropriate reference are given.
*/
void red_black_tree::insert(node *t){
    if(!root){                      // If tree is empty, make node "t" the root and color it black
        root=t;
        root->color='b';
    }
    else{
        
        // Do a routine Balanced Binary Search Tree Insertion
        node *next=root;
        node *prev;
        do{                     // Traversing to appropriate position iteratively by keeping track of "prev"
            prev=next;
            if(next->ID>t->ID)
                next=next->l;
            else
                next=next->r;
        }while(next);
        if(prev->ID>t->ID)      // Inserting node as left or right child of "prev" by comparing the id
            prev->l=t;
        else
            prev->r=t;
        t->p=prev;              // Make "prev" the parent of node "t"
        
        // Now we see if any discrepencies arise due to node insertion pertaining to any of the properties of red-black-tree
        // Since we are inserting a red node, the problem arises only if the parent is also red, else we are done
        if(t->p->color=='r'){
            char c;                 // c will hold color of uncle
            node *parent,*gparent;  // defining parent & grand-parent of t as "parent" & "gparent"
            parent=t->p;
            gparent=parent->p;
            if(gparent->l==parent){ // If-else finds color of uncle (color is black if uncle doesn't exist)
                if(gparent->r!=NULL)
                    c=gparent->r->color;
                else
                    c='b';
            }
            else{
                if(gparent->l!=NULL)
                    c=gparent->l->color;
                else
                    c='b';
            }
            
            /* Here we will use classification XYz as in lecture slides
               X : relation between parent & gparent
               Y : relation between t and gparent
               z : color of uncle of z
            */
            
            
            /*
             Case 1 of XYr : i.e. Color of Uncle is Red with XY being any of LL, LR, RL, or RR
             We will do Color Flips by inverting colors of parent, uncle and gparent, and continuing the discrepencies upwards until we get some other case, or the red-black-tree property is satisfied.
            */
            while(c=='r'&&parent&&gparent){
                parent->color='b';      // Coloring parent black
                gparent->color='r';     // Coloring gparent black
                if(gparent->l==parent&&gparent->r!=NULL)    // Coloring uncle black, if exists
                    gparent->r->color='b';
                else if(gparent->r==parent&&gparent->l!=NULL)
                    gparent->l->color='b';
                root->color='b';
                
                // Checking if XYr discrepency still occurs, we reset t, parent, gparent & c values and continue
                if(gparent->p&&gparent->p->color=='r'){
                    t=gparent;
                    parent=t->p;
                    gparent=parent->p;
                    if(gparent->l==parent){
                        if(gparent->r!=NULL)
                            c=gparent->r->color;
                        else
                            c='b';
                    }
                    else{
                        if(gparent->l!=NULL)
                            c=gparent->l->color;
                        else
                            c='b';
                    }
                }
                else    // Else the discrepency has been satisfied (setting gparent NULL to exit from this loop and prevent entering all further cases
                    gparent=NULL;
            }
            
            /*
             Case 2 of XYb : i.e. Color of Uncle is Black with XY being any of LL, LR, RL, or RR
            */
            if(gparent&&c=='b'){
                /*
                 Case 2.1 of LLb : i.e. Color of Uncle is Black with XY being LL
                 We will do a LL Rotation and flip the colors of "parent" & "gparent"
                */
                if(parent->l==t&&gparent->l==parent){
                    if(gparent->p){                 // Handling Case of gparent being root or not
                        if(gparent->p->l==gparent)
                            gparent->p->l=parent;
                        else
                            gparent->p->r=parent;
                        parent->p=gparent->p;
                    }
                    else{
                        root=parent;
                        parent->p=NULL;
                    }
                    gparent->l=parent->r;
                    if(parent->r)
                        parent->r->p=gparent;
                    gparent->p=parent;
                    parent->r=gparent;
                    parent->color='b';
                    gparent->color='r';
                }
                /*
                 Case 2.2 of RRb : i.e. Color of Uncle is Black with XY being RR
                 We will do a RR Rotation and flip the colors of "parent" & "gparent"
                */
                else if(parent->r==t&&gparent->r==parent){
                    if(gparent->p){                 // Handling Case of gparent being root or not
                        if(gparent->p->l==gparent)
                            gparent->p->l=parent;
                        else
                            gparent->p->r=parent;
                        parent->p=gparent->p;
                    }
                    else{
                        root=parent;
                        parent->p=NULL;
                    }
                    gparent->r=parent->l;
                    if(parent->l)
                        parent->l->p=gparent;
                    gparent->p=parent;
                    parent->l=gparent;
                    parent->color='b';
                    gparent->color='r';
                }
                /*
                 Case 2.3 of LRb : i.e. Color of Uncle is Black with XY being LR
                 We will do a LR Rotation and flip the colors of "t" & "gparent"
                */
                else if(parent->r==t&&gparent->l==parent){
                    if(gparent->p){                 // Handling Case of gparent being root or not
                        if(gparent->p->l==gparent)
                            gparent->p->l=t;
                        else
                            gparent->p->r=t;
                        t->p=gparent->p;
                    }
                    else{
                        root=t;
                        t->p=NULL;
                    }
                    gparent->l=t->r;
                    if(t->r)
                        t->r->p=gparent;
                    gparent->p=t;
                    t->r=gparent;
                    parent->r=t->l;
                    if(t->l)
                        t->l->p=parent;
                    parent->p=t;
                    t->l=parent;
                    t->color='b';
                    gparent->color='r';
                }
                /*
                 Case 2.4 of RLb : i.e. Color of Uncle is Black with XY being RL
                 We will do a RL Rotation and flip the colors of "t" & "gparent"
                */
                else{
                    if(gparent->p){                 // Handling Case of gparent being root or not
                        if(gparent->p->l==gparent)
                            gparent->p->l=t;
                        else
                            gparent->p->r=t;
                        t->p=gparent->p;
                    }
                    else{
                        root=t;
                        t->p=NULL;
                    }
                    gparent->r=t->l;
                    if(t->l)
                        t->l->p=gparent;
                    gparent->p=t;
                    t->l=gparent;
                    parent->l=t->r;
                    if(t->r)
                        t->r->p=parent;
                    parent->p=t;
                    t->r=parent;
                    t->color='b';
                    gparent->color='r';
                }
            } // End of Case 2
        } // End of Case of any discrepencies
    } // End of Case when root was not empty, and "t" as inserted in a subtree
};

/*
 User Command : reduce count of "id" by "m", if present (removes node if count becomes 0 or less)
*/
int red_black_tree::reduce(int id,int m){
    node *t=search(id);             // Search for node with given id
    int count=0;                    // Increase temporary variable count with 0
    if(t){                          // If node found
        if(t->count>m){             // Decrease it's count by m if "t->count" is greater than m
            t->count-=m;
            count=t->count;         // Save this value in variable count
        }
        else                        // Else remove the node "t"
            remove(t);
    }
    return count;                   // Return the value of variable count
};

/*
 Remove : Deletes node "t" from Red-Black-Tree with "root"
 All cases discussed are exactly what was discussed in class. The appropriate reference are given.
*/
void red_black_tree::remove(node *t){
    if(!t)                          // Dummy Check if NULL node delete requested
        return;
    
    // Do a routine Balanced Binary Search Tree Deletion i.e. if the node to be deleted has 2 children swap it by its successor and delete the successor node (which will have 0 or 1 child)
    if(t->l&&t->r){
        node *n=next(t);
        int x,y;
        x=n->ID;
        y=n->count;
        n->ID=t->ID;
        n->count=t->count;
        t->ID=x;
        t->count=y;
        t=n;
    }
    
    /*
     Case 0 : When root is to be deleted
     Note it will have only one child from above swaps
     We just advance the root, to its subtree if any and make it's color black
     Now we are done.
    */
    if(t==root){
        if(root->l)
            root=root->l;
        else
            root=root->r;
        root->p=NULL;
        if(root)
            root->color='b';
        return;
    }
    
    /* 
     Now Deleting the Node (if it wasn't the root). Here we also declare the following variables:
        parent  : parent of t
        y       : subtree of t, if any
        s       : sibling of t, if any
    */
    node *parent,*y,*s;
    parent=t->p;
    if(parent->l==t)
        s=parent->r;
    else
        s=parent->l;
    if(t->l){               // Deleting t if it has left child subtree
        if(parent->l==t)
            parent->l=t->l;
        else
            parent->r=t->l;
        y=t->l;
        y->p=parent;
    }
    else if(t->r){          // Deleting t if it has right child subtree
        if(parent->l==t)
            parent->l=t->r;
        else
            parent->r=t->r;
        y=t->r;
        y->p=parent;
    }
    else{                   // Deleting t if it a leaf
        if(parent->l==t)
            parent->l=NULL;
        else
            parent->r=NULL;
        y=NULL;
    }
    
    // Now we see if any discrepencies arise due to node deletion pertaining to any of the properties of red-black-tree, the problem arises only if black node is deleted, else we are done
    if(t->color=='r')
        return;
    
    /*
     Case 1 : When y (deleted node's child) is red,  we just make it black and we are done
    */
    if(t->color=='b'&&y&&y->color=='r'){
        y->color='b';
        return;
    }
    
    /* Here we will use classification Xcn as in lecture slides
     X : relation between parent & y
     c : color of sibling s (assumend black if NULL)
     n : number of red children of s
    */
    
    // Computing n
    int n=0;
    if(s->l&&s->l->color=='r')
        ++n;
    if(s->r&&s->r->color=='r')
        ++n;
    
    /*
     Case 2.1 : Xb0 and parent is black
     We make s black and continue the discrepancy upwards
    */
    while(s->color=='b'&&n==0&&parent->color=='b'){
        s->color='r';
        
        // Resetting pointers y, parent & s and the counter n
        y=parent;
        if(y->p)
            parent=y->p;
        else
            return;
        if(parent->l==y)
            s=parent->r;
        else
            s=parent->l;
        if(!s)
            return;
        n=0;
        if(s->l&&s->l->color=='r')
            ++n;
        if(s->r&&s->r->color=='r')
            ++n;
    }
    
    /*
     Case 2.2 : Xb0 and parent is red
     We swap colors of s and parent and we are done
    */
    if(s->color=='b'&&n==0&&parent->color=='r'){
        parent->color='b';
        s->color='r';
        return;
    }
    
    /*
     Case 3 : Xb1 & Xb2
        Case 3.1 : If X is L, n is 1 and s's right child is red
        Case 3.2 : If X is R, n is 1 and s's left child is red
        Case 3.3 : If X is L, n is 1 and s's left child is red or X is L and n is 2
        Case 3.4 : If X is R, n is 1 and s's right child is red or X is R and n is 2
    */
    if(s->color=='b'&&n!=0){
        if(s->p->l==s){
            /* 
             Case 3.4 : LR rotation. Let s->right child be w.
             Make w's right child be parent's left child and w's left child s's right child
             Make w->r=parent & w->l=s
             Make w's color equal to that of parent & parent's color to be black
             And we are done.
            */
            if(s->r&&s->r->color=='r'){
                node *w=s->r;
                if(parent->p){
                    if(parent->p->l==parent)
                        parent->p->l=w;
                    else
                        parent->p->r=w;
                    w->p=parent->p;
                }
                else{
                    root=w;
                    w->p=NULL;
                }
                w->color=parent->color;
                parent->color='b';
                parent->l=w->r;
                if(w->r)
                    w->r->p=parent;
                w->r=parent;
                parent->p=w;
                s->r=w->l;
                if(w->l)
                    w->l->p=s;
                w->l=s;
                s->p=w;
            }
            /*
             Case 3.2 : LL rotation.
             We'll make s's color equal to parent's color & color parent & s's left child to black.
             And we are done.
            */
            else{
                if(parent->p){
                    if(parent->p->l==parent)
                        parent->p->l=s;
                    else
                        parent->p->r=s;
                    s->p=parent->p;
                }
                else{
                    root=s;
                    s->p=NULL;
                }
                parent->l=s->r;
                if(s->r)
                    s->r->p=parent;
                parent->p=s;
                s->r=parent;
                s->color=parent->color;
                parent->color='b';
                s->l->color='b';
            }
        }
        else{
            /*
             Case 3.3 : RL rotation. Let s->left child be w.
             Make w's left child be parent's right child and w's right child s's left child
             Make w->l=parent & w->r=s
             Make w's color equal to that of parent & parent's color to be black
             And we are done.
            */
            if(s->l&&s->l->color=='r'){
                node *w=s->l;
                if(parent->p){
                    if(parent->p->l==parent)
                        parent->p->l=w;
                    else
                        parent->p->r=w;
                    w->p=parent->p;
                }
                else{
                    root=w;
                    w->p=NULL;
                }
                w->color=parent->color;
                parent->color='b';
                parent->r=w->l;
                if(w->l)
                    w->l->p=parent;
                w->l=parent;
                parent->p=w;
                s->l=w->r;
                if(w->r)
                    w->r->p=s;
                w->r=s;
                s->p=w;
            }
            /*
             Case 3.1 : RR rotation.
             We'll make s's color equal to parent's color & color parent & s's right child to black.
             And we are done.
            */
            else{
                if(parent->p){
                    if(parent->p->l==parent)
                        parent->p->l=s;
                    else
                        parent->p->r=s;
                    s->p=parent->p;
                }
                else{
                    root=s;
                    s->p=NULL;
                }
                parent->r=s->l;
                if(s->l)
                    s->l->p=parent;
                parent->p=s;
                s->l=parent;
                s->color=parent->color;
                parent->color='b';
                s->l->color='b';
            }
        }
        return;
    }
    
    // Following cases for color of s to be red
    
    /* Here we will use classification Xr(n) as in lecture slides
     X : relation between parent & y
     r : color of sibling s which is red always
     n : number of red children of s's right child (say w)
    */
    node *w;
    if(parent->l==s)
        w=s->r;
    else
        w=s->l;
    
    // Computing no. of red children of w
    n=0;
    if(w->l&&w->l->color=='r')
        ++n;
    if(w->r&&w->r->color=='r')
        ++n;
    
    /*
     Case 4 : Xr(0)
    */
    if(n==0){
        /*
         Case 4.1 : Rr(0)
         We do a LL Rotation.
         Color s as black, and parent's new left child (s's old right child) as red if it exists.
         And we are done.
        */
        if(parent->l==s){
            if(parent->p){
                if(parent->p->l==parent)
                    parent->p->l=s;
                else
                    parent->p->r=s;
                s->p=parent->p;
            }
            else{
                root=s;
                s->p=NULL;
            }
            parent->l=s->r;
            if(s->r)
                s->r->p=parent;
            parent->p=s;
            s->r=parent;
            s->color='b';
            if(parent->l)
                parent->l->color='r';
        }
        /*
         Case 4.1 : Lr(0)
         We do a RR Rotation.
         Color s as black, and parent's new right child (s's old left child) as red if it exists.
         And we are done.
        */
        else if(parent->r==s){
            if(parent->p){
                if(parent->p->l==parent)
                    parent->p->l=s;
                else
                    parent->p->r=s;
                s->p=parent->p;
            }
            else{
                root=s;
                s->p=NULL;
            }
            parent->r=s->l;
            if(s->l)
                s->l->p=parent;
            parent->p=s;
            s->l=parent;
            s->color='b';
            if(parent->r)
                parent->r->color='r';
        }
        return;
    }
    /*
     Case 5 : Xr(1) & Xr(2)
     Case 5.1 : If X is L, n is 1 and w's right child is red
     Case 5.2 : If X is R, n is 1 and w's left child is red
     Case 5.3 : If X is L, n is 1 and w's left child is red or X is L and n is 2
     Case 5.4 : If X is R, n is 1 and w's right child is red or X is R and n is 2
    */
    if(n==1){
        /*
         Case 5.2 : Rr(1) with w->r as black
         We do a LR Rotation.
         Color s's new right child (w's old left child) as black if it exists.
         And we are done.
        */
        if(parent->l==s&&(!w->r||w->r->color=='b')){
            if(parent->p){
                if(parent->p->l==parent)
                    parent->p->l=w;
                else
                    parent->p->r=w;
                w->p=parent->p;
            }
            else{
                root=w;
                w->p=NULL;
            }
            parent->l=w->r;
            if(w->r)
                w->r->p=parent;
            w->r=parent;
            parent->p=w;
            s->r=w->l;
            if(w->l){
                w->l->p=s;
                w->l->color='b';
            }
            w->l=s;
            s->p=w;
        }
        /*
         Case 5.1 : Lr(1) with w->l as black
         We do a RL Rotation.
         Color s's new left child (w's old right child) as black if it exists.
         And we are done.
        */
        else if(parent->r==s&&(!w->l||w->l->color=='b')){
            if(parent->p){
                if(parent->p->l==parent)
                    parent->p->l=w;
                else
                    parent->p->r=w;
                w->p=parent->p;
            }
            else{
                root=w;
                w->p=NULL;
            }
            parent->r=w->l;
            if(w->l)
                w->l->p=parent;
            w->l=parent;
            parent->p=w;
            s->l=w->r;
            if(w->r){
                w->r->p=s;
                w->r->color='b';
            }
            w->r=s;
            s->p=w;
        }
        return;
    }
    
    /*
     Case 5.4 : Rr(1) with w->r as red or Rr(2)
     We do a Rotation. Let w's right child be x. We make x as root, x->r to be parent & x->l to be s.
     And x's left child will become w's right child & x's right child will become parent's left child.
     And we are done.
    */
    if(parent->l==s&&(!w->r||w->r->color=='r')){
        node *x=w->r;
        if(parent->p){
            if(parent->p->l==parent)
                parent->p->l=x;
            else
                parent->p->r=x;
            x->p=parent->p;
        }
        else{
            root=x;
            x->p=NULL;
        }
        w->r=x->l;
        if(x->l)
            x->l->p=w;
        parent->l=x->r;
        if(x->r)
            w->r->r->p=parent;
        x->l=s;
        s->p=x;
        x->r=parent;
        parent->p=x;
    }
    /*
     Case 5.3 : Lr(1) with w->l as red or Rr(2)
     We do a Rotation. Let w's left child be x. We make x as root, x->l to be parent & x->r to be s.
     And x's right child will become w's left child & x's left child will become parent's right child.
     And we are done.
    */
    else if(parent->r==s&&(!w->l||w->l->color=='r')){
        node *x=w->l;
        if(parent->p){
            if(parent->p->l==parent)
                parent->p->l=x;
            else
                parent->p->r=x;
            x->p=parent->p;
        }
        else{
            root=x;
            x->p=NULL;
        }
        w->l=x->r;
        if(x->r)
            x->r->p=w;
        parent->r=x->l;
        if(x->l)
            x->l->p=parent;
        x->r=s;
        s->p=x;
        x->l=parent;
        parent->p=x;
    }
};

/*
 User Command : count of "id", if present we return thr count else we return 0
*/
int red_black_tree::count(int id){
    node *t=search(id);         // Search returns node if "id" found else NULL
    if(t)                       // If node found, return its count
        return t->count;
    return 0;                   // 0 returned only when node isn't found
};

/*
 User Command : inrange between "id1" & "id2", if present we all counts between these two id's (inclusive)
*/
int red_black_tree::inrange(int id1,int id2){
    return inrange_recursive(root,id1,id2);     // Accomplished by inrange_recursive function
};

/*
 inrange_recursive : Recursice function to sum up all counts between "i1" and "i2"
*/
int red_black_tree::inrange_recursive(node *t,int i1,int i2){
    int sum=0;                  // Initialize local variable sum to 0
    if(t){
        if(t->ID>i1)            // Recurse left if t's ID is more than "i1"
            sum+=inrange_recursive(t->l,i1,i2);
        if(t->ID>=i1&&t->ID<=i2)// Add count of t to sum, if t's ID is within the range of id1 "i1" and "i2"
            sum+=t->count;
        if(t->ID<i2)            // Recurse right if t's ID is more than "i1"
            sum+=inrange_recursive(t->r,i1,i2);
    }
    return sum;
};

/*
 search : Search for "id" in Red-Black-Tree
*/
node* red_black_tree::search(int id){
    if(root){
        node *t=root;
        do{
            if(t->ID==id)           // Return t if id found
                return t;
            if(t->ID>id&&t->l)      // Traverse iteratively in left subtree if t->ID is greater than id
                t=t->l;
            else if(t->ID>id)       // Break if rightmost child reached and id not found
                break;
            else if(t->ID<id&&t->r) // Traverse iteratively in right subtree if t->ID is less than id
                t=t->r;
            else if(t->ID<id)       // Break if leftmost child reached and id not found
                break;
        }while(t);
    }
    return NULL;                    // Return NULL if id not found
};

/*
 search : Search next of "id", given "id" is not present in Tree
*/
node* red_black_tree::search_next(int id){
    node *t=root;
    if(root){
        do{
            if(t->ID>id&&t->l)      // Traverse iteratively in left subtree if t->ID is greater than id
                t=t->l;
            else if(t->ID>=id)       // Break if rightmost child reached
                break;
            else if(t->ID<id&&t->r) // Traverse iteratively in right subtree if t->ID is less than id
                t=t->r;
            else if(t->ID<=id)       // Break if leftmost child reached
                break;
        }while(t);
    }
    if(t&&t->ID<id)                 // If current t'ID is less than id, we just call next of t and return it
        t=next(t);
    if(t->ID==id)
        t=NULL;
    return t;
};

/*
 search : Search previous of "id", given "id" is not present in Tree
*/
node* red_black_tree::search_previous(int id){
    node *t=root;
    if(root){
        do{
            if(t->ID>id&&t->l)      // Traverse iteratively in left subtree if t->ID is greater than id
                t=t->l;
            else if(t->ID>=id)       // Break if rightmost child reached
                break;
            else if(t->ID<id&&t->r) // Traverse iteratively in right subtree if t->ID is less than id
                t=t->r;
            else if(t->ID<=id)       // Break if leftmost child reached
                break;
        }while(t);
    }
    if(t&&t->ID>id)                 // If current t'ID is more than id, we just call prev of t and return it
        t=previous(t);
    if(t->ID==id)
        t=NULL;
    return t;
};

/*
 Function returns root of the red-black-tree
 */
node* red_black_tree::getroot(){
    return root;
};

/*
 User Command : next of node t, return NULL if t is righmost leaf child
*/
node* red_black_tree::next(node *t){
    if(t&&t->r!=NULL){              // Case when t has right child
        t=t->r;                     // next is right child's leftmost child (via loop)
        while(t->l!=NULL)
            t=t->l;
        return t;
    }
    else if(t){                     // Case when t doesn't has right child
        while(t->p&&t->p->r==t)     // next is parent until parent is left child of some other node, else 0 0
            t=t->p;
        if(t->p)
            return t->p;
    }
    return NULL;
};

/*
 User Command : previous of node t, return NULL if t is leftmost leaf child
*/
node* red_black_tree::previous(node *t){
    if(t&&t->l!=NULL){         // Case when t has right child
        t=t->l;                // previous is left child's rightmost child (via loop)
        while(t->r!=NULL)
            t=t->r;
        return t;
    }
    else if(t){                // Case when t doesn't has left child
        while(t->p&&t->p->l==t)// previous is parent until parent is right child of some other node, else 0 0
            t=t->p;
        if(t->p)
            return t->p;
    }
    return NULL;
};

//Extra Functions Implimented

/*
 Function displays the red-black-tree as a stair-case (also lists count, color, parent and children)
*/
void red_black_tree::display(node *t,int n,char c){
    if(!t)
        return;
    for(int i=0;i<n;++i)
        cout<<".";
    cout<<t->ID<<"("<<c<<","<<t->count<<","<<t->color<<") has";
    if(t->p)
        cout<<" "<<t->p->ID<<" as parent ";
    if(t->l)
        cout<<" "<<t->l->ID<<" as left child ";
    if(t->r)
        cout<<" "<<t->r->ID<<" as right child ";
    cout<<"\n";
    
    display(t->l,n+1,'L');
    display(t->r,n+1,'R');
};

/*
 Function calculates maximum height of any binary tree
*/
int red_black_tree::max_height(node *t){
    int h=0;
    if(t){
        h=1+max(max_height(t->l),max_height(t->r));
    }
    return h;
};

/*
 Function colors a BBST according to red-black tree properties, given its maximum height h
*/
void red_black_tree::color(node *t,int h){
    if(t){
        if(h==1)
            t->color='r';
        else
            t->color='b';
        color(t->l,h-1);
        color(t->r,h-1);
    }
};
