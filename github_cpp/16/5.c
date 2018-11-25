

#include "shellsort.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>


void shellsort::readFile(std::string file) {
	std::cout << "Reading file: " << file << std::endl;
	long val;
	std::ifstream infile(file);
	while (infile >> val) {
		inputs.push_back(val);
	}
}


void shellsort::saveFile(std::string file) {
	std::cout << "Saving to file: " << file << std::endl;
	std::ofstream savefile;
	savefile.open(file);

	for (int i = 0; i < inputs.size(); ++i) {
		savefile << std::to_string(inputs[i]) << std::endl;
	}

	savefile.close();
}

void shellsort::getGaps(int n) {
	int i = 1, k = 1;
	while (i < n) {
		gaps.push_back(i);
		k = k + 1;
		i = (int)pow(2, k) - (int)1;
	}
}

void shellsort::shellSort() {
	getGaps(inputs.size());
	shellSort(inputs);
}


void shellsort::shellSort(std::vector<long>& vec) {
	std::cout << "Sorting file" << std::endl;

	int i, j = 0, inc = 1;
	long temp;

	

	inc = gaps.back();

	while (!gaps.empty()) {
		for (i = inc; i < vec.size(); i++) {
			temp = vec[i];
			j = i;
			while (j >= inc && vec[j - inc] > temp) {
				vec[j] = vec[j - inc];
				j = j - inc;
			}
			vec[j] = temp;
		}

		gaps.pop_back();
		inc = gaps.back();
	}

	inputs = vec;
	
	std::cout << "File sorted" << std::endl;
}