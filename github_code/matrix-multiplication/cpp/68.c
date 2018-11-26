/*
Parallel program to perform matrix-matrix multiplication
*/
#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <cmath>
#include <omp.h>

using namespace std;

void populateMatrix(double ** matrix, int n);
double ** initializeMatrix(int n);
double multiplyMatrix(int n);
double** getTranspose(double** A, int n);
double tiledMultiplication(int n);

// Assign random values to square matrice.
void populateMatrix(double ** matrix, int n){

	for(int i = 0; i < n; i++ ){
		for(int j = 0; j < n; j ++){
			matrix[i][j] = rand();
		}
	}
}

// Initialized the square matrice.
double ** initializeMatrix(int n){
	double ** matrix;
	matrix = new double*[n];;
	for (int row = 0; row<n; row++) {
	  matrix[row] = new double[n];
	}
	return matrix;
}

//Get the transpose of a given matrix
double** getTranspose(double** A, int n){
	double** matrix = new double*[n]; //declare a new matrix to store the transpose of matrix B
	for(int i=0; i<n; i++){  
		matrix[i]=new double[n];
		for(int j=0; j<n; j++){
			matrix[i][j] = A[j][i];
		}
	}
	return matrix;
}

double multiplyMatrix(int n) {

	//define metrices
	double **matrixA;
	double **matrixB;
	double **matrixC;
	double **matrixBT;

	//initialze metrices
	matrixA = initializeMatrix(n);
	matrixB = initializeMatrix(n);
	matrixC = initializeMatrix(n);
	matrixBT = initializeMatrix(n);

	//fill values for metrices randomly
	populateMatrix(matrixA, n);
	populateMatrix(matrixB, n);
        
    double start, end;
	start = omp_get_wtime();  //take the time before multiplication
        
	/*
	*matrix multiplication (parallel_optimized)
	*/
	matrixBT = getTranspose(matrixB, n);  //get the transpose of matrix B
	double sum;
	cout << "Threds 1: " << omp_get_num_threads() << endl;
	
 	#pragma omp parallel for reduction(+:sum) num_threads(4)					//OpenMP parallel for
	for(int i = 0; i < n; i++){
	        for(int j = 0; j < n; j++){
	            sum = 0.0;
	            for (int k = 0; k < n; k++) {
	            	sum += matrixA[i][k] *  matrixBT[j][k];;
	            }
	            matrixC[i][j] =sum;
	        }
	    }
	/*
	*end of matrix multiplication (parallel_optimized)
	*/

	end = omp_get_wtime(); //take the time after the multiplication
	double elapsed_time = end -start;

	//delete the matrices
	for (size_t i = 0; i < n; i++) {
        delete [] matrixA[i];
        delete [] matrixB[i];
        delete [] matrixC[i];
    }
	delete[] matrixA;
	delete[] matrixB;
	delete[] matrixC;

	return elapsed_time;
}
double tiledMultiplication(int n) {
	//define metrices
	double **matrixA;
	double **matrixB;
	double **matrixC;
	
	//initialze metrices
	matrixA = initializeMatrix(n);
	matrixB = initializeMatrix(n);
	matrixC = initializeMatrix(n);
	
	//fill values for metrices randomly
	populateMatrix(matrixA, n);
	populateMatrix(matrixB, n);
        
    double start, end;
	int tile = n/20;
	double sum;
	
	start = omp_get_wtime();  //take the time before multiplication
	
	matrixB = getTranspose(matrixB, n);  //get the transpose of matrix B
	
	int x,y,z,i,j,k;
 	#pragma omp parallel for shared(matrixA,  matrixB, matrixC)  private(x, y, z, i, j, k, sum) schedule(static) num_threads(4)					//OpenMP parallel for
	for (x = 0; x < n; x += tile) {
		for (y = 0; y < n; y += tile) {
			for (z = 0; z < n; z += tile) {
				for (i = x; i < x + tile; i++) {
					for (j = y; j < y + tile; j++) {
						sum = 0.0;
						for (k = z; k < z + tile; k++) {
							sum += matrixA[i][k] *  matrixB[j][k];;
						}
						matrixC[i][j] = sum;
					}
				}
			}
		}
	}
	
	end = omp_get_wtime(); //take the time after the multiplication
	double elapsed_time = end -start;

	//delete the matrices
	for (size_t i = 0; i < n; i++) {
        delete [] matrixA[i];
        delete [] matrixB[i];
        delete [] matrixC[i];
    }
	delete[] matrixA;
	delete[] matrixB;
	delete[] matrixC;

	return elapsed_time;
}	

int main(int argc, const char * argv[]) {
	int n = atoi(argv[1]);  //getting the input for the matrix size
	double elapsed_time = multiplyMatrix(n);
	cout  << "Time for Multiplication with matrix transpose: " << elapsed_time << endl;
	double elapsed_time_tile = tiledMultiplication(n) ;
	cout  << "Time for Multiplication with tiled matrix: " << elapsed_time_tile  << endl;
	return 0;
}
