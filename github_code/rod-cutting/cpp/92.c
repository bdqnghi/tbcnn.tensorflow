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
   if (n <= 0)  /**jokhn rod er katar sonkha 0 er soman othoba negative hoye jabe , mane rod tahkbe na tokhn kono value nai, tai return korbe 0 **/
        return 0;
   int m = INT_MIN;  /** INT_MIN dhore newa hoise karon minimum ekta value dorkar jeita theke katle profit pawa jab e **/


   for (int i = 0; i<n; i++)
         m = max(m, price[i] + rodcutting(price, n-i-1));  /** ei khane recursion kora hoise , recursion kor e protibar koy piece e kata jay seita ber kora hoy**/
              /** eta eki sathe oi piece gular total price hisab kor e **/
   return m; /** main function e call hoisilo tai main ke return korbe koto taka pawa jabe **/
}

int main()
{
    int arr[] = {1, 5, 8, 9, 10, 17, 17, 20}; /** ei array tay dewa ache kon piece rod er price koto , ei array ta always choto theke boro akare sort kore nite hbe**/
    int n = 8; /**total koto gula pice er price  */
    int result=rodcutting(arr, n);
    printf("Maximum Obtainable Value is %d\n",result);

    return 0;
}
