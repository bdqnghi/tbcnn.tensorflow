#include "MatrixMultiplication.h"

using namespace std;

/*
  * Constructor: Creating a regular square matrix, with random number of zeroes
  * Here, true represents a matrix is populated with 0's and a false represents that matrix is populated with random #
  * */
MatrixMultiplication::MatrixMultiplication(int size, bool empty, bool ranNum){
		
		matrixZOrder = NULL;
		matrixZOrderSize = 0;
		matrixRowSize = size;
		
		if(!ranNum){
			srand(time(NULL));
		
		}
		
		//populating the matrix with some memory allocation 
		matrixRow = (int**) malloc(matrixRowSize * sizeof(int*));
		
		for(int i = 0; i < matrixRowSize; i++){
			
			matrixRow[i] = (int*) malloc(matrixRowSize * sizeof(int));
			
			for(int j = 0; j < matrixRowSize; j++){
				
				if(empty){
					
					matrixRow[i][j] = 0;
					
				}else{
					
					matrixRow[i][j] = rand() %100 + 1;
				}
			}
		}
}

/*
 * deConstructor : deallocating the memory
 * */
MatrixMultiplication::~MatrixMultiplication(){

	if(matrixRow != NULL){
		
		for(int i = 0; i < matrixRowSize; i++){
			
			if(matrixRow[i] != NULL)
				free(matrixRow[i]);
		}
		
		free(matrixRow);
	}
	
	if(matrixZOrder != NULL){
		free(matrixZOrder);
	
	}
}

void MatrixMultiplication::convertToZorder(unsigned int startIndexI, unsigned int startIndexJ, unsigned int size){
	if(size < 4){
		
		for(unsigned int i = startIndexI; i < startIndexI + size; i++){
			for(unsigned int j = startIndexJ; j < startIndexJ + size; j++){
				unsigned int indexZ = 0;
				

				for(int k = 0; k < sizeof(i) * CHAR_BIT; k++){
					 indexZ |= (j & 1U << k) << k | (i & 1U << k) << (k + 1);
				}
				
				matrixZOrder[indexZ] = matrixRow[i][j];
			}
		}
	}else{
		
		convertToZorder(startIndexI, startIndexJ, size / 2);
		convertToZorder(startIndexI, startIndexJ + (size / 2), size / 2);
		convertToZorder(startIndexI  + (size / 2), startIndexJ,  size / 2);
		convertToZorder(startIndexI + (size / 2), startIndexJ + (size / 2), size / 2);
		
	}
}

//updating the z-order matrix
void MatrixMultiplication::updatingMatrixZOrder(){
		if(matrixRow != NULL){
			if(matrixZOrder == NULL){
				
				matrixZOrderSize = matrixRowSize * matrixRowSize;
				matrixZOrder = (int*)malloc(matrixZOrderSize * sizeof(int));
			
			}
			
			convertToZorder(0, 0, matrixRowSize);
		}
}

void MatrixMultiplication::convertToRowMatrix(unsigned int startIndexK, unsigned int length){
		if(length < 4){
			
			for(unsigned int k = startIndexK; k < startIndexK + length; k++){
				unsigned int indexI = 0;
				unsigned int indexJ = 0;
				

				for(int l = 0; l < sizeof(k) * CHAR_BIT; l += 2){
					 indexJ |= (k & 1U << l) >> (l / 2);
					 indexI |= (k & 1U << (l + 1)) >> (1 + (l / 2));
				}
				

				matrixRow[indexI][indexJ] = matrixZOrder[k];
			}
		}else{

			convertToRowMatrix(startIndexK, length / 4);
			convertToRowMatrix(startIndexK + (length / 4), length / 4);
			convertToRowMatrix(startIndexK + ((length / 4) * 2), length / 4);
			convertToRowMatrix(startIndexK + ((length / 4) * 3), length / 4);
			
		}
}

//getter methods
int** MatrixMultiplication::getMatrixRow(){
		return matrixRow;
		
}

int* MatrixMultiplication::getMatrixZOrder(){
		return matrixZOrder;
		
}

void MatrixMultiplication::updatingMatrixRow(){
		if(matrixZOrder != NULL){
			convertToRowMatrix(0, matrixZOrderSize);
			
		}
		
}

//printing the Row Matrix
void MatrixMultiplication::printMatrixRow(){
	for(int i = 0; i < matrixRowSize; i++){
		for(int j = 0; j < matrixRowSize; j++){
			cout << matrixRow[i][j] << " ";
		}
		cout << endl;
	}
}

//print the z-order matrix
void MatrixMultiplication::printMatrixZOrder(){
	for(int i = 0; i < matrixZOrderSize; i++){
		cout << matrixZOrder[i] << " ";
		
	}
	cout << endl;
	
}
