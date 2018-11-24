/**
 * 	author: satyajith
 * 	algorithm: bucket sort
 */

#include <cmath>
#include <iostream>
#include <list>
#include <vector>

// constants
#define N 10

// function declarations
std::list< float >* bucket_sort(float[]);

// operator overloading to print a list
std::ostream& operator<<(std::ostream& ostr, const std::list< float >& list) {
	for (auto& i : list)
		ostr << " " << i;
	return ostr;
}

int main(int argc, char const* argv[]) {
	// input array
	float arr[ N ] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};

	std::list< float >* final = bucket_sort(arr);
	std::cout << * final;						   // print final list
	final->erase(final->begin(), final->end());	// erase all elements

	delete final;	// free the memory
	return 0;
}

// the bucket sort routine definition
std::list< float >* bucket_sort(float arr[]) {
	int i;
	std::vector< std::list< float > > B(N);	// initialize a vector of lists

	for (i = 0; i < N; ++i)
		B[ floor(N * arr[ i ]) ].push_back(arr[ i ]);	// distribute into buckets

	for (i = 0; i < N; ++i)
		B[ i ].sort();	// sort each list in ascending order

	std::list< float >* final = new std::list< float >;	// final list of concatenated buckets
	auto iter = final->begin();							   // iterator to final list

	for (i = 0; i < N; ++i) {
		final->splice(iter, B[ i ]);	// concatenate all buckets
		iter = final->end();
	}

	B.erase(B.begin(), B.end());	// erase all data from the vector of lists

	return final;
}