#ifndef SELECTION_SORT_HPP
#define SELECTION_SORT_HPP

#include <iostream>
#include <vector>

using namespace std;


template <class T>
class selectionSort {
	public:
		selectionSort();
		virtual ~selectionSort();
		int sort(vector<T>& values, bool debug = false);
		void swap(T& a, T& b);
		int selectMin(const vector<T>& values, int start, int end, bool debug);
		ostream& debugValues(const vector<T>& values, int start, int current, int min, ostream& os = cout);
};


template<class T>
selectionSort<T>::selectionSort() {}


template <class T>
selectionSort<T>::~selectionSort() {}


template <class T>
void selectionSort<T>::swap(T& a, T& b) {
	T aux(a);
	a = b;
	b = aux;
}


template <class T>
int selectionSort<T>::sort(vector<T>& values, bool debug) {
	int size = values.size();
	int steps = 0;

	for (int i = 0; i < size; ++i) {
		int min = selectMin(values, i, size, debug);
		swap(values[min], values[i]);
	}
	return steps;
}


template <class T>
int selectionSort<T>::selectMin(const vector<T>& values, int start, int end, bool debug) {
	int min = start;
	for (int i = start; i < end; ++i) {
		if (values[i] < values[min])
			min = i;
		if (debug)
			debugValues(values, start, i, min);
	}
	return min;
}


template <class T>
ostream& selectionSort<T>::debugValues(const vector<T>& values, int start, int current, int min, ostream& os) {
	int size = values.size();

	for (int i = 0; i < size; i++) {
		if ((i == start) || (i == current))
			os << "[" << values[i] << "] ";
		else
			os << " " << values[i] << "  ";
	}
	os << " min: [" << values[min] << "]" << endl;
	cin.ignore();
	return os;
}

#endif 
