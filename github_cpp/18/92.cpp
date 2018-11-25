#include<stdio.h>
#include<limits.h>


int max(int a, int b)
{
    if(a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}


int rodcutting(int price[], int n)
{
   if (n <= 0)  
        return 0;
   int m = INT_MIN;  


   for (int i = 0; i<n; i++)
         m = max(m, price[i] + rodcutting(price, n-i-1));  
              
   return m; 
}

int main()
{
    int arr[] = {1, 5, 8, 9, 10, 17, 17, 20}; 
    int n = 8; 
    int result=rodcutting(arr, n);
    printf("Maximum Obtainable Value is %d\n",result);

    return 0;
}
