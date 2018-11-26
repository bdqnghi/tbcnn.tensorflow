//============================================================================
// Name        : matrix.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
class matrix {
	int a[3][3], b[3][3];
public:
	void input();
	void display();
	void checkUpper();
	void diagonalSum();
	void transpose();
	void sum();
	void subtraction();
	void multiplication();
};
void matrix::input() {
	cout << "Enter values of 1st matrix" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> a[i][j];
		}
	}
	cout << "Enter values of 2nd matrix" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> b[i][j];
		}
	}
}
void matrix::display() {
	cout << "1st matrix is " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "The 2nd matrix is " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << b[i][j] << "\t";
		}
		cout << endl;
	}
}
void matrix::checkUpper() {
	int i, j, z;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (i > j && a[i][j] != 0) {
				z = 1;
				break;
			}
		}
	}
	if (z == 1) {
		cout << "Not an upper triangular matrix" << endl;
	} else {
		cout << "An upper triangular matrix" << endl;
	}

}
void matrix::diagonalSum() {
	int i, j, sum = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (i == j) {
				sum = sum + a[i][j];
			}
		}

	}
	cout << "diagonal sum is " << sum << endl;

}
void matrix::transpose() {


	int e[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			e[i][j] = a[j][i];
		}
	}
	cout<<"The transpose is "<<endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << e[i][j] << "\t";
		}
		cout << "\n";

	}
}
void matrix::sum() {
	int c[3][3], i, j;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			c[i][j] = a[i][j] + b[i][j];

		}

	}
	cout << "The matrix sum is " << endl;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			cout << c[i][j] << "\t";
		}
		cout << endl;
	}
}
void matrix::subtraction() {
	int f[3][3], i, j;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			f[i][j] = a[i][j] - b[i][j];

		}

	}
	cout << "The matrix subtraction is " << endl;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			cout << f[i][j] << "\t";
		}
		cout << endl;
	}
}

void matrix::multiplication() {
	int d[3][3], i, j, k;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			d[i][j] = 0;
		}
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			for (k = 0; k < 3; k++) {
				d[i][j] = d[i][j] + a[i][k] * b[k][j];
			}
		}

	}
	cout << "The multiplication is " << endl;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			cout << d[i][j] << "\t";
		}
		cout << endl;
	}

}
int main() {
	matrix m;
	m.input();
	m.display();
	m.checkUpper();
	m.diagonalSum();
	m.transpose();
	m.sum();
	m.subtraction();
	m.multiplication();
	return 0;
}
