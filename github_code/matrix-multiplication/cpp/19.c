/*
	Matrix Multiplication
*/
#include "bits/stdc++.h"
#include "omp.h"

using namespace std;
#define SIZE 1000

int a[SIZE][SIZE], b[SIZE][SIZE], res[SIZE][SIZE];

void init()
{
	int i,j;
	for(i=0; i<SIZE; i++)
	{
		for(j=0; j<SIZE; j++)
		{
			a[i][j] = rand()%1000;
		}
	}

	for(i=0; i<SIZE; i++)
	{
		for(j=0; j<SIZE; j++)
		{
			b[i][j] = rand()%1000;
		}
	}
}

void parallel()
{
	int i,j,k;
	#pragma omp parallel for shared(a,b) private(i,j,k)
		for(i=0; i<SIZE; i++)
		{
			for(j=0; j<SIZE; j++)
			{
				res[i][j] = 0;
				for(k=0; k<SIZE; k++)
				{
					res[i][j] += a[i][k]*b[k][j];
				}
			}
		}
}

void serial()
{
	int i,j,k;

	for(i=0; i<SIZE; i++)
	{
		for(j=0; j<SIZE; j++)
		{
			res[i][j]=0;
			for(k=0; k<SIZE; k++)
			{
				res[i][j] += a[i][k]*b[k][j];
			}
		}
	}
}

int main()
{
	init();
	double serial_start_time, serial_end_time;
	double parallel_start_time, parallel_end_time;

	// Serial
	serial_start_time = omp_get_wtime();
	serial();
	serial_end_time = omp_get_wtime();

	// Parallel
	parallel_start_time = omp_get_wtime();
	parallel();
	parallel_end_time = omp_get_wtime();

	// Output
	printf("Size of matrix: %d\n", SIZE);
	printf("Serial Time   : %lf \n", (serial_end_time - serial_start_time)*1000);
	printf("Parallel Time : %lf \n", (parallel_end_time - parallel_start_time)* 1000);
}
