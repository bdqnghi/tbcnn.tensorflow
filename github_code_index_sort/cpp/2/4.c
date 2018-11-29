//!MERGE-SORT(A,p,r)
/*
1   if p < r
2       q = !(p+r)/2!//向下取整
3       MERGE-SORT(A,p,q);
4       MERGE-SORT(A,q+1,r)
5       MERGE(A,p,q,r)
*/
//!    MERGE(A,p,q,r)
/*
1   n1 = q-p+1
2   n2 = r-q
3   let L[1...n1+1] and R[1...n2+1] be new array
4   for i=1 to n1
5       L[i] = A[p+i-1]
6   for j=1 to n2
7       R[j] = A[q+j]
8   L[n1+1] = +∞
9   R[n2+1] = +∞
10  i = 0
11  j = 0
12  for k=p to r
13  if L[i] < R[j]
14      A[k] = L[i]
15      i = i + 1
16  else A[k] = R[j]
17      j = j+1
17
*/
#include<vector>
#include<iostream>
using namespace std;

void Merge(vector<int> &A,int beg,int mid,int end)
{
    size_t lf_len = mid-beg+1;
    size_t rt_len = end-mid;

    vector<int> L,R;  //!two length are lf_length+1 , rt_length+1
    for(int i=1;i<=lf_len;++i)
        L.push_back(A[beg+i-1]);//!add A[beg...beg+lf_length] to L
    for(int j=1;j<=rt_len;++j)
        R.push_back(A[mid+j]);//! add A[mid+1...mid+1+rt_length] to R
    L.push_back(INT_MAX); //!哨兵
    R.push_back(INT_MAX);
    int j=0,i=0;
    for(int k=beg;k<=end;++k){//!must be <=,cause end also point element
        A[k] = R[j]<=L[i]?R[j++]:L[i++];
    }
}



void Merge_sort(vector<int> &A,int p,int r)
{
    //cout << " Merge_sort " << endl;
    if(p<r){
        int q = (p+r)/2;  //编译器自带向下取整
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
