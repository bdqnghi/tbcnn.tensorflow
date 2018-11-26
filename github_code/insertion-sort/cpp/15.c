#include <stdio.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector
#include <sstream>
#include <string>
#include <fstream>

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

using namespace std;

/*
  $ clang++ -std=c++11 -stdlib=libc++ insertion-sort.cpp
  (No optimization option)
  - real  0m0.017s
  - user  0m0.005s
  - sys   0m0.003s

  $ clang++ -std=c++11 -stdlib=libc++ -Os insertion-sort.cpp
  (-Os optimiztion)
  - real  0m0.012s
  - user  0m0.002s
  - sys   0m0.002s
*/

vector<int> read_nums(const string &filename) {
  ifstream infile(filename);
  vector<int> vect;
  string line;
  while (getline(infile, line)) {
    istringstream iss(line);
    int n;
    if (!(iss >> n)) { break; } // error
    vect.push_back(n);
  }
  return vect;
}

void write_nums(const string &filename, const vector<int> nums) {
  ofstream file;
  file.open (filename);
  for(int n: nums) {
    file << n << '\n';
  }
  file.close();
}

void insertion_sort(vector<int> &data) {
  FOR(i, 1, data.size()) {
    // data[0..i-1] are sorted
    int j = i;
    int t = data[i];
    while (j >= 1 && data[j-1] > t) {
      // data[0..j-1] are sorted. data[j] needs to be inserted.
      data[j] = data[j-1];
      j -= 1;
    }
    data[j] = t;
  }
}

int main () {
  auto data = read_nums("input.dat");

  insertion_sort(data);

  write_nums("output.dat", data);

  return 0;
}
