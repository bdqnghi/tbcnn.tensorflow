// The rod-cutting problem
// Dynamic programming approach
// Author: Chakresh Singh
// Date: 12-21-2016
#include <iostream>

using namespace std;
int count = 0;

int r[10];
int max(int a, int b) {
  // a util function..
  return (a > b ? a : b);
}

int memoized_cut_rod_aux(int p[], int n) {

  if (r[n - 1] >= 0)
    return r[n - 1];
  // Set revenue to minus infinity
  int q = -1;
  if (n == 0)
    q = 0;
  else
    for (int i = 0; i < n; i++) {
      q = max(q, (p[i] + memoized_cut_rod_aux(p, n - i - 1)));
    }
  r[n - 1] = q;
  count++;
  return q;
}

int main() {

  int p[10] = {1,  5,  8,  9,  10,
               17, 17, 20, 24, 30}; // taken as is, from the book's example
  for (int j = 0; j < 10; j++)
    r[j] = -1;
  for (int i = 0; i < 10; i++)
    cout << "\nThe revenue for rod of lenght " << i + 1
         << " is: " << memoized_cut_rod_aux(p, i + 1);

  cout << "\nCount: " << count;
  return 0;
}
