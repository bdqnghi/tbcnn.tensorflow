/* levenshtein.cpp
  return the Levenshtein distance between two words prompted by the user, using
  a recursive technique

  implementation strategy: following its own formula and defining the base
  induction
*/

#include <iostream>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

int editDistance(string u, string v){
  /* basic induction */
  if (u.size() == 0) return v.size();
  if (v.size() == 0) return u.size();

  /* implement the recursion part */
  int ind = 0;    // indicator function
  int i = 0;      // counter for the strings
  ind = v[i] == u[i]? 0 : 1;

  /* find the minimum and return the distance
  /* obs: instead of going backwards, we go forward until we find the
  immediate whitespace after the last character of a string */
  int lev1 = editDistance(u.substr(i + 1), v) + 1;
  int lev2 = editDistance(u, v.substr(i + 1)) + 1;
  int lev3 = editDistance(u.substr(i + 1), v.substr(i + 1)) + ind;

  if (lev1 < lev2 && lev1 < lev3) return lev1;
  else if (lev2 < lev3) return lev2;
  else return lev3;
}

int main(void) {
  string input, u, v;
  getline(cin, input);

  /* find the whitespace between the two words */
  int i = 0;
  while (!isspace(input[i])) {
    i++;
  }

  /* get the two separate strings from the input string */
  v = input.substr(0, i);
  u = input.substr(i + 1, input.size());

  /* get the Levenshtein and print it */
  cout << editDistance(u, v) << endl;

  return 0;
}
