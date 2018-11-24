#include <iostream>
#include <vector>
#define INF 2 << 8 
#define pb push_back


using namespace std;

typedef vector<int> vi;

void mergeSort(vi &v, int s) {
  if (s == 1) return;

  vi u1, u2;
  for(int i=0; i < s/2; i++) u1.pb(v[i]);
  for(int i=s/2; i < s; i++) u2.pb(v[i]);

  mergeSort(u1, s/2);
  mergeSort(u2, s/2);

  u1.pb(INF);
  u2.pb(INF);

  int ini1 = 0, ini2 = 0;

  for(int i = 0; i < s; i++) {
    if(u1[ini1] < u2[ini2]) {
      v[i] = u1[ini1];
      ini1++;
    }
    else {
      v[i] = u2[ini2];
      ini2++;
    }
  }

  return;
}

int main() {
  vi v = {1, 4, 3, 5, 7, 8, 2, 6};
  mergeSort(v, v.size());

  for(int i : v) {
    cout << i << " ";
  } cout << endl;

  return 0;
}
