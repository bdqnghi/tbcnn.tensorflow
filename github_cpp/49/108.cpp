#include <fstream>
#include <iostream>
#include <cmath>
#include "helfer.h"
#include "gamma.h"

using namespace std;


// The following class implements the linear fit to the function a + b * t
class Fitab 
{
private:
	// Initialisation of vectors containing data (already chopped to the required interval)
	VecDoub x;
	VecDoub y;
	VecDoub std_y; // Standard deviation in y
	VecDoub t; // Auxiliary variables for fit
	const int N; // Number of lines passed to the object
	double S, S_x, S_xx, S_y, S_xy, S_tt;

public:
	Fitab(VecDoub x_in, VecDoub y_in, VecDoub std_y_in) : x(x_in), y(y_in), std_y(std_y_in), N( x_in.size() )
	{
		t.resize(N); // I tried to initialise it as t(N), but it gives a not well defined behaviour
		set_auxiliary_t(); // Initialise auxiliary values t[i]

		// Calculation of the different sums
		S = Sum();
		S_x = Sum_x();
		S_xx = Sum_xx();
		S_y = Sum_y();
		S_xy = Sum_xy();
		S_tt = Sum_tt();
	}

	// Definition of functions that calculate the different sums
	double Sum();
	double Sum_x();
	double Sum_xx();
	double Sum_y();
	double Sum_xy();
	double Sum_tt();
	void set_auxiliary_t(); // Initialises auxiliary t[i] values

	// Calculation of parameters of the fit and corresponding uncertainties + D.O.F (degrees of freedom)
	VecDoub get_parameters();
	int get_dof();

};

double Fitab::Sum()
{
	double sum = 0;
	for (int i = 0; i < N; ++i)
		sum += 1./(std_y[i]*std_y[i]);
	return sum;
}

double Fitab::Sum_x()
{
	double sum = 0;
	for (int i = 0; i < N; ++i)
		sum += x[i]/(std_y[i]*std_y[i]);
	return sum;
}

double Fitab::Sum_xx()
{
	double sum = 0;
	for (int i = 0; i < N; ++i)
		sum += (x[i]*x[i])/(std_y[i]*std_y[i]);
	return sum;
}

double Fitab::Sum_y()
{
	double sum = 0;
	for (int i = 0; i < N; ++i)
		sum += y[i]/(std_y[i]*std_y[i]);
	return sum;
}

double Fitab::Sum_xy()
{
	double sum = 0;
	for (int i = 0; i < N; ++i)
		sum += (x[i]*y[i])/(std_y[i]*std_y[i]);
	return sum;
}

double Fitab::Sum_tt()
{
	double sum = 0;
	for (int i = 0; i < N; ++i)
		sum += t[i]*t[i];	
	return sum;
}

void Fitab::set_auxiliary_t()
{

	for (int i = 0; i < N; ++i)
{
		t[i] = 1./std_y[i] * (x[i] - Sum_x()/Sum());
}
}

VecDoub Fitab::get_parameters() 
{
	double sum = 0;
	VecDoub parameters(5); // Vector that will contain the different parameters
	double chi2 = 0;

	for (int i = 0; i < N; ++i)
		sum += t[i] * y[i] / std_y[i];

	double b = 1./S_tt * sum;	
	double var_b = 1./S_tt;
	double a = (S_y - S_x * b)/S;
	double var_a = 1./S * (1+S_x*S_x/(S_tt*S));
	
	for (int i = 0; i < N; ++i)
	{
		chi2 += (y[i]-(a + b * x[i]))/(std_y[i])*(y[i]-(a + b * x[i]))/(std_y[i]);
	}

	// The following lines could have been directly written above as parameters[0] = b = ...? only if b,a, etc had been initialised?
	parameters[0] = b;
	parameters[1] = var_b;
	parameters[2] = a;
	parameters[3] = var_a;
	parameters[4] = chi2;
	return parameters;
}

int Fitab::get_dof()
{
return N - 2; // Degrees of freedom for chi-square test
}

int main()
{

	const int N = 5000; // Number of lines of data file: possible improvement: use a function to calculate it (for loop with function get_lines() ? )
	VecDoub t(N), x2(N), std_x2(N), y2(N), std_y2(N);
	ifstream import("msq.txt", ios::in); // Open input stream
	int j = 0;
	const double threshold = 600; // Lower bound of fitting interval (time >=600)
	bool flag = 1; // Flag used to indicate when we import the first value of time that satisfies t>=600
	int skip_line; // Number of line corresponding to minimum time

	// Import all data. Possible improvement: skip first 600 lines straight away?
	while ( import.good() && !import.eof() )
	{
		import >> t[j++] >> x2[j] >> std_x2[j] >> y2[j] >> std_y2[j]; // Note: compiler gives me a warning about possible undefined behaviour for j

		if ( t[j-1] >= threshold && flag )  // Detect when we read first value of time above threshold t > = 600
		{
			skip_line = j-1; 
			flag = 0;
		}
	}

	// Selecting the range of data (in lines) we're interested in (t >= 600) and calculate perpendicular displacement and uncertainty
	int size_subset = N - skip_line;
	VecDoub t_subset(size_subset);
	VecDoub r_perp2(size_subset);
	VecDoub std_r_perp2(size_subset);

	for (int i = 0; i < size_subset; ++i) // This could easily be done in the while loop above if we'd created the corresponding VecDoub's before
	{
		t_subset[i] = t[skip_line + i];
		r_perp2[i] = (x2[skip_line + i] + y2[skip_line + i])/2;
		// standard deviation of r_perp2: Right now standard propagation of errors used in physics
		std_r_perp2[i] = sqrt(std_x2[skip_line + i]*std_x2[skip_line + i] + std_y2[skip_line + i]*std_y2[skip_line + i])/2;

	}

	// Fitting procedure
	Fitab fit(t_subset, r_perp2, std_r_perp2);
	VecDoub parameters = fit.get_parameters();
	int dof = fit.get_dof();// Degrees of freedom: number of points(of the fit) - free parameters (a, b)

	// Calculation of p-value
	Gamma Q; // Instantiation of gamma-integral object
	double chi2 = parameters[4];
	double p_value = Q.gammq(dof/2, chi2/2);


	// Showing the results of the fit
	cout << "# b +- std_b:" << parameters[0] << "+-" << sqrt(parameters[1]) << "\n" <<
		"# a +- std_a:" << parameters[2] << "+-" << sqrt(parameters[3]) << "\n" <<
		"# chi^2 = " << chi2 << "\n" <<
		"# p-value = " << p_value << endl;
	cout << "# Since p-value > significance level (typically 0.01 or 0.05), we conclude from the statistical test that null hypothesis is valid at that significance level, i.e. the data is correctly modelled (at that significance level) by a straight line (the p-value represents the probability of finding a discrepancy between observed and theoretical model at least as large as the one measured here if the null hypothesis is valid (i.e. data follows linear model). In other words, probability of chance fluctuations w.r.t. theoretical model giving at least such a discrepancy. The larger the p-value (in this case), the more accurate the model)" << endl;

}
