/*
*	shellsort.cpp
*
*	Authors: Cody Ponder, Michael McHugh, Aaron Goerg
*	Date Created: 10/6/2017
*	Professor: Dr. Hyoil Han
*	Class: IT 279
*/

#include "shellsort.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

//Reads the selected file and saves the values to inputs if file is valid
void shellsort::readFile(std::string file) {
	std::cout << "Reading file: " << file << std::endl;
	long val;
	std::ifstream infile(file);
	while (infile >> val) {
		inputs.push_back(val);
	}
}

//Saves sorted values of inputs to the specified file. Creates file if it isn't found
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

//sorts the values of inputs by shellsort method using hibbard's increments
void shellsort::shellSort(std::vector<long>& vec) {
	std::cout << "Sorting file" << std::endl;

	int i, j = 0, inc = 1;
	long temp;

	//std::cout << "Initial vector first and last: " << inputs[0] << " " << inputs[inputs.size()-1] << std::endl;		//For testing

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
	//std::cout << "\nSorted vector first and last: " << inputs[0] << " " << inputs[inputs.size() - 1] << std::endl;		//For testing
	std::cout << "File sorted" << std::endl;
}