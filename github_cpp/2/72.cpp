#include <bits/stdc++.h>
using namespace std;

#define FOR(i, n) for(int i=0; i<n; ++i)
#define FOR1(i, n) for(int i=1; i<n; ++i)
#define FORrev(i, n) for(int i=n-1; i>=0; --i)
#define pb push_back
#define ll long long

struct heap
{
    int num;
    int left;
    int right;
    int parent;
    int ind;
};

int n;
priority_queue< pair<int, string>, vector< pair<int, string> >, greater< pair<int, string> > > p;
vector<int> index;

int main() {

    cin>>n;
    string s, int temp;

    FOR(i, n)
    {
        cin>>s>>temp;
        p.push(pair<int, string>(temp, s));
    }


    pair<int, string> a, b, c;
    while(p.size() != 1)
    {
        a= p.top(); p.pop();
        b= p.top(); p.pop();

        c.first= a.first + b.first;
        c.second= NULL;

        p.
    }

    return 0;
}
