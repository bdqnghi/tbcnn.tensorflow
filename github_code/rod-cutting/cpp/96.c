#include <bits/stdc++.h>
using namespace std;

typedef  long long lli;
typedef vector< long long int > vi;
typedef  double d;
typedef  pair<lli,pair<lli,lli> >  pipii;
#define bg begin()
#define rbg rbegin()
#define ren rend()
#define en end()
#define f first
#define s second
#define For(ii,aa,bb) for(lli ii=aa;ii<=bb;++ii)
#define Rof(ii,aa,bb) for(lli ii=aa;ii>=bb;--ii)
#define pb push_back
#define minf(a,b,c) min(min(a,b),c)
#define maxf(a,b,c) max(max(a,b),c)
#define mp make_pair
#define error(args...) { vector<string> _v = split(#args, ','); err(_v.begin(), args); }

vector<string> split(const string& s, char c) {
	vector<string> v;
	stringstream ss(s);
	string x;
	while (getline(ss, x, c))
		v.emplace_back(x);
	return move(v);
}

void err(vector<string>::iterator it) {}
template<typename T, typename... Args>
void err(vector<string>::iterator it, T a, Args... args) {
	cerr << it -> substr((*it)[0] == ' ', it -> length()) << " = " << a << '\n';
	err(++it, args...);
}
/// ********* debug template bt Bidhan Roy *********

template < typename F, typename S >
ostream& operator << ( ostream& os, const pair< F, S > & p ) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template < typename T >
ostream &operator << ( ostream & os, const vector< T > &v ) {
    os << "{";
    typename vector< T > :: const_iterator it;
    for( it = v.begin(); it != v.end(); it++ ) {
        if( it != v.begin() ) os << ", ";
        os << *it;
    }
    return os << "}";
}

template < typename T >
ostream &operator << ( ostream & os, const set< T > &v ) {
    os << "[";
    typename set< T > :: const_iterator it;
    for ( it = v.begin(); it != v.end(); it++ ) {
        if( it != v.begin() ) os << ", ";
        os << *it;
    }
    return os << "]";
}

template < typename F, typename S >
ostream &operator << ( ostream & os, const map< F, S > &v ) {
    os << "[";
    typename map< F , S >::const_iterator it;
    for( it = v.begin(); it != v.end(); it++ ) {
        if( it != v.begin() ) os << ", ";
        os << it -> first << " = " << it -> second ;
    }
    return os << "]";
}

#define deb(x) cerr << #x << " = " << x << endl;



// lli rodcutting(lli n,lli p[],lli r[],lli ck[]){
//     if(r[n]!=-1) return r[n];
    
//     if(r[n]==-1){
//         lli maxi=INT_MIN;
//         lli cnt;
//         For(k,1,n){
//             if(r[n-k]!=-1){
//                 if(maxi<p[k]+r[n-k]) cnt=k;
//                 maxi=max(maxi,p[k]+r[n-k]);
//             }
                
//             else{
//                 lli t=rodcutting(n-k,p,r,ck);
//                 if(maxi<p[k]+t) cnt=k;
//                 maxi=max(maxi,t);

//             }
//         }
//         ck[n]=cnt;
//         r[n]=maxi;
//         return maxi;
//     }
// }

lli rodcuttingbottom(lli n,lli p[],lli r[],lli ck[]){
    For(l,1,n){
        lli maxi=INT_MIN;
        lli cnt;
        For(k,1,l){
            if(maxi<p[k]+r[l-k]) cnt=k;
            maxi=max(maxi,p[k]+r[l-k]);
            error(maxi);
        }
        ck[l]=cnt;
        r[l]=maxi;
    }
    return r[n];
}

int main(){
    lli n;
    cout<<"enter the value of n:"<<endl;
    cin>>n;
    lli p[n+1],r[n+1],ck[n+1];
    cout<<" enter the values of prices"<<endl;
    p[0]=0;
    r[0]=0;
    memset(ck,0,sizeof(ck));
    For(i,1,n){
        r[i]=-1;
    }
    For(i,1,n){
        cin>>p[i];
    }
    cout<<"maximum value is:  "<<rodcuttingbottom(n,p,r,ck)<<endl;
    cout<<"cut points:"<<endl;
    For(i,1,n){
        cout<<ck[i]<<" ";
    }
}
