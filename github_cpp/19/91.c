#include "insertion_sort.cpp"
#include "merge_sort.cpp"
#include "quick_sort.cpp"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

using namespace std;
using namespace std::chrono;

void benchmark_sort_algorithm(string alg) {
  mt19937 mt(1821);
  uniform_real_distribution<float> dist(-1000, 1000);

  int sizes[] = {5000, 10000, 20000, 40000, 80000, 160000, 320000};
  for (int i = 0; i < 7; i++) {
    int N = sizes[i];
    float *a = new float[N];
    for (int i = 0; i < N; i++)
      a[i] = dist(mt);

    auto t1 = high_resolution_clock::now();
    if (alg.compare("merge-sort") == 0)
      merge_sort(a, N);
    else if (alg.compare("quick-sort") == 0)
      quick_sort(a, N);
    else if (alg.compare("STL-sort") == 0)
      sort(a, a + N);
    else if (alg.compare("insertion-sort") == 0)
      insertion_sort(a, N);
    auto t2 = high_resolution_clock::now();

    auto elapsed_time = duration_cast<milliseconds>(t2 - t1).count();
    cout << fixed << setprecision(3);
    cout << "Elapsed time " << alg << "\t" << sizes[i] << "\t" << elapsed_time
         << " milliseconds" << endl;
    delete[] a;
  }
}

int main(int argc, char **argv) {
  benchmark_sort_algorithm("insertion-sort");
  cout << "#####################################" << endl;
  benchmark_sort_algorithm("merge-sort");
  cout << "#####################################" << endl;
  benchmark_sort_algorithm("quick-sort");
  cout << "#####################################" << endl;
  benchmark_sort_algorithm("STL-sort");
  cout << "#####################################" << endl;
}
