//
// Created by guilherme on 08/06/18.
//

#include <iostream>

using namespace std;

void FillMatrix( int **matrix, int lines, int columns ){

    for(int lin=0; lin<lines; lin++)
        for(int col=0; col<columns; col++)
            cin >> matrix[lin][col];

}

int MatrixMultiplication( int **matrixOne, int linesOne, int columnsOne, int **matrixTwo, int linesTwo, int columnsTwo ){

    if( columnsOne == linesTwo ){

    }

}

int main(){

    int linesOne=0, linesTwo=0, columnsOne=0, columnsTwo=0;

    // First matrix
    cout << "Input the lines of the first matrix:";
    cin >> linesOne;
    cout << "Input the coluns of the first matrix:";
    cin >> columnsOne;
    int **matrixOne = nullptr;
    matrixOne = new int * [linesOne];
    for(int lin=0; lin<linesOne; lin++) matrixOne[lin] = new int [columnsOne];

    cout << "\n\n" << "Second matrix" << "\n\n";

    // Second matrix
    cout << "Input the lines of the second matrix";
    cin >> linesTwo;
    cout << "Input the columns of the second matrix";
    cin >> columnsTwo;
    int **matrixTwo = nullptr;
    matrixTwo = new int * [linesTwo];
    for(int lin=0; lin<linesTwo; lin++) matrixTwo[lin] = new int [columnsTwo];

    // Fill matrices
    cout << "\n\n" << "Fill the fist matrix:" << endl;
    FillMatrix(matrixOne, linesOne, columnsOne);
    cout << "\n\n" << "Fill the second matrix:" << endl;
    FillMatrix(matrixTwo, linesTwo, columnsTwo);

    return 0;
}