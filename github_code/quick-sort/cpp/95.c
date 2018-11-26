/*
Quick-Sort
Complexity
Best case:O(n)
Avg case:O(n^2)
worst case:O(n^2)
*/

#include<iostream>
using namespace std;

int partition(int a[],int p,int q){
    int b,i,t;
    b=a[p];
    i=p;
    for(int j=p+1;j<q;j++){
            if(a[j]<b){
                       t=a[j];
                       a[j]=a[i];
                       a[i]=t;
                       }
            }
    t=a[i];
    a[i]=a[p];
    a[p]=t;
    return i;
    }
    

void quickSort(int a[],int p,int q){
     int r;
     if(p<q){
             r=partition(a,p,q);
             quickSort(a,p,r);
             quickSort(a,r+1,q);
             }
     }
       
int main(){
    system("cls");
    int a[20],size;
    cout<<"\nEnter the size of array:";
    cin>>size;
    cout<<"\nEnter the values:";
    for(int i=0;i<size;i++){
            cin>>a[i];
            }
    cout<<"\nThe Arary u entered is:";
    for(int i=0;i<size;i++){
            cout<<"-->"<<a[i];
            }
    quickSort(a,0,size);
    cout<<"\nThe sorted array is:";
    for(int i=0;i<size;i++){
            cout<<"-->";
            cout<<a[i];
            }
    system("pause");
    return 0;
    }
