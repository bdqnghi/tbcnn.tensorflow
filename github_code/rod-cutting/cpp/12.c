/**
 * 	author: satyajith
 * 	program: rod cutting; dynamic programming bottom-up approach
 *
 * 	question: Given a rod of length 'n' units and a table of prices P(i) for
 * 	i = 1,2,...,n determine the maximum revenue r(n) obtainable by cutting up
 * 	the rod and selling the pieces.
 *
 * 	compile using: g++ -O3 <file-name> -std=c++11
 */

#include <climits>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

unique_ptr< vector< int > > rod_cut_bottom_up(vector< int > &);
void rod_cut_solution(vector< int > &);

int main(int argc, char const *argv[]) {
	vector< int > price({0, 1, 5, 8, 9, 10, 17, 17, 20});
	// use push_back for a larger input from a file
	rod_cut_solution(price);
	return 0;
}

// compute and display revenue and solution
void rod_cut_solution(vector< int > &p) {
	unique_ptr< vector< int > > solution = rod_cut_bottom_up(p);

	int r = solution->back();	// extract revenue value
	solution->pop_back();

	printf("revenue: %d", r);
	int n = p.size() - 1;
	printf("\nsolution: ");

	while (n > 0) {
		printf("%d, ", solution->at(n));
		n -= solution->at(n);
	}
}

// compute and return solution and revenue(appended to solution here)
unique_ptr< vector< int > > rod_cut_bottom_up(vector< int > &p) {
	int n = p.size() - 1;									  // rod length
	vector< int > r({0});									  // revenue
	unique_ptr< vector< int > > s(new vector< int >({0}));	// aux vector for solution
	int i = 0, j = 0, temp_rev = 0;

	for (i = 1; i <= n; ++i) {
		temp_rev = INT_MIN;
		s->push_back(0);
		for (j = 1; j <= i; ++j) {
			if (temp_rev < p.at(j) + r.at(i - j)) {
				temp_rev = p.at(j) + r.at(i - j);
				s->at(i) = j;
			}
		}
		r.push_back(temp_rev);
	}

	s->push_back(r.at(n));	// append revenue
	return s;
}