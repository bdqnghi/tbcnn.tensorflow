#include<iostream>
#include<vector>

using namespace std;

//Avg. Time Complexity: O(nlogn)
//Worst Time Complexity: O(n^2), mergeSort which had O(nlogn)
//Extra Space Complexity: O(1), mergeSort had O(n)


//Lomuto Partitioning
//choose a pivot element
//and partition the subarray a[l,...,r] "in place"
//such that all elements <= pivot are to left of pivot
//and elements > pivot are to its right

int partition(int l, int r, vector<int> &a){
    int pivot = a[r];

    int i=l-1, temp;

    //at any point in this for loop
    //a[l,..,i] are all <= pivot
    //a[i+1,...,j-1] are all > pivot
    //deal with a[j] accordingly

    for(int j=l; j<=r; j++){
        if(a[j]<=pivot){
            i++;
            //swap
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    //now i is the index of pivot
    return i;
}

void quickSort(int l, int r, vector<int> &a){
    if(l>=r) return;

    //p is index of pivot element
    //in rearranged subarray a[l,...,r]
    int p = partition(l, r, a);

    //cal quickSort on both sides of pivot
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