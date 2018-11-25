#include <iostream>
using namespace std;
int array[1000000+5];

void mergesort(int L, int R);

void merge(int lfirst, int rightfirst, int leftsecond, int rightsecond);

int main() {
    int z,n,k;
    cin >> z;
    while(z--) {
        cin >> n >> k;
        for ( int i = 0 ; i < n ; i++) {
            cin >> array[i];
        }
        mergesort(0,n-1);
        for ( int i = 0; i < n; i++ ) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
    return 0;
}

void mergesort(int L, int R) {
    if ( L >= R ) return;
    int s = (L+R)/2;
    mergesort(L,s);
    mergesort(s+1,R);
    merge(L, s, s+1, R);
}

void merge(int lfirst, int rightfirst, int leftsecond, int rightsecond) {
    int * newarray = new int[rightsecond-lfirst+5];
    int i = lfirst, j = leftsecond, k = 0;
    while( i<=rightfirst && j <=rightsecond) {
        if(array[i]>=array[j]){
            newarray[k++] = array[i++];
        }
        else {
            newarray[k++] = array[j++];
        }
    }
    while( i<= rightfirst) {
        newarray[k++] = array[i++];
    }
    while( j<= rightsecond) {
        newarray[k++] = array[j++];
    }
    k = 0;
    for ( int i = lfirst; i <= rightsecond; i++) {
        array[i] = newarray[k++];
    }
    delete [] newarray;
}