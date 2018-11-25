#include "heap.hpp"

int main(int argc, char **argv)
{
    int n = atoi(argv[1]), i, old, arr[n] = {0};
    for (i = 0; i < n; ++i)
        cin >> arr[i];

    struct heap *h = create_heap(n);
    cout << endl
         << "Before heap build: ";
    for (i = 0; i < n; ++i)
        cout << arr[i] << " ";
    build_heap(h, arr, n);
    cout << endl
         << "Before sorting: ";
    print_heap(h);

    old = h->count;

    for (i = n - 1; i > 0; i--)
    {
        swap(h->array[0], h->array[i]);
        h->count--;
        heapify(h, 0);
    }

    h->count = old;
    cout << endl
         << "After: ";
    print_heap(h);

    return 0;
}
