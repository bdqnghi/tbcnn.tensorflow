#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#define NUM_VAR 1
#define N_MAX 4096
//#define ETA 0.00000007
#define ETA 0.008
#define LAMBDA 0
#define MEAN_COL 14.0
#define NUM_CHECKS 1024

double predictedProb(double weights[NUM_VAR+1], double x_values[NUM_VAR+1])
{
	double exponent = 0.0;
	for (int w = 0; w < NUM_VAR+1; w++)
		exponent = exponent + (weights[w] * x_values[w]);
	//exponent = (weights[0]*x_values[0]) + (weights[1]*x_values[1]);
	//double normal = (weights[NUM_VAR]/(sqrt(2*acos(-1.0)))) * exp(-0.5*pow(((x_values[NUM_VAR]-MEAN_COL)*weights[NUM_VAR]), 2));
	//cout << normal << "\n";
	return exp(exponent)/(1.0+exp(exponent)); //+ (weights[2]*x_values[2]);
}

double predictedNorm(double invStdev, double x_val)
{
	return (invStdev/sqrt(2*acos(-1.0))) * exp(-0.5*pow(((x_val-MEAN_COL)*invStdev), 2));
}

int main(void)
{
	ifstream infile ("NPercentTestSummary.txt");
	int L = 0;
	infile >> L;
	double X[L][NUM_VAR+1];
	double Y[L];
	double W[NUM_VAR+1];
	for (int l = 0; l < L; l++)
	{
		infile >> Y[l];
		Y[l] = Y[l]/NUM_CHECKS;
		X[l][0] = 1;
		for (int nv = 1; nv <= NUM_VAR; nv++)
		{
			infile >> X[l][nv];
			//cout << X[l][nv] << " ";
		}
		//cout << "\n";
	}
	
	W[0] = 0;
	W[1] = 0;
	//W[2] = 0;
	//W[3] = 1;
	//W[4] = 0.147;
	/*for (int wI = 1; wI <= NUM_VAR; wI++)
	{
		W[wI] = 0;
	}*/
	
	double avgDiff = 100000;
	cout << ETA  << "\n";
	while (avgDiff > 9e-5)
	{
		double W_new[NUM_VAR+1];
		avgDiff = 0.0;
		for (int i = 0; i < NUM_VAR+1; i++)
		{
			double totalAdd = 0;
			for (int j = 0; j < L; j++)
			{
				double difference = (double) Y[j] - predictedProb(W, X[j]);
				//double difference = (double) Y[j] - predictedNorm(W[NUM_VAR], X[j][NUM_VAR]);
				//maxDiff = max(maxDiff, pow(difference, 2));
				avgDiff = avgDiff + pow(difference, 2);
				totalAdd = totalAdd + (double) ETA * ((X[j][i] * (difference)) - LAMBDA*W[i]);
			}
			W_new[i] = W[i] + totalAdd;
		}
		for (int i2 = 0; i2 < NUM_VAR+1; i2++)
		{
			//maxDiff = max(max(maxDiff, W[i2]-W_new[i2]), W_new[i2]-W[i2]);
			W[i2] = W_new[i2];
			cout << i2 << " " << W[i2] << " " << predictedProb(W, X[0]) << " " << predictedProb(W, X[5]) << "\n";
		}
		avgDiff = avgDiff/L;
		cout << avgDiff << "\n";		
	}
	double error = 0.0;
	for (int test = 0; test < L; test++)
	{
		error = error + pow(Y[test]-predictedProb(W, X[test]), 2);
		if (test == 0)
			cout << Y[test] << " " << pow(Y[test]-predictedProb(W, X[test]), 2) << "\n";
	}
	for (int output = 0; output < NUM_VAR; output++)
		cout << W[output] << " ";
	cout << W[NUM_VAR] << "\n";
	cout << error << "\n";
	
	return 0;
}
