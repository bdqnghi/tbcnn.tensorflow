/*
 *File:  b.cpp
 *Date : 2014-10-07 15:32:28
 */
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
typedef  long long LL;

#define clr(x) memset((x),0,sizeof(x))
#define inf 0x3f3f3f3f
#define loop(i,l,r) for(int (i)=(l);(i)<=(r);(i)++)
#define iloop(i,l,r) for(int (i)=(r);(i)>=(l);(i)--)

using namespace std;
#define maxn 100010
int n,q,s;
struct seg {
    int v, next;
} edge[maxn*2];
int tol,pos;
int begin[maxn];
int fa[maxn];
int son[maxn];
int dep[maxn];
int p[maxn];
int num[maxn];
int top[maxn];
void init()
{
    tol  = 0;
    memset(begin,-1,sizeof(begin));
    memset(son,-1,sizeof(son));
    pos = 0;
}

void addedge(int u,int v)
{
    edge[tol].v = v;edge[tol].next = begin[u];begin[u]=tol++;

}



void dfs1(int x,int d,int f)
{
    dep[x] =d;
    fa[x] = f;
    num[x] = 1;
    for(int i = begin[x];i!=-1;i=edge[i].next)
    {
        int v = edge[i].v;
        if(v!=f)
        {
           dfs1(v,d+1,x);
           num[x] += num[v];
           if(son[x] == -1|| num[v]>num[son[x]] )
               son[x] = v;
        }
    }
}
void getpos(int x,int sp)
{
   top[x] =sp; 
   p[x] = pos++;
   if(son[x] == -1) return ;
   getpos(son[x],sp);
   for(int i = begin[x];i!=-1;i=edge[i].next)
   {
       int v = edge[i].v;
        if(v!=fa[x]&&v!=son[x])
        {
            getpos(v,v);
        }
   }
}

struct node{
    int l,r;
    int sum;
    int col;
}tree[maxn<<2];
void push_up(int rt)
{
    tree[rt].sum = tree[rt<<1].sum+tree[rt<<1|1].sum;
    
}
void build(int l,int r,int rt)
{
    tree[rt].sum = 0;
    tree[rt].col = 0;
    tree[rt].l = l;
    tree[rt].r = r;
    if(l == r) return ;
    int mid = (l+r)>>1;
    build(l,mid,rt<<1);
    build(mid+1,r,(rt<<1)|1);
    push_up(rt);
}
void update(int x,int data,int rt)
{
    int l =tree[rt].l;
    int r = tree[rt].r;
    if(l==r&&x==l)
    {
        tree[rt].sum = data;
        tree[rt].col = 0;
        return;
    }
    int m = (l+r)>>1;
    if(x <= m) update(x,data,rt<<1);
    else update(x,data,(rt<<1)|1);
    push_up(rt);
}
int query(int L,int R,int rt)
{
    int l = tree[rt].l;
    int r = tree[rt].r;
    if(L<=l &&r<=R)
    {
        return tree[rt].sum;
    }
    int m= (l+r)>>1;
    int ret = 0;
    if(L<=m) ret+= query(L,R,rt<<1);
    if(R>m) ret +=  query(L,R,rt<<1|1);
    return ret;
}
int find(int u,int v)
{
    int f1 = top[u],f2 = top[v];
    int tmp  = 0;
    while(f1!=f2)
    {
        if(dep[f1]<dep[f2])
        {
            swap(f1,f2);
            swap(u,v);
        }
        tmp += query(p[f1],p[u],1);
        u = fa[f1];f1 =top[u];
    }
    if(u == v) return tmp;
    if(dep[u]>dep[v]) swap(u,v);
    return tmp += query(p[son[u]],p[v],1);
}
int e[maxn][3];

int main()
{
    init();
    scanf("%d%d%d",&n,&q,&s);
    for(int i=1;i<=n-1;i++)
    {
        scanf("%d%d%d",&e[i][0],&e[i][1],&e[i][2]);
        addedge(e[i][0],e[i][1]);
        addedge(e[i][1],e[i][0]);
    }
    dfs1(1,0,0);
    getpos(1,1);
    build(1,pos,1);
    for(int i = 1;i<=n-1;i++)
    {
        if(dep[e[i][0]]>dep[e[i][1]])
            swap(e[i][0],e[i][1]);
        update(p[e[i][1]],e[i][2],1);
    }
    int a,l,r;
    for(int i=1;i<=q;i++)
    {
        scanf("%d",&a);
        if(a==0)
        {
            scanf("%d",&l);
            int ans = find(s,l);
            printf("%d\n",ans);
            s =l;
            
        }
        else {
            scanf("%d%d",&l,&r);
           update(p[e[l][1]],r,1);
        }
    }
    return 0;
}

