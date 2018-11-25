


#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <amp.h>
#include <chrono>
#include <conio.h>

using namespace concurrency;
using namespace std::chrono;

void MatrixMultiplication() {
	int Matrix1[30000];
	int Matrix2[30000];
	int Matrix3[30000 * 3];
	
	for (int i = 0; i < 30000; i++)
	{
		srand(time(NULL));
		Matrix1[i] = rand();
		Matrix2[i] = rand();
	}

	high_resolution_clock::time_point startTime = high_resolution_clock::now();

	array_view<int, 2> Arr1(3, 2, Matrix1);
	array_view<int, 2> Arr2(2, 3, Matrix2);
	array_view<int, 2> product(3, 3, Matrix3);
	product.discard_data();

	parallel_for_each(product.extent, [=](index<2> idx) restrict(amp) {
		int linea = idx[0];
		int columna = idx[1];
		for (int dentro = 0; dentro < 2; dentro++)
		{
			product[idx] += Arr1(linea, dentro)*Arr2(dentro, columna);
		}
	});

	product.synchronize();
	high_resolution_clock::time_point finishTime = high_resolution_clock::now();

	auto duration = duration_cast<milliseconds>(finishTime - startTime).count();

	std::cout << duration;

	
	
	
	
	
	
	
	
}

int main()
{
	MatrixMultiplication();
	_getch();
    return 0;
}

