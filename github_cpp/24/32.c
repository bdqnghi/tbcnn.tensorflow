#include <iostream>
#include <vector>
#include <iterator>

template <typename RandomAccessIterator, typename Key>
RandomAccessIterator binary_search_iterative(RandomAccessIterator p, RandomAccessIterator r, Key k)
{
    auto const e = r;
    for (auto d = r - p; d > 0; d = r - p) {
        auto m = p + d/2;
        if (k == *m) return m;
        else if (k < *m) r = m;
        else p = m + 1;
    }
    return e;
}

template <typename RandomAccessIterator, typename Key>
RandomAccessIterator binary_search_recursive(RandomAccessIterator p, RandomAccessIterator r, Key k)
{
    static auto const e = r;
    auto d = r - p;
    auto m = p + d/2;
    if (d <= 0) return e;
    else if (k < *m) return binary_search_recursive(p, m, k);
    else if (k > *m) return binary_search_recursive(m + 1, r, k);
    else return m;
}

int main()
{
    std::vector<int> v = {1,2,3,4,5,6,7,8,9};
    std::cout << (binary_search_iterative(begin(v), end(v), 0) == end(v)) << std::endl;
    std::cout << (binary_search_recursive(begin(v), end(v), 0) == end(v)) << std::endl;
}
