#include <iostream>
#include <string>

using namespace std;

int minimum(int a, int b, int c) {
  if (a <= b) {
    if (a <= c) return a;
    else return c;

  } else {
    if (b <= c) return b;
    else return c;

  }
}

int levenshtein_distance(string str1, string str2, int m, int n) {
  if (m == 0) return n;
  if (n == 0) return m;

  if (str1[m-1] == str2[n-1]) {
    return levenshtein_distance(str1,str2,m-1,n-1);
  }

  return 1 + minimum(levenshtein_distance(str1,str2,m,n-1),     //insert
                      levenshtein_distance(str1,str2,m-1,n),    // delete
                      levenshtein_distance(str1,str2,m-1,n-1)); // replace
}

int main(int argc, char const *argv[]) {
  string s = "accuse";
  string t = "assume";

  cout << levenshtein_distance(s,t,s.length(),t.length()) << endl;

  return 0;
}
