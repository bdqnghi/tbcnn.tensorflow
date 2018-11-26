// =====================================================================================
// 
//       Filename:  B.cpp
//        Created:  2017년 09월 24일 23시 36분 56초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll linf=0x3f3f3f3f3f3f3f3f;
struct Idt1{
	ll tree[400005];
	int sz;
	Idt1(){}
	Idt1(int n){
		sz=1;
		while(sz<n)
			sz*=2;
	}
	void update(int idx, int val){
		idx+=sz;
		tree[idx]=val;
		idx/=2;
		while(idx){
			tree[idx]=min(tree[idx*2], tree[idx*2+1]);
			idx/=2;
		}
	}
	ll query(int a, int b){
		a+=sz;
		b+=sz;
		ll ret=linf;
		while(a<=b){
			if(a&1)
				ret=min(ret, tree[a++]);
			if(!(b&1))
				ret=min(ret, tree[b--]);
			a/=2;
			b/=2;
		}
		return ret;
	}
};
struct Idt2{
	ll tree[400005];
	int sz;
	Idt2(){}
	Idt2(int n){
		sz=1;
		while(sz<n)
			sz*=2;
	}
	void update(int idx, int val){
		idx+=sz;
		tree[idx]=val;
		idx/=2;
		while(idx){
			tree[idx]=max(tree[idx*2], tree[idx*2+1]);
			idx/=2;
		}
	}
	ll query(int a, int b){
		a+=sz;
		b+=sz;
		ll ret=-linf;
		while(a<=b){
			if(a&1)
				ret=max(ret, tree[a++]);
			if(!(b&1))
				ret=max(ret, tree[b--]);
			a/=2;
			b/=2;
		}
		return ret;
	}
};
int n, p, q, r;
int arr[100005];
int main(){
	ll ans=-0x3f3f3f3f3f3f3f3f;
	cout<<ans<<endl;
	scanf("%d%d%d%d", &n, &p, &q, &r);
	Idt1 idt1(n);
	Idt2 idt2(n);
	for(int i=0;i<n;i++){
		scanf("%d", &arr[i]);
		idt1.update(i, arr[i]);
		idt2.update(i, arr[i]);
	}
	for(int i=0;i<n;i++){
		ll now=(ll)arr[i]*q;
		if(p<=0)
			now+=idt1.query(0, i)*p;
		else
			now+=idt2.query(0, i)*p;
		if(r<=0)
			now+=idt1.query(i, n-1)*r;
		else
			now+=idt2.query(i, n-1)*r;
		ans=max(ans, now);
	}
	printf("%lld\n", ans);
	return 0;
}

