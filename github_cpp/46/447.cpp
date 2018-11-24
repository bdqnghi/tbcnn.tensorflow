#include <iostream>

using namespace std;

template<int MAXN>
struct SegmentTree {
	int idx[4 * MAXN + 10];
	int bs;

	SegmentTree() {
		for (int i = 0; i < 4 * MAXN + 10; i++) {
			idx[i] = 0;
		}

		for (bs = 1; bs <= MAXN; bs *= 2) {}
	}
	
	void update(int x, int v) {
		x += bs;
		while (x) {
			idx[x] += v;
			x /= 2;
		}
	}

	int sum(int x, int y) {
		int res = 0;

		x += bs;
		y += bs;

		while (x < y) {
			if (x % 2 == 1) {
				res += idx[x];	
				x++;
			}

			if (y % 2 == 0) {
				res += idx[y];
				y--;
			}
			x /= 2;
			y /= 2;
		}

		if (x == y) {
			res += idx[x];
		}

		return res;
	}
};

int main() {
	SegmentTree<10> tree;
	for (int i = 0; i < 10; i++) {
		tree.update(i, i+1);
	}

	cout << tree.sum(0, 9) << endl;
	
	return 0;
}
