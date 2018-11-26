// matrixmultiplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "omp.h"
#include <iostream>
#include <random>
#include <stdio.h>
#include <vector>;
#include <chrono>;

using namespace std;

long long RunSequencialMultiplication(int n1, int n2, int n3, bool is_parallel_mode, int chunk = 0);
long long RunBlockMultiplication(int n1, int n2, int n3, int block_side, bool is_parallel_mode, int chunk = 0);
vector<long> MultipleMatrix(vector<long> m1, vector<long> m2, int n1, int n2, int n3, bool is_parallel_mode, int chunk = 0);
vector<vector<long>> MultipleMatrixBlocks(vector<vector<long>> &result, vector<vector<long>> m1_blocks, vector<vector<long>> m2_blocks, int n1, int n2, int n3, int block_size, bool is_parallel_mode, int chunk = 0);
int GenerateRandomValue();
void GenerateMatrix(int row_number, int column_number, vector<long> &m);
void PrintMatrix(int row_number, int column_number, vector<long> m);
void AddMatrixes(vector<long> &m1, vector<long> m2, int row_number, int column_number);
void GenerateMatrixBlocks(vector<vector<long>> &m_blocks, int row_number, int column_number, int block_side);

int main() {
	const int n = 100, m = 100;
	const int block_size = 20;

	long long sequentialTime = RunSequencialMultiplication(n, n, n, false);
	cout << "sequential time " << sequentialTime << endl;

	long long blockTime = RunBlockMultiplication(n, n, n, block_size, false);
	cout << "block time " << blockTime << endl;
	
	long long sequentialParallelTime = RunSequencialMultiplication(n, n, n, true, 1);
	cout << "sequential parallel time " << sequentialParallelTime << endl;
	
	long long blockParallelTime = RunBlockMultiplication(n, n, n, block_size, true, 1);
	cout << "block parallel time " << blockParallelTime << endl; 
	
	system("pause");
    return 0;
}

long long RunSequencialMultiplication(int n1, int n2, int n3, bool is_parallel_mode, int chunk) {
	vector<long> m1 = {}, m2 = {}, m3 = {};
	m3.resize(n1, n3);

	GenerateMatrix(n1, n2, m1);
	GenerateMatrix(n2, n3, m2);

	auto start = chrono::steady_clock::now();
	m3 = MultipleMatrix(m1, m2, n1, n2, n3, is_parallel_mode, chunk);
	auto duration = chrono::duration_cast<chrono::milliseconds>
                            (std::chrono::steady_clock::now() - start);
	return duration.count();
}

long long RunBlockMultiplication(int n1, int n2, int n3, int block_side, bool is_parallel_mode, int chunk) {
	vector<vector<long>> m1_blocks = {};
	vector<vector<long>> m2_blocks = {};
	vector<vector<long>> m3_blocks = {};
	m3_blocks.resize(n1 * n3);

	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n3; j++) {
			m3_blocks[i * n1 + j].resize(block_side * block_side);
		}
	}

	GenerateMatrixBlocks(m1_blocks, n1 / block_side, n2 / block_side, block_side);
	GenerateMatrixBlocks(m2_blocks, n2 / block_side, n3 / block_side, block_side);

	auto start = chrono::steady_clock::now();

	MultipleMatrixBlocks(m3_blocks, m1_blocks, m2_blocks, n1 / block_side, n2 / block_side, n3 / block_side, block_side, is_parallel_mode, chunk);
	
	/*for (int i = 0; i < n1 * n3; i++) {
		PrintMatrix(block_side, block_side, m3_blocks[i]);
	}*/

	auto duration = chrono::duration_cast<chrono::milliseconds>
		(std::chrono::steady_clock::now() - start);
	
	return duration.count();
}

void GenerateMatrixBlocks(vector<vector<long>> &m_blocks, int row_number, int column_number, int block_side) {
	m_blocks.resize(row_number * column_number * block_side);

	long m_blocks_number = row_number * column_number;

	for (int i = 0; i < m_blocks_number; i++) {
		vector<long> block = {};
		GenerateMatrix(block_side, block_side, block);
		m_blocks[i] = block;
		//PrintMatrix(block_side, block_side, block);
	}
}

int GenerateRandomValue() {
	int sign = (rand() % 2) == 0 ? -1 : 1;
	return (rand() % 100) * sign;
}

void GenerateMatrix(int row_number, int column_number, vector<long> &m) {
	m.resize(row_number * column_number);
	for (int i = 0; i < row_number; i++) {
		for (int j = 0; j < column_number; j++) {
			m[i* row_number + j] = GenerateRandomValue();
		}
	}
}

void PrintMatrix(int row_number, int column_number, vector<long> m) {
	for (int i = 0; i < row_number; i++) {
		for (int j = 0; j < column_number; j++) {
			std::cout << m[i * row_number + j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

vector<long> MultipleMatrix(vector<long> m1, vector<long> m2, int n1, int n2, int n3, bool is_parallel_mode, int chunk) {
	int i, j, k;
	vector<long> result_matrix = {};
	result_matrix.resize(n1 * n3);

	if (!is_parallel_mode) {
		for (i = 0; i < n1; i++) {
			for (j = 0; j < n3; j++) {
				for (k = 0; k < n2; k++) {
					result_matrix[i * n1 + j] += m1[i * n1 + k] * m2[k * n2 + j];
				}
			}
		}
	}
	else {
		#pragma omp parallel shared(result_matrix, m1, m2, n1, n2, n3, chunk) private(i, j, k) 
		#pragma omp for schedule (static, chunk)
		for (i = 0; i < n1; i++) {
			for (j = 0; j < n3; j++) {
				for (k = 0; k < n2; k++) {
					result_matrix[i * n1 + j] += m1[i * n1 + k] * m2[k * n2 + j];
				}
			}
		}
	}
			
	return result_matrix;
}

vector<vector<long>> MultipleMatrixBlocks(vector<vector<long>> &result_matrix, vector<vector<long>> m1_blocks, vector<vector<long>> m2_blocks, int n1, int n2, int n3, int block_size, bool is_parallel_mode, int chunk) {
	int i, j, k;

	if (!is_parallel_mode) {
		for (i = 0; i < n1; i++) {
			for (j = 0; j < n3; j++) {
				for (k = 0; k < n2; k++) {
					AddMatrixes(result_matrix[i * n1 + j],
						MultipleMatrix(m1_blocks[i * n1 + k], m2_blocks[k * n2 + j], block_size, block_size, block_size, false), block_size, block_size);
				}
			}
		}
	}
	else {
		#pragma omp parallel shared(result_matrix, m1_blocks, m2_blocks, block_size, n1, n2, n3, chunk) private(i, j, k) 
		#pragma omp for schedule (static, chunk)
		for (i = 0; i < n1; i++) {
			for (j = 0; j < n3; j++) {
				for (k = 0; k < n2; k++) {
					AddMatrixes(result_matrix[i * n1 + j],
						MultipleMatrix(m1_blocks[i * n1 + k], m2_blocks[k * n2 + j], block_size, block_size, block_size, true, chunk), block_size, block_size);
				}
			}
		}
	}
	return result_matrix;
}


void AddMatrixes(vector<long> &m1, vector<long> m2, int row_number, int column_number) {
	for (int i = 0; i < row_number; i++) {
		for (int j = 0; j < column_number; j++) {
			m1[i * row_number + j] = m1[i * row_number + j] + m2[i * row_number + j];
		}
	}
}




