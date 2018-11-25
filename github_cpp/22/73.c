
#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ui;


void bucket_sort(vector<int>& a, int ex){

    
    if(ex == 0){
        return;
    }

    
    vector<int> b[10];
    for(ui i = 0; i < a.size(); i++){
        int idx = (a[i]/ex)%10;
        b[idx].push_back(a[i]);
    }

    
    for(int i = 0; i < 10; i++){
        if(b[i].size() > 1){
            bucket_sort(b[i], ex/10);
        }
    }

    
    int idx = 0;
    for(int i = 0; i < 10; i++){
        for(ui j = 0; j < b[i].size(); j++){
            a[idx++] = b[i][j];
        }
    }
}


void radix_sort(vector<int>& a){

    int maxx = 0;
    for(ui i = 0; i < a.size(); i++){
        maxx = max(maxx, a[i]);
    }

    
    int ex = 1;
    while(maxx/ex > 0) ex *= 10;
    ex /= 10;

    bucket_sort(a, ex);
}

int main(){

    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    radix_sort(a);

    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}