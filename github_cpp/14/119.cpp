#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream>
#include <vector>
#include "armadillo.hpp"


arma::Col<double> gradient(arma::Mat<double> x, arma::Col<short> y, arma::Col<double> w);
arma::Col<double> new_w(arma::Col<double> w, double alpha, arma::Mat<double> x, arma::Col<short> y);
arma::Col<double> regression(arma::Col<double> w, double alpha, arma::Mat<double> x, arma::Col<short> y);

int main()
{
	std::vector <double> dataX;
	std::vector <double> dataY;
	std::vector <double> test;
	double storage;
	short storagei;

	// reading dataX
	std::ifstream read_file("dataX.dat");
	assert(read_file.is_open());
	while (!read_file.eof())
	{
		read_file >> storage;
		dataX.push_back(storage);
	}
	read_file.close();

	// reading dataY
	read_file.open("dataY.dat");
	assert(read_file.is_open());
	while (!read_file.eof())
	{
		read_file >> storagei;
		dataY.push_back(storagei);
	}
	read_file.close();

	// reading dataXtest
	read_file.open("dataXtest.dat");
	assert(read_file.is_open());
	while (!read_file.eof())
	{
		read_file >> storage;
		test.push_back(storage);
	}
	read_file.close();

	int lenX;
	lenX = dataX.end() - dataX.begin() - 1;
	int lenY;
	lenY = dataY.end() - dataY.begin() - 1;
	int lenTest;
	lenTest = test.end() - test.begin() - 1;
	int XY;
	XY = lenX / lenY;

	// Converting dataX to arma matrix
	arma::mat X(lenY, XY, arma::fill::none);
	for (int i = 0; i < lenY; i++)
	{
		for (int j = 0; j < XY; j++)
		{
			X(i, j) = dataX[XY*i + j];
		}
	}

	int test_rows = lenTest / XY;

	// Converting test to arma matrix
	arma::mat Xtest(test_rows, XY, arma::fill::none);
	for (int i = 0; i < test_rows; i++)
	{
		for (int j = 0; j < XY; j++)
		{
			Xtest(i, j) = test[XY*i + j];
		}
	}

	// Converting dataY to arma vector
	arma::Col<short> Y(lenY);
	for (int i = 0; i < lenY; i++)
	{
		Y(i) = dataY[i];
	}
	
	arma::Col<double> w = arma::zeros(X.n_cols);
	// sign
	arma::Col<double> y(Xtest.n_rows);
	arma::Col<int> out(Xtest.n_rows);
	y = Xtest*regression(w, 0.9, X, Y);

	for (int i = 0; i < Xtest.n_rows; i++)
	{
		if (y(i) > 0)
		{
			out(i) = 1;
		}
		else
		{
			out(i) = -1;
		}
	}
	//out.print();

	std::ofstream write_file("LogReg.dat");
	for (int h = 0; h < Xtest.n_rows; h++)
	{
		write_file << out[h] << "\n";
	}
	return 0;
}


arma::Col<double> gradient(arma::Mat<double> x, arma::Col<short> y, arma::Col<double> w)
{
	arma::vec out(x.n_cols);
	out.fill(0);
	for (int i = 0; i < x.n_rows; i++)
	{
		out -= (y[i] * x.row(i).t()/(1+exp(y[i] *x.row(i)*w)[0]));
	}
	return out/x.n_rows;
}

arma::Col<double> new_w(arma::Col<double> w, double alpha, arma::Mat<double> x, arma::Col<short> y)
{
	return w - alpha*gradient(x, y, w);
}

arma::Col<double> regression(arma::Col<double> w, double alpha, arma::Mat<double> x, arma::Col<short> y)
{
	int count = 0;
	while (norm(gradient(x,y,w)) > pow(10,-7) & count <100000)
	{
		w = new_w(w, alpha, x, y);
		count++;
	}
	return w;
}

