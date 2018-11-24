#include <iostream>
#include <random>
#include <vector>

using namespace std;

//implementation of binary search algorithm
int binary_search(std::vector<int> arr, int target){
  int lo = 0, hi = arr.size()-1;

  while (lo <= hi) {
    int mid = lo + (hi - lo)/2;
    if (arr[mid] == target) {
      return mid;
    } else if (arr[mid] < target) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }

  return -1;
}


//test
int main() {
  std::vector<int> v(16);

  for (int i = 0; i < 15; i++) {
    v[i] = i;
    std::cout << "index " << i << " value " << i*i <<  '\n';
  }

  for (int i = 0; i < 15; i++) {
    std::cout << binary_search(v, i) << endl;
  }

  std::cout << "Target " << binary_search(v, 1000) << '\n';

  return 0;
}
