#include<bits/stdc++.h>
#define PI              acos(-1)
#define min3(a,b,c)     min(a,min(b,c))
#define max3(a,b,c)     max(a,max(b,c))
#define READ(f)         freopen(f, "r", stdin)
#define WRITE(f)        freopen(f, "w", stdout)
#define lli             long long int
#define ull             unsigned long long int
#define pii             pair < int, int>
#define pll             pair < ll, ll>
#define sc              scanf
#define scin(x)         sc("%d",&(x))
#define scln(x)         sc("%lld",&(x))
#define pf              printf
#define ms(a,b)         memset(a,b,sizeof(a))
#define veci            vector<int>
#define vecl            vector<long long int>
#define pb              push_back

using namespace std ;

long long int m=0;



void towers(int num, char frompeg, char topeg, char auxpeg)
{
    if (num == 1)
    {
     printf("\n Move disk 1 from peg %c to peg %c", frompeg, topeg);
     m++;
        return;
    }
    towers(num - 1, frompeg, auxpeg, topeg);
    printf("\n Move disk %d from peg %c to peg %c", num, frompeg, topeg);
    m++;
    towers(num - 1, auxpeg, topeg, frompeg);
}


int main()
{
    int num;

    cout << "Enter the number of disks : " << endl;
    cin >> num ;


    towers(num, 'A', 'C', 'B');

    cout <<endl <<  " Number of movements = " << m << endl;

    return 0;
}



