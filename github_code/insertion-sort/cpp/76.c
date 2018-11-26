#include "insertionSort.h"



insertionSort::insertionSort()
{
}


insertionSort::~insertionSort()
{
}

void insertionSort::sort(std::vector<int> a) {
	for (int i = 1; i < a.size(); i++) {
		int j = i;
		while (j > 0 && a.at(j) < a.at(j - 1)) {
			int temp = a.at(j);
			a.at(j) = a.at(j - 1);
			a.at(j - 1) = temp;
			j--;
		}

	}
	print(a); 

}

void insertionSort::sortByRef(std::vector<int> & a) {
	for (int i = 1; i < a.size(); i++) {
		int j = i;
		while (j > 0 && a.at(j) < a.at(j - 1)) {
			int temp = a.at(j);
			a.at(j) = a.at(j - 1);
			a.at(j - 1) = temp;
			j--;
		}

	}

}