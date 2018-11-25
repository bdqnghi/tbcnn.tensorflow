#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int min(int a,int b, int c)
{	return min(a,min(b,c));	}

int EditDistance(string &A,string &B,vector<vector<int> > &matrix, int I,int J)
{	if(I==0)return J;
	if(J==0)return I;

	if( A[I-1] == B[J-1] ) matrix[I][J] = min( EditDistance(A,B,matrix,I-1,J-1), 
											   EditDistance(A,B,matrix,I,J-1) + 1 ,
											   EditDistance(A,B,matrix,I-1,J) + 1
											 );
	else matrix[I][J] = min(EditDistance(A,B,matrix,I-1,J-1)+1, 
							EditDistance(A,B,matrix,I,J-1)+1,
							EditDistance(A,B,matrix,I-1,J-1)+1
						   );
	return matrix[I][J];
}
int EditDistance(string &A,string &B)
{

	vector<vector<int> > matrix=vector<vector<int> >(A.size()+1,vector<int>(B.size()+1,0));
	int a = EditDistance( A,B,matrix,A.size(),B.size() );
	for(int i = 0 ; i<matrix.size(); ++i)
	{	for(int j=0 ; j<matrix[i].size();++j)
				cout<<matrix[i][j]<<' ';
		cout<<endl;
	}
	return a;
}
int main()
{	string A= string("saturday");
	string B= string("sunday");
	cout<<"Edit Distance : "<<EditDistance(A,B)<<endl;
	
	return 0;
}