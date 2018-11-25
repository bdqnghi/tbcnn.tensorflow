

#include<bits/stdc++.h>
using namespace std;
void iterativeReverse(char *str,int m, int n)
{
        int l = m;
        int r = n-1;
        while(l < r)
        {
            char ch = str[l];
            str[l] = str[r];
            str[r] = ch;
            l++;r--;
        }
}


void recursiveReverse(char *str,int start, int end)
{
    if(start>=end)
        return;
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    recursiveReverse(str, start+1, end-1);
}


int main()
{
    char str[] = "String";
    int n = strlen(str);

    int i = sizeof(str)/sizeof(str[0]);
    cout<<endl<<"Length of the string:"<<i<< " "<<n;


    recursiveReverse(str,0,n-1);
    cout<<endl<<str;
    iterativeReverse(str,0,n);
    cout<<endl<<str;
    return 0;
}
