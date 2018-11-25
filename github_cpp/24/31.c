







#include "binarysearch.h"

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;


template <class T>
int BiSearch(T *v, int n, T key) {
    int left=0,right,mid;
    right=n-1;
    while (left<=right) {
        mid=(int)(left+right)/2;
        if (key==v[mid]) {
            return mid;
        }
        else if (key>v[mid]) left=mid+1;
        else right = mid -1;
    }
    return -1;
    
}

inline int RandI(int n)
{
    return rand()%n+1;
}

template <class T>
void Exchange(T &a, T &b)
{
    T temp;
    temp=a;
    a=b;
    b=temp;
}

template <class T>
void Bubble(T *v,int n) {
    for (int i=0; i<n; i++) {
        for (int j=n; j>i; j--) {
            if (v[j]<v[j-1]) {
                Exchange(v[j], v[j-1]);
            }
        }
    }
    return;
}


int main()
{
    int index,key=32;
    const int size=20;
    int data[size];
    for (int i=0; i<size; i++) {
        data[i]=RandI(85); 
    }
    cout << "\ndata's original value: \n";
    for (int i=0; i<size; i++) {
        cout <<setw(10)<<data[i];
        if (i%5==4) {
            cout<<endl;
        }
    }
    
    Bubble(data, size);
    cout<<"\n after buuble sort , the data's values are:\n";
    for (int i=0; i<size; i++) {
        cout <<setw(10)<< data[i];
        if (i%5==4) {
            cout <<endl;
        }
    }
    
    index=BiSearch(data, size, key);
    if (index>-1) {
        cout<<key<< " is located at " <<index+1 << "'s element ,\n";
    }
    else
        cout << "can;t find the key"<<endl;
    return 0;
}