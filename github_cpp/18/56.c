#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int recur(vector<int> &B, int l, int r, vector<vector<long>> &dp, vector<vector<int>> &parent){
    if(l+1 >= r) return 0;

    if(dp[l][r] != -1) return dp[l][r];

    long ret = numeric_limits<long>::max();
    int bestind = -1;

    for(int i = l+1; i < r; ++i){
        long p = recur(B, l, i, dp, parent) + recur(B, i, r, dp, parent) + B[r] - B[l];

        if(p < ret){
            ret = p;
            bestind = i;
        }
    }

    parent[l][r] = bestind;

    return dp[l][r] = ret;
}

void buildsol(vector<vector<int>> &parent, vector<int> &ans, int l, int r){
    if(l+1 >= r) return;
    ans.push_back(parent[l][r]);
    buildsol(parent, ans, l, parent[l][r]);
    buildsol(parent, ans, parent[l][r], r);
}

vector<int> rodcut(int A, vector<int> &B){

    B.push_back(A);
    B.insert(B.begin(), 0);
    int n = B.size();
    vector<vector<long>> dp(n, vector<long>(n, -1));
    vector<vector<int>> parent(n, vector<int>(n, 0));

    int bestsol = recur(B, 0, n-1, dp, parent);
    vector<int> ans;
    buildsol(parent, ans, 0, n-1);
    return ans;
}

int main(){
    int A = 6;
    vector<int> B = {1, 2, 5};
    vector<int> ans = rodcut(A, B);

    for(int i : ans) cout<<i<<" ";
}
