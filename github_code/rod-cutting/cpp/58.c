/** Rod Cutting Problem using both bottomUp and TopDown dynamic programming, implemented by Arpan Pathak 
    Time Cimplexity O(l^2) where l is the length of the road**/
#include <iostream>
using namespace std;
int M[100];
int cut(int *length,int *price,int l)
{
    if(l==0) return 0;
    if(l==1) return price[0];
    if(M[l]!=0) return M[l];
    M[l]=0;
    for(int i=1;i<=l;i++)
    {
        M[l]=max(M[l],price[i-1]+cut(length,price,l-i));
    }
    return M[l];
}
int cutBottomUp(int *length,int *price,int l)
{
    for(int i=1;i<=l;i++)
    {
        M[i]=0;
        for(int k=1;k<=i;k++)
        {
            M[i]=max(M[i],price[k-1]+M[i-k]); // I can use max if I'll not have to print the lengths.....
        }
    }
    return M[l];
}
int main()
{
    int length[]={1,2,3,4,5,6,7,8}, price[]={1,5,8,9,10,17,17,20};
    cout<<cutBottomUp(length,price,5);

}
