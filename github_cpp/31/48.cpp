//============================================================================
// Name        : MatrixMultiplication.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime> //library for current time
#include <cstdlib> //library for random number
#include <cstring>
#include <fstream>
#define THRESHOLD 16

using namespace std;

class MyMatrix{
public:
	//n=dimension of submatrix
	MyMatrix(int** matrix, int rowstart,int colstart,int n):size(n),startrow(rowstart),startcol(colstart){
		if(colstart>0){
			int** tempPtr=matrix+rowstart;
			squareMatrix=new int*[n];
			for(int i=0;i<n;i++){
				squareMatrix[i]=tempPtr[i]+colstart;
			}
		}else{
			squareMatrix=matrix+rowstart;
		}
	}	
	static void classicalMultiply(const int**, const int**, int**, int);
	static void divideAndConquer(int**, int**, int**, int);
	static void addMatrix(MyMatrix& firstMatrix, MyMatrix& secondMatrix, MyMatrix& newMatrix,int n);
	static void subtractMatrix(MyMatrix& firstMatrix, MyMatrix& secondMatrix, MyMatrix& newMatrix,int n);
	static void strassen(int**, int**, int**, int);

	~MyMatrix(){
		if(startcol>0){
			delete[] squareMatrix;
		}
	}
	void getMatrixPtr(int**& returnPtr,int& returnSize){
		returnPtr=squareMatrix;
		returnSize=size;
	}
	int getSize(){
		return size;
	}
private:
	int size,startrow,startcol;
	int **squareMatrix;
	static void helperDivideAndConquer(MyMatrix& firstMatrixClass, MyMatrix& secondMatrixClass,MyMatrix& newMatrixClass,int n);
	static void helperStrassen(MyMatrix& firstMatrixClass, MyMatrix& secondMatrixClass,MyMatrix& newMatrixClass,int n);
};

//classical way to multiply matrix
void MyMatrix::classicalMultiply(const int** firstMatrix, const int** secondMatrix,int** newMatrix, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<n;k++){
				newMatrix[i][j]=newMatrix[i][j]+firstMatrix[i][k]*secondMatrix[k][j];
			}
		}
	}
}


void MyMatrix::addMatrix(MyMatrix& firstMatrix, MyMatrix& secondMatrix, MyMatrix& newMatrix,int n){
	int** ptr1=firstMatrix.squareMatrix;
	int** ptr2=secondMatrix.squareMatrix;
	int** ptr3=newMatrix.squareMatrix;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			ptr3[i][j]=ptr1[i][j]+ptr2[i][j];
		}
	}
}

void MyMatrix::subtractMatrix(MyMatrix& firstMatrix, MyMatrix& secondMatrix, MyMatrix& newMatrix,int n){
	int** ptr1=firstMatrix.squareMatrix;
	int** ptr2=secondMatrix.squareMatrix;
	int** ptr3=newMatrix.squareMatrix;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			ptr3[i][j]=ptr1[i][j]-ptr2[i][j];
		}
	}
}

//divide and conquer - testing purpose only
void MyMatrix::helperDivideAndConquer(MyMatrix& firstMatrixClass, MyMatrix& secondMatrixClass,MyMatrix& newMatrixClass,int n){
	if(n<=1){
		**newMatrixClass.squareMatrix=**firstMatrixClass.squareMatrix*(**secondMatrixClass.squareMatrix);
		return;
	}
	MyMatrix a11MatrixClass(firstMatrixClass.squareMatrix,0,0,n/2);
	MyMatrix b11MatrixClass(secondMatrixClass.squareMatrix,0,0,n/2);
	MyMatrix c11MatrixClass(newMatrixClass.squareMatrix,0,0,n/2);
	helperDivideAndConquer(a11MatrixClass,b11MatrixClass,c11MatrixClass,n/2); //c11=a11*b11;
	int** temp=new int*[n/2];
	for(int i=0;i<n/2;i++){
		temp[i]=new int[n/2];
	}
	MyMatrix a12MatrixClass(firstMatrixClass.squareMatrix,0,n/2,n/2);
	MyMatrix b21MatrixClass(secondMatrixClass.squareMatrix,n/2,0,n/2);
	MyMatrix newerMatrixClass(temp,0,0,n/2);
	helperDivideAndConquer(a12MatrixClass,b21MatrixClass,newerMatrixClass,n/2); //temp=a12*b21;
	addMatrix(c11MatrixClass,newerMatrixClass,c11MatrixClass,n/2);
	
	MyMatrix b12MatrixClass(secondMatrixClass.squareMatrix,0,n/2,n/2);
	MyMatrix c12MatrixClass(newMatrixClass.squareMatrix,0,n/2,n/2);
	helperDivideAndConquer(a11MatrixClass,b12MatrixClass,c12MatrixClass,n/2); //c12=a11*b12;

	MyMatrix b22MatrixClass(secondMatrixClass.squareMatrix,n/2,n/2,n/2);
	helperDivideAndConquer(a12MatrixClass,b22MatrixClass,newerMatrixClass,n/2); //temp=a12*b22;
	addMatrix(c12MatrixClass,newerMatrixClass,c12MatrixClass,n/2);
	
	MyMatrix a21MatrixClass(firstMatrixClass.squareMatrix,n/2,0,n/2);
	MyMatrix c21MatrixClass(newMatrixClass.squareMatrix,n/2,0,n/2);
	helperDivideAndConquer(a21MatrixClass,b11MatrixClass,c21MatrixClass,n/2); //c21=a21*b11

	MyMatrix a22MatrixClass(firstMatrixClass.squareMatrix,n/2,n/2,n/2);
	helperDivideAndConquer(a22MatrixClass,b21MatrixClass,newerMatrixClass,n/2); //temp=a22*b21;
	addMatrix(c21MatrixClass,newerMatrixClass,c21MatrixClass,n/2);
	
	MyMatrix c22MatrixClass(newMatrixClass.squareMatrix,n/2,n/2,n/2);
	helperDivideAndConquer(a21MatrixClass,b12MatrixClass,c22MatrixClass,n/2); //c22=a21*b12

	helperDivideAndConquer(a22MatrixClass,b22MatrixClass,newerMatrixClass,n/2); //temp=a22*b22;
	addMatrix(c22MatrixClass,newerMatrixClass,c22MatrixClass,n/2);
	
	for(int i=0;i<n/2;i++){
		delete[] temp[i];
	}
	delete[] temp;
}

void MyMatrix::divideAndConquer(int** firstMatrix, int** secondMatrix,int** newMatrix,int n){
	//printMatrix((const int**)firstMatrix,n);
	//printMatrix((const int**)secondMatrix,n);
	MyMatrix firstMatrixClass(firstMatrix,0,0,n);
	MyMatrix secondMatrixClass(secondMatrix,0,0,n);
	MyMatrix newMatrixClass(newMatrix,0,0,n);
	helperDivideAndConquer(firstMatrixClass,secondMatrixClass,newMatrixClass,n);
}

void MyMatrix::helperStrassen(MyMatrix& firstMatrixClass, MyMatrix& secondMatrixClass,MyMatrix& newMatrixClass,int n){
	if(n<=THRESHOLD){
		for(int i=0;i<n;i++){
			memset(newMatrixClass.squareMatrix[i],0,sizeof(int)*n);
/*
			for(int j=0;j<n;j++){
				newMatrixClass.squareMatrix[i][j]=0;
			}
*/
		}

		classicalMultiply((const int**)firstMatrixClass.squareMatrix, (const int**)secondMatrixClass.squareMatrix,newMatrixClass.squareMatrix, n);
		return;
	}else{
		MyMatrix a11MatrixClass(firstMatrixClass.squareMatrix,0,0,n/2);
		MyMatrix b12MatrixClass(secondMatrixClass.squareMatrix,0,n/2,n/2);
		MyMatrix b22MatrixClass(secondMatrixClass.squareMatrix,n/2,n/2,n/2);

		int** temp=new int*[n/2];
		for(int i=0;i<n/2;i++){
			temp[i]=new int[n/2];
		}
		MyMatrix tempClass(temp,0,0,n/2);

		int** tempRArr=new int*[n/2];
		for(int i=0;i<n/2;i++){
			tempRArr[i]=new int[n/2];
		}
		MyMatrix R(tempRArr,0,0,n/2);
		subtractMatrix(b12MatrixClass,b22MatrixClass,tempClass,n/2);	//tempClass=b12-b22
		helperStrassen(a11MatrixClass,tempClass,R,n/2);	//R=a11*tempClass

		MyMatrix a22MatrixClass(firstMatrixClass.squareMatrix,n/2,n/2,n/2);
		MyMatrix b11MatrixClass(secondMatrixClass.squareMatrix,0,0,n/2);
		MyMatrix b21MatrixClass(secondMatrixClass.squareMatrix,n/2,0,n/2);
		
		int** tempSArr=new int*[n/2];
		for(int i=0;i<n/2;i++){
			tempSArr[i]=new int[n/2];
		}
		MyMatrix S(tempSArr,0,0,n/2);
		subtractMatrix(b21MatrixClass,b11MatrixClass,tempClass,n/2);	//tempClass=b21-b11
		helperStrassen(a22MatrixClass,tempClass,S,n/2);	//S=a22*tempClass

		MyMatrix a12MatrixClass(firstMatrixClass.squareMatrix,0,n/2,n/2);

		int** tempTArr=new int*[n/2];
		for(int i=0;i<n/2;i++){
			tempTArr[i]=new int[n/2];
		}
		MyMatrix T(tempTArr,0,0,n/2);
		addMatrix(a11MatrixClass,a12MatrixClass,tempClass,n/2);	//tempClass=a11+a12
		helperStrassen(tempClass,b22MatrixClass,T,n/2);	//T=tempClass*b22

		MyMatrix a21MatrixClass(firstMatrixClass.squareMatrix,n/2,0,n/2);

		int** temp2=new int*[n/2];
		for(int i=0;i<n/2;i++){
			temp2[i]=new int[n/2];
		}
		MyMatrix tempClass2(temp2,0,0,n/2);

		int** tempPArr=new int*[n/2];
		for(int i=0;i<n/2;i++){
			tempPArr[i]=new int[n/2];
		}
		MyMatrix P(tempPArr,0,0,n/2);
		addMatrix(a11MatrixClass,a22MatrixClass,tempClass,n/2);	//tempClass=a11+a22
		addMatrix(b11MatrixClass,b22MatrixClass,tempClass2,n/2);	//tempClass2=b11+b22
		helperStrassen(tempClass,tempClass2,P,n/2);	//P=(a11+a22)(b11+b22)

		int** tempQArr=new int*[n/2];
		for(int i=0;i<n/2;i++){
			tempQArr[i]=new int[n/2];
		}
		MyMatrix Q(tempQArr,0,0,n/2);
		addMatrix(a21MatrixClass,a22MatrixClass,tempClass,n/2);	//tempClass=a21+a22
		helperStrassen(tempClass,b11MatrixClass,Q,n/2);	//Q=tempClass*b11

		int** tempUArr=new int*[n/2];
		for(int i=0;i<n/2;i++){
			tempUArr[i]=new int[n/2];
		}
		MyMatrix U(tempUArr,0,0,n/2);
		subtractMatrix(a21MatrixClass,a11MatrixClass,tempClass,n/2);	//tempClass=a21-a11
		addMatrix(b11MatrixClass,b12MatrixClass,tempClass2,n/2); //tempClass2=b11+b12
		helperStrassen(tempClass,tempClass2,U,n/2);	//U=tempClass*tempClass2

		int** tempVArr=new int*[n/2];
		for(int i=0;i<n/2;i++){
			tempVArr[i]=new int[n/2];
		}
		MyMatrix V(tempVArr,0,0,n/2);
		subtractMatrix(a12MatrixClass,a22MatrixClass,tempClass,n/2);	//tempClass=a12-a22
		addMatrix(b21MatrixClass,b22MatrixClass,tempClass2,n/2); //tempClass2=b21+b22
		helperStrassen(tempClass,tempClass2,V,n/2);	//V=tempClass*tempClass2

		MyMatrix c11MatrixClass(newMatrixClass.squareMatrix,0,0,n/2);
		MyMatrix c12MatrixClass(newMatrixClass.squareMatrix,0,n/2,n/2);
		MyMatrix c21MatrixClass(newMatrixClass.squareMatrix,n/2,0,n/2);
		MyMatrix c22MatrixClass(newMatrixClass.squareMatrix,n/2,n/2,n/2);

		addMatrix(P,S,c11MatrixClass,n/2);
		subtractMatrix(c11MatrixClass,T,c11MatrixClass,n/2);
		addMatrix(c11MatrixClass,V,c11MatrixClass,n/2);

		addMatrix(R,T,c12MatrixClass,n/2);

		addMatrix(Q,S,c21MatrixClass,n/2);

		addMatrix(P,R,c22MatrixClass,n/2);
		subtractMatrix(c22MatrixClass,Q,c22MatrixClass,n/2);
		addMatrix(c22MatrixClass,U,c22MatrixClass,n/2);

		for(int i=0;i<n/2;i++){
			delete[] temp[i];
			delete[] temp2[i];
			delete[] tempPArr[i];
			delete[] tempQArr[i];
			delete[] tempRArr[i];
			delete[] tempSArr[i];
			delete[] tempTArr[i];
			delete[] tempUArr[i];
			delete[] tempVArr[i];
		}
		delete [] temp;
		delete [] temp2;
		delete [] tempPArr;
		delete [] tempQArr;
		delete [] tempRArr;
		delete [] tempSArr;
		delete [] tempTArr;
		delete [] tempUArr;
		delete [] tempVArr;
	}
}

void MyMatrix::strassen(int** firstMatrix, int** secondMatrix,int** newMatrix,int n){
	MyMatrix firstMatrixClass(firstMatrix,0,0,n);
	MyMatrix secondMatrixClass(secondMatrix,0,0,n);
	MyMatrix newMatrixClass(newMatrix,0,0,n);
	helperStrassen(firstMatrixClass,secondMatrixClass,newMatrixClass,n);
}

void createMatrix(int **newMatrix,int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			int num=rand()%100+1;
			newMatrix[i][j] = num;
		}
	}
}

void printMatrix(ostream& os, const int** matrix, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			os << matrix[i][j] << " ";
		}
		os << endl;
	}
}

void printMatrixToFile(const int** matrix, int n,string &filename){
	ofstream myfile;
	myfile.exceptions (ofstream::failbit | ofstream::badbit);
	try {
		myfile.open(filename.c_str());
		/*
		if(myfile.fail()){
			cerr<<"error opening file "<<filename.c_str()<<" to write"<<endl;
			return;
		}
		*/
		printMatrix(myfile,matrix,n);
	}catch(ofstream::failure e) {
		cerr << "Exception opening/writing file"<<filename.c_str()<<e.what()<<endl;
	}
	myfile.close();
}

int main(int argc, char** argv){
	int n;
	int **firstMatrix, **secondMatrix, **multipliedMatrix;
	long timeBefore, timeAfter;
	bool print=false;
	bool classical=false;
	bool strassen=false;
	bool writefile=false;
	string *filename=NULL;
	for(int i=1;i<argc;i++){
		if(strcmp(argv[i],"--print")==0) print=true;
		else if(strcmp(argv[i],"--classical")==0) classical=true;
		else if(strcmp(argv[i],"--strassen")==0) strassen=true;
		else if(strcmp(argv[i],"--writefile")==0){
			if(argc<=(++i)){
				cerr<<"please specify a file name"<<endl;
				return 1;
			}
			writefile=true;
			filename=new string(argv[i]);
		}
	}
	if(!classical&&!strassen){
		cout<<"usage: "<<argv[0]<<" with at least one of the following two switches:"<<endl;
		cout<<"--classical for classical, --strassen for strassen multiplication"<<endl;
		cout<<"optional switch: --print to print matrix --writefile filename to write to file"<<endl;
		return 1;
	}
	cout << "Please enter the size of the matrix: ";
	cin >> n;
	cout << "First matrix: "<<endl;

	firstMatrix=new int*[n];
	for(int i=0;i<n;i++){
		firstMatrix[i]=new int[n];
	}

	createMatrix(firstMatrix,n);
	if(print)
		printMatrix(cout,(const int**)firstMatrix,n);
	cout << "Second matrix: "<<endl;
	
	secondMatrix=new int*[n];
	for(int i=0;i<n;i++){
		secondMatrix[i]=new int[n];
	}
	
	createMatrix(secondMatrix,n);
	if(print)
		printMatrix(cout,(const int**)secondMatrix,n);
	
	multipliedMatrix=new int*[n];
	for(int i=0;i<n;i++){
		multipliedMatrix[i]=new int[n];
		for(int j=0;j<n;j++){
			multipliedMatrix[i][j]=0;
		}
	}
	
	cout<<"begin multiplying:"<<endl;
	if(classical){
		timeBefore=clock();
		MyMatrix::classicalMultiply((const int**)firstMatrix,(const int**)secondMatrix,multipliedMatrix,n);
		timeAfter=clock();
		cout << "After multiply: " << endl;
		if(print){
			printMatrix(cout,(const int**)multipliedMatrix,n);
		}
		if(writefile){
			string filenameclassical=*filename;
			printMatrixToFile((const int**)multipliedMatrix,n,filenameclassical.append("_classical"));
		}
		cout<< "It took " << difftime(timeAfter, timeBefore) / CLOCKS_PER_SEC << " s for the classical multiplication."<<endl;
	}

/*
	timeBefore=clock();
	MyMatrix::divideAndConquer(firstMatrix,secondMatrix,multipliedMatrix,n);
	timeAfter=clock();

	cout << "After divide and conquer: " << endl;
	if(print){
		printMatrix((const int**)multipliedMatrix,n);
	}
it took
	cout<< "It took " << difftime(timeAfter, timeBefore) / CLOCKS_PER_SEC << " s for the divide and conquer."<<endl;
*/
	if(strassen){
		timeBefore=clock();
		MyMatrix::strassen(firstMatrix,secondMatrix,multipliedMatrix,n);
		timeAfter=clock();

		cout << "After strassen: " << endl;
		if(print){
			printMatrix(cout,(const int**)multipliedMatrix,n);
		}
		if(writefile){
			string filenamestrassen=*filename;
			printMatrixToFile((const int**)multipliedMatrix,n,filenamestrassen.append("_strassen"));
		}
		cout<< "It took " << difftime(timeAfter, timeBefore) / CLOCKS_PER_SEC << " s for the strassen."<<endl;
	}

	delete filename;
	for(int i=0;i<n;i++){
		delete[] firstMatrix[i];
		delete[] secondMatrix[i];
		delete[] multipliedMatrix[i];
	}
	delete[] firstMatrix;
	delete[] secondMatrix;
	delete[] multipliedMatrix;
	return 0;
}

