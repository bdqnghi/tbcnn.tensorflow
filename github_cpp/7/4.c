



#include<vector>
#include<iostream>
using namespace std;

void Merge(vector<int> &A,int beg,int mid,int end)
{
    size_t lf_len = mid-beg+1;
    size_t rt_len = end-mid;

    vector<int> L,R;  
    for(int i=1;i<=lf_len;++i)
        L.push_back(A[beg+i-1]);
    for(int j=1;j<=rt_len;++j)
        R.push_back(A[mid+j]);
    L.push_back(INT_MAX); 
    R.push_back(INT_MAX);
    int j=0,i=0;
    for(int k=beg;k<=end;++k){
        A[k] = R[j]<=L[i]?R[j++]:L[i++];
    }
}



void Merge_sort(vector<int> &A,int p,int r)
{
    
    if(p<r){
        int q = (p+r)/2;  
        Merge_sort(A,p,q);
        Merge_sort(A,q+1,r);
        Merge(A,p,q,r);
    }
}

int main()
{
    vector<int> ivec = {42,5,68,46,46,81,6,12};
    size_t b = 0;
    Merge_sort(ivec,b,ivec.size()-1);
    for(auto unit:ivec){
        cout << unit << ",";
    }
    return 0;
}
