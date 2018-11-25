#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <numeric>
#include <random>       
#include <chrono>       

void selectionsort(std::vector<int>& nodes){
	for(auto it=nodes.begin(); it!=nodes.end(); ++it){
		int min = *it;
		auto pos = it;
		for(auto itt=it; itt!=nodes.end(); ++itt){
				if(min > *itt){
					min = *itt;
					pos = itt;
				}
			}
		*pos = *it;
		*it = min;
	}
}

int main(){
	std::cout << "Give the number of the nodes ";
	int NumberOfNodes;
	std::cin >> NumberOfNodes;
	std::vector<int> nodes(NumberOfNodes);
	std::iota(nodes.begin(),nodes.end(),0);
	
  	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  	std::shuffle (nodes.begin(), nodes.end(), std::default_random_engine(seed));
  	std::cout << "Before sort: " << std::endl;
  	std::copy(nodes.begin(),nodes.end(),std::ostream_iterator<int>(std::cout," "));
  	
  	selectionsort(nodes);
  	std::cout << "\nAfter sort: " << std::endl;
	std::copy(nodes.begin(),nodes.end(),std::ostream_iterator<int>(std::cout," "));
}