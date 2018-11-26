#include <iostream>
#include <vector>

const int Size = 1025;

using Row = std::vector<int>;
using Matrix = std::vector<Row>;

static __inline__ unsigned long long rdtsc( void )
{
	unsigned hi, lo;
	__asm__ __volatile__ ( "rdtsc" : "=a" ( lo ), "=d" ( hi ) );
	return ( ( unsigned long long ) lo ) | ( ( ( unsigned long long ) hi ) << 32 );
}

Matrix MultiplyMatricesByColumn( Matrix& lhs, Matrix& rhs )
{
	Matrix result( Size, Row( Size ) );

	for( int i = 0; i < Size; ++i ) {
		for( int j = 0; j < Size; ++j ) {
			for( int k = 0; k < Size; ++k ) {
				result[i][j] += lhs[i][k] * rhs[k][j];
			}
		}
	}

	return result;
}

Matrix MultiplyMatricesByRow( Matrix& lhs, Matrix& rhs )
{
	Matrix result( Size, Row( Size ) );

	for( int i = 0; i < Size; ++i ) {
		for( int j = 0; j < Size; ++j ) {
			for( int k = 0; k < Size; ++k ) {
				result[i][k] += lhs[i][j] * rhs[j][k];
			}
		}
	}

	return result;
}

int main()
{
	Matrix lhs( Size, Row( Size ) );
	Matrix rhs( Size, Row( Size ) );

	unsigned long long rdtscStart = rdtsc();
	MultiplyMatricesByColumn( lhs, rhs );
	std::cout << rdtsc() - rdtscStart << std::endl;

	rdtscStart = rdtsc();
	MultiplyMatricesByRow( lhs, rhs );
	std::cout << rdtsc() - rdtscStart << std::endl;

	return 0;
}
