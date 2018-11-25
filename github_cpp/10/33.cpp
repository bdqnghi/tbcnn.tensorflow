

#include <iostream>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

int editDistance(string u, string v){
  
  if (u.size() == 0) return v.size();
  if (v.size() == 0) return u.size();

  
  int ind = 0;    
  int i = 0;      
  ind = v[i] == u[i]? 0 : 1;

  
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

  
  int i = 0;
  while (!isspace(input[i])) {
    i++;
  }

  
  v = input.substr(0, i);
  u = input.substr(i + 1, input.size());

  
  cout << editDistance(u, v) << endl;

  return 0;
}
