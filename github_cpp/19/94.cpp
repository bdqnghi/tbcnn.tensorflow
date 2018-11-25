#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <array>
#include <memory>
#include "./arrayutils.cpp"
#include "./mergeSort.cpp"
#include "./selectionSort.cpp"

using namespace std;
using namespace arrayutils;

namespace ownsort {

    template<typename T, size_t SIZE>
    void quickSort(std::array<T, SIZE> &a, size_t l, size_t r) {
      if (r <= l) return;

      size_t i = l - 1,
           j = r,
           p = l,
           q = r;

      std::swap(a[(l + r) / 2], a[r]);

      T v = a[r];

      for (;;)
      {
          while (a[++i] < v);

          while (v < a[--j])
              if (j == l) break;

          if (i >= j) break;

          swap(a[i], a[j]);

          if (a[i] == v) {
              swap(a[p], a[i]);
              p++;
          }

          if (v == a[j]) {
              q--;
              swap(a[j], a[q]);
          }
      }

      swap(a[i], a[r]);

      j = (i == 0 ? 0 : i - 1);
      i = i + 1;

      for (size_t k = l; k < p; k++) {
          swap(a[k], a[j]);
          if (j > 0) {
            j--;
          }
      }
      for (size_t k = r - 1; k > q; k--, i++)
          swap(a[i], a[k]);
        quickSort(a, l, j);
        quickSort(a, i, r);
    }

    template<typename T, size_t SIZE>
    void quickSort(std::array<T, SIZE> &a) {
        quickSort(a, 0, SIZE - 1);
    }

    template<typename T, size_t SIZE>
    void quickSortHybrid(std::array<T, SIZE> &a, std::array<T, SIZE> &aux, size_t l, size_t r) {
        if ((r - l) <= 5) {
            ownsort::selectionSort(a, l, r + 1);
        } else {
          size_t i = l - 1,
                 j = r,
                 p = l,
                 q = r;

            std::swap(a[(l + r) / 2], a[r]);

            T v = a[r];

            for (;;)
            {
                while (a[++i] < v);

                while (v < a[--j])
                    if (j == l) break;

                if (i >= j) break;

                swap(a[i], a[j]);

                if (a[i] == v) {
                    swap(a[p], a[i]);
                    p++;
                }

                if (v == a[j]) {
                    q--;
                    swap(a[j], a[q]);
                }
            }

            swap(a[i], a[r]);

            j = (i == 0 ? 0 : i - 1);
            i = i + 1;

            for (size_t k = l; k < p; k++) {
                swap(a[k], a[j]);
                if (j > 0) {
                  j--;
                }
            }
            for (size_t k = r - 1; k > q; k--, i++)
                swap(a[i], a[k]);

            if ((j - l) > (20 * r - i) || ((j - l) * 20) < (r - i)) {
                long mid = (l + r) / 2;
                quickSortHybrid(a, aux, l, mid);
                quickSortHybrid(a, aux, mid + 1, r);
                ownsort::merge(a, aux, l, mid, r);
            } else {
                quickSortHybrid(a, aux, l, j);
                quickSortHybrid(a, aux, i, r);
            }
        }
    }

    template<typename T, size_t SIZE>
    void quickSortHybrid(std::array<T, SIZE> &a) {
        shared_ptr<array<T, SIZE>> aux (new std::array<T, SIZE>);
        quickSortHybrid(a, *aux, 0, SIZE - 1);
    }
}

#endif
