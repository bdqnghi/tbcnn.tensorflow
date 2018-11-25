#include<iostream>
#include<vector>

using namespace std;












int partition(int l, int r, vector<int> &a){
    int pivot = a[r];

    int i=l-1, temp;

    
    
    
    

    for(int j=l; j<=r; j++){
        if(a[j]<=pivot){
            i++;
            
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    
    return i;
}

void quickSort(int l, int r, vector<int> &a){
    if(l>=r) return;

    
    
    int p = partition(l, r, a);

    
    quickSort(l, p-1, a);
    quickSort(p+1, r, a);
}

int main(){

    vector<int> a = {23, 43, 18, 8, 4, 12, 34, 20, 15, 33, 21, 7};
    int n = a.size();

    quickSort(0, n-1, a);

    for(int num:a) cout << num << " ";
    cout << endl;

}