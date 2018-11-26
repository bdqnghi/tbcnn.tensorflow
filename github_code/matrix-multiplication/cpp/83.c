// Lab3AsyncAndFuture.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <future>
#include <thread>
#include <iostream>

using namespace std;
using namespace std::chrono;

const int SIZE_1 = 40, SIZE_2 = 40;

void PrintMatrix(int m[][SIZE_2]);
void InitializeMatrices(int matrix1[][SIZE_2], int matrix2[][SIZE_2], int resultMatrixSum[][SIZE_2], int resultMatrixMultiplication[][SIZE_2]);
void CalculateSumMatrix(int matrix1[][SIZE_2], int matrix2[][SIZE_2], int resultMatrixSum[][SIZE_2]);
void CalculateMultiplicationMatrix(int matrix1[][SIZE_2], int matrix2[][SIZE_2], int resultMatrixMultiplication[][SIZE_2]);

int main()
{
	int matrix1[SIZE_1][SIZE_2], matrix2[SIZE_1][SIZE_2], resultMatrixSum[SIZE_1][SIZE_2], resultMatrixMultiplication[SIZE_1][SIZE_2];

	InitializeMatrices(matrix1, matrix2, resultMatrixSum, resultMatrixMultiplication);

	//PrintMatrix(matrix1);
	//PrintMatrix(matrix2);

	milliseconds start = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

	//CalculateSumMatrix(matrix1, matrix2, resultMatrixSum);
	//PrintMatrix(resultMatrixSum);

	CalculateMultiplicationMatrix(matrix1, matrix2, resultMatrixMultiplication);
	//PrintMatrix(resultMatrixMultiplication);

	milliseconds end = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
	cout << "Total time is " << (end - start).count() << endl;
	return 0;
}

void CalculateMultiplicationMatrix(int matrix1[][SIZE_2], int matrix2[][SIZE_2], int resultMatrixMultiplication[][SIZE_2]) {
	vector<future<int>> multiplicationResultFutures;
	for (int i = 0; i < SIZE_1; i++)
	{
		for (int j = 0; j < SIZE_2; j++)
		{
			for (int k = 0; k < SIZE_1; k++)
			{
				multiplicationResultFutures.push_back(async(launch::async, [matrix1, matrix2, i, j, k] { return (matrix1[i][k] * matrix2[k][j]); }));
			}
		}
	}

	for (int i = 0; i < SIZE_1; i++)
	{
		for (int j = 0; j < SIZE_2; j++)
		{
			for (int k = 0; k < SIZE_1; k++)
			{
				int temp = i*SIZE_2 + j * SIZE_1 + k;
				resultMatrixMultiplication[i][j] += multiplicationResultFutures[i*SIZE_2 * SIZE_1 + j * SIZE_1 + k].get();
			}
		}
	}
}

void CalculateSumMatrix(int matrix1[][SIZE_2], int matrix2[][SIZE_2], int resultMatrixSum[][SIZE_2]) {
	vector<future<int>> futures;
	for (int i = 0; i < SIZE_1; i++)
	{
		for (int j = 0; j < SIZE_2; j++)
		{
			futures.push_back(async(launch::async, [matrix1, matrix2, i, j] { return (matrix1[i][j] + matrix2[i][j]); }));
		}
	}

	for (int i = 0; i < SIZE_1; i++)
	{
		for (int j = 0; j < SIZE_2; j++)
		{
			resultMatrixSum[i][j] = futures[i*SIZE_1 + j].get();
		}
	}
}

void PrintMatrix(int m[][SIZE_2]) {

	for (int i = 0; i < SIZE_1; i++)
	{
		for (int j = 0; j < SIZE_2; j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void InitializeMatrices(int matrix1[][SIZE_2], int matrix2[][SIZE_2], int resultMatrixSum[][SIZE_2], int resultMatrixMultiplication[][SIZE_2]) {
	for (int i = 0; i < SIZE_1; i++)
	{
		for (int j = 0; j < SIZE_2; j++)
		{
			matrix1[i][j] = 1;
			matrix2[i][j] = 2;
			resultMatrixMultiplication[i][j] = 0;
			resultMatrixSum[i][j] = 0;
		}
	}
}


