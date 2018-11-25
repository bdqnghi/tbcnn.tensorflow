#include "gtest/gtest.h"

#include "sorting.h"
#include "verifysortedarrays.h"


TEST(BubbleSorts, BubbleSortMultipleSizesDouble)
{
    const double to_sorts[] = {6.0,   5.0,  3.0,  1.0,  2.4, 4.0, 10.0, 7.0,
                               3.42, 32.2, 44.2, 56.3, 67.9, 3.2, 44.2, 2.0};

    VERIFY_SORTING_INPLACE_FIXED_SIZE_ARRAYS(16, double, to_sorts, sorting::bubble::BubbleSort, false);
}


TEST(BubbleSorts, BubbleSortMultipleSizesInt)
{
    const double to_sorts[] = {6,  5,  3,  1,  2, 4, 10, 7,
                               3, 32, 44, 56, 67, 3, 44, 2};

    VERIFY_SORTING_INPLACE_FIXED_SIZE_ARRAYS(16, int, to_sorts, sorting::bubble::BubbleSort, false);
}


TEST(BubbleSorts, BubbleSortKnownResultDouble)
{
    const double to_sorts[] = {6.0,   5.0,  3.0,  1.0,  2.4, 4.0, 10.0, 7.0,
                               3.42, 32.2, 44.2, 56.3, 67.9, 3.2, 44.2, 2.0};
    const double known_sorted[] = { 1.0, 2.0,  2.4,  3.0,  3.2,  3.42,  4.0,  5.0,
                                    6.0, 7.0, 10.0, 32.2, 44.2, 44.2,  56.3, 67.9};

    VERIFY_SORTING_INPLACE_FIXED_SIZE_ARRAYS_AND_COMPARE(16, double, to_sorts, known_sorted, sorting::bubble::BubbleSort, false);
}


TEST(BubbleSorts, BubbleSortKnownResultInt)
{
    const double to_sorts[] = {6,   5,  3,  1,  2, 4, 10, 7,
                               3, 32, 44, 56, 67, 3, 44, 2};
    const double known_sorted[] = { 1, 2,  2,  3,  3,  3,  4,  5,
                                    6, 7, 10, 32, 44, 44,  56, 67};

    VERIFY_SORTING_INPLACE_FIXED_SIZE_ARRAYS_AND_COMPARE(16, int, to_sorts, known_sorted, sorting::bubble::BubbleSort, false);
}


TEST(BubbleSorts, BubbleSortMultipleSizesRandomDouble)
{
    VERIFY_SORTING_INPLACE_RANDOM_ARRAYS(100, double, sorting::bubble::BubbleSort, false);
}


TEST(BubbleSorts, BubbleSortMultipleSizesRandomInt)
{
    VERIFY_SORTING_INPLACE_RANDOM_ARRAYS(100, int, sorting::bubble::BubbleSort, false);
}



TEST(BubbleSorts, BubbleSortSortedDouble)
{
    VERIFY_SORTING_INPLACE_SORTED_ARRAY(100, double, sorting::bubble::BubbleSort, false);
}


TEST(BubbleSorts, BubbleSortSortedInt)
{
    VERIFY_SORTING_INPLACE_SORTED_ARRAY(100, int, sorting::bubble::BubbleSort, false);
}


TEST(BubbleSorts, BubbleSortInvSortedDouble)
{
    VERIFY_SORTING_INPLACE_INV_SORTED_ARRAY(100, double, sorting::bubble::BubbleSort, false);
}


TEST(BubbleSorts, BubbleSortInvSortedInt)
{
    VERIFY_SORTING_INPLACE_INV_SORTED_ARRAY(100, int, sorting::bubble::BubbleSort, false);
}
