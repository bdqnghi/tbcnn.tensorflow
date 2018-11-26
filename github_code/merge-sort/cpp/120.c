#include <bits/stdc++.h>
#define MAX 50

void mergeSort(int arr[],int low,int mid,int high)
{

    int i,m,k,l;
    int temp[MAX];

    l=low;
    i=low;
    m=mid+1;

    while((l<=mid)&&(m<=high)){

         if(arr[l]<=arr[m]){
             temp[i]=arr[l];
             l++;
         }
         else{
             temp[i]=arr[m];
             m++;
         }
         i++;
    }

    if(l>mid){
         for(k=m;k<=high;k++){
             temp[i]=arr[k];
             i++;
         }
    }
    else{
         for(k=l;k<=mid;k++){
             temp[i]=arr[k];
             i++;
         }
    }

    for(k=low;k<=high;k++){
         arr[k]=temp[k];
    }
}
void Partition(int arr[],int low,int high)
{

    int mid;

    if(low<high){
         mid=(low+high)/2;
         Partition(arr,low,mid);
         Partition(arr,mid+1,high);
         mergeSort(arr,low,mid,high);
    }
}

int main()
{

    int arr[MAX],i,n;

    printf("Number of elements: \n");
    scanf("%d",&n);

    printf("Enter elements : \n");
    for(i=0;i<n;i++){
         scanf("%d",&arr[i]);
    }

    Partition(arr,0,n-1);

    printf("Sorted:  \n");
    for(i=0;i<n;i++){
         printf("%d ",arr[i]);
    }

   return 0;
}






