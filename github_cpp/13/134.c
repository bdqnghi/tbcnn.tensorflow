#include "common_header.h"


template <std::size_t N>
using ArrayType = std::array<int, N>;



template <std::size_t N>
auto BubbleSort(ArrayType<N> values) {
    const int last_i = static_cast<int>(values.size()) - 1;
    for (int i = 0, j, last_j; i < last_i; ++i) {
        for (j = 1, last_j = values.size() - i; j < last_j; ++j) {
            if (values[j - 1] > values[j]) {
                std::swap(values[j - 1], values[j]);
            }
        }
    }

    return values;
}


template <std::size_t N>
auto BubbleSortOptimized(ArrayType<N> values) {
    const int last_i = static_cast<int>(values.size()) - 1;
    bool swapped;

    for (int i = 0, j, last_j; i < last_i; ++i) {
        for (j = 1, last_j = values.size() - i, swapped = false; j < last_j; ++j) {
            if (values[j - 1] > values[j]) {
                std::swap(values[j - 1], values[j]);
                swapped = true;
            }
        }

        if (not swapped) {
            break;
        }
    }

    return values;
}



template <std::size_t N>
void BubbleSortRecursive(ArrayType<N> &values, const typename ArrayType<N>::size_type n) {
    if (n > 1) {
        for (typename ArrayType<N>::size_type i = 1; i < n; ++i) {
            if (values[i - 1] > values[i]) {
                std::swap(values[i - 1], values[i]);
            }
        }

        BubbleSortRecursive(values, n - 1);
    }
}
template <std::size_t N>
auto BubbleSortRecursive(ArrayType<N> values) {
    BubbleSortRecursive(values, values.size());
    return values;
}


constexpr ArrayType<0> VALUES1 = {};
constexpr ArrayType<1> VALUES2 = {1};
constexpr ArrayType<2> VALUES3 = {1, 2};
constexpr ArrayType<3> VALUES4 = {2, 3, 1};
constexpr ArrayType<3> EXPECTED4 = {1, 2, 3};
constexpr ArrayType<4> VALUES5 = {2, 3, 4, 1};
constexpr ArrayType<4> EXPECTED5 = {1, 2, 3, 4};
constexpr ArrayType<6> VALUES6 = {1, 2, 3, 1, 2, 2};
constexpr ArrayType<6> EXPECTED6 = {1, 1, 2, 2, 2, 3};

SIMPLE_TEST(BubbleSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(BubbleSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(BubbleSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(BubbleSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(BubbleSort, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(BubbleSort, TestSAMPLE6, EXPECTED6, VALUES6);

SIMPLE_TEST(BubbleSortOptimized, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(BubbleSortOptimized, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(BubbleSortOptimized, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(BubbleSortOptimized, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(BubbleSortOptimized, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(BubbleSortOptimized, TestSAMPLE6, EXPECTED6, VALUES6);

SIMPLE_TEST(BubbleSortRecursive, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(BubbleSortRecursive, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(BubbleSortRecursive, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(BubbleSortRecursive, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(BubbleSortRecursive, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(BubbleSortRecursive, TestSAMPLE6, EXPECTED6, VALUES6);
