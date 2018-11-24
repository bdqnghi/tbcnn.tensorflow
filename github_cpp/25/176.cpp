void swap(vector<int> &A,int l,int r)
{
    int temp=A[l];
    A[l]=A[r];
    A[r]=temp;
}

void allPermutations(vector<vector<int> > &res, vector<int> &A,int l,int r)
{
    if(l==r)
    res.push_back(A) ;
    else
    {
        for(int i=l;i<=r;i++)
        {
            swap(A,l,i);
            allPermutations(res,A,l+1,r);
            swap(A,l,i);
        }
    }
}

vector<vector<int> > Solution::permute(vector<int> &A) {
    vector<vector<int> > res;
    allPermutations(res,A,0,A.size()-1);
    return res;
}
