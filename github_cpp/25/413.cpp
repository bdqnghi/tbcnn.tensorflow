Handle   : vipsharmavip 
Email id : vipsharmavip@gmail.com
Facebook : https://www.facebook.com/vipsharmavip


#include<bits/stdc++.h>
using namespace std;
int main(){
	    char x[101], y[101];
	    int line = 0;
	    while(scanf("%s %s",x, y) != EOF){
	    	 int n = strlen(x);
	    	 int m = strlen(y);
	    	 vector< int > v;
	    	 for(int i = 0 ; i < n ; ++i) v.push_back(0);
	    	 for(int i = 0 ; i < n ; ++i) v.push_back(1);
	    	 int found = 0;
	    	 if(line == 1)
	    	 cout << endl; 
	    	 cout << "[" << endl;
	    	 if(n == m){	    	 	
	    	 	n += n;
             do{
             	stack< int > S;
             	int sz = 0;
             	int idx = 0;
             	for(int i = 0 ; i < n  ; ++i){
             		if(v[i] == 0) S.push(x[idx++]);  else {
             			if(!S.size()) break;
             			char ch;
             			ch = S.top();
             			S.pop();
             			if(ch == y[sz]) ++sz; else break;
             		}
             	}
             	if(sz + sz == n){
             		for(int i = 0 ; i < n ; ++i ){
             			 if(v[i] == 0) cout << "i"; else 
             			 cout << "o";
             			 cout <<" ";
             			}
             			cout << endl;
             	}
             }
             while(next_permutation( v.begin(), v.end()));
         }
             cout << "]";
             line = 1;
 	    }
}
