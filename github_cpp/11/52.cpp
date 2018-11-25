#include <iostream>

 void max_heapify(int arr[],int i,int si){
 int largest, l=(2*i)+1, r=l+1;


 if(l<si&&arr[l]>arr[i])
    largest=l;
 else
    largest=i;

 if(r<si&&arr[r]>arr[largest])
    largest=r;

 if(largest!=i){
    int temp=arr[i];
    arr[i]=arr[largest];
    arr[largest]=temp;
    max_heapify(arr,largest,si);
}
}

 void build_max_heap(int arr[],int si){
 for(int i=(si/2)-1;i>=0;i--)
    max_heapify(arr,i,si);
 }

 void heap_sort(int arr[],int si){
 build_max_heap(arr,si);
 int sz=si;
 for(int i=si-1;i>0;i--){
    int temp=arr[i];
    arr[i]=arr[0];
    arr[0]=temp;
    sz--;
    max_heapify(arr,0,sz);
    }
 }

 int main()
 {
    int a[10]={4,1,3,2,16,9,10,14,8,7};
    int s=sizeof(a)/sizeof(int);
    heap_sort(a,s);
   for(int i=0;i<s;i++){
    std::cout<<a[i]<<" ";
 }
    return 0;
}
