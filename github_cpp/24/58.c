#include <iostream>
#include <stdio.h>

using namespace std;

int bsearch(int A[],int l,int r, int target){
    while( l < r ){
        int m = (l+r)/2;
        if(A[m] > target){
            r = m;
        }else if(A[m] < target){
            l = m + 1 ;
        }else{
            return m;
        }
    }
    return -1;
}

int bsearch2(int A[],int l,int r, int target){
    r = r - 1;
    while( l <= r ){
        int m = (l+r)/2;
        if(A[m] > target){
            r = m - 1;
        }else if(A[m] < target){
            l = m + 1 ;
        }else{
            return m;
        }
    }
    return -1;
}

int main(int argc, char const* argv[])
{
    int (*search)(int A[],int ,int ,int );
    search = bsearch2;
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11};
    printf("%d\n", search(arr, 0, 11, 1));
    printf("%d\n", search(arr, 0, 11, 11));
    printf("%d\n", search(arr, 0, 11, -11));
    printf("%d\n", search(arr, 0, 11, 1212));
    return 0;
}
