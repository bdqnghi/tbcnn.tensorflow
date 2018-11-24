// Insertion Sort Advanced Analysis
// Day #15
// Sunday, May 14, 2017
// https://www.hackerrank.com/challenges/insertion-sort

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

unsigned long long merge_sort(vector<int>&, vector<int>&, int, int);
unsigned long long merge(vector<int>&, vector<int>&, int, int, int);

int main() {
    
    int num_queries;
    cin >> num_queries;
    
    unsigned long long num_shifts = 0;
    
    for (int query = 0; query < num_queries; query++) {
        
        int num_elements;
        cin >> num_elements;
    
        vector<int> arr(num_elements);
    
        for (int element = 0; element < num_elements; element++) {
        
            cin >> arr[element];
        
        } // for
        
        vector<int> temp(num_elements);
        
        num_shifts = merge_sort(arr, temp, 0, num_elements - 1);
        
        cout << num_shifts << endl;
        
    } // for query < num_queries
    
    return 0;

} // main()

unsigned long long merge_sort(vector<int> & arr, vector<int> & temp, 
                              int left, int right) {
    
    unsigned long long num_shifts = 0;
    
    int middle = 0;
    
    if (right > left) {
        
        middle = (right + left) / 2;
        
        num_shifts += merge_sort(arr, temp, left, middle);
        
        num_shifts += merge_sort(arr, temp, middle + 1, right);
        
        num_shifts += merge(arr, temp, left, middle + 1, right);
        
    }
    
    return num_shifts;
    
} // merge_sort()

unsigned long long merge(vector<int> & arr, vector<int> & temp, 
                         int left, int middle, int right) {
    
    unsigned long long num_shifts = 0;
    
    int i = left;
    int j = middle;
    int k = left;
    
    while (i <= middle - 1 && j <= right) {
        
        if (arr[i] <= arr[j]) {
            
            temp[k++] = arr[i++];
            
        } else {
            
            temp[k++] = arr[j++];
            num_shifts += middle - i;
            
        }
        
    } // while
    
    while (i <= middle - 1) {
            
        temp[k++] = arr[i++];
            
     }
        
    while (j <= right) {

        temp[k++] = arr[j++];

    }
        
    for (i = left; i <=right; i++) {

        arr[i] = temp[i];

    }
    
    return num_shifts;
    
} // merge()