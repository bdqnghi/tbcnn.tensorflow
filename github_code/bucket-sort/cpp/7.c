// https://www.hackerearth.com/practice/algorithms/sorting/bucket-sort/tutorial/
#include <bits/stdc++.h>
#include <bitset>
#define endl '\n'

using namespace std;

// calculate the number of 1s in binary representation
int calculateBin(int n) {
    string binary = bitset<10>(n).to_string();
    size_t ctr = count(binary.begin(), binary.end(), '1');
    return ctr;
}

// overload operator for printing vector
ostream &operator<<( ostream &output, vector<int> v ) {
    for(auto it: v)
        output<<it<< ' ';
    return output;
}

// sorting vector
void sortVec(vector<int>& v) {
    sort(v.begin(), v.end());
    cout<<v<<endl;
}

void bucket_sort(int arr[], int n) {
    // since the limit is 10^3, we can safely assume a map of 1-10
    // with vectors representing bins should be suffice
    map<int, vector<int>> mp;
    for(int i=0; i<n; i++) {
        int bin = calculateBin(arr[i]);

        // see if the entry already exists
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
