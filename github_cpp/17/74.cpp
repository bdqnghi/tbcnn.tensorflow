
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;

const int inf = ;
const int N = 100005;
int a[N];
struct node {
	int l, r;
	int add;
	int sum;
	int mx; 
	int mn; 
}tree[N * 4];
void pushup(int index) {
	tree[index].sum = tree[index << 1].sum + tree[index << 1 | 1].sum;
	tree[index].mx = max(tree[index << 1].mx, tree[index << 1 | 1].mx);
	tree[index].mn = min(tree[index << 1].mn, tree[index << 1 | 1].mn);
}
void pushdown(int index) {
	
	if (tree[index].add) {
		
		
		
		
		
		
		
		
		
		
		
		tree[index << 1].sum += (tree[index << 1].r - tree[index << 1].l + 1)*tree[index].add;
		tree[index << 1 | 1].sum += (tree[index << 1 | 1].r - tree[index << 1 | 1].l + 1)*tree[index].add;
		tree[index << 1].mx += tree[index].add;
		tree[index << 1 | 1].mx += tree[index].add;
		tree[index << 1].mn += tree[index].add;
		tree[index << 1 | 1].mn += tree[index].add;
		tree[index << 1].add += tree[index].add;
		tree[index << 1 | 1].add += tree[index].add;
		tree[index].add = 0;
	}
}
void build(int l, int r, int index) {
	tree[index].l = l;
	tree[index].r = r;
	tree[index].add = 0;
	if (l == r) { tree[index].mn = tree[index].mx = tree[index].sum = a[l]; return; }
	int mid = (l + r) >> 1;
	build(l, mid, index << 1);
	build(mid + 1, r, index << 1 | 1);
	pushup(index);
}
void update(int l, int r, int index, int val) {
	if (l <= tree[index].l && r >= tree[index].r) {
		
		
		
		
		
		
		tree[index].sum += (tree[index].r - tree[index].l + 1)*val;
		tree[index].mn += val;
		tree[index].mx += val;
		tree[index].add += val;
		return;
	}
	pushdown(index);
	int mid = (tree[index].l + tree[index].r) >> 1;
	if (l <= mid) update(l, r, index << 1, val);
	if (r > mid) update(l, r, index << 1 | 1, val);
	pushup(index);
}
int query(int l, int r, int index) {
	if (l <= tree[index].l && r >= tree[index].r) {
		
		return tree[index].mx;
		
	}
	pushdown(index);
	int mid = (tree[index].l + tree[index].r) >> 1;
	int ans = 0;
	int Max = 0;
	int Min = inf;
	if (l <= mid) {
		
		
		Min = min(query(l, r, index << 1), Min);
	}
	if (r > mid) {
		
		
		Min = min(query(l, r, index << 1 | 1), Min);
	}
	
	
	return Min;
}
