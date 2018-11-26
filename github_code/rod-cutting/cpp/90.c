#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// price array
//int p[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
int max_size = 40;
vector<int> p(max_size);
vector<int> r(max_size, -1);

// top down with memoization
int optimizeRod(int n){
    if(r[n-1] >= 0) {
        return r[n-1];
    }
    
    int m = p[n - 1];
    for(int i = 1; i < n; ++i){
        m = max(m, optimizeRod(i) + optimizeRod(n - i));
    }
    
    r[n-1] = m;
    return m;
}

// bottom up
int optimizeRodBottomUp(int n){
    if(r[n-1] >= 0) {
        return r[n-1];
    }
    
    int mx = 0;
    for(int i = 1; i <= n; ++i){
        int m = p[i - 1];
        for(int j = 1; j < i; ++j){
            m = max(m, optimizeRodBottomUp(j) + optimizeRodBottomUp(i - j));
        }
        
        mx = max(mx, m);
    }
    
    r[n-1] = mx;
    return mx;
}

int main(){
    for(int i = 0; i < p.size(); ++i){
        p[i] = i + 1;
    }
    
    cout << optimizeRodBottomUp(18) << endl;
    
    return 0;
}