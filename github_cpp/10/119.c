

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::min;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::vector;


int Levenshtein_distance(string A, string B) {
  
  if (A.size() < B.size()) {
    swap(A, B);
  }

  vector<int> D(B.size() + 1);
  
  iota(D.begin(), D.end(), 0);

  for (int i = 1; i <= A.size(); ++i) {
    int pre_i_1_j_1 = D[0];  
    D[0] = i;
    for (int j = 1; j <= B.size(); ++j) {
      int pre_i_1_j = D[j];  
      D[j] = A[i - 1] == B[j - 1] ? pre_i_1_j_1
                                  : 1 + min(pre_i_1_j_1, min(D[j - 1], D[j]));
      
      pre_i_1_j_1 = pre_i_1_j;
    }
  }
  return D.back();
}


string rand_string(int len) {
  default_random_engine gen((random_device())());
  uniform_int_distribution<int> dis('a', 'z');
  string ret;
  while (len--) {
    ret += dis(gen);
  }
  return ret;
}

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  string A, B;
  
  A = "Saturday", B = "Sunday";
  assert(3 == Levenshtein_distance(A, B));
  A = "kitten", B = "sitting";
  assert(3 == Levenshtein_distance(A, B));

  if (argc == 3) {
    A = argv[1], B = argv[2];
  } else {
    uniform_int_distribution<int> dis(1, 100);
    A = rand_string(dis(gen));
    B = rand_string(dis(gen));
  }
  cout << A << endl << B << endl;
  cout << Levenshtein_distance(A, B) << endl;
  return 0;
}
