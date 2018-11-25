

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int cnt = 0;



int levenshteinDistanceBacktrace (const string& a, const string& b, int i, int j) {
  
  const int possible_edits = 3;
  array<int, possible_edits> distances{{0}};
  cout << i << " " << j << " " << cnt++ <<  endl;
  
  if (i < 0) return j+1;
  if (j < 0) return i+1;

  
  distances[0] = levenshteinDistanceBacktrace(a, b, i-1, j-1) + (a[i] != b[j]);
  
  distances[1] = levenshteinDistanceBacktrace(a, b, i, j-1) + 1;
  
  distances[2] = levenshteinDistanceBacktrace(a, b, i-1, j) + 1;

  return *(min_element(distances.begin(), distances.end()));
}

int levenshteinDistanceBacktrace (const string& a, const string& b) {
  return levenshteinDistanceBacktrace(a, b, a.size()-1, b.size()-1);
}





int levenshteinDistanceCache (const string& a, const string& b, int i, int j, vector<vector<int>>* cache_ptr) {
  
  const int possible_edits = 3;
  array<int, possible_edits> distances{{0}};
  vector<vector<int>>& cache = *cache_ptr;
  
  
  if (i < 0) return j+1;
  if (j < 0) return i+1;
  if (cache[i][j] >= 0) return cache[i][j];

  cout << i << " " << j << " " << cnt++ <<  endl;

  
  distances[0] = levenshteinDistanceCache(a, b, i-1, j-1, cache_ptr) + (a[i] != b[j]);
  
  distances[1] = levenshteinDistanceCache(a, b, i, j-1, cache_ptr) + 1;
  
  distances[2] = levenshteinDistanceCache(a, b, i-1, j, cache_ptr) + 1;

  cache[i][j] = *(min_element(distances.begin(), distances.end()));

  return cache[i][j];
}

int levenshteinDistanceCache (const string& a, const string& b) {
  vector<vector<int>> cache(a.size(), vector<int>(b.size(),-1));
  return levenshteinDistanceCache(a, b, a.size()-1, b.size()-1, &cache);
}








int levenshteinDistanceTabular (const string& a, const string& b) {
  
  vector<vector<int>> table(a.size()+1, vector<int>(b.size()+1,-1));

  
  for (int i = 0; i <= a.size(); ++i) table[i][0] = i;
  for (int j = 0; j <= b.size(); ++j) table[0][j] = j;

  for (int i = 1; i <= a.size(); ++i) {
    for (int j = 1; j <= b.size(); ++j) {
      table[i][j] = min(table[i-1][j-1] + (a[i] != b[j]), 
			min(table[i][j-1] + 1, table[i-1][j] + 1));
      cout << table[i][j] << " ";
    }
    cout << endl;
  }

  return table[a.size()][b.size()];
}



int main (void) {
  string s1{"Saturday"}, s2{"Sundays"};
  cout << levenshteinDistanceTabular(s1, s2);
}
