#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
 
int t;	

class BTreeNode
{
public:
    int *keys;  
    BTreeNode **C; 
    int n;     
    bool leaf; 
    BTreeNode *parent;    
    int *noofdes; 

 
    BTreeNode(bool _leaf);   
 
    
    void traverse();
 
    
    BTreeNode *search(int k);   
 
    
    
    int findKey(int k);
 
    
    
    
    void insertNonFull(int k);
 
    
    
    
    void splitChild(int i, BTreeNode *y);
 
    
    
    void remove(int k);
 
    
    
    void removeFromLeaf(int idx);
 
    
    
    void removeFromNonLeaf(int idx);
 
    
    
    int getPred(int idx);
 
    
    
    int getSucc(int idx);
 
    
    
    void fill(int idx);
 
    
    
    void borrowFromPrev(int idx);
 
    
    
    void borrowFromNext(int idx);
 
    
    
    void merge(int idx);
 
void findmsm(int m);
    
    
    friend class BTree;
};
 
class BTree
{
public:
    BTreeNode *root; 
    int ht;	
 
    
    BTree()
    {
        root = NULL;
        ht=0;
    }
 
    void traverse()
    {
        if (root != NULL) root->traverse();
    }
 
    
    BTreeNode* search(int k)
    {
        return (root == NULL)? NULL : root->search(k);
    }
 
    
    void insert(int k);
 
    
    void remove(int k);
 
void findmthsmallest(int m);
};



void BTree::findmthsmallest(int m)
{
root->findmsm(m);
}



void BTreeNode::findmsm(int m)
{

if(leaf==true)
{
cout<<keys[m-1]<<"\n";
return;
}

int n1=0;
int n2=noofdes[0];
int i=0;
while(i<=n)
{
if(((m>n1)&&(m<n2+1)))
C[i]->findmsm(m-n1);

else if(m==n2+1)
{
cout<<keys[i]<<"\n";
return;
}
n1=n1+noofdes[i]+1;
n2=n2+noofdes[i+1]+1;
i++;

}


}



BTreeNode::BTreeNode(bool leaf1)
{

parent=NULL;    

   
    
    leaf = leaf1;
 
    
    
    keys = new int[4*t];
    C = new BTreeNode *[4*t];
    noofdes=new int[4*t];
 
    
    n = 0;


	
	for(int i=0;i<2*t;i++)
	noofdes[i]=0;


}



 

int findwhichchild(BTreeNode *par,BTreeNode *chi)
{
int i,index;
for(i=0;i<par->n+1;i++)
if(par->C[i]==chi)
index=i;

return index;
}



void updatenoofdes(BTreeNode *node,int i)
{

if(node->parent==NULL)
return;
int j=findwhichchild(node->parent,node);
(node->parent)->noofdes[j]+=i;
updatenoofdes(node->parent,i);
}









void mergenodes1(int k,BTreeNode* b1,BTreeNode* b2)
{
BTreeNode *child = b1;
    BTreeNode *sibling = b2;
    
    
    child->keys[child->n] = k;
child->n++;
    
    for (int i=0; i<sibling->n; ++i)
        child->keys[i+child->n] = sibling->keys[i];
    
    if (!sibling->leaf)
    {   for(int i=0; i<=sibling->n; ++i)
	{
   (sibling->C[i])->parent=child;
            child->C[i+child->n] = sibling->C[i];
}
    }



for(int i=0; i<=sibling->n; ++i)
{      child->noofdes[i+child->n] = sibling->noofdes[i];
}    

int sum=0,ind=0;

if(child->parent!=NULL)
{
ind=findwhichchild(child->parent,child);
sum=sum+1+sibling->n;
for(int j=0; j<=sibling->n; ++j)
sum+=sibling->noofdes[j];
 (child->parent)->noofdes[ind]+=sum;
updatenoofdes(child->parent,sum);
}


    child->n += sibling->n;
  sort(child->keys,(child->keys+child->n));
 

    return;

}

void mergenodes2(int k,BTreeNode* b1,BTreeNode* b2)
{

BTreeNode *child = b1;
    BTreeNode *sibling = b2;
    
    
    child->keys[child->n] = k;
child->n++;
    
    for (int i=0; i<sibling->n; ++i)
        child->keys[i+child->n] = sibling->keys[i];
    
    if (!sibling->leaf)
    {   for(int i=0; i<=sibling->n; ++i)
	{

 child->C[i+child->n] = sibling->C[i];
   (sibling->C[i])->parent=child;
}
    }



for(int i=0; i<=sibling->n; ++i)
{      child->noofdes[i+child->n] = sibling->noofdes[i];
}    

int sum=0,ind=0;
if(sibling->parent!=NULL)
{
ind=findwhichchild(sibling->parent,sibling);

sum=sum+child->n;
for(int j=0; j<=child->n; ++j)
sum+=child->noofdes[j];
 
child->parent=sibling->parent;
sibling->parent=NULL;
child->parent->C[ind]=child;

(child->parent)->noofdes[ind]+=sum;
updatenoofdes(child->parent,sum);
}


    child->n += sibling->n;
  sort(child->keys,(child->keys+child->n));
 


    return;


}


void splitnodes(BTreeNode* y)
{
if(y->parent==NULL)
{
return;
}

else if(y->n>(2*t-1))
{
BTreeNode* x=y->parent;
int i=findwhichchild(x,y);

    
    BTreeNode *z = new BTreeNode(y->leaf);
    z->n = y->n-t;
 
    
    for (int j = 0; j < y->n-t; j++)
        z->keys[j] = y->keys[j+t];

    
for(int l=0;l<=y->n-t;l++)
z->noofdes[l]=y->noofdes[l+t];
     
    
    if (y->leaf == false)
    {
        for (int j = 0; j <= y->n-t; j++)
{
            z->C[j] = y->C[j+t];
   (y->C[j+t])->parent=z;
}
    }
 
    
    
    for (int j = x->n; j >= i+1; j--)
{
        x->C[j+1] = x->C[j];
     x->noofdes[j+1]=x->noofdes[j];
}

int k;


x->noofdes[i+1]=z->n;
for(int l=0;l<=z->n;l++)
x->noofdes[i+1]+=z->noofdes[l];
x->noofdes[i]-=(1+x->noofdes[i+1]);




   
    x->C[i+1] = z;
    z->parent=x;


    
    for (int j = x->n-1; j >= i; j--)
        x->keys[j+1] = x->keys[j];
 
    
    x->keys[i] = y->keys[t-1];



 
    
    x->n = x->n + 1;


    y->n = t-1;

if(z->n>2*t-1)
splitnodes(z);



splitnodes(x);

}
}


BTree threewayjoin(BTree t1,int k,BTree t2)
{
int h;
if(t1.ht>t2.ht)
{
h=t1.ht;
BTreeNode *b=new BTreeNode(false);
b=t1.root;
while(h!=t2.ht)
{
b=b->C[b->n];
h--;
}
mergenodes1(k,b,t2.root);

splitnodes(b);
b=t1.root;
if((b->n)>(2*t-1))
{
BTreeNode *s=new BTreeNode(false);
s->parent=NULL;
s->C[0]=b;
int sum=b->n;
for(int i=0;i<b->n+1;i++)
sum+=b->noofdes[i];
s->noofdes[0]=0;
s->noofdes[0]+=sum;
b->parent=s;
s->n=0;
splitnodes(b);
t1.root=b->parent;
t1.ht++;
}
return t1;
}

else if(t1.ht<t2.ht)
{
h=t2.ht;
BTreeNode *b=new BTreeNode(false);
b=t2.root;
while(h!=t1.ht)
{
b=b->C[0];
h--;
}
mergenodes2(k,t1.root,b);
b=t1.root;
splitnodes(b);
b=t2.root;
if((b->n)>(2*t-1))
{
BTreeNode *s=new BTreeNode(false);
s->parent=NULL;
s->C[0]=b;
int sum=b->n;
for(int i=0;i<b->n+1;i++)
sum+=b->noofdes[i];
s->noofdes[0]=0;
s->noofdes[0]+=sum;
b->parent=s;
s->n=0;
splitnodes(b);
t2.root=b->parent;
t2.ht++;
}
return t2;
}


else if(t1.ht==t2.ht)
{
h=t2.ht;
BTreeNode *b=new BTreeNode(false);
b=t2.root;
while(h!=t1.ht)
{
b=b->C[0];
h--;
}
mergenodes2(k,t1.root,b);
b=t1.root;
splitnodes(b);

b=t1.root;
if((b->n)>(2*t-1))
{
BTreeNode *s=new BTreeNode(false);
s->parent=NULL;
s->C[0]=b;
int sum=b->n;
for(int i=0;i<b->n+1;i++)
sum+=b->noofdes[i];
s->noofdes[0]=0;
s->noofdes[0]+=sum;
b->parent=s;
s->n=0;
splitnodes(b);
t1.root=b->parent;
t1.ht++;
}
return t1;
}


}


BTree splitatreeg(BTreeNode* y,int i)
{

    
    BTreeNode *z = new BTreeNode(y->leaf);
	z->parent=NULL;

    z->n = y->n-(i+1);

    
    for (int j = 0; j < y->n-(i+1); j++)
        z->keys[j] = y->keys[j+(i+1)];

    
for(int l=0;l<=y->n-(i+1);l++)
z->noofdes[l]=y->noofdes[l+(i+1)];
     
    
    if (y->leaf == false)
    {
        for (int j = 0; j <= y->n-(i+1); j++)
{
            z->C[j] = y->C[j+(i+1)];
   (y->C[j+(i+1)])->parent=z;
}
    }
 
    
    
   



BTree temp;
temp.root=z;

int h=0;
BTreeNode *tempno=new BTreeNode(z->leaf);
tempno=z;
while(tempno!=NULL)
{
tempno=tempno->C[0];
h++;

}
temp.ht=h;
if((z->n==0)&&((z->C[0])!=NULL))
{
temp.root=z->C[0];
temp.root->parent=NULL;
temp.ht-=1;
}
return temp;


}



BTree makegreatertree(BTreeNode* node,int i)
{
BTree temp1=splitatreeg(node,i);

while(node->parent!=NULL)
{
int ind=findwhichchild(node->parent,node);
int k=node->parent->keys[ind];

if(ind!=node->parent->n)
{
BTree temp2=splitatreeg(node->parent,ind);

BTree temp3=threewayjoin(temp1,k,temp2);
temp1=temp3;
}
node=node->parent;
}

return temp1;
}

BTree splitatreel(BTreeNode* y,int i)
{

    
    BTreeNode *z = new BTreeNode(y->leaf);
	z->parent=NULL;

    z->n = i;

    
    for (int j = 0; j < i; j++)
        z->keys[j] = y->keys[j];

    
for(int l=0;l<=i;l++)
z->noofdes[l]=y->noofdes[l];
     
    
    if (y->leaf == false)
    {
        for (int j = 0; j <= i; j++)
{
            z->C[j] = y->C[j];
   (y->C[j])->parent=z;
}
    }
 
    
    
   



BTree temp;
temp.root=z;

int h=0;
BTreeNode *tempno=new BTreeNode(z->leaf);
tempno=z;
while(tempno!=NULL)
{
tempno=tempno->C[0];
h++;

}
temp.ht=h;
if((z->n==0)&&((z->C[0])!=NULL))
{
temp.root=z->C[0];
temp.root->parent=NULL;
temp.ht-=1;
}
return temp;


}




BTree makelessertree(BTreeNode* node,int i)
{
BTree temp1=splitatreel(node,i);

while(node->parent!=NULL)
{
int ind=findwhichchild(node->parent,node);
int k=node->parent->keys[ind-1];

if(ind!=0)
{
BTree temp2=splitatreel(node->parent,ind-1);

BTree temp3=threewayjoin(temp2,k,temp1);
temp1=temp3;
}
node=node->parent;
}

return temp1;
}

BTreeNode* searchnode(BTreeNode* b,int k)
{
int i = 0;
    while (i < b->n && k > b->keys[i])
        i++;
 
    
    if (b->keys[i] == k)
        return b;
 
    
    if (b->leaf == true)
        return b;
 
    
    return searchnode(b->C[i],k);

}



BTree splittreegrt(BTree T,int k)
{
BTreeNode* b=new BTreeNode(true);

if(T.search(k)!=NULL)
{
b=T.search(k);
int i=b->findKey(k);
return makegreatertree(b,i);
}
else
{
b=searchnode(T.root,k);
int i=b->findKey(k);
return makegreatertree(b,i-1);

}


}



BTree splittreeles(BTree T,int k)
{
BTreeNode* b=new BTreeNode(true);

if(T.search(k)!=NULL)
{
BTree temp=T;
b=T.search(k);
int i=b->findKey(k);
return makelessertree(b,i);

}

else
{
b=searchnode(T.root,k);
int i=b->findKey(k);
return makelessertree(b,i+1);

}
}






int BTreeNode::findKey(int k)
{
    int idx=0;
    while (idx<n && keys[idx] < k)
        ++idx;
    return idx;
}
 

void BTreeNode::remove(int k)
{
    int idx = findKey(k);
 
    
    if (idx < n && keys[idx] == k)
    {
 
        
        
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {
 
        
        if (leaf)
        {
            cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }
 
        
        
        
        bool flag = ( (idx==n)? true : false );
 
        
        
        if (C[idx]->n < t)
            fill(idx);
 
        
        
        
        if (flag && idx > n)
            C[idx-1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}
 


void BTreeNode::removeFromLeaf (int idx)
{
 
    
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];
 
    
    n--;

 

updatenoofdes(this,-1);

    return;
}
 

void BTreeNode::removeFromNonLeaf(int idx)
{
 
    int k = keys[idx];
 
    
    
    
    
    if (C[idx]->n >= t)
    {
        int pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    }
 
    
    
    
    
    
    else if  (C[idx+1]->n >= t)
    {
        int succ = getSucc(idx);
        keys[idx] = succ;
        C[idx+1]->remove(succ);
    }
 
    
    
    
    
    else
    {
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}
 

int BTreeNode::getPred(int idx)
{
    
    BTreeNode *cur=C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
 
    
    return cur->keys[cur->n-1];
}
 
int BTreeNode::getSucc(int idx)
{
 
    
    BTreeNode *cur = C[idx+1];
    while (!cur->leaf)
        cur = cur->C[0];
 
    
    return cur->keys[0];
}
 

void BTreeNode::fill(int idx)
{
 
    
    
    if (idx!=0 && C[idx-1]->n>=t)
        borrowFromPrev(idx);
 
    
    
    else if (idx!=n && C[idx+1]->n>=t)
        borrowFromNext(idx);
 
    
    
    
    else
    {
        if (idx != n)
            merge(idx);
        else
            merge(idx-1);
    }
    return;
}




void BTreeNode::borrowFromPrev(int idx)
{
 
    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx-1];
 
    
    
    
 
    
    for (int i=child->n-1; i>=0; --i)
        child->keys[i+1] = child->keys[i];
 

       for(int i=child->n; i>=0; --i)
            child->noofdes[i+1] = child->noofdes[i];
    




    if (!child->leaf)
    {
        for(int i=child->n; i>=0; --i)
            child->C[i+1] = child->C[i];
    }
 

    
    child->keys[0] = keys[idx-1];


child->noofdes[0] = sibling->noofdes[sibling->n];

 

if(!(sibling->leaf))
{
(sibling->C[sibling->n])->parent=child;

        child->C[0] = sibling->C[sibling->n];
     }


    
    
    keys[idx-1] = sibling->keys[sibling->n-1];
 
    child->n += 1;
    sibling->n -= 1;
 

this->noofdes[idx-1]-=(1+child->noofdes[0]);
this->noofdes[idx]+=(1+child->noofdes[0]);




    return;
}
 


void BTreeNode::borrowFromNext(int idx)
{
 
    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx+1];
 
    
    child->keys[(child->n)] = keys[idx];
 
    
    
    if (!(child->leaf))
{
(sibling->C[0])->parent=child;
        child->C[(child->n)+1] = sibling->C[0];
     }
 

   child->noofdes[(child->n)+1] = sibling->noofdes[0];
 
 
    
    keys[idx] = sibling->keys[0];
 
    
    for (int i=1; i<sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];
 
    
    if (!sibling->leaf)
    {
        for(int i=1; i<=sibling->n; ++i)
            sibling->C[i-1] = sibling->C[i];
    }
 

   for(int i=1; i<=sibling->n; ++i)
            sibling->noofdes[i-1] = sibling->noofdes[i];
 
    
    
    child->n += 1;
    sibling->n -= 1;
 

this->noofdes[idx]+=(1+child->noofdes[(child->n)]);
this->noofdes[idx+1]-=(1+child->noofdes[(child->n)]);
 
 
    return;
} 


void BTreeNode::merge(int idx)
{
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx+1];
 
    
    
    child->keys[t-1] = keys[idx];
 
    
    for (int i=0; i<sibling->n; ++i)
        child->keys[i+t] = sibling->keys[i];
 
    
    if (!child->leaf)
    {
        for(int i=0; i<=sibling->n; ++i)
{
   (sibling->C[i])->parent=child;
            child->C[i+t] = sibling->C[i];
}
    }


for(int i=0; i<=sibling->n; ++i)
{
       child->noofdes[i+t] = sibling->noofdes[i];
}    

 
    
    
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];
 


noofdes[idx]+=(1+noofdes[idx+1]);


    
    
    for (int i=idx+2; i<=n; ++i)
{
        C[i-1] = C[i];
noofdes[i-1]=noofdes[i];
}
 

    
    child->n += sibling->n+1;
    n--;
 
sibling->parent=NULL;
    
    delete(sibling);
    return;
}
 

void BTree::insert(int k)
{
int i;
    
    if (root == NULL)
    {
	ht++;
        
        root = new BTreeNode(true);
        root->keys[0] = k;  
        root->n = 1;  
for(i=0;i<root->n+1;i++) 
root->noofdes[i]=0;
    }
    else 
    {
        
        if (root->n == 2*t-1)
        {
	ht++;
            
            BTreeNode *s = new BTreeNode(false);
 
            
            s->C[0] = root;
        root->parent=s;
            
   for(i=0;i<root->n+1;i++)
   s->noofdes[0]+=root->noofdes[i];

            
            s->splitChild(0, root);
 
            
            
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
 
            
            root = s;
        }
        else  
            root->insertNonFull(k);
    }
}
 





void BTreeNode::insertNonFull(int k)
{

    
    int i = n-1;
 
    
    if (leaf == true)
    {
        
        
        
        while (i >= 0 && keys[i] > k)
        {
            keys[i+1]=keys[i];
   i--;
        }
 
        
        keys[i+1] = k;
        n = n+1;




updatenoofdes(this,1);
    }

    else 


    {
        
        while (i >= 0 && keys[i] > k)
            i--;
 
        
        if (C[i+1]->n == 2*t-1)
        {
            
            splitChild(i+1, C[i+1]);
 
            
            
            
            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}
 


void BTreeNode::splitChild(int i, BTreeNode *y)
{
    
    
    BTreeNode *z = new BTreeNode(y->leaf);
    z->n = t - 1;
 
    
    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];

    
for(int l=0;l<t;l++)
z->noofdes[l]=y->noofdes[l+t];
     
    
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
{
            z->C[j] = y->C[j+t];
   (y->C[j+t])->parent=z;
}
    }
 
    
    y->n = t - 1;
 
    
    
    for (int j = n; j >= i+1; j--)
{
        C[j+1] = C[j];
     noofdes[j+1]=noofdes[j];
}

int k;


this->noofdes[i+1]=0;
this->noofdes[i+1]+=t-1;
if(this->n==0)
this->noofdes[i]+=t-1;
else
this->noofdes[i]-=t;
for(k=0;k<z->n+1;k++)
{
       this->noofdes[i+1]+=z->noofdes[k];
       this->noofdes[i]-=z->noofdes[k];
}

    
    C[i+1] = z;
    z->parent=this;


    
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
 
    
    keys[i] = y->keys[t-1];



 
    
    n = n + 1;

}
 

void BTreeNode::traverse()
{
    
    
    int i;
    for (i = 0; i < n; i++)
    {
        
        
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }
 
    
    if (leaf == false)
        C[i]->traverse();
}
 

BTreeNode *BTreeNode::search(int k)
{
    
    int i = 0;
    while (i < n && k > keys[i])
        i++;
 
    
    if (keys[i] == k)
        return this;
 
    
    if (leaf == true)
        return NULL;
 
    
    return C[i]->search(k);
}
 
void BTree::remove(int k)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }
 
    
    root->remove(k);
 
    
    
    if (root->n==0)
    {
	ht--;

        BTreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
{
            root = root->C[0];
        root->parent=NULL;
}

        
        delete tmp;
    }
    return;
}
 

int main()
{




int tno,noofchoice,noofele;
cin>>t>>noofchoice;
BTree tree[10001];
char str[10];
int i,ele,m;
while(noofchoice--)
{
cin>>str;

if(strcmp(str,"insert")==0)
{
cin>>tno>>noofele;
for(i=0;i<noofele;i++)
{
cin>>ele;
tree[tno].insert(ele);
}

}

if(strcmp(str,"delete")==0)
{
cin>>tno>>noofele;
for(i=0;i<noofele;i++)
{
cin>>ele;
tree[tno].remove(ele);
}
}

if(strcmp(str,"select")==0)
{
cin>>tno>>m;
tree[tno].findmthsmallest(m);
}

if(strcmp(str,"join")==0)
{
int tr1,tr2,tr3;
int k;
cin>>tr1>>k>>tr2>>tr3;

tree[tr3]=threewayjoin(tree[tr1],k,tree[tr2]);


}

if(strcmp(str,"split")==0)
{

int tr,trl,trg;
int k;
cin>>tr>>k>>trl>>trg;
tree[trl]=splittreeles(tree[tr],k);
tree[trg]=splittreegrt(tree[tr],k);

}

}
return 0;
}
