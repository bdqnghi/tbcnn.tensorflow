/**
* E:\Dropbox\Code\Codemarshal\CodeMask Championship Qualification Round-01\B.cpp
* Created on: 2016-02-04-18.34.36, Thursday
* Verdict: Not Solved
* Author: Enamul Hassan
**/

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

#define SZ(a) ((ll)a.size())
#define sz 444005
#define pb push_back
#define pp pop_back()
#define all(a) a.begin(),a.end()
#define ll long long
#define cntbit(mask) __builtin_popcount(mask)
#define unify(a) stable_sort(a.begin(),a.end());a.resize(distance(a.begin(),unique(all(a))));
#define fread freopen("input.txt","r",stdin)
#define fwrite freopen("output.txt","w",stdout)
#define inf (1e18)
#define chng(a,b) a^=b^=a^=b;
#define clr(abc,z) memset(abc,z,sizeof(abc))
#define PI acos(-1)
#define pi 3.14159265358979323846264338327950288419716939937510
#define fr(i,a,b) for(i=a;i<=b;i++)
#define cspf printf("Case %d:", cas++);
#define csco cout<<"Case "<<cas++<<":\n";
#define mod 1000000007

#ifdef ENAM
#define deb(args...) {dbg,args; cerr<<endl;}
#else
#define deb(args...)
#endif

ll bigmod(ll sonkha,ll ghat,ll vag_const){ll vag_shesh=1;while(ghat>0){if(ghat%2==1){vag_shesh=(vag_shesh*sonkha)%vag_const;}ghat/=2;sonkha=(sonkha*sonkha)%vag_const;}return vag_shesh;}
ll inverse_mod(ll bivajok, ll vag_const){return bigmod(bivajok,vag_const-2, vag_const);}

using namespace std;

int tree[sz];
const int f = 110005;

int query(int idx)
{
       int sum=0;
       while(idx>0)
       {
             sum+=tree[idx];
             idx -= (idx & (-idx));
       }
       return sum;

}

void update(int idx, int x, int n)
{
    //cerr<<idx<<"-> Updated: "<<x<<":"<<n<<endl;
       while(idx<=n)
       {
             tree[idx]+=x;
             idx += (idx & (-idx));
       }


}

int main()
{
#ifdef ENAM
//      fread;
//  fwrite;
#endif // ENAM
	_
	int t,x,n, first, cas=1,lef,rig, mid;
	cin>>t;

	while(t--)
    {
        for(int i =0; i<sz; i++) tree[i]=0;
        tree[f]=0;
        csco
        first = 1;
        cin>>n;
        for(int i = 0; i<n; i++)
        {
            cin>>x;
            if(x==3){
                lef = 1,rig=f,first=1;
                while(lef<=rig)
                {
                    mid = (lef+rig)/2;
                    if(query(mid)==mid)
                    {
                        lef = mid+1;
                        first=max(first,lef);
                    }
                    else rig = mid-1;
                }

                cout<<first<<"\n";
            }
            else if(x==1){
                cin>>x;
                if(x>f) continue;
                if(query(x)==query(x-1)){update(x,1,f);}

            }
            else{
                cin>>x;
                if(x>f) continue;
                if(query(x)-query(x-1)==1)update(x,-1,f);
            }
           // cerr<<i<<":--------"<<endl;
            //for(int j = 1; j<12;j++) cerr<<query(j)<<" ";
            //cerr<<endl;
        }
    }

//    end = clock();
//    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
//    cerr<<"Time spent = "<<time_spent<<endl;

   return 0;
}
/**
1
10
1 5
1 8
1 7
1 6
1 5
1 4
1 3
1 2
1 1
3

1
9
1 8
1 7
1 6
1 5
1 4
1 3
1 2
1 1
3

1
11
1 5
1 8
1 7
1 6
1 5
1 4
1 3
1 2
1 1
2 5
3
*/
