#include<iostream>
#include <stdlib.h>
#include <string.h>

#define M  5
#define MIN (M/2)
#define MAX (M-1)

typedef  int  KeyType;
typedef struct
{

}Record;

typedef struct
{
    KeyType key;
    Record *recptr;
}ElemType;

typedef struct BNode
{
    ElemType data[M+1];
    struct BNode *parent;
    struct BNode *sub[M+1];
    int num;
}BNode,*BpNode;

typedef struct Result
{
    BpNode pnode;
    int pos;
    bool tag;
}Result;

BpNode buy_bnode()
{
    BpNode node = (BpNode)malloc(sizeof(BNode));
    if(node == NULL)
    {
        std::cout<<"malloc error\n";
        exit(0);
    }
    memset(node,0,sizeof(BNode));
    return node;
}

void free_node(BpNode p)
{
    if(p != NULL)
    {
        free(p);
    }
}

Result serch(BpNode node,KeyType data)
{
    Result res = {NULL,-1,false};
    if(node != NULL)
    {
        node->data[0].key = data;
        int i = node->num;
        while(data < node->data[i].key)
        {
            --i;
        }
        res.pnode = node;
        res.pos = i;
        if(i != 0 && node->data[i].key == data)
        {
            res.tag = true;
        }
        else
        {
            res = serch(node->sub[i],data);
        }

    }
    return res;
}
Result find(BpNode node,KeyType kx)
{
    Result res = {NULL,-1,false};
    while(node != NULL)
    {
        node->data[0].key = kx;
        int i = node->num;
        while(kx < node->data[i].key)
        {
            --i;
        }
        res.pnode = node;
        res.pos = i;
        if(i > 0 && node->data[i].key == kx)
        {
            res.tag = true;
            break;
        }
        node = node->sub[i];
    }
    return res;
}

BpNode creat_root(ElemType x, BpNode right, BpNode left)
{
    BpNode root = buy_bnode();
    root->data[1] = x;
    root->num = 1;
    root->parent = NULL;
    root->sub[0] = left;
    root->sub[1] = right;
    if(right != NULL)
    {
        right->parent = root;
    }
    if(left != NULL)
    {
        left->parent = root;
    }
    return root;
}

void insert_item(BNode *p,int pos,ElemType x, BNode *right)
{
    if(p == NULL)
    {
        return;
    }
    for(int i = p->num; pos < i; --i)
    {
        p->data[i+1] = p->data[i];
        p->sub[i+1] = p->sub[i];
    }
    p->data[pos+1] = x;
    p->sub[pos+1] = right;
    if(right != NULL)
        right->parent = p;
    p->num += 1;
}

ElemType  move_item(BNode *newnode, BNode *s)
{
    newnode->parent = s->parent;
    for(int i = MIN+2,j = 1; i <= s->num; ++i,++j)
    {
        newnode->data[j] = s->data[i];
        newnode->sub[j] = s->sub[i];
        if(newnode->sub[j] != NULL)
        {
            newnode->sub[j]->parent = newnode;
        }
    }
    newnode->sub[0] = s->sub[MIN+1];
    if(newnode->sub[0] != NULL)
    {
        newnode->sub[0]->parent = newnode;
    }
    s->num = MIN;
    newnode->num = MIN;
    return s->data[MIN+1];

}

BNode *splice(BNode *p)
{
    BNode *newroot = NULL;
    BNode *newnode = buy_bnode();
    ElemType x = move_item(newnode,p);
    if(p->parent == NULL)
    {
        return creat_root(x,p,newnode);
    }
    p = p->parent;
    p->data[0] = x;
    int pos = p->num;
    for(; p->data[pos].key > x.key; --pos);
    insert_item(p,pos,x,newnode);
    if(p->num > MAX)
    {
        newroot = splice(p);
    }
    return newroot;
}
BNode * insert(BNode *p, KeyType key, Record *rec)
{
    ElemType item = {key,rec};
    if(p == NULL)
    {
        return creat_root(item,NULL,NULL);
    }
    Result res = find(p,key);
    if(res.tag)
    {
        std::cout<<"the key exsist\n";
        return p;
    }
    else if(!res.tag && res.pnode == NULL)
    {
        std::cout<<"error\n";
        exit(1);
    }
    BNode *ptr = res.pnode;
    int pos = res.pos;
    insert_item(ptr,pos,item,NULL);
    if(p->num > MAX)
    {
        BNode *newroot = splice(ptr);
        if(newroot != NULL)
        {
            p = newroot;
        }
    }
    return p;
}

void in_order(BNode *ptr)
{
    if(ptr != NULL)
    {
        int i = 0;
        for(; i < ptr->num; ++i)
        {
            in_order(ptr->sub[i]);
            std::cout<<ptr->data[i+1].key<<"  ";
        }
        in_order(ptr->sub[i]);
    }
}

BNode *Min(BNode *ptr)
{
    while(ptr != NULL && ptr->sub[0] != NULL)
    {
        ptr = ptr->sub[0];
    }
    return ptr;
}
void del_leaf_item(BNode *ptr,int pos)
{
    for(int i = pos; i < ptr->num; ++i)
    {
        ptr->data[i] = ptr->data[i+1];
        ptr->sub[i] = ptr->sub[i+1];
    }
    ptr->num -= 1;
}

void adjust_right_leaf(BNode *ptr, BNode *parent, int pos, BNode *right)
{
    ptr->num += 1;
    ptr->data[ptr->num] = parent->data[pos+1];
    parent->data[pos+1] = right->data[1];
    del_leaf_item(right,1);
}
void adjust_left_leaf(BNode *ptr,BNode *parent, int pos, BNode *left)
{
    insert_item(ptr,0,parent->data[pos],NULL);
    parent->data[pos] = left->data[left->num];
    left->num -= 1;
}
void merge_ptr_right(BNode *ptr,BNode *parent,int pos,BNode *right)
{
    ptr->num += 1;
    ptr->data[ptr->num] = parent->data[pos+1];
    ptr->sub[ptr->num] = right->sub[0];
    if(ptr->sub[ptr->num] != NULL)
    {
        ptr->sub[ptr->num]->parent = ptr;
    }
    for(int i = 1; i <= right->num; ++i)
    {
        ptr->num += 1;
        ptr->data[ptr->num] = right->data[i];
        ptr->sub[ptr->num] = right->sub[i];
        if(ptr->sub[ptr->num] != NULL)
        {
            ptr->sub[ptr->num]->parent = ptr;
        }

    }
    free_node(right);
    del_leaf_item(parent,pos+1);
}
void adjust_right_brach(BNode *ptr,BNode *parent,int pos, BNode * right)
{
    ptr->num += 1;
    ptr->data[ptr->num] = parent->data[pos+1];
    ptr->sub[ptr->num] = right->sub[0];
    if(ptr->sub[ptr->num] != NULL)
    {
        ptr->sub[ptr->num]->parent = ptr;
    }
    parent->data[pos+1] = right->data[1];
    right->sub[0] = right->sub[1];
    del_leaf_item(right,1);
}
void adjust_left_brach(BNode *ptr,BNode *parent,int pos, BNode *left)
{
    ptr->num += 1;
    for(int i = ptr->num; i > 1; --i)
    {
        ptr->data[i] = ptr->data[i-1];
        ptr->sub[i] = ptr->sub[i-1];
    }
    ptr->data[1] = parent->data[pos];
    ptr->sub[1] = ptr->sub[0];
    ptr->sub[0] = left->sub[left->num];
    if(ptr->sub[0] != NULL)
    {
        ptr->sub[0]->parent = ptr;
    }
    parent->data[pos] = left->data[left->num];
    left->num -= 1;

}
BNode *merge_branch(BNode *ptr)
{
    BNode *newroot = NULL;
    BNode *left = NULL, *right = NULL;
    BNode *parent = ptr->parent;
    int pos = parent->num;
    while(pos >= 0 && parent->sub[pos] != ptr)
    {
        --pos;
    }
    if(pos > 0)
    {
        left = parent->sub[pos-1];
    }
    if(pos < parent->num)
    {
        right = parent->sub[pos+1];
    }
    if(right != NULL && right->num > MIN)
    {
        adjust_right_leaf(ptr,parent,pos,right);
        return newroot;
    }
    else if(left != NULL && left->num > MIN)
    {
        adjust_left_leaf(ptr,parent,pos,left);
        return newroot;
    }
    if(right != NULL)
    {
        merge_ptr_right(ptr,parent,pos,right);
    }
    if(left != NULL)
    {
        merge_ptr_right(left,parent,pos-1,ptr);
    }
    if(parent->parent == NULL && parent->num == 0)
    {
        free_node(parent);
        left->parent = NULL;
        newroot = left;
    }
    else if(parent->parent != NULL && parent->num < MIN)
    {
        newroot = merge_branch(parent);
    }
    return newroot;

}

BNode *merge_leaf(BNode *ptr)
{
    BNode *newroot = NULL;
    BNode *right = NULL;
    BNode *left = NULL;
    BNode *parent = ptr->parent;
    int pos = parent->num;
    while(pos >= 0 && parent->sub[pos] != ptr)
    {
        --pos;
    }
    if(pos < 0)
    {
        exit(1);
    }
    if(pos > 0)
    {
        left = parent->sub[pos-1];
    }
    if(pos < parent->num)
    {
        right = parent->sub[pos+1];
    }
    if(right != NULL && right->num > MIN)
    {
        adjust_right_leaf(ptr,parent,pos,right);
        return newroot;
    }
    else if(left != NULL && left->num > MIN)
    {
        adjust_left_leaf(ptr,parent,pos,left);
        return newroot;
    }
    if(right != NULL)
    {
        merge_ptr_right(ptr,parent,pos,right);
    }
    else if(left != NULL)
    {
        merge_ptr_right(left,parent,pos-1,ptr);
    }
    if(parent->parent != NULL && parent->num < MIN)
    {
        newroot = merge_branch(parent);
    }
    return newroot;
}

BNode *remove(BNode *ptr, KeyType key)
{
    if(ptr == NULL)
    {
        return NULL;
    }
    Result res = find(ptr,key);
    if(!res.tag)
    {
        std::cout<<"the key not exsist\n";
        return ptr;
    }
    if(res.tag && res.pnode == NULL)
    {
        exit(1);
    }
    BNode *p = res.pnode;
    int pos = res.pos;
    if(p->sub[pos] != NULL)
    {
        BNode *pn = Min(p->sub[pos]);
        p->data[pos] = pn->data[1];
        p = pn;
        pos = 1;
    }
    del_leaf_item(p,pos);
    if(p->parent != NULL && p->num < MIN)
    {
        BNode *newroot = merge_leaf(p);
        if(newroot != NULL)
        {
            ptr = newroot;
        }
    }
    return ptr;
}


int main()
{
    BNode *root = NULL;
    KeyType arr[] = {1,3,14};
    Record *rec = NULL;
    int n = sizeof(arr)/sizeof(arr[0]);
    for(int i = 0; i < n; ++i)
    {
        root = insert(root,arr[i],rec);
    }
    in_order(root);
    std::cout<<"\n";
    KeyType key;
    while(std::cin>>key,key != -1)
    {
        root = remove(root,key);
        in_order(root);
        std::cout<<"\n";
    }
}
