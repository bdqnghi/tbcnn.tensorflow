#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int rodCutting(int [],int);
int max(int ,int);

int main(void){
 int arr[]={1, 5, 6, 7, 3, 16, 16};
 int size=sizeof(arr)/sizeof(arr[0]);
 printf("%d",rodCutting(arr,size));
 return 0;

}

 int rodCutting(int price[],int n){

  int val[n+1];
  val[0]=0;
  int i,j;

  for(i=1;i<=n;i++){
   int max_val=-1;
   for(j=0;j<i;j++)
   max_val=max(max_val,price[j]+val[i-j-1]);
   val[i]=max_val;

  }
  return val[n];
 }

 int max(int a,int b){
  return (a>b)?a:b;
 }
