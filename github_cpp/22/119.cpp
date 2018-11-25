#include <iostream>
#include "pch.h"
#include "BucketSort.h"
#include <vector>


BucketSort::BucketSort()
{
}


BucketSort::~BucketSort()
{
}

std::vector<int>* BucketSort::sortVector(std::vector<int> *v) {
	
	int k = NULL;
	for(auto element : *v) {
		if (k == NULL) {
			k = element;
		}
		else {
			if (k < element) {
				k = element;
			}
		}
	}

	
	std::vector<int> w(k + 1, 0);

	
	for (auto i : *v) {
		w[i]++;
	}

	
	int index = 0;
	for (int i = 0; i < w.size(); i++) {
		if (w[i] != 0) {
			for (int j = 0; j < w[i]; j++) {
				v->at(index) = i;
				index++;
			}
		}
	}

	return v;
}

void BucketSort::printVector(std::vector<int> *v) {
	std::cout << "vector : [ ";
	for (auto i : *v) {
		std::cout << i << " ";
	}
	std::cout << "]\n";
}

std::string BucketSort::getDiscription() {
	return "BucketSort";
}