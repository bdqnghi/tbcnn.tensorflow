//线段树 
//可以计算长度和线段数 
//可以处理加入边和删除边不同的情况 
//insert_seg和del_seg用于加入边删除边
//seg_len求长度,seg_cnt求线段数 
//id传根节点(一律为1) 
//ll,rr传线段(端点)
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using std::sort;
#define N 10110

struct line{ int x,y1,y2,tag; }l[N<<1];
struct seg_tree
{
	int l,r,col,len,cnt,bl,br; 
}segt[N<<2];
//col重叠线段数,０表示无线段覆盖
//len该段上的已有线段总长度
//cnt该段上不连续不重叠的线段数
//bl,br该段上左右端是否有线段覆盖

inline int L(int i){ return i<<1; }
inline int R(int i){ return (i<<1)|1; }
inline int min(int a,int b){ return a<b?a:b; }
inline int max(int a,int b){ return a>b?a:b; }
inline int length(int l,int r){ return coor[r]-coor[l]; }

int coor[N<<1],ttl,top;
//coor离散化坐标数组

int get_id(int x)
{
	int l,r,m;
	for(l=1,r=top; l<=r; )
	{
		m=(l+r)>>1;
		if(coor[m]<x)
			l=m+1;
		else if(coor[m]>x)
			r=m-1;
		else
			return m;
	}
	return -1; //impossible
}

void create_tree(int id,int l,int r)
{
	int m=(l+r)>>1;
	segt[id].l=l,segt[id].r=r;
	segt[id].col=segt[id].len=0;
	segt[id].bl=segt[id].br=segt[id].cnt=0;
	if(r-l<=1)
		return ;
	create_tree(L(id),l,m);
	create_tree(R(id),m,r);
}

void update(int id,int l,int r)
{
	if(segt[id].col||r==l)
	{
		segt[id].len=length(l,r);
		segt[id].cnt=segt[id].bl=segt[id].br=1;
	}
	else
	{
		segt[id].len=segt[L(id)].len+segt[R(id)].len;
		segt[id].cnt=segt[L(id)].cnt+segt[R(id)].cnt;
		if(segt[L(id)].br&&segt[R(id)].bl)
			segt[id].cnt--;
		segt[id].bl=segt[L(id)].bl;
		segt[id].br=segt[R(id)].br;
	}
}

//往id上加[ll,rr]的线段
void insert_seg(int id,int ll,int rr)
{
	int l=segt[id].l,r=segt[id].r,m=(l+r)>>1;
	if(ll==l&&rr==r)
		segt[id].col++;
	else
	{
		if(ll<m)
			insert_seg(L(id),ll,min(m,rr));
		if(rr>m)
			insert_seg(R(id),max(ll,m),rr);
		if(segt[L(id)].col&&segt[R(id)].col)
		{
			segt[L(id)].col--;
			update(L(id),l,m);
			segt[R(id)].col--;
			update(R(id),m,r);
			segt[id].col++;
		}
	}
	update(id,l,r);
}

//往id上减[ll,rr]的线段
void del_seg(int id,int ll,int rr)
{
	int l=segt[id].l,r=segt[id].r,m=(l+r)>>1;
	if(ll==l&&rr==r)
		segt[id].col--;
	else if(segt[id].col)
	{
		segt[id].col--;
		if(ll>l)
			insert_seg(id,l,ll);
		if(rr<r)
			insert_seg(id,rr,r);
	}
	else
	{
		if(ll<m)
			del_seg(L(id),ll,min(m,rr));
		if(rr>m)
			del_seg(R(id),max(ll,m),rr);
	}
	update(id,l,r);
}

//求id上[ll,rr]范围内覆盖的线段长度
int seg_len(int id,int ll,int rr)
{
	int l=segt[id].l,r=segt[id].r,m=(l+r)>>1,ret=0;
	if(segt[id].col||(ll==l&&rr==r))
		return segt[id].len;
	if(ll<m)
		ret+=seg_len(L(id),ll,min(rr,m));
	if(rr>m)
		ret+=seg_len(R(id),max(ll,m),rr);
	return ret;
}

//求id上[ll,rr]范围内线段的段数
int seg_cnt(int id,int ll,int rr)
{
	int l=segt[id].l,r=segt[id].r,m=(l+r)>>1,ret=0;
	if(segt[id].col)
		return 1;
	if(l==ll&&r==rr)
		return segt[id].cnt;
	if(ll<m)
		ret+=seg_cnt(L(id),ll,min(rr,m));
	if(rr>m)
		ret+=seg_cnt(R(id),max(ll,m),rr);
	return ret;
}
