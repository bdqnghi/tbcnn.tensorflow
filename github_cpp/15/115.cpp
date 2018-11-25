

#ifndef MATRIXMULTIPLICATION_H_
#define MATRIXMULTIPLICATION_H_
#include <iostream>
using namespace std;

template <typename NUM>
class MatrixMultiplication {
public:
	MatrixMultiplication() {

	}
	virtual ~MatrixMultiplication() {

	}
	void multiply(NUM* m1, NUM* m2) {
		NUM C[4][4];
		for(int i = 0; i < 4; i++) {
					for(int j = 0; j < 4; j++) {
						C[i][j] = 0;
				}
		}
		for(int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for(int k = 0; k < 4; k++) {
					C[i][j] += m1[i*4+k]*m2[k*4+j];
				}
			}
		}
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				cout << C[i][j];
				cout << "\t";
			}
			cout << "\n";
		}
	}
};

#endif 
