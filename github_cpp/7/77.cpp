






#include <iostream>
#include <vector>

using namespace std;

int sentinel = INT32_MAX; 

void mergeSort(vector<int> &T) {
    vector<int> L, R;
    L.assign(T.begin(), T.begin()+T.size()/2); 
    R.assign(T.begin()+T.size()/2, T.end()-1);  
    
    L.push_back(sentinel);
    R.push_back(sentinel);  
    
    if (L.size() != 2) { mergeSort(L); }
    if (R.size() != 2) { mergeSort(R); }  
    
    int m = 0, n = 0;
    for (int i = 0; i < L.size() + R.size() - 2; i++) {
        if (L[m] < R[n]) {  
            T[i] = L[m];
            m++;
        } else {
            T[i] = R[n];
            n++;
        }
    }
}

int main()
{
    int x;
    vector<int> A;
    while (cin >> x) {
        A.push_back(x);
    }
    A.push_back(sentinel);
    mergeSort(A);
    A.pop_back();  
    for (vector<int>::iterator it = A.begin(); it != A.end(); ++it) {
        cout << *it << " ";
    }
    
    return 0;
}




