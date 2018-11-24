#include<bits/stdc++.h>
using namespace std;

int binarySearch(vector<int> &arr, int left, int right, int target){

  if(left > right) return -1;
  int middle = (left+ right)/2;
  
  if(arr[middle]==target) return middle;
  
  if(arr[middle] < target){
    return binarySearch(arr, middle+1, right, target);
  }
  else {
    return binarySearch(arr, left, middle-1, target);
  }
}

int main(){
  //test cases
  vector<int> n1={-1,0,1,2,3,4,8,11};
  
  //{1, 3},{2}
  // 
  cout<<"The element is at index: "<<binarySearch(n1, 0, (int)n1.size()-1,0);
  return 0;
}

#include<bits/stdc++.h>
using namespace std;

int binarySearch(vector<int>& nums, int target){
  int left=0, right=nums.size()-1;
  
  while(left <= right){
    int mid= left + (right-left)/2;
    if(nums[mid]== target) return mid;
    else if(nums[mid]< target) left = mid+1;
    else right = mid-1;
  }
  return -1;
}

int main(){
  vector<int> n1={0,1,2,4,7};
  cout<<binarySearch(n1, 4);
  
  return 0;
}