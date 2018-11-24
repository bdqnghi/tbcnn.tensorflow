//水平序凸包
inline bool turn_left(const point &a, const point &b, const point &c) {
	return det(b - a, c - a) > EPS;
}
inline bool turn_right(const point &a, const point &b, const point &c) {
	return det(b - a, c - a) < -EPS;
}
inline vector<point> convex_hull(vector<point> a) {
	int n = (int)a.size(), cnt = 0;r
	sort(a.begin(), a.end());
	vector<point> ret;
	for (int i = 0; i < n; ++i) {
		while (cnt > 1 && turn_left(ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt;
			ret.pop_back();
		}
		ret.push_back(a[i]);
		++cnt;
	}
	int fixed = cnt;
	for (int i = n - 1; i >= 0; --i) {
		while (cnt > fixed && turn_left(ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt;
			ret.pop_back();
		}
		ret.push_back(a[i]);
		++cnt;
	}
	// this algorithm will preserve the points which are collineation
	// the lowest point will occur twice , i.e. ret.front () == ret.back ()
	return ret;
}
