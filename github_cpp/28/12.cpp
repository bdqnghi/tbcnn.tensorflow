//
// Created by Henry on 17/2/21.
//
#include "main.h"


#define keyValue ch[ch[root][1]][0]



int ch[MAXN][2],s[MAXN],pre[MAXN],siz[MAXN],colg[MAXN],colc[MAXN],mgrade[MAXN];
int tot1,tot2,root;
inf Inf[MAXN];

void updateg(int rt,int v){
    if(!rt)return;
    Inf[rt].grade = v;
    colg[rt] = v;
}

void updatec(int rt,int v){
    if(!rt)return;
    Inf[rt].cls = v;
    colc[rt] = v;
}

void pushUp(int rt){
    siz[rt] = 1;
    mgrade[rt] = Inf[rt].grade;
    if(ch[rt][0]) {
        siz[rt] += siz[ch[rt][0]];
        mgrade[rt] = max(mgrade[rt],mgrade[ch[rt][0]]);
    }
    if(ch[rt][1]) {
        siz[rt] += siz[ch[rt][1]];
        mgrade[rt] = max(mgrade[rt],mgrade[ch[rt][1]]);
    }
}

void pushDown(int rt){
    if(colc[rt]){
        updatec(ch[rt][0],colc[rt]);
        updatec(ch[rt][1],colc[rt]);
        colc[rt] = 0;
    }

    if(colg[rt]){
        updateg(ch[rt][0],colg[rt]);
        updateg(ch[rt][1],colg[rt]);
        colg[rt] = 0;
    }
}

int newNode(int fa,inf * tmp){
    int rt = tot2 ? s[--tot2] : ++tot1;
    ch[rt][0] = ch[rt][1] = 0;
    mgrade[rt] = tmp->grade;
    Inf[rt] = *tmp;
    pre[rt] = fa;
    siz[rt] = 1;
    colc[rt] = colg[rt] = 0;
    return rt;
}

void initSplay(){
    tot1 = tot2 = root = 0;
    siz[root] = ch[root][0] = ch[root][1] = 0;
    Inf[root].cls = Inf[root].grade = mgrade[root] = pre[root] = 0;
    colc[root] = colg[root] = 0;
    inf tmp;
    tmp.grade = -1;
    root = newNode(0,&tmp);
    ch[root][1] = newNode(root,&tmp);
    pushUp(ch[root][1]);
    pushUp(root);
}

void Rotate(int x,int kind){
    int y = pre[x];
    pushDown(y);
    pushDown(x);
    ch[y][!kind] = ch[x][kind];
    pre[ch[x][kind]] = y;
    if(pre[y]) ch[pre[y]][ch[pre[y]][1] == y] = x;
    pre[x] = pre[y];
    ch[x][kind] = y;
    pre[y] = x;
    pushUp(y);
}

void Splay(int x,int goal){
    pushDown(x);
    while (pre[x] != goal){
        if(pre[pre[x]] == goal){
            pushDown(pre[x]);
            pushDown(x);
            Rotate(x,ch[pre[x]][0] == x);
        } else{
            int y = pre[x];
            pushDown(pre[y]);
            pushDown(y);
            pushDown(x);
            int kind = ch[pre[y]][0] == y;

            if(ch[y][kind] == x){
                Rotate(x,!kind);
                Rotate(x,kind);
            } else{
                Rotate(y,kind);
                Rotate(x,kind);
            }
        }
    }
    pushUp(x);
    if(!goal)
        root = x;

}

int Build(inf A[],int l,int r,int fa){
    if (l > r) return 0;

    int mid = Mid(l,r);
    int rt = newNode(fa,&A[mid]);

    ch[rt][0] = Build(A,l,mid-1,rt);
    ch[rt][1] = Build(A,mid+1,r,rt);
    pushUp(rt);
    return rt;
}

int getKth(int k,int rt){
    int t = siz[ch[rt][0]] + 1;
    if(k == t) return rt;
    else if(k < t)
        return getKth(k,ch[rt][0]);
    else
        return getKth(k-t,ch[rt][1]);
}

void Erase(int rt){
    if(!rt) return;
    s[++tot2] = rt;
    Erase(ch[rt][0]);
    Erase(ch[rt][1]);
}

void Insert(int pos, inf A[],int size){
    Splay(getKth(pos+1,root),0);
    Splay(getKth(pos+2,root),root);
    pushDown(root);
    pushDown(ch[root][1]);
    keyValue = Build(A,0,size-1,ch[root][1]);
    pushUp(ch[root][1]);
    pushUp(root);
}

void Delete(int pos,int n){
    Splay(getKth(pos ,root),0);
    Splay(getKth(pos + 1 + n,root),root);
    pushDown(root);
    pushDown(ch[root][1]);
    Erase(keyValue);
    pre[keyValue] = 0;
    keyValue = 0;
    pushUp(ch[root][1]);
    pushUp(root);
}

void update(int pos, int n,int key,void (*updater)(int root,int key)){
    Splay(getKth(pos  ,root),0);
    Splay(getKth(pos + 1 + n,root),root);
    pushDown(root);
    pushDown(ch[root][1]);
    updater(keyValue,key);
    pushUp(ch[root][1]);
    pushUp(root);
}


int MaxGrade(int l,int r){
    Splay(getKth(l+1,root),0);
    Splay(getKth(r+2,root),root);
    pushDown(root);
    pushDown(ch[root][1]);
    return mgrade[keyValue];
}

int id;
void prt(int rt){
    if (!rt)return;
    pushDown(rt);
    prt(ch[rt][0]);
    printf("Pos:%2d\tName:%s\tGrade:%2d\tClass:%2d\n",id++,Inf[rt].name,Inf[rt].grade,Inf[rt].cls);
    prt(ch[rt][1]);
}

void prtTree(){
    Splay(getKth(1,root),0);
    Splay(getKth(siz[root],root),root);
    id = 1;
    prt(keyValue);
    printf("BestScore : %d \n",MaxGrade(0,siz[root]-2));
}
int cnt;

void deconstruct(inf A[],int rt){
    pushDown(rt);

    if(ch[rt][0]) deconstruct(A,ch[rt][0]);
    A[cnt++] = Inf[rt];
    if(ch[rt][1]) deconstruct(A,ch[rt][1]);
}

void toArray(inf A[],int l,int r) {
    Splay(getKth(l, root), 0);
    Splay(getKth(r + 2, root), root);
    pushDown(root);
    pushDown(ch[root][1]);
    cnt = 0;
    deconstruct(A,keyValue);
}