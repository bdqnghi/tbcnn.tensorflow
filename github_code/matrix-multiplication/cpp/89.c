
//Multiply Two Matrices

#include<iostream>
using namespace std;

int main() {

  int matrixOne[10][10], matrixTwo[10][10], matrixThree[10][10], sum=0, i, j, k;
  int matrixOneWidth, matrixOneHeight, matrixTwoWidth, matrixTwoHeight; //width = columns, height = rows

  cout<< "Enter first matrix's width : ";
  cin>> matrixOneWidth;
  cout<< "Enter first matrix's height : ";
  cin>> matrixOneHeight;

  cout<< "Enter second matrix's width : ";
  cin>> matrixTwoWidth;
  cout<< "Enter second matrix's height : ";
  cin>> matrixTwoHeight;

  if(matrixOneWidth != matrixTwoHeight) {
    cout<< "Can not multiply the matrices.";
    exit(-1);
  }

  cout<< "Enter first matrix elements : ";

  for(i=0; i<matrixOneHeight; i++) {
    for(j=0; j<matrixOneWidth; j++)
      cin>> matrixOne[i][j];
  }

  cout<< "Enter second matrix elements : ";

  for(i=0; i<matrixTwoHeight; i++) {
    for(j=0; j<matrixTwoWidth; j++)
      cin>> matrixTwo[i][j];
  }

  cout<< "Multiplying two matrices...\n";

  for(i=0; i<matrixOneHeight; i++) { //iterate through rows of 1st matrix
    for(j=0; j<matrixTwoWidth; j++) { //iterate through columns of 2nd matrix
      sum = 0; //reset sum
      for(k=0; k<matrixTwoHeight; k++) //iterate through rows of 2nd matrix
        sum = sum + (matrixOne[i][k] * matrixTwo[k][j]); //multiply each and find the sum
      matrixThree[i][j] = sum;
    }
  }

  cout<< "\nProduct of two matrices : \n";

  for(i=0; i<matrixOneHeight; i++) {
    for(j=0; j<matrixTwoWidth; j++)
      cout<< matrixThree[i][j] << " ";
    cout<< "\n";
  }
}


