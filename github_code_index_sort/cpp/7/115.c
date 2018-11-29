#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>
#include <bitset>
#include <utility>
#include <set>
#include <numeric>
#include <time.h>
#include <fstream>
#include <limits>
#include <iomanip>
#define INT_MAX 2147483647
#define INT_MIN -2147483648
#define pi acos(-1.0)
#define E 2.71828182845904523536
using namespace std;

bool comapre(pair<string,int> x, pair<string,int> y)
{
    return x.second > y.second;
}
int main()
{
    int N;
    scanf("%d",&N);
    char Input[5000];

    gets(Input);
    for (int i=0; i<N; i++)
    {
        vector<string> given;
        map<string,int> wanted;

        int n;
        scanf("%d",&n);
        gets(Input);

        for (int j=0; j<n; j++)
        {
            gets(Input);
            given.push_back(Input);
        }

        for (int j=0; j<n; j++)
        {
            gets(Input);
            wanted[Input] = j;
        }

        vector< pair<string, int> > order;

        for (int j=0; j<n; j++)
        {
            order.push_back(make_pair(given[j], wanted[given[j]]));
        }

        vector< pair<string, int> > ToSwap;
        for (int j=n-1, next=n-1; j >= 0; j--)
        {
            if (order[j].second != next) ToSwap.push_back(order[j]);
            else next--;
        }
        sort(ToSwap.begin(), ToSwap.end(), comapre);

        for (int j=0; j<ToSwap.size(); j++) cout << ToSwap[j].first << endl;
        cout << endl;
    }
    return 0;
}
