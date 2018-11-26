# Matrix-multiplication

#include "Matrix.h"

Matrix::Matrix()
{
	a = new int*[N];
	for (int i = 0; i < N; i++)
	{
		a[i] = new int[N];
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			a[i][j] = 0;
		}
	}
}

void Matrix::Entering()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << "Enter element of matrix [" << i << "]" << "[" << j << "]:";
			cin >> a[i][j];
		}
	}
}

void Matrix::Printing()const
{
	n++;
	cout << "Matrix #"<<n<<"\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

Matrix& Matrix :: operator*(Matrix&b)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			a[i][j] = a[i][j] * b.a[i][j];
	}
	return *this;
}

Matrix& Matrix :: operator=(Matrix&b)
{
	for (int i = 0; i < N; i++)
	{
		delete[]a[i];
	}

	a = new int*[N];
	for (int i = 0; i < N; i++)
	{
		a[i] = new int[N];
	}


	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			a[i][j] = b.a[i][j];
	}
	
	return *this;
}

Matrix::~Matrix() 
{
	for (int i = 0; i < N; i++)
	{
		delete[] a[i];
	}
}
