


#include<iostream>
using namespace std;

int main() {

  int matrixOne[10][10], matrixTwo[10][10], matrixThree[10][10], sum=0, i, j, k;
  int matrixOneWidth, matrixOneHeight, matrixTwoWidth, matrixTwoHeight; 

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

  for(i=0; i<matrixOneHeight; i++) { 
    for(j=0; j<matrixTwoWidth; j++) { 
      sum = 0; 
      for(k=0; k<matrixTwoHeight; k++) 
        sum = sum + (matrixOne[i][k] * matrixTwo[k][j]); 
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


