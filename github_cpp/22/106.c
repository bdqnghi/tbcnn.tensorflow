









#include <iostream>
using std::cout;
using std::endl;

#include <vector>  















template <typename FDIter>
void almostBucketSort(FDIter first, FDIter last)
{
    std::vector<std::vector<int> > buckets(10);

    
    for (FDIter it = first; it != last; ++it)
    {
        buckets[*it].push_back(*it);
    }

    
    FDIter copyBack = first;
    for (int i = 0; i < 10; ++i)
    {
        copyBack =
            std::copy(buckets[i].begin(), buckets[i].end(), copyBack);
    }
}




int main()
{
    const int SIZE = 11;
    
    
    int arr[SIZE] = { 6, 1, 9, 5, 8, 8, 5, 0, 2, 1, 5 };
    almostBucketSort(arr, arr+SIZE);
    for (int i = 0; i < SIZE; ++i)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
