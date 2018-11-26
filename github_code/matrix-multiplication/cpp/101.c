#include<iostream>
using namespace std;
int SIZE;
int getmatrix(int c[5][5]){
	int i,j,a,b;
	cout<<"\nGet the matrix dimension";
	cin>>i;
	SIZE=i;
	cin>>j;
	for(a=0;a<i;a++){
		for(b=0;b<j;b++){
			cout<<"\nInput for a["<<a<<"]["<<b<<"]:";
			cin>>c[a][b];
		}
	}
	return(c[i][j]);
}
void MatrixMultiply(int a[5][5], int b[5][5], int mul[5][5]){
	cout<<"\nResult:";
	int row,col,k;
  	for (row = 0; row < SIZE; row++){
    	for (col = 0; col < SIZE; col++){
      		mul[row][col] = 0;
      			for (k = 0; k < SIZE; k++){
        			mul[row][col] += a[row][k] * b[k][col];
      			}
      			cout<<"\n["<<row<<"]["<<col<<"]:"<<mul[row][col];
    		}
  		}
}

int main(){
	cout<<"\n The matrix Program";
	int a[5][5],b[5][5],c[5][5];
	getmatrix(a);
	getmatrix(b);
	MatrixMultiply(a,b,c);
	
}

