

#include <cmath>
#include <iostream>
#include <list>
#include <vector>


#define N 10


std::list< float >* bucket_sort(float[]);


std::ostream& operator<<(std::ostream& ostr, const std::list< float >& list) {
	for (auto& i : list)
		ostr << " " << i;
	return ostr;
}

int main(int argc, char const* argv[]) {
	
	float arr[ N ] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};

	std::list< float >* final = bucket_sort(arr);
	std::cout << * final;						   
	final->erase(final->begin(), final->end());	

	delete final;	
	return 0;
}


std::list< float >* bucket_sort(float arr[]) {
	int i;
	std::vector< std::list< float > > B(N);	

	for (i = 0; i < N; ++i)
		B[ floor(N * arr[ i ]) ].push_back(arr[ i ]);	

	for (i = 0; i < N; ++i)
		B[ i ].sort();	

	std::list< float >* final = new std::list< float >;	
	auto iter = final->begin();							   

	for (i = 0; i < N; ++i) {
		final->splice(iter, B[ i ]);	
		iter = final->end();
	}

	B.erase(B.begin(), B.end());	

	return final;
}