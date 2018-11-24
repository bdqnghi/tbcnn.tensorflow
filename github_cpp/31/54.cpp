#include "papi.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>
#include <ctime>
using namespace std;

void read_matrix(ifstream &my_stream, float* &matrix, uint &size)
{
	my_stream >> size;
	matrix = new float [size*size];

	for (uint i = 0; i < size; ++i)
		for (uint j = 0; j < size; ++j)
			my_stream >> matrix[i*size + j];
}

void print_matrix(ofstream &my_stream, float* matrix, uint size)
{
	my_stream << size << endl;
	for (uint i = 0; i < size; ++i)
	{
		for (uint j = 0; j < size; ++j)
			my_stream << matrix[i * size + j] << " ";
		my_stream << endl;
	}
}

static void do_block(uint n, uint M, uint N, uint K, float* A, float* B, float* C)
{
	for (uint i = 0; i < M; ++i)
	{
		const int iOffset = i*n;
		for (uint j = 0; j < N; ++j)
		{
			float cij = 0.0;
			for (uint k = 0; k < K; ++k)
				cij += A[iOffset+k] * B[k*n+j];
			C[iOffset+j] += cij;
		}
	}
}

void block_multiply(uint n , float* A, float* B, float* C, bool index_order, uint block_size)
{
	//index_order = 0, если ijk, index_order = 1, если ikj
	if (!index_order)
	{		
		for (uint i = 0; i < n; i+=block_size)
		{
			const uint iOffset = i * n;
			for (uint j = 0; j < n; j+=block_size)
			{
				for (uint k = 0; k < n; k+=block_size)
				{
					uint M = min(block_size,n-i);
					uint N = min(block_size,n-j);
					uint K = min(block_size,n-k);

					do_block(n, M, N, K, A + iOffset + k, B + k*n + j, C + iOffset + j);
				}
			}
		}
	}
	else
	{
		for (uint i = 0; i < n; i+=block_size)
		{
			const uint iOffset = i * n;
			for (uint k = 0; k < n; k+=block_size)
			{
				for (uint j = 0; j < n; j+=block_size)
				{
					uint M = min(block_size,n-i);
					uint N = min(block_size,n-j);
					uint K = min(block_size,n-k);

					do_block(n, M, N, K, A + iOffset + k, B + k*n + j, C + iOffset + j);
				}
			}
		}
	}
}

int main(int argc, char** argv)
{

	if (argc != 6)
	{
		cout << "Неверное число параметров" << endl;
		return 1;
	}

	ifstream input_A(argv[1]), input_B(argv[2]);
	ofstream output_C(argv[3]);

	int block_size = atoi(argv[5]);
	if (block_size == -1)
		block_size = sqrt(16 * 512 / 3);

	uint size_A, size_B;
	float* A, *B, *C;
	read_matrix(input_A, A, size_A);
	read_matrix(input_B, B, size_B);
	C = new float[size_A*size_A];
	for (uint i = 0; i < size_A * size_A; i++)
        C[i] = 0;

	if (size_A != size_B)
	{
		cout << "Матрицы должны быть одного размера" << endl;
		delete[] A;
		delete[] B;
		delete[] C;
		input_A.close();
		input_B.close();
		output_C.close();
		return 1;
	}
	if (block_size > size_A)
		block_size = size_A;
	
	int events[4] = {PAPI_L1_DCM, PAPI_L2_TCM, PAPI_TOT_CYC, PAPI_TLB_DM};
    long_long values[4];

    if (PAPI_num_counters() < 4)
    {
        cout << "No hardware counters here, or PAPI not supported." << endl;
        delete[] A;
		delete[] B;
		delete[] C;
        input_A.close();
        input_B.close();
        output_C.close();
        return -1;
    }

    if (PAPI_start_counters(events, 4) != PAPI_OK)
    {
        cout << "PAPI faild to start counters." << endl;
        delete[] A;
		delete[] B;
		delete[] C;
        input_A.close();
        input_B.close();
        output_C.close();
        return -1;
    }

    float time = clock();
	/*Computations*/
	if (argv[4] == "ijk")
		block_multiply(size_A, A, B, C, 0, block_size);
	else
		block_multiply(size_A, A, B, C, 1, block_size);	
	/*End of computations*/
	time = clock() - time;

	if (PAPI_read_counters(values, 4) != PAPI_OK)
    {
        cout << ">PAPI faild to read counters." << endl;
        delete[] A;
		delete[] B;
		delete[] C;
        input_A.close();
        input_B.close();
        output_C.close();
        return -1;
    }


    /*
    cout << "Time = " << time / CLOCKS_PER_SEC << endl;
    cout << "TLB misses = " << (float)values[3] << endl;
    cout << "L1 data cache misses is = " << (float)values[0] << endl;
    cout << "L2 data cache misses is = " << (float)values[1] << endl;
    cout << "Total cycles = " << (float)values[2] << endl;*/
    ofstream time_file("plots_data/time.dat", ios::app);
    ofstream cycles_file("plots_data/cycles.dat", ios::app);
    ofstream l1_file("plots_data/l1.dat", ios::app);
    ofstream l2_file("plots_data/l2.dat", ios::app);
    ofstream tlb_file("plots_data/tlb.dat", ios::app);

    time_file << " " << time / CLOCKS_PER_SEC << endl;
    cycles_file << " " << (float)values[2] << endl;
    l1_file << " " << (float)values[0] << endl;
    l2_file << " " << (float)values[1] << endl;
    tlb_file << " " << (float)values[3] << endl;

    time_file.close();
    cycles_file.close();
    l1_file.close();
    l2_file.close();
    tlb_file.close();

    if (PAPI_stop_counters(values, 4) != PAPI_OK)
    {
        cout << "PAPI faild to stop counters." << endl;
        delete[] A;
		delete[] B;
		delete[] C;
        input_A.close();
        input_B.close();
        output_C.close();
        return -1;
    }

	print_matrix(output_C, C, size_A);
	delete[] A;
	delete[] B;
	delete[] C;
	input_A.close();
	input_B.close();
	output_C.close();
	return 0;
}