






#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

const int MAX_LENGTH = 1000001; 

void merge_sort_recursive(int arr[], int result[], int start, int end){
    if (start >= end)
        return;
    int len = end - start, mid = (len >> 1) + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    merge_sort_recursive(arr, result, start1, end1);
    merge_sort_recursive(arr, result, start2, end2);
    int ptr = start;
    while (start1 <= end1 && start2 <= end2)
        result[ptr++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
    while (start1 <= end1)
        result[ptr++] = arr[start1++];
    while (start2 <= end2)
        result[ptr++] = arr[start2++];
    for (int i = start; i <= end; i++)
        arr[i] = result[i];
}

void merge_sort(int arr[], const int length) {
    int result[length];
    merge_sort_recursive(arr, result, 0, length-1);
}

int main(){
    cout << "CPP\n";

    
    fstream ifs, ofs;
    ifs.open("not_sorted.txt", fstream::in);
    ofs.open("sorted_cpp.txt", fstream::out);

    
    int num = 0, len = 0;
    int arr[MAX_LENGTH];
    while (ifs >> num) {
       arr[len++] = num; 
    }
    
    
    cout << "Sorting...\n";

    
    merge_sort(arr, len);

    
    for (int i = 0; i < len; i++) {
        ofs << arr[i] << endl;
    }

    
    cout << "Done!\n";

    return 0;
}
