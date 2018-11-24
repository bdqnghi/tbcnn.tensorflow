//
//  main.cpp
//  Alg_Project2-1
//
//  Created by D&F on 10/11/13.
//  Copyright (c) 2013 D&F. All rights reserved.
//

#include <iostream>
#define KeyType char

using namespace std;


//template <typename KeyType>                          // create a template

//define a class of B-Tree Node: BTNode
class BTNode
{
    int t;                          //minimum degree
    KeyType *key;                      //keys Array
    int n;                          //key number
    BTNode **C;                     //array of child pointers
    bool leaf;                      //whether node is leaf or not, true: leaf, false: not
public:
    BTNode(int t1, bool leaf1);     //Constructor of B-tree node
    
    void BTree_Insert_Notfull(KeyType k);
    
    void BTree_Split_Child(int i, BTNode *y);
    
    void traverse();
    
    BTNode *BTSearch(KeyType k, int index);         // k is keyword, and index is child index
    
    int findKey(KeyType k);
    
    void fill(int index);
    
    void merge(int index);
    
    void rmFromleaf(int index);
    
    void rmFromNonleaf(int index);
    
    int getPre(int index);
    int getSuc(int index);
    
    void brFromPrev(int index);
    
    void brFromNext (int index);
    
    void removeKey(KeyType k);
    
    
    
friend class BTree;
    
};

//A friend class BTree
class BTree
{
    BTNode *root;
    int t;
public:
    BTree(int t1){ root =NULL; t=t1;}       //Initialize a B-tree
    
    void traverse()
    {
        if (root !=NULL) root->traverse();
    }
    
    BTNode *BTSearch(KeyType k, int index)
    {
        if (root !=NULL) return  root->BTSearch(k, index);
        else return NULL;
    }
    
    void Insert(KeyType k);
    
    void Delete(KeyType k);                   //delete keyword k
};

// Construct the BTNode class
BTNode::BTNode(int t1, bool leaf1)
{
    t=t1;
    leaf=leaf1;
    key= new KeyType [2*t-1];      //allocate memory for key array
    C=new BTNode * [2*t];
    n=0;                        //initialized key number is 0
}

void BTNode::traverse()         //a recursion process
{
    int i;
    for (i=0; i<n;i++ ) {
        if (leaf == false)         //non leaf nodes,keeping on traversing
            C[i]->traverse();
        cout<< "  "<< key[i]<< '\t';
    }
    if(leaf==false) C[i]->traverse();  //child number is keyword number plus 1.
}



//BTreee Search function
BTNode *BTNode::BTSearch(KeyType k, int index)
{
    int i=0;
    while (i<n && k> key[i])
        i=i+1;
    if (i<n && k==key[i])
    {
        index=i;
        cout<< k<< " is found in the tree! The child "<< index+1 << endl;
        return  this;
      
    }
    else if (leaf ==true)
        return NULL;
    else return  C[i]->BTSearch(k, index);
}

//BTree split child function

void BTNode::BTree_Split_Child(int i, BTNode *y)
{
    BTNode *z=new BTNode(y->t,y->leaf);          // create a new BTNode z
    
    z->n=t-1;                               //initialize z node
    
    
    for(int j=0; j<t-1; j++)                //copy the last t-1 keys of y into z node
    {
        z->key[j]=y->key[j+t];
    }
    
    if(!y->leaf)                                //y->leaf: false, y is an interior node
    {
        for(int j=0; j< t; j++) z->C[j]=y->C[j+t];      //copy children
    }
    y->n=t-1;                                       //turn the keyword number of y into t-1
    
    for (int j=n; j>i+1; j--) C[j+1]=C[j];
    
    C[i+1]=z;
    
    for (int j=n-1; j>=i; j--) key[j+1]=key[j];  //
    
    key[i]=y->key[t-1];
    n=n+1;

}


//BTree insert not_full function
void BTNode::BTree_Insert_Notfull(KeyType k)
{
    int i=n-1;
    
    if (leaf ==true)                                //leaf nodes
    {
        while (i>=0 && k< key[i])
        {
            key[i+1]= key[i];
            i=i-1;
        }
        key[i+1]=k;
        n=n+1;
    }
    
    else                                      //non-leaf nodes, find the right child that k is going to insert
    {
        while (i>=0 && k< key[i])   i=i-1;
        
        if(C[i+1]->n == 2*t -1)
        {
            
            BTree_Split_Child(i+1, C[i+1]);
            
            if(k>key[i])
                i=i+1;
        }
        
        C[i+1]->BTree_Insert_Notfull(k);
    }
}

void BTree:: Insert(KeyType k)
{
    if(root == NULL)                            //null tree, create a new root node
    {                                           //and update key array and number of keywords
        root= new BTNode(t,true);
        root->key[0]=k;
        root->n=1;
       // root->C[0]=NULL;
    }
    else
    {
        if(root->n==2*t-1)                      //if root is full,split it into two parts
        {
            BTNode *T= new BTNode(t,false);
            T->C[0]=root;
            
            T->BTree_Split_Child(0, root);
            
            int i=0;
            if(T->key[i] <k) i++;               //find  the location where k inserts
            T->C[i]->BTree_Insert_Notfull(k);
            root =T;                            //update root of B-tree
        }
        else root->BTree_Insert_Notfull(k);     //not full root, just insert k
    }
}

//findKey function: find the first key that is greater than or equal to k
int BTNode::findKey(KeyType k)
{
    int idx=0;
    while(idx<n && key[idx]<k) ++idx;
    return idx;
}



//removeKey function
void BTNode:: removeKey(KeyType k)
{
    int idx=findKey(k);
    
    if(idx<n && key[idx]==k)            //key is in this node
       
    {
        
        if(leaf==true)
            rmFromleaf(idx);
        else
            rmFromNonleaf(idx);
    }
    else                                //key is in the child node
    {
        if(leaf==true)                  //leaf node
        {
            cout<< "The key " <<k<<" is not in the tree, no need to delete!"<<endl;
            return;
        }
        bool flag;
        flag=(idx==n)? true:false;  //it is the last chid of this node having the key
        
        if(C[idx]->n<t)               //key number is t-1
            fill(idx);
        
        if(flag && idx>n)
            C[idx-1]->removeKey(k);
        else
            C[idx]->removeKey(k);
        
    }
    return;
    
}

//rmFromleaf function
void BTNode::rmFromleaf(int idx)
{
    for(int i=idx; i<n;i++)
        key[i]=key[i+1];
    n=n-1;
}

void BTNode::rmFromNonleaf(int idx)
{
    int k=key[idx];     //k is the key waiting to be  deleted
    
    //Predescessor _k has at least t keys, replaced k with _k
    if(C[idx]->n>=t)                    //case 2a
    {
        int _k=getPre(idx);
        key[idx]=_k;                //replace k by its predescessor _k
        C[idx]->removeKey(_k);
    }
    
    else if (C[idx+1]->n >=t)       //case 2b: k has less than  t keys
    {
        int K_=getSuc(idx);
        key[idx]=K_;
        C[idx+1]->removeKey(K_);
    }
    
    else
    {
        merge(idx);
        C[idx]->removeKey(k);
    }
    
    return;
    
}

//get predescessor function
int BTNode::getPre(int idx)
{
    BTNode *p=C[idx];
    
    while (!p->leaf)
        p=p->C[p->n];
    return p->key[p->n-1];
}

//get successor fuction
int BTNode::getSuc(int idx)
{
    BTNode *q=C[idx+1];
    while(!q->leaf)
        q=q->C[0];
    return q->key[0];
}

void BTNode::fill(int idx)
{
    if (idx!=0 && C[idx-1]->n>=t)       //case 3a
        brFromPrev(idx);
    
    else if(idx!=n && C[idx+1]->n>=t)       //case 3a
        brFromNext(idx);
    
    else                                //3b
    {
        if (idx !=n) {
            merge(idx);
        }
        else
            merge(idx-1);
    }
    return ;
}

void BTNode::brFromPrev(int idx)
{
    BTNode *Cur=C[idx];
    BTNode *Sibling=C[idx-1];
    
    for (int i=Cur->n-1; i>=0; --i)
        Cur->key[i+1]=Cur->key[i];
    
    if(!Cur->leaf)                          //non leaf nodes , move their children too
    {
        for (int i=Cur->n; i>=0; --i)
            Cur->C[i+1]=Cur->C[i];
    }
    
    Cur->key[0]=key[idx-1];                 //take one key from Cur's parent node
    
    if(!leaf)
        Cur->C[0]=Sibling->C[Sibling->n];       //borrow one key from its sibling
    
    key[idx-1]=Sibling->key[Sibling->n-1];
    
    Cur->n++;
    Sibling->n--;
    return;
}

void BTNode::brFromNext(int idx)
{
    BTNode *Cur=C[idx];
    BTNode *Sibling=C[idx+1];
    
    Cur->key[Cur->n]=key[idx];
    
    if(!Cur->leaf)
        Cur->C[Cur->n+1]=Sibling->C[0];     //borrow one key from right sibling
    
    key[idx]=Sibling->key[0];
    
    for (int i=1; i<Sibling->n; ++i)
        Sibling->key[i-1]=Sibling->key[i];
    
    
    if(!Sibling->leaf)                          //if sibiling is non leaf nodes , move their children too
    {
        for (int i=1; i<Sibling->n; ++i)
            Sibling->C[i-1]=Sibling->C[i];
    }
    
    Cur->n++;
    Sibling->n--;
    return;
}

void BTNode::merge(int idx)
{
    BTNode *Cur=C[idx];
    BTNode *Sibling=C[idx+1];
    
    Cur->key[t-1]=key[idx];
    
    for(int i=0; i<Sibling->n; ++i)
        Cur->key[i+t]=Sibling->key[i];
    
    if (!Cur->leaf)                     //non leaf node ,copy children too
    {
        for (int i=0; i<Sibling->n; ++i)
        {
            Cur->C[i+t]=Sibling->C[i];
        }
        
        for (int i=idx+1; i<n; ++i)
            key[i-1]=key[i];
        
        for (int i=idx+2; i<=n; ++i)
            C[i-1]=C[i];
        
        Cur->n+=Sibling->n+1;
        n--;
        
        delete Sibling;
        return;
    }
}

void BTree:: Delete(KeyType k)
{
    if(!root)
    {
        cout<<" The tree is empty! \n";
        return;
    }
    root->removeKey(k);
    
}

/*void BTree:: BTree_Delete(KeyType k)
}*/


//Main Function

int main()
{
    //
    int t=3, i=0;
    KeyType k;                  //target keyword to be searched
    KeyType m;                  //target keyword to be deleted
    BTNode *bt;
    BTree T(t);
    T.Insert('A');
    T.Insert('C');
    T.Insert('E');
    T.Insert('X');
    T.Insert('G');
    T.Insert('J');
    T.Insert('O');
    T.Insert('M');
    T.Insert('P');
    T.Insert('V');
    T.Insert('B');
    
    cout<<"Traverse before delete: \n";
    T.traverse();
    cout<<"" <<endl;
    
    
    cout<<"Please input the key you want to search(A-Z): \n";
    cin>>k;
    bt=T.BTSearch(k, i);
   if(bt==NULL)
     cout<< k<< " is not found in the tree!" <<endl;
    
    cout<< "Please input the key you want to delete(A-Z): \n";
    cin>>m;
    T.Delete(m);
    T.traverse();
    cout<<""<<endl;
    return 0;
}