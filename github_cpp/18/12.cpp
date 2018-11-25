

#include <climits>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

unique_ptr< vector< int > > rod_cut_bottom_up(vector< int > &);
void rod_cut_solution(vector< int > &);

int main(int argc, char const *argv[]) {
	vector< int > price({0, 1, 5, 8, 9, 10, 17, 17, 20});
	
	rod_cut_solution(price);
	return 0;
}


void rod_cut_solution(vector< int > &p) {
	unique_ptr< vector< int > > solution = rod_cut_bottom_up(p);

	int r = solution->back();	
	solution->pop_back();

	printf("revenue: %d", r);
	int n = p.size() - 1;
	printf("\nsolution: ");

	while (n > 0) {
		printf("%d, ", solution->at(n));
		n -= solution->at(n);
	}
}


unique_ptr< vector< int > > rod_cut_bottom_up(vector< int > &p) {
	int n = p.size() - 1;									  
	vector< int > r({0});									  
	unique_ptr< vector< int > > s(new vector< int >({0}));	
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

	s->push_back(r.at(n));	
	return s;
}