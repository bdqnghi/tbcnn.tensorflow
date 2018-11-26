/*
Dynamic Programming | Set 13 (Cutting a Rod)
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int mn[9]={0};
int CuttingRodRecursiveTDDP(int arr[],int n)
{
    if(mn[n]>0)
    {
        return mn[n];
    }
    else
    {
        int temp=0;
        for(int i=0;i<n;i++)
        {
            temp=max(temp,arr[i]+CuttingRodRecursiveTD(arr,n-i-1));
        }
        mn[n]=temp;
        return temp;
    }
}
int CuttingRodRecursive(int arr[],int n)
{
    int temp=0;
    for(int i=0;i<n;i++)
    {
        temp=max(temp,arr[i]+CuttingRodRecursive(arr,n-i-1));
    }
    return temp;
}
int CuttingRodBottomUpDP(int arr[],int n)
{
    int temp=0;
    int val[n+1]={0};
    for (int i=1;i<=n;i++)
    {
        for(int j=0;j<i;j++)
        {
            
            temp=max(temp,arr[j]+val[i-j-1]);
        }
        val[i]=temp;
    }
  
    return val[n];
}
int main() {
int arr[] = {1, 5, 8, 9, 10, 17, 17, 20};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Maximum Obtainable Value is %d\n", CuttingRod(arr, size));
        printf("Maximum Obtainable Value is %d\n", CuttingRodRecursive(arr, size));
        printf("Maximum Obtainable Value is %d\n", CuttingRodRecursiveTD(arr, size));

    return 0;
}
