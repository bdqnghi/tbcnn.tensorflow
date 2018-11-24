/* Radix sort (tested)

An non-conparative INTEGER sorting algoritm.

The following implementation of radix sort
starts at the least significant digit (LSD).

LSD radix sort:
  - short keys come before longer keys (ie. 1 < 10)
  - same length keys sorted lexicographically (ie. 10 < 11)

MSD (most significant digit):
  - use lexicographic order
  - ie.: b,c,ba -> b,ba,c

STABLE

Before computing time and space comlexity, some notation:
  - n: number of keys (number of elements in the input array)
  - k (or base): range of digits
  - d: the number of digits

Time complexity:
  Now it's easy to see that the time complexity of radix sort
  is O(d(n+k)) (or O(d(n+base))).

  Let's call maxVal is the maximum value in the input array,
  we have the relation: d = log[base](maxVal). (*)

  Besides n, input array, we might want to provide the algorithm
  base as another input.

  From (*), we can have a sense that there is a tradeoff
  between base and d. To deeply analyze (*) and derive
  the best choice for base, we need to give maxVal a bound,
  that is: the numbers in the input array are b-bit
  numbers, this means:
    - maxVal = 2^b - 1
    - d = log[base](2^b - 1) ~ log[base](2^b)
        = b / log(base)

  Now time complexity is: (b / log(base)) (n + base). (**)

  The problem is now given n and b (the numbers of elements
  and their maximum value), we choose base that minimizes
  (**).

  The math is now easy, but I haven't been able to pull out
  a intuitively for the answer.

Space complexity: O(n+k) = O(n+base)

*/

// ----------------INCLUDE-----------------

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ---------------RADIX SORT---------------

void countingSort(  // pow = base^it
  vector<int> & A, int base, int it, int pow) {
  // List to buckets.
  vector< vector< int > > buckets(base, vector<int>());
  for(int num : A) {
    int digit = (num / pow) % base;
    buckets[digit].push_back(num);
  }

  // Buckets to list.
  A.clear();
  for(vector<int> & bucket : buckets) {
    for(int num : bucket)
      A.push_back(num);
  }
}

void radixSort(vector<int> & A, int base = 10) {
  // Base case
  if (A.size() == 0) return;

  int maxValue = *max_element(A.begin(), A.end());
  int it = 0;  // it = [0..number of digits)
               // or the position of digit.
  int pow = 1;
  while(pow <= maxValue) {
    countingSort(A, base, it, pow);
    it++;
    pow *= base;
  }
}

// -----------------HELPER-----------------

void printArray(const vector<int> & A) {
  for(int num : A) cout << num << ' ';
  cout << '\n';
}

// ----------------------------------------

int main() {
  vector<int> A({0});
  radixSort(A);
  printArray(A);
  return 0;
}
