#ifndef SELECTION_SORT_HPP
#define SELECTION_SORT_HPP

#include <iostream>
#include <vector>

using namespace std;

/**
* Declaración de la clase del algoritmo SelectionSort
*/
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

/**
* Constructor vacío de la clase del algoritmo SelectionSort
*/
template<class T>
selectionSort<T>::selectionSort() {}

/**
* Destructor de la clase del algoritmo SelectionSort
*/
template <class T>
selectionSort<T>::~selectionSort() {}

/**
* Método que intercambia dos posiciones del vector
*/
template <class T>
void selectionSort<T>::swap(T& a, T& b) {
	T aux(a);
	a = b;
	b = aux;
}

/**
* Método que realiza el algoritmo SelectionSort
*/
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

/**
* Método que selecciona el elemento
* más pequeño entre los elementos del
* vector que van desde start hasta end
*/
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

/**
* Método que imprime los elementos del vector
* y muestra los elementos a intercambiar
*/
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

#endif // SELECTIONSORT
