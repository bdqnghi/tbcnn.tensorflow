#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
void counting(vector<int> a,vector<string> s)
    {
    int n=a.size();
    vector<string>b(n,"-");
    vector<int> count(100,0);
    for(int i=0;i<n;i++)
        count[a[i]]++;
    for(int j=0;j<100;j++){
        count[j]+=j==0?0:count[j-1];
    }
   for(int i=n/2;i<n;i++)
    {
        b[count[a[i]]-1]=s[i];
            count[a[i]]--;}
    for(int l=0;l<n;l++)
        cout<<b[l]<<" ";
}

int main() {
    int n;
    cin>>n;
    vector<int> a;
    vector<string>s;
    for(int i=0;i<n;i++)
        {
        int l;string q;
        cin>>l;
        cin>>q;
        a.push_back(l);
        s.push_back(q);
    }
    counting(a,s);
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}
