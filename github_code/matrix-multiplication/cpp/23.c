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
	//uniform_real_distribution<double> dist(-10, 10);	//Use uniform distribution random variable
	normal_distribution<double> dist(0, 5.0);

	/* If colum of first matrix in not equal to row of second matrix, asking user to enter the size of matrix again. 
	while (c1 != r2)
	{
		cout << "Error! column of first matrix not equal to row of second.";
		cout << "Enter rows and columns for first matrix: ";
		cin >> r1 >> c1;
		cout << "Enter rows and columns for second matrix: ";
		cin >> r2 >> c2;
	}
	*/

	/* Storing elements of first matrix. */
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

	/* Storing elements of second matrix. */
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

	/* Initializing elements of matrix mult to 0.*/
	for (i = 0; i<r1; ++i)
	{
		for (j = 0; j < c2; ++j)
		{
			mult[i][j] = 0;
		}
	}

	/* Multiplying matrix a and b and storing in array mult. */
	for (i = 0; i<r1; ++i)
		for (j = 0; j<c2; ++j)
			for (k = 0; k<c1; ++k)
			{
				mult[i][j] += a[i][k] * b[k][j];
			}

	/* Displaying the multiplication of two matrix. */
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
//ttp://www.programiz.com/cpp-programming/examples/matrix-multiplication