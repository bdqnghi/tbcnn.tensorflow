#include<iostream>
#include<vector>

using namespace std;

//Avg. Time Complexity: O(n^2)
//Worst Time Complexity: O(n^2)
//Extra Space Complexity: O(1)

int main(){
    
    vector<int> a = {45, 56, 23, 8, 7, 4, 10, 34, 12, 25, 19};
    int n = a.size();

    //bubble sort

    int temp=0;
    bool swapped = true;

    //each while loop puts maximum
    //element in a[0,..,n-1] at its place
    while(swapped){
        swapped = false;
        for(int i=0; i<n-1; i++){
            if(a[i]>a[i+1]){
                //swap
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
