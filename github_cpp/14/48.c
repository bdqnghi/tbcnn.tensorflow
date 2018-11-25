



#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



void countingSort(  
  vector<int> & A, int base, int it, int pow) {
  
  vector< vector< int > > buckets(base, vector<int>());
  for(int num : A) {
    int digit = (num / pow) % base;
    buckets[digit].push_back(num);
  }

  
  A.clear();
  for(vector<int> & bucket : buckets) {
    for(int num : bucket)
      A.push_back(num);
  }
}

void radixSort(vector<int> & A, int base = 10) {
  
  if (A.size() == 0) return;

  int maxValue = *max_element(A.begin(), A.end());
  int it = 0;  
               
  int pow = 1;
  while(pow <= maxValue) {
    countingSort(A, base, it, pow);
    it++;
    pow *= base;
  }
}



void printArray(const vector<int> & A) {
  for(int num : A) cout << num << ' ';
  cout << '\n';
}



int main() {
  vector<int> A({0});
  radixSort(A);
  printArray(A);
  return 0;
}
