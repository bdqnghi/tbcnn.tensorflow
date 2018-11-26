/* Introducation of Algorithm
 * Capter 2 Merge-Sort
 *
 * Time: 2017-3-3   Author: greyCimath
 *
 * Merge(A,p,q,r)
 * ---------------------------------------------------
 *  n1 = q - p + 1
 *  n2 = r - q
 *  let L[1...n1 + 1] and R[1...n2 + 1] be new arrays
 *  for i = 1 to n1
 *      L[i] = A[p + i - 1]
 *  for j = 1 to n2
 *      R[j] = A[q + j]
 *  L[n1 + 1] = Inf
 *  R[n2 + 1] = Inf
 *  i = 1; j = 1;
 *  for k = p to r
 *      if L[i] <= R[j]
 *          A[k] = L[i]
 *          i = i + 1
 *      else
 *          A[k] = R[j]
 *          j = j + 1
 * ---------------------------------------------------
 *  Merge-Sort(A,p,r)
 * ---------------------------------------------------
 *  if p < r
 *      q = floor((p + r) / 2)
 *      Merge-Sort(A,p,q)
 *      Merge-Sort(A,q + 1,r)
 *      Merge(A,p,q,r)
 * ---------------------------------------------------
 */

#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

const int MaxNum = 9999999;

void Merge(vector<int> &A,int &p,int &q,int &r){
    vector<int> L;  vector<int> R;
    int n1 = q - p + 1;
    int n2 = r - q;
    for(int i = 0;i < n1;i++){
        L.push_back(A[p + i - 1]);
    }
    for(int j = 0;j < n2;j++){
        R.push_back(A[q + j]);
    }
    L.push_back(MaxNum);
    R.push_back(MaxNum);
    int i = 0; int j = 0;
    for(int k = p;k < r;k++){
        if(L[i] <= R[j]){
            A[k] = L[i];
            i = i + 1;
        }else{
            A[k] = R[j];
            j = j + 1;
        }
    }
}

void Merge_Sort(vector<int> &A,int &p,int &r){
    int q = 0;
    if(p < r){
        q = floor((p + r) / 2);
        Merge_Sort(A,p,q);
        q = q + 1;
        Merge_Sort(A,q,r);
        Merge(A,p,q,r);
    }
}

int main(){
    vector<int> A;  int tmp = 0;
    int p = 0;   int r = 0;  int q = 0;
    cout << "Please input a vector(end as #):" << endl;
    while(cin >> tmp){
        A.push_back(tmp);
    }
    r = A.size();
    Merge(A,0,r);
    for(int i = 0;i < A.size();i++){
        cout << A[i] << " ";
    }
    cout << endl;

    return 0;
}
