

typedef long long int ll;
 
vector<int> res, cuts;
vector<vector<ll> > dp;
vector<vector<int> > parent;
 
ll solve(int l, int r)
{
    if((l+1)>=r)
        return 0;
    if(dp[l][r] != -1)
        return dp[l][r];
 
    ll ans = LLONG_MAX;
    int ind = -1;
 
    for(int i=l+1;i<r;i++)
    {
        ll temp = cuts[r] - cuts[l] + solve(l,i) + solve(i,r);
 
        if(ans > temp)
        {
            ans = temp;
            ind = i;
        }
    }
 
    parent[l][r] = ind;
    return dp[l][r] = ans;
}
 
void form(int l, int r)
{
    if((l+1)>=r)
        return;
 
    res.push_back(cuts[parent[l][r]]);
 
    form(l, parent[l][r]);
    form(parent[l][r], r);
}
 
vector<int> Solution::rodCut(int A, vector<int> &B)
{
    if(B.size()==0 || B.size()==1)
        return B;
 
    B.push_back(A);
    B.insert(B.begin(), 0);
 
    dp.clear();
    parent.clear();
    cuts.clear();
    res.clear();
 
    int n = B.size();
    cuts = B;
 
    dp.resize(n, vector<ll>(n, -1));
    parent.resize(n, vector<int>(n));
 
    solve(0,n-1);
 
    form(0,n-1);
 
    return res;
}