














#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

template <typename T> class Selection {
public:
  
  void sort(vector<T> &a);

  bool is_sorted(const vector<T> &a) {
    for (int i = 1; i < a.size(); i++) {
      if (less(a[i], a[i - 1])) {
        return false;
      }
    }
    return true;
  }

  void show(const vector<T> &a) {
    for (auto item : a) {
      cout << item << " ";
    }
    cout << endl;
  }

private:
  
  bool less(T v, T w) { return (v < w); }
  
  void exch(vector<T> &a, int i, int j) { std::swap(a[i], a[j]); }
};

template <typename T> void Selection<T>::sort(vector<T> &a) {
  int N = a.size();
  for (int i = 0; i < N; i++) {
    
    int min = i;
    for (int j = i + 1; j < N; j++) {
      if (less(a[j], a[min])) {
        min = j;
      }
    }
    exch(a, i, min);
  }
}

int main(int argc, char *argv[]) {
  
  string filename;
  if (argc != 2) {
    cout << "Usage: selection-sort ../algs4-data/words3.txt" << endl;
    return EXIT_FAILURE;
  } else {
    filename = argv[1];
  }

  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    cout << "ERROR: failed to open \"" << filename << "\" for reading." << endl;
    return EXIT_FAILURE;
  }

  
  auto sel = Selection<string>();

  
  
  vector<string> tokens;
  for (string tkn; input_file >> tkn;) {
    tokens.push_back(tkn);
  }
  input_file.close();

  
  auto begin = std::chrono::steady_clock::now();
  sel.sort(tokens);
  auto end = std::chrono::steady_clock::now();

  
  if (!sel.is_sorted(tokens)) {
    cout << "ERROR: upon review, selection sort failed "
            "to completely sort the data."
         << endl;
    return EXIT_FAILURE;
  }

  
  cout << "Selection::sort, elapsed time (ns) = "
       << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
              .count()
       << endl;
  sel.show(tokens);
}
