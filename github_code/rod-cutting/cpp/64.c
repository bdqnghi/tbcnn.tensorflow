#include <iostream>
#include <cstring>
#include <list>

using namespace std;
int price[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
int rodCutting(int rod[], int length);
int bottom_up(int rod[], int n);
void get_pieces(int s[], int n);
int rod_cut(int rod[],int length);
int r[10];
int max(int a, int b);
int length = 10;
int main()
{
    memset(r, 0, sizeof(int)*10);
    cout<<"revenue: "<<rodCutting(price, 4);

    return 0;
}

int rod_cut(int rod[], int length)
{
    if(length == 0) return 0;
    int maximum = -1;
    for(int i=1;i<=length;++i)
    {
        maximum = max(maximum,rod[i]+rod_cut(rod,length-1));
    }
    return maximum;
}


int rodCutting(int rod[], int length)
{
    if(length == 1) return rod[0];
    if(r[length-1] > 0) return r[length-1];
    int maximum = -1;
    for(int i = 1; i < length; ++i)
    {
        int curr = max(rod[length-1], rod[i-1] + rodCutting(rod, length-i));
        maximum = max(maximum, curr);
    }
    r[length-1] = maximum;
  return maximum;
}
int bottom_up(int rod[], int n)
{
    int r[n+1];
    int s[n+1];
    r[0] = 0;
    for(int i = 1; i <= n; ++i)
    {
        r[i] = rod[i-1];
    }
    for(int i = 1; i <= n; ++i)
    {
        int maximum = -1;
        for(int j = 1; j <= i; ++j)
        {
            if(maximum < r[j] + r[i-j])
            {
                maximum = r[j] + r[i-j];
                s[i] = j;
            }
        }
        r[i] = maximum;
    }
    get_pieces(s, n);
    return r[n];
}
void get_pieces(int s[], int n)
{
    cout<<"Using pieces:\n";
    while(n > 0)
    {
        cout<<s[n]<<endl;
        n = n - s[n];
    }
}
int max(int a, int b)
{
    return (a > b ? a : b);
}