/*******************************************************************************

Bucket sort
==============

Ref - http://www.geeksforgeeks.org/bucket-sort-2/

--------------------------------------------------------------------------------

Problem
=======
Classic old bucket sort.

--------------------------------------------------------------------------------

Time Complexity
===============
O(n)

--------------------------------------------------------------------------------

Output
======
Array is initially:
0.8970 0.5650 0.6560 0.1234 0.6650 0.3434
After bucket sort, array is:
0.1234 0.3434 0.5650 0.6560 0.6650 0.8970

*******************************************************************************/

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

void printArray(float arr[], int n) {
  for(int i = 0; i < n; ++i)
    printf("%.4f ", arr[i]);
  printf("\n");
}

void bucketSort(float arr[], int n) {

  // create n buckets
  vector<float> b[n];

  // put elements into different buckets
  for (int i = 0; i < n; i++) {
    int j = n * arr[i]; // bucket index
    b[j].push_back(arr[i]);
  }

  // sort individual buckets
  for (int i = 0; i < n; i++) {
    sort(b[i].begin(), b[i].end());
  }

  // concatenate all buckets into arr[]
  int k = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < b[i].size(); j++) {
      arr[k++] = b[i][j];
    }
  }
}

int main()  {
  float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
  printf("Array is initially:\n");
  printArray(arr, 6);
  printf("After bucket sort, array is:\n");
  bucketSort(arr, 6);
  printArray(arr, 6);
  return 0;
}
