#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef double coord_t;
typedef double coord2_t;

struct Point {
	coord_t x, y;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

coord2_t cross(const Point &O, const Point &A, const Point &B) {
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point> P) {
	int n = P.size(), k = 0;
	if (n == 1) return P;
	vector<Point> H(2*n);

	sort(P.begin(), P.end());

	for (int i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	H.resize(k-1);
	return H;
}

int main() {
    long n;
    double x, y;
    cin >> n;

    vector<struct Point> points;
    while (n--) {
        cin >> x >> y;
        struct Point p = {x, y};
        points.push_back(p);
    };
    vector<struct Point> hull = convex_hull(points);
    // ...
    return 0;
}