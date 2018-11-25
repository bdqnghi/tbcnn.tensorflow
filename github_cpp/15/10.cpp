#include <iostream>
#include <cstdlib>


using namespace std;

#define x 8
#define y 8
#define m 8
#define n 8

void multiplication(int i, int j, int c[][8], int a[][8], int b[][8]);
void multiplication(int i, int j, int c[][8], int a[][8], int b[][8]){
	for (i = 0; i<x; i++){
		for (j = 0; j<n; j++){
			c[i][j] = 0;
			for (int k = 0; k<m; k++){
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}
		}
	}
}

int main(int argc, const char* argv[]){

	int i, j;
	int a[x][y] = {
		{ 12, 13, 2, 3, 3, 2, 11, 5 }, 
		{ 3, 5, 2, 14, 11, 5, 6, 12 }, 
		{ 4, 11, 3, 2, 5, 7, 12, 3 }, 
		{ 13, 11, 12, 4, 8, 11, 10, 3 }, 
		{ 11, 6, 3, 2, 6, 7, 1, 2 },
		{ 12, 4, 3, 7, 4, 5, 1, 3 },
		{ 4, 7, 9, 2, 4, 1, 3, 5 },
		{ 10, 4, 8, 4, 6, 9, 2, 5 },
	},
	b[m][n] = {
		{ 12, 11, 3, 5, 10, 1, 3, 6 },
		{12, 3, 5, 6, 1, 7, 9, 2 },
		{2, 3, 5, 1, 3, 2, 4, 1},
		{9, 5, 1, 3, 4, 1, 2, 5},
		{2, 5, 3, 7, 1, 2, 4, 9},
		{2, 6, 3, 2, 7, 9, 1, 2},
		{4, 6, 1, 3, 8, 1, 4, 4},
		{2, 3, 7, 12, 9, 4, 5, 7},
	}, 
	
	c[x][n];

		
    cout<<"\n\nMatrix A :\n\n";
 
    for(i=0;i<x;i++) {
        for(j=0;j<y;j++){
            cout<<"\t"<<a[i][j];
        }
        cout<<"\n\n";
    }
 
    cout<<"\n\nMatrix B :\n\n";
 
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            cout << "\t"<<b[i][j];
        }
        cout << "\n\n";
    }
 

	multiplication(i, j, c,a,b);


 
        cout<<"\n\nMultiplication of Matrix A and Matrix B :\n\n";
 
        for(i=0;i<x;i++) {
            for(j=0;j<n;j++) {
                cout<<"\t"<<c[i][j];
            }
            cout<<"\n\n";
        }
    
    return 0;
} 