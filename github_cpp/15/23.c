#include <iostream>
#include <random>
using namespace std;

int main()
{
	int a[10][10], b[10][10], mult[10][10],i, j, k;
	int r1 = 2;
	int c1 = 2;
	int r2 = 2;
	int c2 = 2;

	random_device rd;
	mt19937 mt(rd());
	
	normal_distribution<double> dist(0, 5.0);

	

	
	cout << endl << "Print elements of matrix 1:" << endl;
	for (i = 0; i < r1; ++i)
	{
		for (j = 0; j < c1; ++j)
		{
			a[i][j] = (int)dist(rd);
		}
	}
	for (i = 0; i<r1; ++i)
		for (j = 0; j<c2; ++j)
		{
			cout << " " << a[i][j];
			if (j == c2 - 1)
				cout << endl;
		}

	
	cout << endl << "Print elements of matrix 1:" << endl;
	for (i = 0; i < r2; ++i)
	{
		for (j = 0; j < c2; ++j)
		{
			b[i][j] = (int)dist(rd);
		}
	}
	for (i = 0; i<r1; ++i)
		for (j = 0; j<c2; ++j)
		{
			cout << " " << b[i][j];
			if (j == c2 - 1)
				cout << endl;
		}

	
	for (i = 0; i<r1; ++i)
	{
		for (j = 0; j < c2; ++j)
		{
			mult[i][j] = 0;
		}
	}

	
	for (i = 0; i<r1; ++i)
		for (j = 0; j<c2; ++j)
			for (k = 0; k<c1; ++k)
			{
				mult[i][j] += a[i][k] * b[k][j];
			}

	
	cout << endl << "Output Matrix: " << endl;
	for (i = 0; i<r1; ++i)
		for (j = 0; j<c2; ++j)
		{
			cout << " " << mult[i][j];
			if (j == c2 - 1)
				cout << endl;
		}
	return 0;
}
