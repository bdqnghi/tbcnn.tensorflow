// https://www.interviewbit.com/problems/rod-cutting/

vector<int> Solution::rodCut(int A, vector<int> &B) {
    vector<int> ans;
    if(B.size() == 0)   return ans;
    else{
        B.insert(B.begin(),0);
        B.push_back(A);
        int n = B.size();
        vector<vector<int> > dp(n, vector<int>(n, INT_MAX));
        vector<vector<int> > par(n, vector<int>(n, -1));
        
        int st, en, j;
        for(int l=2; l<n; l++){
            for(int i=0; i<n-l; i++){
                j = i+l;
                for(int k=i+1; k<j; k++){
                    int cost = dp[i][k]+dp[k][j]+(B[j]-B[i]);
                    if(cost < dp[i][j]){
                        dp[i][j] = cost;
                        par[i][j] = k;
                    }
                }
            }
        }

        
        stack<pair<int, int>> s;
        s.push(make_pair(0,n-1));
        while(!s.empty()){
            auto rod = s.top();
            s.pop();
            int k = par[rod.first][rod.second];
            if(k==-1)   continue;
            ans.push_back(B[k]);
            s.push(make_pair(k, rod.second));
            s.push(make_pair(rod.first, k));
        }
        return ans;
        
    }
}
