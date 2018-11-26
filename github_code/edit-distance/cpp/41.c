
//
//  Created by Amit 
//  Copyright © 2017 Amit. All rights reserved.
//


#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <valarray>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <bitset>
#include <functional>
#include <numeric>
#include <utility>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <complex>

using namespace std;



#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define For(it,c) for(__typeof(c.begin()) it=c.begin();it!=c.end();++it)


int main(){

	// fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	// freopen("B-small-attempt0.in","rt",stdin);
	// freopen("B.out","wt",stdout);

	int t;

	cin >> t;

	while(t--){

		int m,n;

		cin >> m >> n;

	    string s1,s2;

	    cin >> s1 >> s2;

	    //cout << m << " " << n << endl;

	    int dis[m+1][n+1];

	    dis[0][0] = 0;


	    for(int i = 1; i < m+1; i++){

	    		dis[i][0] = i;
	    }

	    for(int i = 1; i < n+1; i++){

	    		dis[0][i] = i;
	    }

	    for(int i = 1; i < m+1; i++){
	    	for(int j = 1 ; j < n+1; j++){
	    		if(s1[i-1] == s2[j-1]){
		    		dis[i][j] = min(dis[i-1][j-1],dis[i-1][j]+1);
		    		dis[i][j] = min(dis[i][j],dis[i][j-1] + 1);
		    	}
		    	else{
		    		dis[i][j] = min(dis[i-1][j-1] + 1,dis[i-1][j] + 1);
		    		dis[i][j] = min(dis[i][j],dis[i][j-1] + 1);
		    	}
	    	}
	    }

	    for(int i = 0; i < m; i++){
	    	for(int j = 0 ; j < n; j++){
	    		cout << dis[i][j] << " ";
	    	}
	    	cout << "\n";
	    }

	    cout << dis[m][n] << "\n";
	}

    return 0;

}