#include<bits/stdc++.h>
using namespace std;
// A utility function to get the maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Returns the best obtainable price for a rod of length n and
price[] as prices of different pieces */
int cutRod(int price[], int n)
{
    if (n <= 0)
        return 0;
    int max_val = INT_MIN;
// Recursively cut the rod in different pieces and compare different
// configurations
    for (int i = 0; i<n; i++)
    {
        max_val = max(max_val, price[i] + cutRod(price, n-i-1));

        cout<<i<<" "<<max_val<<endl;
    }
    cout<<endl<<endl;
    return max_val;
}

/* Driver program to test above functions */
int main()
{
    int arr[] = {1, 5, 8, 9};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Maximum Obtainable Value is %d\n", cutRod(arr, size));
    getchar();
    return 0;
}
