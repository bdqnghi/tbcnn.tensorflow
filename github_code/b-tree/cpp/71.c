/*
 *File:  b.cpp
 *Date : 2015-03-15 12:43:49
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

using namespace std;
const int maxn = 30010;
int r,n,m;
struct seg {
    int a,b,c,d;
    seg(){}
    seg(int a,int b,int c,int d):a(a),b(b),c(c),d(d){}
    seg operator +(seg  p)
    {
        return seg((a*p.a+b*p.c)%r,(a*p.b+b*p.d)%r,(c*p.a+d*p.c)%r,(c*p.b+d*p.d)%r);
    }
}tree[maxn*5];
seg a[maxn];
void bulid(int rt,int l,int r)
{
    if(l==r)
    {
        tree[rt] = a[l];
        return ;
    }
    int mid = (l+r)>>1;
    bulid(rt<<1,l,mid);
    bulid(rt<<1|1,mid+1,r);
    tree[rt] = tree[rt<<1]+tree[rt<<1|1];
}
seg query(int rt,int L,int R,int l, int r)
{
    if(L<=l&&r<=R)
    {
        return tree[rt];
    }
    int mid = (l+r)>>1;
    seg tmp = seg(1,0,0,1);
    if(L<=mid) tmp = tmp + query(rt<<1,L,R,l,mid);  
    if(R>mid) tmp= tmp +query(rt<<1|1,L,R,mid+1,r);
    return tmp;
}

int main()
{
    int cas =1;
    while(~scanf("%d%d%d",&r,&n,&m))
    {
        if(r==0) exit(-1);
        for(int i = 1;i<=n;i++)
            scanf("%d%d%d%d",&a[i].a,&a[i].b,&a[i].c,&a[i].d);
        bulid(1,1,n);
        int l,r;
        int first = 1;
        for(int i = 1;i<=m;i++)
        {
            scanf("%d%d",&l,&r);
            seg ans = query(1,l,r,1,n);
            if(first)
            {
                if(cas)
                {
                    cas = 0;
                }else printf("\n");
                first = 0;
            }else printf("\n");
            printf("%d %d\n%d %d\n",ans.a,ans.b,ans.c,ans.d);
        }
    }
    return 0;
}

