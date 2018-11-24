/*
 * LinearRegression.cpp
 *
 *  Created on: 27 Aug 2011
 *      Author: root
 */

#include "LinearRegression.h"

LinearRegression::LinearRegression(const unsigned int &_size) {
	size = _size;
	Sx = 0;
	Sxx = 0;
	for (unsigned int i = 1; i<=size; i++){
		Sx += i;
		Sxx += (i*i);
	}
}

/*
 * Applies linear regression on the elements of the long long array buffer x_0 to x_{n-1} and
 * returns the prediction for x_n
 */
long long LinearRegression::apply(const long long *buffer) {
	Sy = 0;
	Syy = 0;
	Sxy = 0;
	for (unsigned int i = 0; i<size; i++){
		Sy += buffer[i];
		Syy += (buffer[i] * buffer[i]);
		Sxy += (i+1) * buffer[i];
	}

	double a = (double)(size * Sxy - Sx * Sy) / (double)(size * Sxx - Sx * Sx);
	double b = (double)(Sy - a * Sx) / (double)size;

	// y = ax + b, return y for x = size + 1
	return a * (size+1) + b;
}

LinearRegression::~LinearRegression() {

}

/*
// Testing program - usage
#include <iostream>
using namespace std;
int main() {
	LinearRegression *l = new LinearRegression(10);
	long long buffer[10] = {24,23,25,32,19,27,167,34,26,24};


	for (unsigned int i = 0; i<10; i++) {
		cout << buffer[i] << " ";
	}
	cout << endl;
	long long pred = l->apply(buffer);
	cout << pred << endl;
	assert(pred == 56);
	return 0;
}
*/
