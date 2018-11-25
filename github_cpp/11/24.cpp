



#include <iostream>
#include <vector>
#include <climits>
using namespace std;



int leftIndex(int i) {
  return (i << 1) + 1;
}

int rightIndex(int i) {
  return (i << 1) + 2;
}

void printArray(const vector<int> & A) {
  for(auto & x : A) cout << x << ' ';
  cout << '\n';
}





void maxHeapify(
  vector<int> & A, const int heapSize, int i) {
  int left = leftIndex(i);
  int right = rightIndex(i);
  int largest = i;
  if (left < heapSize && A[left] > A[largest])
    largest = left;
  if (right < heapSize && A[right] > A[largest])
    largest = right;
  if (largest != i) {
    swap(A[i], A[largest]);
    maxHeapify(A, heapSize, largest);
  }
}





void buildMaxHeap(vector<int> & A, const int heapSize) {
  for(int i = A.size()/2 - 1; i >= 0; i--)
    maxHeapify(A, heapSize, i);
}





void heapSort(vector<int> & A) {
  int heapSize = A.size();
  buildMaxHeap(A, heapSize);  
  for(int i = (int)A.size() - 1; i >= 1; i--) {  
    
    
    
    
    
    
    
    swap(A[0], A[i]);
    maxHeapify(A, --heapSize, 0);  
  }
}



int main() {
  vector<int> A({5,3,2,5,2,1,0});
  heapSort(A);
  printArray(A);

  return 0;
}
