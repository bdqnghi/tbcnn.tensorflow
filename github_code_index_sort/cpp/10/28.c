/**
 * Author: subond
 * Time: 2017-03-12
 * Function: 桶排序
 */
#include <cstdio>
#include <vector>
using namespace std;
vector<int> v, temp;
void bucketsort(vector<int> &data, int maxnum) {
  int k = 0;
  for(int i = 0; i <= maxnum; i++) {
    while(temp[i] > 0) {
      data[k++] = i;
      temp[i]--;
    }
  }
}
int main() {
  int n, maxnum, tempnum;
  scanf("%d %d", &n, &maxnum);
  v.resize(n);
  temp.resize(maxnum + 1);
  fill(temp.begin(), temp.end(), 0);
  for(int i = 0; i < n; i++) {
    scanf("%d", &tempnum);
    temp[tempnum]++;
  }
  bucketsort(v, maxnum);
  for(int i = 0; i < v.size(); i++) {
    if(i != 0) printf(" ");
    printf("%d", v[i]);
  }
  return 0;
}
