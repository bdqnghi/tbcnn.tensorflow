// Example program
#include <iostream>
#include <string>
using namespace std;

int main()
{
	int array1[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
	int array2[3][3] = { { 3, 2, 4 }, { 4, 5, 8 }, { 7, 1, 9 } };
	int mul[3][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
	int i, j = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			mul[i][j] = array1[i][j] * array2[i][j];
		}
	}
	cout << "The Original Matix 1 is : ";
	cout << endl;
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++){
			cout << array1[a][b] << " ";
		}
		cout << endl;
	}
	cout << "The Original Matix 2 is : ";
	cout << endl;
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++){
			cout << array2[a][b] << " ";
		}
		cout << endl;
	}
	cout << "The Multiplied Matix is : ";
	cout << endl;
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++){
			cout << mul[a][b] << " ";
		}
		cout << endl;
	}
}
