//
//  shell-sort.cpp
//  Copyright (c) 2017 Dylan Brown. All rights reserved.
//

// NOTES
// Shell sort is a variation on insertion sort which reduces the required number
// of swaps. The idea is to sort to interleaved subsequences with large gaps
// between the elements. Theses gaps shrink in a predefined increment sequence.
//
// [ S H E L L S O R T E X A M P L E ]
//     ... completed to 4-sort ...
// [ L E E A M H L E P S O L T S X R ] // h-sorted.
// [ L-------M-------P-------T       ]
// [   E-------H-------S-------S     ] // Each row
// [     E-------L-------O-------X   ] // is sorted.
// [       A-------E-------L-------R ]
//
// First published by Donald Shell (ACM, 1959). This sorting algorithm is a
// useful tool when a std::sort is unavailable, as in some embedded systems.
// The best increment sequence is an unsetteled question. Here are some options:
//   D. Shell (original): floor( N/(2^k) ), ... 1.           // O(n^2)
// ->V. Pratt (1971): (3^k - 1) / 2, and < ceil(N/3) ... 1.  // O(n^(3/2))
//   M. Ciura (2001): 1750, 701, 301, 132, 57, 23, 10, 4, 1. // Empirical proof

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <typename T> class Shell {
public:
  // requires Sortable<T> (T must implement comparison operators).
  void sort(std::vector<T> &a);

  bool is_sorted(const std::vector<T> &a) {
    for (int i = 1; i < a.size(); i++) {
      if (less(a[i], a[i - 1])) {
        return false;
      }
    }
    return true;
  }

  void show(const std::vector<T> &a) {
    for (auto item : a) {
      std::cout << item << " ";
    }
    std::cout << std::endl;
  }

private:
  // Returns true if v < w. Again, T must implement comparison operators.
  bool less(T v, T w) { return (v < w); }
  // Pass by reference to ensure std::swap mutates the caller's data.
  void exch(std::vector<T> &a, int i, int j) { std::swap(a[i], a[j]); }
};

template <typename T> void Shell<T>::sort(std::vector<T> &a) {
  int N = a.size();
  int h = 1;
  while (h < N / 3) // Note the integer division.
    h = 3 * h + 1;  // 1, 4, 13, 40, 121, 364, 1093, ...
  
  while (h >= 1) {
    for (int i = h; i < N; i++) {
      for (int j = i; j >= h && less(a[j], a[j - h]); j -= h)
        exch(a, j, j - h);
    }

    h = h / 3; // Again, note the integer division.
  }
}

int main(int argc, char *argv[]) {
  // Read file given on command line.
  std::string filename;
  if (argc != 2) {
    std::cout << "Usage: shell-sort ../algs4-data/words3.txt" << std::endl;
    return EXIT_FAILURE;
  } else {
    filename = argv[1];
  }

  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    std::cout << "ERROR: failed to open \"" << filename << "\" for reading."
              << std::endl;
    return EXIT_FAILURE;
  }

  // Instantiate a shell sort object.
  auto shl = Shell<std::string>();

  // For this example, we'll sort strings in alphabetical order.
  // Read the input data into a std::vector of std::string tokens.
  std::vector<std::string> tokens;
  for (std::string tkn; input_file >> tkn;) {
    tokens.push_back(tkn);
  }
  input_file.close();

  // Apply the weighted quick-union algorithm to the input data.
  auto begin = std::chrono::steady_clock::now();
  shl.sort(tokens);
  auto end = std::chrono::steady_clock::now();

  // Ensure that the data structure is sorted.
  if (!shl.is_sorted(tokens)) {
    std::cout << "ERROR: upon review, shell sort"
                 " failed to completely sort the data."
              << std::endl;
    return EXIT_FAILURE;
  }

  // Output the performance and results.
  std::cout << "Shell::sort, elapsed time (ns) = "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
                   .count()
            << std::endl;
  shl.show(tokens);
}
