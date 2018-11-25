
#include <iostream>
#include <vector>

#include "utils.h"

using namespace std;

void swap(vector<int>& nums, int i, int j){
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

void selectionsort(vector<int>& nums){
    
    for(int i = 0; i < nums.size(); i++){
        int idx = i;
        int min = nums[i];
        for(int j = i+1; j < nums.size(); j++){
            if(nums[j] < min){
                min = nums[j];
                idx = j;
            }
        }
        swap(nums, i, idx);
    }
}

int main(){

    vector<int> nums = randomIntVector(20);

    cout << "Unsorted: \n";
    printNums(nums);

    selectionsort(nums);   
    cout << "\nSorted: \n";
    printNums(nums);
    
    return 0;
}
