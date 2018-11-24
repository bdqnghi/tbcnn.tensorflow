#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sys/types.h>
#include <ctime>
using namespace std;
ofstream plot("plot.dat", ios_base::app);

template <typename T>
void read_matrix(ifstream &my_stream, vector< vector<T> > &matrix)
{
	uint N, M;
	my_stream >> N;
	my_stream >> M;
	matrix.resize(N);
	for (uint i = 0; i < N; ++i)
	{
		matrix[i].resize(M);
		for (uint j = 0; j < M; ++j)
			my_stream >> matrix[i][j];
	}
}

template <typename T>
void print_matrix(ofstream &my_stream, vector< vector<T> > &matrix)
{
	if (sizeof(T) == sizeof(double))
		my_stream << "d";
	else
		my_stream << "f";
	my_stream << " " << matrix.size() << " " << matrix[0].size() << endl;

	for (uint i = 0; i < matrix.size(); ++i)
	{
		for (uint j = 0; j < matrix[0].size(); ++j)
			my_stream << matrix[i][j] << " ";
	my_stream << endl;
	}
}

template<typename T>
void multiply_ijk(const vector< vector<T> > &A,const vector< vector<T> > &B,vector< vector<T> > &C)
{
	C.resize(A.size(), vector<T>(B[0].size()));
	uint size1 = A.size(), size2 = B[0].size(), size3 = B.size();
	for (uint i = 0; i < size1; ++i)
	{
		for (uint j = 0; j < size2; ++j)
		{
			T sum = 0;
			for (uint k = 0; k < size3; ++k)
				sum += A[i][k] * B[k][j];
			C[i][j] = sum;
		}
	}
}

template<typename T>
void multiply_jik(const vector< vector<T> > &A,const vector< vector<T> > &B,vector< vector<T> > &C)
{
	C.resize(A.size(), vector<T>(B[0].size()));
	uint size1 = A.size(), size2 = B[0].size(), size3 = B.size();
	for (uint j = 0; j < size2; ++j)
	{
		for (uint i = 0; i < size1; ++i)
		{
			T sum = 0;
			for (uint k = 0; k < size3; ++k)
				sum += A[i][k] * B[k][j];
			C[i][j] = sum;
		}
	}
}

template<typename T>
void multiply_ikj(const vector< vector<T> > &A,const vector< vector<T> > &B,vector< vector<T> > &C)
{
	C.resize(A.size(), vector<T>(B[0].size()));
	uint size1 = A.size(), size2 = A[0].size(), size3 = B[0].size();
	for(uint i = 0; i < size1; i++)
	{
		for (uint j = 0; j < size2; j++)
		{
			T tmp = A[i][j];
			for (uint k = 0; k < size3; ++k)
				C[i][k] += tmp*B[j][k]; 
		}
	}
}

template<typename T>
void multiply_kij(const vector< vector<T> > &A,const vector< vector<T> > &B,vector< vector<T> > &C)
{
	C.resize(A.size(), vector<T>(B[0].size()));
	uint size1 = A.size(), size2 = A[0].size(), size3 = B[0].size();
	for (uint j = 0; j < size2; j++)
	{
		for(uint i = 0; i < size1; i++)
		{
			T tmp = A[i][j];
			for (uint k = 0; k < size3; ++k)
				C[i][k] += tmp*B[j][k]; 
		}
	}
}

template<typename T>
void multiply_jki(const vector< vector<T> > &A,const vector< vector<T> > &B,vector< vector<T> > &C)
{
	C.resize(A.size(), vector<T>(B[0].size()));
	uint size1 = C[0].size(), size2 = A[0].size(), size3 = A.size();
	for(uint j = 0; j < size1; j++)
	{
		for (uint k = 0; k < size2; k++)
		{
			T tmp = B[k][j];
			for (uint i = 0; i < size3; ++i)
				 C[i][j] += A[i][k]*tmp;
		}
	}
}

template<typename T>
void multiply_kji(const vector< vector<T> > &A,const vector< vector<T> > &B,vector< vector<T> > &C)
{
	C.resize(A.size(), vector<T>(B[0].size()));
	uint size1 = C[0].size(), size2 = A[0].size(), size3 = A.size();
	
	for (uint k = 0; k < size2; k++)
	{
		for(uint j = 0; j < size1; j++)
		{
			T tmp = B[k][j];
			for (uint i = 0; i < size3; ++i)
				 C[i][j] += A[i][k]*tmp;
		}
	}
}

template<typename T>
void multiply(const vector< vector<T> > &A,const vector< vector<T> > &B,vector< vector<T> > &C, string index_order)
{
	if (index_order == "ijk")
	{
		multiply_ijk(A, B, C);
		plot << 1;
	}
	else if(index_order == "jik")
	{
		multiply_jik(A, B, C);
		plot << 4;
	}
	else if(index_order == "ikj")
	{
		multiply_ikj(A, B, C);
		plot << 2;
	}
	else if(index_order == "kij")
	{
		multiply_kij(A, B, C);
		plot << 5;
	}
	else if(index_order == "jki")
	{
		multiply_jki(A, B, C);
		plot << 3;
	}
	else if(index_order == "kji")
	{
		multiply_kji(A, B, C);
		plot << 6;
	}
}

int main(int argc, char** argv)
{
	if (argc != 5)
	{
		cout << "Неверное число параметров" << endl;
		return 1;
	}

	ifstream input_A(argv[1]), input_B(argv[2]);
	ofstream output_C(argv[3]);
	string index_order, type_A, type_B;
	index_order = argv[4];

	input_A >> type_A;
	input_B >> type_B;

	bool res_type = false;//res_type = 0, если тип float, res_type = 1, если тип double
	res_type = (type_A == "d") || (type_B == "d");
	
	if (((type_A != "d") || (type_B != "d")) && ((type_A != "f") || (type_B != "f")))
	{
		cout << "Неверный тип" << endl;
		return 1;
	}
	if(res_type)
	{
		vector< vector<double> > A, B, C;
		read_matrix(input_A, A);
		read_matrix(input_B, B);
		if (A[0].size() != B.size())
		{
			cout << "Некорректные размеры матриц" << endl;
			return 1;
		}
		float time = clock();
		multiply(A, B, C, index_order);
		time = clock() - time;
		plot << " "<< time / CLOCKS_PER_SEC << endl;
		print_matrix(output_C, C);
	}
	else
	{

		vector< vector<float> > A, B, C;
		read_matrix(input_A, A);
		read_matrix(input_B, B);
		if (A[0].size() != B.size())
		{
			cout << "Некорректные размеры матриц" << endl;
			return 1;
		}
		float time = clock();
		multiply(A, B, C, index_order);
		time = clock() - time;
		plot << " " << time / CLOCKS_PER_SEC << endl;
		print_matrix(output_C, C);
	}

	plot.close();
	input_A.close();
	input_B.close();
	output_C.close();

}