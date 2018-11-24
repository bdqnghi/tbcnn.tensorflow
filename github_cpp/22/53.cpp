#include <iostream>

template <typename T>
inline void
swap(T& a, T& b)
{
    if (a != b) {
        T tmp = a;
        a = b;
        b = tmp;
    }
}

template <typename T>
void
ajust_heap(T list[], int root, int tail, bool is_ascending)
{
    while (root * 2 + 1 <= tail) {
        int lch = root * 2 + 1;
        size_t to_swap = root;
        if ((is_ascending && list[to_swap] < list[lch]) ||
            (!is_ascending && list[to_swap] > list[lch])) {
            to_swap = lch;
        }
        int rch = lch + 1;
        if (rch <= tail && ((is_ascending && list[to_swap] < list[rch]) ||
                           (!is_ascending && list[to_swap] > list[rch]))) {
            to_swap = rch;
        }
        if (to_swap != root) {
            swap(list[root], list[to_swap]);
            root = to_swap;
        } else {
            return;
        }
    }
}

template <typename T>
inline void
build_heap(T list[], size_t size, bool is_ascending)
{
    int start = (size - 2) / 2;

    while (start >= 0) {
        ajust_heap(list, start, size - 1, is_ascending);
        --start;
    }
}

template <typename T>
void
heap_sort(T list[], size_t size, bool is_ascending=true)
{
    if (list == NULL || size <= 1) {
        return;
    }
    build_heap(list, size, is_ascending);

    int tail = size - 1;
    while (tail > 0) {
        swap(list[tail], list[0]);
        --tail;
        ajust_heap(list, 0, tail, is_ascending);
    }
}
