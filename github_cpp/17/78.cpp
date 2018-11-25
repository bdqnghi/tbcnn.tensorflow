
#include<cstdio>
#include<cstring>
#include<iostream>
#define ll long long 
#define Mem0(x) memset(x,0,sizeof(x))
const int N=1e6+10,M=35;
using namespace std;
struct node{
  ll col;
  int add;
}tree[N<<2];
bool flag[M];

void push_up(int t){
  tree[t].col=tree[t<<1].col | tree[t<<1|1].col;
  
}

void push_down(int t){
  
  if(tree[t].add==-1)return;
  tree[t<<1].col=0;
  tree[t<<1].col|=(1<<tree[t].add);
  tree[t<<1|1].col=0;
  tree[t<<1|1].col|=(1<<tree[t].add);
  tree[t<<1].add=tree[t<<1|1].add=tree[t].add;
  tree[t].add=-1;
}

void build(int t,int L,int R){
  
  tree[t].add=-1;
  if(L==R){
    tree[t].col=2;
    return;
  }
  int mid=(L+R)>>1;
  build(t<<1,L,mid);
  build(t<<1|1,mid+1,R);
  push_up(t);
}



void update(int t,int L,int R,int l,int r,int c){
  
  if(l<=L && R<=r){
    
    tree[t].col=0;
    tree[t].col|=(1<<c);
    tree[t].add=c;
    return;
  }
  push_down(t);
  int mid=(L+R)>>1;
  if(l<=mid)update(t<<1,L,mid,l,r,c);
  if(r>mid)update(t<<1|1,mid+1,R,l,r,c);
  push_up(t);
}

void query(int t,int L,int R,int l,int r){
  
  if(l<=L && R<=r){
    
    for(int i=0;i<30;++i){
      flag[i]|=(tree[t].col & (1<<i));
      
    }
    return;
  }
  push_down(t);
  int mid=(L+R)>>1;
  if(l<=mid)query(t<<1,L,mid,l,r);
  if(r>mid)query(t<<1|1,mid+1,R,l,r);
}

int main(){
  int n,m,l,r,c,i;
  char op[5];
  bool first;
  while(~scanf("%d%d",&n,&m)&&(n||m)){
    build(1,1,n);
    while(m--){
      scanf("%s%d%d",op,&l,&r);
      
      if(op[0]=='P'){
        scanf("%d",&c);
        
        update(1,1,n,l,r,c-1);
      }else{
        first=1,Mem0(flag);
        query(1,1,n,l,r);
        for(i=0;i<30;++i)
          if(first && flag[i])
            printf("%d",i+1),first=0;
          else if(flag[i])printf(" %d",i+1);
        puts("");
      }
    }
  }
}
