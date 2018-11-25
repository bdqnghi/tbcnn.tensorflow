

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include <chrono>
#include "newmat.h"
#include "newmatap.h" 


#include "stdafx.h"

using namespace std;

typedef std::chrono::high_resolution_clock Clock;

class Assignment_8 {

private:

	double get_uniform()
	{
		return (double)rand() / (RAND_MAX);
	}


	Matrix brute_force_multiplication(Matrix input_matrix, int k) {

		Matrix output_matrix = input_matrix;

		for (int i = 1; i < k; i++) {
			output_matrix = input_matrix * output_matrix;
		}

		return output_matrix;
	}

	Matrix repeated_squaring_multiplication(Matrix input_matrix, int k) {

		if (k == 0) {
			IdentityMatrix I(input_matrix.Nrows());
			return I;
		}
		else if ((k % 2) == 1) { 
			return input_matrix * repeated_squaring_multiplication(input_matrix*input_matrix, (k - 1) / 2);
		}
		else if ((k % 2) == 0) { 
			return repeated_squaring_multiplication(input_matrix*input_matrix, (k / 2));
		}
	}


public:

	void write_data(char* file_name, ColumnVector data)
	{

		ofstream os;
		os.open(file_name);

		for (int i = 1; i <= data.Nrows(); i++) { 
			os << data(i) << endl << ends;
		}
	}


	void generate_matrix(Matrix &New_matrix) { 

		get_uniform();

		for (int i = 1; i <= New_matrix.Nrows(); i++)
			for (int j = 1; j <= New_matrix.Ncols(); j++) {
				New_matrix(i, j) = 10 * (get_uniform() - 0.5);
			}
	}

	void print_matrix(Matrix print_matrix) {


		for (int i = 1; i <= print_matrix.Nrows(); i++) {
			for (int j = 1; j <= print_matrix.Ncols(); j++) {
				cout << print_matrix(i, j) << "  ";
			}
			cout << endl;
		}
	}

	void run(int size, int exponent) {

		
		Matrix A(size, size);
		Matrix Answer_brute_force_multiplication(size, size);
		Matrix Answer_repeated_squaring_multiplication(size, size);
		ColumnVector time_data(exponent); 


		generate_matrix(A);

		cout << "The size of matrix is: " << size << endl;
		cout << "The exponent is: " << exponent << endl;

		for (int i = 1; i <= exponent; i++) {

			auto t_repeated_1 = Clock::now();
			Answer_repeated_squaring_multiplication = repeated_squaring_multiplication(A, i);
			auto t_repeated_2 = Clock::now();

			time_data(i) = chrono::duration_cast<chrono::nanoseconds>(t_repeated_2 - t_repeated_1).count() / pow(10, 9);
			
		}

		write_data("data_repeated", time_data); 
		

		for (int i = 1; i <= exponent; i++) {

			auto t_brute_1 = Clock::now();
			Answer_brute_force_multiplication = brute_force_multiplication(A, i);
			auto t_brute_2 = Clock::now();

			time_data(i) = chrono::duration_cast<chrono::nanoseconds>(t_brute_2 - t_brute_1).count() / pow(10, 9);

		} 

		write_data("data_bruted", time_data);
		


	}

};





int main(int argc, char* argv[])
{
	int exponent;
	int matrix_size;

	Assignment_8 Joonha;
	srand((unsigned)time(NULL)); 

	sscanf(argv[1], "%d", &matrix_size);
	sscanf(argv[2], "%d", &exponent);

	Joonha.run(matrix_size, exponent);


	return 0;
}
