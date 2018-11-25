
























#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <typename T> class Shell {
public:
  
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
  
  bool less(T v, T w) { return (v < w); }
  
  void exch(std::vector<T> &a, int i, int j) { std::swap(a[i], a[j]); }
};

template <typename T> void Shell<T>::sort(std::vector<T> &a) {
  int N = a.size();
  int h = 1;
  while (h < N / 3) 
    h = 3 * h + 1;  
  
  while (h >= 1) {
    for (int i = h; i < N; i++) {
      for (int j = i; j >= h && less(a[j], a[j - h]); j -= h)
        exch(a, j, j - h);
    }

    h = h / 3; 
  }
}

int main(int argc, char *argv[]) {
  
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

  
  auto shl = Shell<std::string>();

  
  
  std::vector<std::string> tokens;
  for (std::string tkn; input_file >> tkn;) {
    tokens.push_back(tkn);
  }
  input_file.close();

  
  auto begin = std::chrono::steady_clock::now();
  shl.sort(tokens);
  auto end = std::chrono::steady_clock::now();

  
  if (!shl.is_sorted(tokens)) {
    std::cout << "ERROR: upon review, shell sort"
                 " failed to completely sort the data."
              << std::endl;
    return EXIT_FAILURE;
  }

  
  std::cout << "Shell::sort, elapsed time (ns) = "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
                   .count()
            << std::endl;
  shl.show(tokens);
}
