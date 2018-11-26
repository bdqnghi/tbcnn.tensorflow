// To multiply two matrices stored as vector of vectors

#include <iostream>
#include <vector>

using namespace std;

void print(vector <vector <int> > M, int m, int n)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
			cout<<M[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
}

void initialize(vector < vector<int> > &M, int m, int n)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
			cin>>M[i][j];
	}
}

void multiply(vector <vector<int> > &A, vector <vector<int> > &B, vector <vector<int> > &C, int m, int n, int l)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<l;j++)
		{
			for(int k=0;k<n;k++)
				C[i][j]= C[i][j]+ A[i][k]*B[k][j];
		}
	}
}

int main()
{
	int m,n,l;
	cin>>m>>n>>l;
	// Dimension of A: mxn 
	// Dimension of B: nxl
	// Dimension of C: mxl
	vector< vector<int> > A(m, vector<int> (n) );
	vector< vector<int> > B(n, vector<int> (l) );
	vector< vector<int> > C(m, vector<int> (l,0) );

	initialize(A, m, n);
	initialize(B, n, l);
	cout<<"Initializing...."<<endl;
	print(A, m, n);
	print(B, n ,l);	
	print(C,m,l);
	cout<<endl<<"Product: "<<endl;
	multiply(A,B,C,m,n,l);

	print(C, m, l);

}
