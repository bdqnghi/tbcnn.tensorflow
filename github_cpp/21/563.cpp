#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::min;

typedef vector<vector<int> > matrix;

int diff(char a, char b) {
	return (a == b) ? 0 : 1;
}

template<typename T>
std::ostream& operator<<(std::ostream& s, const std::vector<T>& v) {
	s.put('[');
	char comma[3] = {'\0', ' ', '\0'};
	for (const auto& e : v) {
		s << comma << e;
		comma[0] = ',';
	}
	return s << ']';
}

int edit_distance(string one, string two) {
	matrix E;
	int m = one.size();
	int n = two.size();

	E.resize(m + 1);
	for (int i = 0; i <= m; i++) {
		vector<int> temp;
		temp.resize(n + 1);
		E.at(i) = temp;
	}

	// set up top row
	for (int i = 0; i <= m; i++) {
		E.at(i).at(0) = i;
	}

	// set up left column
	for (int j = 1; j <= n; j++) {
		E.at(0).at(j) = j;
	}

	// find distances
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			E.at(i).at(j) = min({
				E.at(i - 1).at(j) + 1,
				E.at(i).at(j - 1) + 1,
				E.at(i - 1).at(j - 1) + diff(one.at(i - 1), two.at(j - 1)),
			});
		}
	}

	return E.at(m).at(n);
}

int main(int argc, char const *argv[]) {
	if (argc < 3)
		cerr << argv[0] << " string1 string2" << endl;

	string one = argv[1];
	string two = argv[2];

	cout << edit_distance(one, two) << endl;

	return 0;
}
