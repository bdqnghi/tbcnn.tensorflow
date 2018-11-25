#include <stdio.h>
#include <iostream>     
#include <algorithm>    
#include <vector>       
#include <sstream>
#include <string>
#include <fstream>

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

using namespace std;



vector<int> read_nums(const string &filename) {
  ifstream infile(filename);
  vector<int> vect;
  string line;
  while (getline(infile, line)) {
    istringstream iss(line);
    int n;
    if (!(iss >> n)) { break; } 
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
    
    int j = i;
    int t = data[i];
    while (j >= 1 && data[j-1] > t) {
      
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
