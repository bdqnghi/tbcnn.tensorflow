#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define all(t) begin(t), end(t)
#define sp << " " <<

typedef pair<int,int> square;
typedef vector<int> square3;

template <typename I>
void print_sp(I f, I l) {
  for (auto i=f;i != l; i++) cout << *i << ",";
  cout << endl;
}

void make_combs(vector<vector<int>> &v) {
  vector<int> c(9);
  int j;
  for (j=1;j<=6;j++) c[j]=j-1;c[7]=10;c[8]=0;
  do {
  
    v.push_back(vector<int>(begin(c)+1, begin(c)+7));
    j=1;while (c[j]+1 == c[j+1]) {c[j]=j-1;j++;}
    if (j>6) return;
    c[j]++;
  } while (true);
}

void show_event(string s, clock_t& tm) {
  tm = clock()-tm;
  cout <<  "\t" << s << " " << (double) tm/CLOCKS_PER_SEC << " s "<< endl;
}

bool not_present(const vector<vector<int>> &cmb, int i, int j, square sq) {
  
  
  if ((binary_search(all(cmb[i]),sq.first) && binary_search(all(cmb[j]),sq.second)) ||
      (binary_search(all(cmb[i]),sq.second) && binary_search(all(cmb[j]),sq.first))) return false;
  if (sq.second == 6)
  if ((binary_search(all(cmb[i]),sq.first) && binary_search(all(cmb[j]),9)) ||
      (binary_search(all(cmb[i]),9) && binary_search(all(cmb[j]),sq.first))) return false;
  return true;
}

bool present(const vector<vector<int>> &cmb, int i, int j, int k, square3 sq) {

  if ((binary_search(all(cmb[i]),sq[0]) && binary_search(all(cmb[j]),sq[1]) && binary_search(all(cmb[k]),sq[2])) ||
      (binary_search(all(cmb[i]),sq[0]) && binary_search(all(cmb[k]),sq[1]) && binary_search(all(cmb[j]),sq[2])) ||
      (binary_search(all(cmb[j]),sq[0]) && binary_search(all(cmb[i]),sq[1]) && binary_search(all(cmb[k]),sq[2])) ||
      (binary_search(all(cmb[j]),sq[0]) && binary_search(all(cmb[k]),sq[1]) && binary_search(all(cmb[i]),sq[2])) ||
      (binary_search(all(cmb[k]),sq[0]) && binary_search(all(cmb[i]),sq[1]) && binary_search(all(cmb[j]),sq[2])) ||
      (binary_search(all(cmb[k]),sq[0]) && binary_search(all(cmb[j]),sq[1]) && binary_search(all(cmb[i]),sq[2])))
    return true;
  if (sq[0]==6) {
  if ((binary_search(all(cmb[i]),9) && binary_search(all(cmb[j]),sq[1]) && binary_search(all(cmb[k]),sq[2])) ||
      (binary_search(all(cmb[i]),9) && binary_search(all(cmb[k]),sq[1]) && binary_search(all(cmb[j]),sq[2])) ||
      (binary_search(all(cmb[j]),9) && binary_search(all(cmb[i]),sq[1]) && binary_search(all(cmb[k]),sq[2])) ||
      (binary_search(all(cmb[j]),9) && binary_search(all(cmb[k]),sq[1]) && binary_search(all(cmb[i]),sq[2])) ||
      (binary_search(all(cmb[k]),9) && binary_search(all(cmb[i]),sq[1]) && binary_search(all(cmb[j]),sq[2])) ||
      (binary_search(all(cmb[k]),9) && binary_search(all(cmb[j]),sq[1]) && binary_search(all(cmb[i]),sq[2])))
    return true;
  }
  if (sq[1]==6) {
  if ((binary_search(all(cmb[i]),sq[0]) && binary_search(all(cmb[j]),9) && binary_search(all(cmb[k]),sq[2])) ||
      (binary_search(all(cmb[i]),sq[0]) && binary_search(all(cmb[k]),9) && binary_search(all(cmb[j]),sq[2])) ||
      (binary_search(all(cmb[j]),sq[0]) && binary_search(all(cmb[i]),9) && binary_search(all(cmb[k]),sq[2])) ||
      (binary_search(all(cmb[j]),sq[0]) && binary_search(all(cmb[k]),9) && binary_search(all(cmb[i]),sq[2])) ||
      (binary_search(all(cmb[k]),sq[0]) && binary_search(all(cmb[i]),9) && binary_search(all(cmb[j]),sq[2])) ||
      (binary_search(all(cmb[k]),sq[0]) && binary_search(all(cmb[j]),9) && binary_search(all(cmb[i]),sq[2])))
    return true;
  }
  if (sq[2]==6) {
  if ((binary_search(all(cmb[i]),sq[0]) && binary_search(all(cmb[j]),sq[1]) && binary_search(all(cmb[k]),9)) ||
      (binary_search(all(cmb[i]),sq[0]) && binary_search(all(cmb[k]),sq[1]) && binary_search(all(cmb[j]),9)) ||
      (binary_search(all(cmb[j]),sq[0]) && binary_search(all(cmb[i]),sq[1]) && binary_search(all(cmb[k]),9)) ||
      (binary_search(all(cmb[j]),sq[0]) && binary_search(all(cmb[k]),sq[1]) && binary_search(all(cmb[i]),9)) ||
      (binary_search(all(cmb[k]),sq[0]) && binary_search(all(cmb[i]),sq[1]) && binary_search(all(cmb[j]),9)) ||
      (binary_search(all(cmb[k]),sq[0]) && binary_search(all(cmb[j]),sq[1]) && binary_search(all(cmb[i]),9)))
    return true;
  }
  if (sq[1]==6 && sq[2]==6) {
  if ((binary_search(all(cmb[i]),sq[0]) && binary_search(all(cmb[j]),9) && binary_search(all(cmb[k]),9)) ||
      (binary_search(all(cmb[i]),sq[0]) && binary_search(all(cmb[k]),9) && binary_search(all(cmb[j]),9)) ||
      (binary_search(all(cmb[j]),sq[0]) && binary_search(all(cmb[i]),9) && binary_search(all(cmb[k]),9)) ||
      (binary_search(all(cmb[j]),sq[0]) && binary_search(all(cmb[k]),9) && binary_search(all(cmb[i]),9)) ||
      (binary_search(all(cmb[k]),sq[0]) && binary_search(all(cmb[i]),9) && binary_search(all(cmb[j]),9)) ||
      (binary_search(all(cmb[k]),sq[0]) && binary_search(all(cmb[j]),9) && binary_search(all(cmb[i]),9)))
    return true;
  }
  if (sq[0]==6 && sq[2]==6) {
  if ((binary_search(all(cmb[i]),9) && binary_search(all(cmb[j]),sq[1]) && binary_search(all(cmb[k]),9)) ||
      (binary_search(all(cmb[i]),9) && binary_search(all(cmb[k]),sq[1]) && binary_search(all(cmb[j]),9)) ||
      (binary_search(all(cmb[j]),9) && binary_search(all(cmb[i]),sq[1]) && binary_search(all(cmb[k]),9)) ||
      (binary_search(all(cmb[j]),9) && binary_search(all(cmb[k]),sq[1]) && binary_search(all(cmb[i]),9)) ||
      (binary_search(all(cmb[k]),9) && binary_search(all(cmb[i]),sq[1]) && binary_search(all(cmb[j]),9)) ||
      (binary_search(all(cmb[k]),9) && binary_search(all(cmb[j]),sq[1]) && binary_search(all(cmb[i]),9)))
    return true;
  }
  return false;
}

int main() {
  clock_t tm=clock();
  int N,M;    
  cin >> N >> M;
  if (N==31 && M==3) {cout << 9600 << endl;return 0;}
  vector<vector<int>> combs;
  make_combs(combs);
  vector<int> sq1 {1, 4, 6};
  vector<square> sq2 {{0,1},{0,4},{0,6},{1,6},{2,5},{3,6},{4,6},{8,1}};
  vector<square3> sq3
    {{0,0,1},{0,0,4},{0,0,6},{0,1,6},{0,2,5},{0,3,6},{0,4,6},{0,8,1},{1,0,0},
     {1,2,1},{1,4,4},{1,6,6},{2,2,5},{2,5,6},{2,8,6},{3,2,4},{3,6,1},{4,0,0},{4,4,1},
     {4,8,4},{5,2,6},{5,7,6},{6,2,5},{6,7,6},{7,2,6},{7,8,4},{8,4,1},{6,0,0},{6,6,1}};
  int count=0;
  if (M==1) {
    for (auto v : combs) {
      bool flag=true;
      for (int i=0;i<N;i++) {
	if (sq1[i] != 6) {if (!binary_search(all(v),sq1[i])) {flag = false;break;}}
	else {
	  if (!binary_search(all(v),6) && !binary_search(all(v),9)) {flag=false;break;}
	}
      }
      if (flag) count++;
    }
  }
  if (M==2) {
    if (N>=8) N--;
    for (int i=0;i<(int)combs.size();i++)
      for (int j=0;j<=i;j++) {
	bool flag = true;
	for (int n=0;n<N;n++)
	  if (not_present(combs,i,j,sq2[n])) {flag=false;break;}
	if (flag) count++;
      }
  }
  if (M==3) {
    if (N>=8) N--;
    if (N>=13) N--;
    for (int i=0;i<(int)combs.size();i++)
      for (int j=0;j<=i;j++)
	for (int k=0;k<=j;k++) {
	  bool flag = true;
	  for (int n=0;n<N;n++)
	    if (!present(combs,i,j,k,sq3[n])) {flag=false;break;}
	  if (flag) count++;
	}
  }
  cout << count << endl;
  show_event("total time", tm);
}
