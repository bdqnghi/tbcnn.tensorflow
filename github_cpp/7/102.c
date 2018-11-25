




#include<iostream>
using std::cout;
using std::endl;

void merge(int *,int,int,int);
void merge_sort(int *,int,int);

int main(){
    int A[9] = {5,2,4,7,1,3,2,6,8};
    merge_sort(A,0,8);
    for (int i : A) {
        cout << i << " ";
    }
    cout<<endl;
    return 0;
}

void merge_sort(int *A, int p, int r) {
    if(p < r){
        int q =( p + r ) / 2;
        merge_sort(A,p,q);
        merge_sort(A,q+1,r);
        merge(A,p,q,r);
    }
}

void merge(int *A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    auto *L = new int [n1+1];
    for (int i = 0; i < n1; ++i) {
        L[i] = A[p+i];
    }

    auto *R = new int [n2+1];
    for (int j = 0; j < n2; ++j) {
        R[j] = A[q+j+1];
    }

    
    
    L[n1] = 65535;
    R[n2] = 65535;

    int i = 0;
    int j = 0;
    for (int k = p; k < r+1; ++k) {
        if(L[i]<R[j]){
            A[k] = L[i];
            i++;
        } else{
            A[k] = R[j];
            j++;
        }
    }
    
    delete []L;
    delete []R;
}
