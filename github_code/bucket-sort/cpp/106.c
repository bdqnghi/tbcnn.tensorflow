// almost_bucket_sort.cpp
// Glenn G. Chappell
// 18 Oct 2006
//
// For CS 311
// Not-quite-Bucket-Sort Using Forward Iterators
// (A normal Bucket Sort will sort the contents of each bucket. We do
// not. However, we only allow one value per bucket; thus, we do
// actually sort.)

#include <iostream>
using std::cout;
using std::endl;

#include <vector>  // for std::vector;


// almostBucketSort
// Sorts a sequence of 1-digit nonnegative int's, using "Bucket Sort",
//  but without sorting the contents of each bucket.
// Requirements on Types:
//     FDIter must be a forward iterator type.
//     FDIter::value_type must be int.
// Pre:
//     [first, last) is a valid range.
//     Items in [first, last) are all in [0, 9]
//      (1-digit nonnegative int's)
// Post:
//     [first, last) contains the same items as it did initially,
//      but now sorted by < (in a stable manner).
template <typename FDIter>
void almostBucketSort(FDIter first, FDIter last)
{
    std::vector<std::vector<int> > buckets(10);

    // place each item in the appropriate bucket (stable!)
    for (FDIter it = first; it != last; ++it)
    {
        buckets[*it].push_back(*it);
    }

    // Copy each bucket back to original list, one after the other
    FDIter copyBack = first;
    for (int i = 0; i < 10; ++i)
    {
        copyBack =
            std::copy(buckets[i].begin(), buckets[i].end(), copyBack);
    }
}


// main
// Test function almostBucketSort (takes iterators)
int main()
{
    const int SIZE = 11;
    //int arr[SIZE] = { 5, 3, 2, 8, 5, 9, 10, 4, 6, 1, -4};
    // Values must be 0..9
    int arr[SIZE] = { 6, 1, 9, 5, 8, 8, 5, 0, 2, 1, 5 };
    almostBucketSort(arr, arr+SIZE);
    for (int i = 0; i < SIZE; ++i)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
