#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    float a[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof(a)/sizeof(a[0]);

    vector<float> bucket[n];

    for(int i=0;i<n;i++){
        int bi = a[i]*n;
        bucket[bi].push_back(a[i]);
    }

    for(int i=0;i<n;i++){
        sort(bucket[i].begin(),bucket[i].end());
    }
    float b[n];
    int index=0;
    for(int i=0;i<n;i++){
        for(int j=0; j<bucket[i].size();j++){
           b[index++] = bucket[i][j];
        }
    }

    for(int i=0;i<n;i++){
        cout<<b[i]<<" ";
    }
}
