#include<iostream>
#include<vector>

using namespace std;





int main(){
    
    vector<int> a = {45, 56, 23, 8, 7, 4, 10, 34, 12, 25, 19};
    int n = a.size();

    

    int temp=0;
    bool swapped = true;

    
    
    while(swapped){
        swapped = false;
        for(int i=0; i<n-1; i++){
            if(a[i]>a[i+1]){
                
                temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
                swapped = true;
            }
        }
        n = n-1;
    }

    for(int num:a) cout << num << " ";
    cout << endl;

}
