/*************************************************************************
	> File Name: b.cpp
	> Author: UnknownCUnknown
	> Mail: jsnjhcb@icloud.com
	> Created Time: 日  1/18 02:35:59 2015
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <list>
#include <string>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <climits>
using namespace std;
int top;
const long long N=100000000100;
struct trie{
    char c;
    int l,r,rk;
}tree[N];
void init(){
    top=1;
    memset(tree,0,sizeof tree[0]);
}
void insert (char *s,int rk=1){
    int i,rt;
    for(rt=0;*s;++s,rt=i){
        for(i=tree[rt].l;i;i=tree[i].r){
            if(tree[i].c==*s) break;
        }
        if(i==0){
            tree[top].r=tree[rt].l;
            tree[top].l=0;
            tree[top].c=*s;
            tree[top].rk=0;
            tree[rt].l=top;
            i=top++;
        }
    }
    tree[rt].rk=rk;
}
int profix(char *s){
    int rt=0,lv;
    for(lv=0;*s;++s,++lv){
        for(rt=tree[rt].l;rt;rt=tree[rt].r){
            if(tree[rt].c==*s) break;
        }
        if(rt==0) break;
    }
    return lv;
}
char s[1000010];
int main(){
    int T;
    scanf("%d",&T);
    for(int ca=1;ca<=T;++ca){
        int n;
        scanf("%d",&n);
        init();
        int ans=0;
        for(int i=0;i<n;++i){
            scanf("%s",s);
            int size=(int)strlen(s);
            int k=profix(s);
            if(k+1>size) ans+=size;
            else ans+=k+1;
            insert(s);
        }
        printf("Case #%d: %d\n",ca,ans);
    }
    return 0;
}
