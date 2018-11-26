#include<iostream>
using namespace std;

int rod_cutting(int* price_array,int n)
{
int without_cutting_price=price_array[n-1];
int after_cutting_price=without_cutting_price;
if(n==1)
return(price_array[n-1]);
for(int i=1;i<n;i++)
{
int current_price=rod_cutting(price_array,n-i)+rod_cutting(price_array,i);
if(current_price>after_cutting_price)
after_cutting_price=current_price;
}
return (after_cutting_price);
}

int rod_cutting_dp(int* price_array,int n)
{
int dp[n];
int current;
for(int i=0;i<n;i++)
{
current=price_array[i];
if(i==0)
dp[i]=price_array[i];
else if(i==1)
{
if(dp[i-1]+dp[i-1]>current)
dp[i]=dp[i-1]+dp[i-1];
}
else
{
for(int j=0;j<=(i/2+1);j++)
{
if(price_array[j]+price_array[i-j]>current)
dp[i]=price_array[j]+price_array[i-j];
}
}
}
return dp[n-1];
}

int main()
{
    int arr[] = {3, 5, 8, 9, 10, 17, 17, 20};
    int size = sizeof(arr)/sizeof(arr[0]);
    cout<<"Maximum Obtainable Value is "<<rod_cutting(arr, size);
    //getchar();
    return 0;
}
