#include "LinearRegression.h"
#include <cstdlib>

namespace Metagross {
	LinearRegression::LinearRegression() {
		m = 0;
		n = 2;
		initTheta();
	}

	LinearRegression::LinearRegression(int features) {
		m = 0;
		n = features;
		initTheta();
	}

	LinearRegression::LinearRegression(double a) {
		m = 0;
		n = 2;
		initTheta();
		alpha = a;
	}

	LinearRegression::LinearRegression(int f, double a) {
		m = 0;
		n = f;
		alpha = a;
		initTheta();
	}

	LinearRegression::~LinearRegression() {
		
	}

	void LinearRegression::train(Matrix X, Matrix y) {
		m = X.getRows();
		theta = theta - (alpha/m)*(h(X) - y) * X;
	}

	void LinearRegression::train(Matrix X, Matrix y, double lambda) {
		m = X.getRows();
		theta = theta*(1-alpha*lambda/m) - (alpha/m)*(h(X) - y) * X;
	}

	void LinearRegression::trainNormal(Matrix X, Matrix y) {
		theta = (~X*X).inverse() * ~X * y;
	}

	void LinearRegression::trainNormal(Matrix X, Matrix y, double lambda) {
		theta = (~X*X + lambda*(identity(n+1).set(0,0,0))).inverse() * ~X * y;
	}

	double LinearRegression::test(Matrix X, Matrix y) {
		Matrix prd = predict(X);
	}

	Matrix LinearRegression::predict(Matrix X) {
		//do later
	}

	void LinearRegression::initTheta() {
		double* data = new double[n+1];
		for(int x = 0; x < n+1; x++) {
			data[x] = std::rand();
		}
		theta = Matrix(1, n+1, data);
	}

	Matrix LinearRegression::h(Matrix X) {
		return (theta*X);
	}
}