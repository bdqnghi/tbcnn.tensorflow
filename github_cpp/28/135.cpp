#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef struct node{
    int key;
    struct node * left, * right, * parent;

    node(){key = -1; left = right = parent = NULL;};
    node(const int n):key(n), left(NULL), right(NULL), parent(NULL){};
    ~node()
    {
        if(left)
            delete left;
        if(right)
            delete right;
    };
} node, * pnode;

class SplayTree{
private:
    void zig(pnode T);
    void zag(pnode T);
    void splay(pnode T, pnode ANC);
    void splay(pnode & T);
    void insert(pnode & T, int key);
    pnode find(pnode T, int key);
    pnode findpre(pnode & root, int key);
    pnode findnext(pnode & root, int key);
    void remove(pnode & root, int key);
    void removeInterval(pnode & root, int a, int b);

public:
    pnode root;

    SplayTree()
    {
        root = NULL;
    }

    ~SplayTree()
    {
        if(root)
            delete root;
    }

    void Insert(int key);
    int Find(int key);
    int FindPre(int key);
    int FindNext(int key);
    void Remove(int key);
    void RemoveInterval(int a, int b);
};

//右旋
void SplayTree::zig(pnode x)
{
    pnode p = x->parent;
    x->parent = p->parent;

    if(p->parent != NULL)
    {
        if(p->parent->left == p)
            p->parent->left = x;
        else
            p->parent->right = x;
    }
    else root = x;

    p->left = x->right;
    if(x->right != NULL)
        x->right->parent = p;
    x->right = p;
    p->parent = x;
}

//左旋
void SplayTree::zag(pnode x)
{
    pnode p = x->parent;
    x->parent = p->parent;

    if(p->parent != NULL)
    {
        if(p->parent->left == p)
            p->parent->left = x;
        else
            p->parent->right = x;
    }
    else root = x;

    p->right = x->left;
    if(x->left != NULL)
        x->left->parent = p;
    x->left = p;
    p->parent = x;
}

//T转为ANC的孩子, 需要保证ANC是T的祖先
void SplayTree::splay(pnode T, pnode ANC)
{
    pnode p = NULL, g = NULL;

    while(T != NULL && T->parent != ANC)
    {
        p = T->parent;
        if(p->parent == ANC)
        {
            p->left == T ? zig(T) : zag(T);
        }
        else
        {
            g = p->parent;
            if(g->left == p)
            {
                p->left == T ? zig(p) : zag(T), zig(T);
            }
            else
            {
                p->left == T ? zig(T) : zag(p), zag(T);
            }
        }
    }
}

void SplayTree::splay(pnode & T)
{
    while(T->parent != NULL)
    {
        if(T->parent->parent != NULL)
        {
            if(T->parent->left == T) zig(T);
            else zag(T);
        }
        else if(T->parent->left == T& T->parent->parent->left == T->parent)
        {
            zig(T->parent);
            zig(T);
        }
        else if(T->parent->right == T& T->parent->parent->right == T->parent)
        {
            zag(T->parent);
            zag(T);
        }
        else if(T->parent->left == T& T->parent->parent->right == T->parent)
        {
            zig(T);
            zag(T);
        }
        else
        {
            zag(T);
            zig(T);
        }
    }
}

void SplayTree::insert(pnode & T, int key)
{
    if(T == NULL)
    {
        T = new node(key);
        return;
    }

    if(T->key == key)
    {
        splay(T, NULL);
    }
    else if(T->key > key)
    {
        if(T->left == NULL)
        {
            T->left = new node(key);
            T->left->parent = T;
            splay(T->left, NULL);
        }
        else insert(T->left, key);
    }
    else if(T->key < key)
    {
        if(T->right == NULL)
        {
            T->right = new node(key);
            T->right->parent = T;
            splay(T->right, NULL);
        }
        else insert(T->right, key);
    }
}

pnode SplayTree::find(pnode T, int key)
{
    if(T == NULL)
    {
        return NULL;
    }

    if(T->key == key)
    {
        return T;
    }
    else if(T->key > key)
    {
        if(T->left == NULL)
        {
            return NULL;
        }
        else return find(T->left, key);
    }
    else if(T->key < key)
    {
        if(T->right == NULL)
        {
            return NULL;
        }
        else return find(T->right, key);
    }
}

pnode SplayTree::findpre(pnode & root, int key)
{
    pnode p = find(root, key);
    bool flag = false;

    if(p == NULL)
    {
        insert(root, key);
        flag = true;
    }
    else splay(p, NULL);

    pnode l = root->left;
    if(l != NULL)
        while(l->right != NULL)
            l = l->right;

    if(flag)
        remove(root, key);

    return l;
}

pnode SplayTree::findnext(pnode & root, int key)
{
    pnode p = find(root, key);
    bool flag = false;

    if(p == NULL)
    {
        insert(root, key);
        flag = true;
    }
    else splay(p, NULL);

    pnode r = root->right;

    if(r != NULL)
        while(r->left != NULL)
            r = r->left;

    if(flag)
        remove(root, key);

    return r;
}

void SplayTree::remove(pnode & root, int key)
{
    pnode pre = findpre(root, key);
    pnode next = findnext(root, key);
    splay(pre, NULL);
    splay(next, pre);

    if(next != NULL)
    {
        delete next->left;
        next->left = NULL;
    }
    else if(pre != NULL)
    {
        delete pre->right;
        pre->right = NULL;
    }
}

void SplayTree::removeInterval(pnode & root, int a, int b)
{
    pnode pre = findpre(root, a);
    pnode next = findnext(root, b);
    splay(pre, NULL);
    splay(next, pre);

    if(next != NULL)
    {
        delete next->left;
        next->left = NULL;
    }
    else if(pre != NULL)
    {
        delete pre->right;
        pre->right = NULL;
    }
}

void SplayTree::Insert(int key)
{
    insert(root, key);
}

int SplayTree::Find(int key)
{
    pnode p = find(root, key);

    if(p == NULL)
        return -1;
    else
        return p->key;
}

int SplayTree::FindPre(int key)
{
    pnode p = findpre(root, key);

    if(p == NULL)
        return -1;
    else
        return p->key;
}

int SplayTree::FindNext(int key)
{
    pnode p = findnext(root, key);

    if(p == NULL)
        return -1;
    else
        return p->key;
}

void SplayTree::Remove(int key)
{
    remove(root, key);
}

void SplayTree::RemoveInterval(int a, int b)
{
    if(find(root, a) == NULL)
        insert(root, a);
    if(find(root, b) == NULL)
        insert(root, b);

    removeInterval(root, a, b);
}

int main()
{
    SplayTree ST;

    int n, a, b;
    char c;

    scanf("%d", &n);
    while(n --)
    {
        getchar();
        scanf("%c", &c);
        switch(c)
        {
            case 'I':
                scanf("%d", &a);
                ST.Insert(a);
            break;
            case 'D':
                scanf("%d %d", &a, &b);
                ST.RemoveInterval(a, b);
            break;
            case 'Q':
                scanf("%d", &a);
                printf("%d\n", ST.Find(a) == a ? a : ST.FindPre(a));
            break;
        }
    }

    return 0;
}
