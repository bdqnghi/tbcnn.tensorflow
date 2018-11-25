
#include <bits/stdc++.h>
#include <bitset>
#define endl '\n'

using namespace std;


int calculateBin(int n) {
    string binary = bitset<10>(n).to_string();
    size_t ctr = count(binary.begin(), binary.end(), '1');
    return ctr;
}


ostream &operator<<( ostream &output, vector<int> v ) {
    for(auto it: v)
        output<<it<< ' ';
    return output;
}


void sortVec(vector<int>& v) {
    sort(v.begin(), v.end());
    cout<<v<<endl;
}

void bucket_sort(int arr[], int n) {
    
    
    map<int, vector<int>> mp;
    for(int i=0; i<n; i++) {
        int bin = calculateBin(arr[i]);

        
        auto it = mp.find(bin);
        if(it==mp.end()) {
            vector<int> v;
            v.push_back(arr[i]);
            mp[bin] = v;
        } else {
            (mp[bin]).push_back(arr[i]);
        }
    }

    for(auto i:mp)
        sortVec(i.second);

}


int main() {
    int n;
    cin>>n;
    int arr[n];
    for(int i=0; i<n; i++)
        cin>>arr[i];

    bucket_sort(arr, n);
}
