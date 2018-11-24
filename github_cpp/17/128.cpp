#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<functional>
#include<math.h>
#include<assert.h>
#include<stdarg.h>
#include<time.h>
#include<limits.h>
#include<ctype.h>
#include<string>
#include<map>
#include<set>
#include<queue>
#include<algorithm>
#include<vector>
#include<iostream>
#include<sstream>
using namespace std;

const int N=1000000,// maximum number of nodes in the suffix tree
INF=1000000000 ;// constant " infinity"
string a; // input string , for which it is necessary to construct a tree
int t[N][26],// array of transitions (the state , the letter )
l[N], // ​​Left
r[N], // ​​and right boundaries of the substring of a, corresponding to the edge entering the vertex
p[N], // ​​ancestor top
s[N], // ​​suffix link
tv, // ​​vertex of the current suffix (if we have the middle ribs , the lower vertex of the edge )
tp, // ​​position in the row corresponding to the place on the edge ( from l [tv] to r [tv] inclusive)
ts, // ​​number of vertices
la; // current character string

void ukkadd(int c)
{// append to the tree symbol c
suff:; // will come here after each move to the suffix ( and re-add the character)
if(r[tv]<tp)
{// check if we did not come out beyond the current edge
// If it got out, we find the following edge . If it is not - create a sheet and a trailer to a tree
if(t[tv][c]==-1)
{
    t[tv][c]=ts;
    l[ts]=la;
    p[ts++]=tv;
    tv=s[tv];
    tp=r[tv]+1;
    goto suff;
}
tv=t[tv][c];
tp=l[tv]; // otherwise, just move on to the next edge
}
if(tp==-1||c==a[tp]-'a')
tp++;
else
{// if the letter on the edge coincides with c that are on the edge , otherwise
// Share on the edge of two. Middle - top ts
l[ts]=l[tv];
r[ts]=tp-1 ;
p[ts]=p[tv];
t[ts][a[tp]-'a']=tv;
// Set list ts +1. It corresponds to a transition with c.
t[ts][c]=ts+1;
l[ts+1]=la;
p[ts+1]=ts;
// Update the parameters of the current node . Do not forget about the transition from an ancestor to the tv ts.
l[tv]=tp;
p[tv]=ts;
t[p[ts]][a[l[ts]]-'a']=ts;
ts+=2 ;
// Prepare for the descent : up to the edge and went on suffix link .
// Tp will celebrate where we are in the current suffix .
tv=s[p[ts-2]];
tp=l[ts-2] ;
// While the current suffix is ​​not over, we stamp down
while(tp<=r[ts-2])
{
    tv=t[tv][a[tp]-'a'];
    tp+=r[tv]-l[tv]+1;
}
// If we come to the top, then put it in a suffix link , otherwise we put in ts
// ( In fact on track . Iteration we create ts).
if(tp==r[ts-2]+1)
s[ts-2]=tv;
else
s[ts-2]=ts;
// Set tp to the new edge and are going to add a letter suffix .
tp=r[tv]-(tp-r[ts-2])+2;
goto suff;
}
}

void build ()
{
ts=2 ;
tv=0 ;
tp=0 ;
fill(r,r+N,(int)a.size()-1);
// Initialize the data for the root of the tree
s[0]=1;
l[0]=1;
r[0]=1;
l[1]=-1;
r[1]=-1;
memset(t,-1,sizeof t);
fill(t[1],t[1], 26.0) ;
// Add text to the tree , one letter
for(la=0;la<(int)a.size(); ++la)
ukkadd(a[la]-'a');
}
int main()
{
    cin>>a;
    build();
}
