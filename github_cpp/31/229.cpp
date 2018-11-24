/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 MatrixMultiplication.cpp
* @version:
* @Time: 		 2015-11-06 22:41:08
* @Description:  implement the matrix multiplication with brute-force, divide-and-conquer and Strassen's algorithm
*
+----------------------------------------------------------
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

using namespace std;
using Matrix = vector<vector<int>>;

class ChildMatrix
{
public:
	Matrix* _parentMatrix;
	int _startRow;
	int _startColum;
	int _length;

public:
	ChildMatrix(Matrix &parentMatrix, int startRow, int startColumn, int length ): _parentMatrix(&parentMatrix), _startRow(startRow), _startColum(startColumn), _length(length) {}
	~ChildMatrix() {}
	int getFromParentMatrix(int row, int colum) {
		return (*_parentMatrix)[row][colum];
	}
};

Matrix matrixMulplBruteforce(const Matrix& A, const Matrix& B);
Matrix MatrixMulplDAC(const Matrix& A, const Matrix& B);
Matrix MatrixMulplDAC(const ChildMatrix& A, const ChildMatrix& B, int lastStartRowA, int lastStartColumnA, int lastStartRowB, int lastStartColumnB);

void print(const Matrix matrix);
void initialize(Matrix& matrix, int rows, default_random_engine &e);

int main() {
	// freopen("test.in", "r", stdin);
	// freopen("test.out", "w", stdout);
	Matrix A, B;
	int rows;
	cin >> rows;
	clock_t time;
	default_random_engine e(time);
	initialize(A, rows, e);
	initialize(B, rows, e);

	print(A);
	print(B);

	Matrix result = matrixMulplBruteforce(A, B);
	print(result);

	result = MatrixMulplDAC(A, B);
	print(result);

	cout << endl;
	system("pause");
	return 0;
}
void initialize(Matrix& matrix, int rows, default_random_engine &e) {
	for (int i = 0; i < rows; ++i) {
		vector<int> temp(rows, 0);
		for (int j = 0; j < rows; ++j) {
			temp[j] = e() % 100;
		}
		matrix.push_back(std::move(temp));
	}
}


Matrix matrixMulplBruteforce(const Matrix& A, const Matrix& B) {
	Matrix result;
	const int rows = static_cast<int>(A.size());
	for (int i = 0; i < rows; ++i) {
		vector<int> temp(rows, 0);
		for (int j = 0; j < rows; ++j)
			for (int k = 0; k < rows; ++k)
				temp[j] += A[i][k] * B[k][j];
		result.push_back(std::move(temp));
	}
	return result;
}

void print(const Matrix matrix) {
	cout << "---------Matrix--------" << endl;
	for (auto row : matrix) {
		for (auto item : row)
			cout << item << " ";
		cout << endl;
	}
	cout << endl;

}

Matrix MatrixMulplDAC(const Matrix& A, const Matrix& B) {
	const int rows = static_cast<int>(A.size());
	Matrix result(rows, vector<int>(rows, 0));
	MatrixMulplDAC(A, B, result, 0, 0, rows - 1, rows - 1, 0, 0, rows - 1, rows - 1);
	return result;
}
Matrix MatrixMulplDAC(const ChildMatrix& A, const ChildMatrix& B, int lastStartRowA, int lastStartColumnA, int lastStartRowB, int lastStartColumnB) {
	Matrix C = vector<vector<int>>(A.length, vector<int>(A.length, 0));
	if (A._length == 1)
		C[0][0] = A.getFromParentMatrix(A._startRow, A._startColum) * B.getFromParentMatrix(B._startRow, B._startColum);
	else {
		int childLength = A._length / 2;
		//part 1 : decompress
		ChildMatrix childMatrixA11 = ChildMatrix(A._parentMatrix, lastStartRowA, lastStartColumnA, childLength);
		ChildMatrix childMatrixA12 = ChildMatrix(A._parentMatrix, lastStartRowA, lastStartColumnA + childLength, childLength);
		ChildMatrix childMatrixA21 = ChildMatrix(A._parentMatrix, lastStartRowA + childLength, lastStartColumnA, childLength);
		ChildMatrix childMatrixA22 = ChildMatrix(A._parentMatrix, lastStartRowA + childLength, lastStartColumnA + childLength, childLength);

		ChildMatrix childMatrixB11 = ChildMatrix(B._parentMatrix, lastStartRowB, lastStartColumnB, childLength);
		ChildMatrix childMatrixB12 = ChildMatrix(B._parentMatrix, lastStartRowB, lastStartColumnB + childLength, childLength);
		ChildMatrix childMatrixB21 = ChildMatrix(B._parentMatrix, lastStartRowB + childLength, lastStartColumnB, childLength);
		ChildMatrix childMatrixB22 = ChildMatrix(B._parentMatrix, lastStartRowB + childLength, lastStartColumnB + childLength, childLength);
		//step 2: solve
		ChildMatrix C11 = ChildMatrix()


		                  MatrixMulplDAC(A, B, result, leftXA, leftYA, midXA, midYA, leftXB, leftYB, midXB, midYB);
		MatrixMulplDAC(A, B, result, midXA + 1, leftYA, rightXA, midYA, leftXB, midYB + 1, midXB, rightYB);

		MatrixMulplDAC(A, B, result, leftXA, leftYA, midXA, midYA, midXB + 1, leftYB, rightXB, midYB);
		MatrixMulplDAC(A, B, result, midXA + 1, leftYA, rightXA, midYA, midXB + 1, midYB + 1, rightXB, rightYB);

		MatrixMulplDAC(A, B, result, leftXA, midYA + 1, midXA, rightYA, leftXB, leftYB, midXB, midYB);
		MatrixMulplDAC(A, B, result, midXA + 1, midYA + 1, rightXA, rightYA, leftXB, midYB + 1, midXB, rightYB);

		MatrixMulplDAC(A, B, result, leftXA, midYA + 1, midXA, rightYA, midXB + 1, leftYB, rightXB, midYB);
		MatrixMulplDAC(A, B, result, midXA + 1, midYA + 1, rightXA, rightYA, midXB + 1, midYB + 1, rightXB, rightYB);
	}

	return C;
}

