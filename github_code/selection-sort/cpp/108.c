#include<iostream>
void swap(int *p1,int *p2);
using namespace std;
int main()
{
int n;
cout<<"enter the size of the array : ";
cin>>n;

int a[n];

cout<<"enter the array elements : ";

for(int i = 0; i < n; i++){
cin>>a[i];

}

int small,temp,p,check = 0;
for (int i = 0; i < n-1 ; i ++){
         check = 0;
         small = a[i];
               for(int j = i; j < n; j ++){

             if(small > a[j]){// p = j;
                               small = a[j];
                               p = j;
              check = 1; }}
     if(check){      swap(&a[i],&a[p]);
} }


cout<<"the sorted array is : ";

for(int i = 0; i < n; i++){
cout<<a[i]<<" ";

}

cout<<endl;


return 0;
}

void swap(int *ptr1, int *ptr2)

{
  int temp;
  temp = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 =temp;
}

