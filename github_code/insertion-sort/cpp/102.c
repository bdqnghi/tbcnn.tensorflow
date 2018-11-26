#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <array>
#include "swap.h"


#include <iostream>

namespace oal {
  namespace sorting {
    namespace insertionsort {
      // STATUS: working
      namespace normal{
        template <typename T, size_t S>
        void sort(std::array<T,S>& a) {
          size_t i,j;
          for (i = 1; i < S; ++i) {
            for (j = i; j > 0 && a[j] < a[j - 1]; --j)
              std::swap(a[j], a[j-1]);
          }
        }
      }

      // STATUS: working
      namespace withguard {
        template <typename T, size_t S>
        void sort(std::array<T,S>& a) {
          //http://coderevisited.com/insertion-sort/
          //http://algs4.cs.princeton.edu/21elementary/
          size_t i = S-1, j = 0;

          // Find guard; for loop below is equal to std::swap(a[l], *std::min_element(&a[l], &a[r])); (see sortRange(...))
          for (; i > 0; i--) {
            if (a[i] < a[i - 1]) {
              std::swap(a[i], a[i-1]);
            }
          }

  //        std::cout << "Loop one over" << std::endl;

          for (i = 2; i < S; i++) {
  //          std::cout << "outer[" << i << "] : inner[" << j << "]" << std::endl;
            for (j = i; a[j] < a[j - 1]; j--) {
  //            std::cout << "outer[" << i << "] : inner[" << j << "]" << std::endl;
              std::swap(a[j], a[j-1]);
            }
  //            if(i >= 4500)
  //              std::cout << "outer[" << i << "] : inner[" << j << "]" << std::endl;
          }
        }
      }

      // STATUS: not implemented
  //    namespace withguardidxtransform {
  //      template <typename T, size_t S>
  //      void sort(std::array<T,S>& a) {
  //        //http://coderevisited.com/insertion-sort/
  //        size_t i, j = 0;

  //        T tmp;
  //        for(i = 1; i < S; ++j) {
  //          tmp = a[i];
  //          for(j = i-1; (j > 0) && (a[j] < tmp); --j)
  //            a[j+1] = a[j];
  //          a[j+1] = tmp;
  //        }
  //      }
  //    }

      // STATUS: working (still some minor issue with incorrect access at some point; check indices again)
      namespace withguardidxtransform {
        template <typename T, size_t S>
        void sort(std::array<T,S>& a) {
          size_t r = S, l = 0;
          if (r == 0) return;

          size_t min = l;

          //used to be i < (r+1), which does not make sence since we start with r = SIZE,
          //thus the loop will iterate SIZE number of steps leading to incorrect access

          // von links nach rechts
          for (size_t i = l+1; i < r; ++i)
            if (a[i] < a[min]) min = i;

          std::swap(a[l], a[min]);

          for (size_t i = l+2; i < r + 1; ++i) {
            T tmp = a[i];
            for (size_t j = i; tmp < a[--j];)
                 std::swap(a[j + 1], a[j]);
          }
        }
      }

      // My old version
      template <typename T, size_t S>
      void sortRange(array<T,S>& a, size_t lo, size_t hi) {
        size_t i = lo, j;

        for (; i <= hi; ++i)
          for (j = i; j > lo && a[j] < a[j-1]; --j)
            swap(a, j, j-1);
      }

      // New version
  //    template<typename T, size_t SIZE>
  //    void sortRange(std::array<T, SIZE>& a, size_t l, size_t r)
  //    {
  //        // Spaw the smalles element on the given position
  //        std::swap(a[l], *std::min_element(&a[l], &a[r]));

  //        //Run over the right array
  //        for (size_t i = l + 1; i < r; ++i) {
  //            T t = a[i];
  //            // Runs over from the current element in the array backwards to the left and sets it on the correct position if it's smaller
  //            for (size_t j = i; t < a[--j];) { // before this j has been decremented once
  //                std::swap(a[j+1], a[j]);
  //            }
  //        }
  //    }
    }
  }
}

#endif // INSERTIONSORT_H
