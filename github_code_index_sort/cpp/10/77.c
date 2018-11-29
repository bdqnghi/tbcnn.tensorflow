/* Bucket Sort (Radix Sort)  (BucketSort.cpp) */
#include <iostream>
#include <vector>
using namespace std;
 
void bucketSort(int a[], int size);
void bucketSort(vector<int> & list, int radix);
void printBuckets(const vector<int> buckets[], int size);
void print(const vector<int> list);
 
const int NUM_BUCKETS = 10;
 
int main() {
   const int SIZE = 13;
   int a[] = {28, 104, 25, 593, 22, 129, 4, 11, 129, 4, 111, 20, 9};
   bucketSort(a, SIZE);
}
 
void bucketSort(int a[], int size) {
   // find maximum to decide on the number of significant digits
   int max = a[0];
   for (int i = 1; i < size; ++i) {
      if (a[i] > max) max = a[i];
   }
 
   // Decide on the max radix (1000, 100, 10, 1, etc)
   int radix = 1;
   while (max > 10) {
      radix *= 10;
      max /= 10;
   }
 
   // copy the array into a vector
   vector<int> list(size);
   for (int i = 0; i < size; ++i) {
      list[i] = a[i];
   }
   bucketSort(list, radix);
}
 
// Sort the given array of size on the particular radix (1, 10, 100, etc)
// Assume elements are non-negative integers
// radix shall be more than 0
void bucketSort(vector<int> & list, int radix) {
   if (list.size() > 1 && radix > 0) {  // Sort if more than 1 elements
      // For tracing
      cout << "To sort: ";
      print(list);
 
      vector<int> buckets[NUM_BUCKETS];  // 10 buckets
 
      // Distribute elements into buckets
      for (int i = 0; i < list.size(); ++i) {
         int bucketIndex = list[i] / radix % 10;
         buckets[bucketIndex].push_back(list[i]);
      }
 
      // For tracing
      cout << "radix=" << radix << ": ";
      printBuckets(buckets, NUM_BUCKETS);
 
      // Recursively sort the non-empty bucket
      for (int bi = 0; bi < NUM_BUCKETS; ++bi) {
         if (buckets[bi].size() > 0) {
            bucketSort(buckets[bi], radix / 10);
         }
      }
 
      // Gather all the buckets into list and return
      list.resize(0);  // remove all elements
      for (int bi = 0; bi < NUM_BUCKETS; ++bi) {
         for (int j = 0; j < buckets[bi].size(); ++j) {
            list.push_back((buckets[bi])[j]);
         }
      }
 
      // For tracing
      cout << "Sorted: ";
      print(list);
   }
}
 
// Print the contents of all buckets
void printBuckets(const vector<int> buckets[], int size) {
   for (int i = 0; i < size; ++i) {
      // print each bucket
      cout << "{";
      for (int bi = 0; bi < buckets[i].size(); ++bi) {
         cout << (buckets[i])[bi];
         if (bi < buckets[i].size() - 1) cout << ",";
      }
      cout << "} ";
   }
   cout << endl;
}
 
// Print the contents of vector<int>
void print(const vector<int> list) {
   cout << "{";
   for (int i = 0; i < list.size(); ++i) {
      cout << list[i];
      if (i < list.size() - 1) cout << ",";
   }
   cout << "}" << endl;
}