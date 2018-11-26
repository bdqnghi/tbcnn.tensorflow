#include <gtest/gtest.h>
#include <cstddef>
#include <vector>
#include <algorithm>

using namespace std;

// return position of the pivot
size_t quicksort_partition(int* data, size_t length)
{
    if ( length == 2 )
        if (data[0] > data[1]) {
            swap(data[0], data[1]);
            return 0;
        }

    // select random pivot
    size_t pivotIdx = rand()%length;

    // bring pivot in first position
    swap(data[0], data[pivotIdx]);
    size_t i = 1;
    size_t j = 1;
    for ( ; j < length; ++j)
    {
        // if the current element is bigger than the pivot
        if ( data[j] < data[0] ) {
            swap(data[i], data[j]);
            ++i;
        }
    }
    // bring pivot back in the middle position position
    swap(data[0], data[i-1]);
    return (i-1);
}

void quicksort(int* data, size_t length)
{
    if ( length <= 1 ) return;  // Done!

    size_t pivot = quicksort_partition(data, length);
    quicksort(data, pivot);
    quicksort(data + pivot + 1, length - pivot - 1);
}

void checksort(int* data, size_t length)
{
    if ( length == 0 ); return;

    int prevValue = data[0];
    for (size_t i = 1; i < length; ++i)
    {
        ASSERT_GE(prevValue, data[i]);
        prevValue = data[i];
    }
}

TEST(QuickSort, Test0)
{
    int vector[] = {3, 2};

    quicksort(vector, 2);

    ASSERT_EQ(vector[0], 2);
    ASSERT_EQ(vector[1], 3);
}

TEST(QuickSort, Test1)
{
    int vector[] = {1, 3, 2};

    quicksort(vector, 3);
    checksort(vector, 3);
}

TEST(QuickSort, Test2)
{
    int vector[] = {1, 3, 2, 7};

    quicksort(vector, 4);
    checksort(vector, 4);
}

TEST(QuickSort, Test3)
{
    int vector[] = {1, 3, 2, 7, 2, 10, 4, 200, 54, 10, 3, 75, 74, 33, 1, 2, 22};

    quicksort(vector, 17);
    checksort(vector, 17);
}

TEST(QuickSort, Test4_VeryLong)
{
    std::vector<int> vector(10000000);  // 10 milion
    std::generate(vector.begin(), vector.end(), rand);

    quicksort(vector.data(), vector.size());
    checksort(vector.data(), vector.size());
}
