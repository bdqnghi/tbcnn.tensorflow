/* Heapsort (tested)

For ascending sorting, we use a max heap.

Heap sort can be thought of as an improved selection sort.

Time complexity: Θ(nlgn)

Space complexity: O(1) - if `maxHeapify` is implemented iteratively.

Not stable

In-place

Wikipedia has a very nice comparision between Heapsort and Mergesort:
  - Mergesort O(n) in space, Heapsort O(1).
  - Mergesort can be implemented using linked-list to have O(1) in space.
  - Mergesort can be well parallelized to achive close to linear
    speed up, heap sort is not an ideal candidate for parallel
    algorithm.
  - Mergesort is stable, Heapsort not
  - Merge sort on arrays has considerably better data cache
    performance, often outperforming heapsort on modern desktop
    computers because merge sort frequently accesses contiguous
    memory locations (good locality of reference); heapsort
    references are spread throughout the heap.
*/

// ----------------INCLUDE-----------------

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// ---------------UTILITIES----------------

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

// --------------MAX-HEAPIFY---------------

/*

This subprocedure is to maintain the max heap property
for the subtree rooted at i-th element and has heapSize.

"Float down" i-the element if its value is not the
largest.

Time complexity:
  Since heap is a nearly complete binary tree,
  in the worst case left-subtree and right-subtree of
  i might be at most 1-height difference:
                    i (quantity: 1)
               /          \
            n/2            n/2
            /               \
    FULL OF LEAVES (n/2)    NO LEAVES (0)

  and the left-subtree can have up to 2n/3 elements.

  So T(n) <= (worst-case) T(2n/3) + Θ(1)
  Apply master theorem: T(n) = O(lgn)

Space complexity
  - The space complexity of heapsort algorithm depends entirely
  on this subprocedure's.
  - O(lgn) if implemented recursively, O(1) if iteratively.

*/

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

// -------------BUILD-MAX-HEAP-------------

/*

This subprocedure convert an array A into a max heap,
with:
  - Root at A[0]
  - A[i]->left = A[2*i]
  - A[i]->right = A[2*i + 1]

This subprocedure utilies the property that:
Leaf nodes is (if 1-based):
floor(n/2) + 1
floor(n/2) + 2
..

Time complexity:
  Easily to provide an upper bound: calling maxHeapify
  (that takes O(lgn) each) on (n/2) elements
  => O(n/2ln) = O(nlgn)

  However we can prove a tight bound:
    - Perform `maxHeapify` for each node.
    - Maximum number of nodes of height h' in a heap
      = n / 2^h'.
    => T(n) = sum[h=0..floor(lgn)]( n/2^h * h )
            = n sum[h=0..floor(lgn)] ( n / 2^h * h )
            = O(n sum[h=0..inf]( 2^h * h))
            = O(2 n)
            = O(n), wow, suprised mtfk!
*/

void buildMaxHeap(vector<int> & A, const int heapSize) {
  for(int i = A.size()/2 - 1; i >= 0; i--)
    maxHeapify(A, heapSize, i);
}

// ----------------HEAP SORT---------------

/*

Time complexity:

Once 1 element at length h is swapped (to root),
the maxHeapify applied to it (the root) can take up to O(H-h)
int worst case to heapfiy the heap.

So the time compexity of heapSort is:
T(n) = sum[h=0..floor(lgn)] ( n/2^h * (H - h) )
     = sum[h=0..floor(lgn)] ( n/2^h * (lgn - h))
Solve this gives us T(n) = 2nlgn - 2n = O(nlgn)
*/

void heapSort(vector<int> & A) {
  int heapSize = A.size();
  buildMaxHeap(A, heapSize);  // O(n)
  for(int i = (int)A.size() - 1; i >= 1; i--) {  // O(n)
    // The root of the heap is always the largest value.
    //
    // Swapping this value with end of array will put it
    // into correct position.
    //
    // After swapping, root may not maintain maxHeap property
    // any longer => maxHeapify it with heapSize decreased by 1.
    swap(A[0], A[i]);
    maxHeapify(A, --heapSize, 0);  // O(lgn)
  }
}

// ----------------------------------------

int main() {
  vector<int> A({5,3,2,5,2,1,0});
  heapSort(A);
  printArray(A);

  return 0;
}
