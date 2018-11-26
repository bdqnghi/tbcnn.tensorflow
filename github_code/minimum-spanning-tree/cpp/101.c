#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
static const int Max = 100;
static const int Infinit = 1000000; // ����
static const int Nil = -1; // 

enum Status {
	Not_Searched = 0,
	Searched = 1,
	Mts = 2 
};

int n;
int M[Max][Max] = {};
Status st[Max] = {}; 
int min_cost[Max] = {}; // i �ԖڂɂȂ���_�ł̍ŏ��R�X�g
int parent[Max] = {}; // �e��index

int prim_search() {
	for (int i = 0; i < n; i++) {
		min_cost[i] = Infinit;
		parent[i] = -1;
		st[i] = Not_Searched;
	}
	min_cost[0] = 0;

	while (1) {
		int mincost = Infinit;
		int mincost_idx = -1;

		for (int i = 0; i < n; i++) {
			if (st[i] != Mts && min_cost[i] < mincost) {
				mincost = min_cost[i];
				mincost_idx = i;
			}
		}
		if (mincost_idx == -1) {
			break;
		}
		st[mincost_idx] = Mts;
		for (int i = 0; i < n; i++) {
			if (st[i] != Mts && M[mincost_idx][i] != Infinit) {
				if (min_cost[i] > M[mincost_idx][i]) {
					min_cost[i] = M[mincost_idx][i];
					parent[i] = mincost_idx;
					st[i] = Searched;
				}
			}
		}
	}
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (parent[i] != Nil) sum += M[i][parent[i]];
	}
	return sum;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int e;
			cin >> e;
			M[i][j] = (e == -1) ? Infinit : e;
		}
	}

	cout << prim_search() << endl;
	return 0;
}

/*
vector<string> split(string& str, char separator) {
	stringstream sstream(str);
	string part;
	vector<string> result;

	while (getline(sstream, part, separator)) {
		result.push_back(part);
	}
	return result;
}
*/
