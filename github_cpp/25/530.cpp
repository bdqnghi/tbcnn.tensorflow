#include<cstdio>
#include<cassert>
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// factorials[i] = i!
int factorials[12];
// perm 이 [0..n-1] 의 permutation 일 때 사전순 번호를 반환한다. (0에서 시작)
int getIndex(const vector<int>& perm) {
	int ret = 0;
	for(int i = 0; i < perm.size(); ++i) {
		int less = 0;
		for(int j = i+1; j < perm.size(); ++j) {
			if(perm[j] < perm[i])
				++less;
		}
		ret += factorials[perm.size()-i-1] * less;
	}
	return ret;
}

int main() {
	factorials[0] = 1;
	for(int i = 1; i < 12; ++i)
		factorials[i] = factorials[i-1] * i;
	vector<int> a;
	for(int i = 0; i < 8; ++i) a.push_back(i);
	int x = 0;
	do {
		assert(getIndex(a) == x++);
	} while(next_permutation(a.begin(), a.end()));
	printf("checked %d permutations\n", x);
}

