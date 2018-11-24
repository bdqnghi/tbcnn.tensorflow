#include <iostream>
#include <string>

namespace  betacore
{

void printArray(char **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
		for (int j = 0; j < cols; j++)
		{
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << "" << std::endl;
    }
}
int max(int a, int b){
	return (a>b)? a : b ;
}

void printArray(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
		for (int j = 0; j < cols; j++)
		{
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << "" << std::endl;
    }
}
	int longest_palindrome( char * input, int length )
	{
		int n = length;// input.length();
		int i = 0, k, j;

		bool **m = new bool*[n];

		
		int mx = -1;
		/*
		* Case : |input| = 1
		*/
		for ( i = 0 ; i < n-1; ++i )
		{
			m[i] = new bool[n];
			m[i][i]=true;
		}
		/*
		* Case : |input| = 2
		*/
		int s = 0;
		for( i =0; i < n-1; ++i )
		{
			if(input[i] == input[i+1])
			{
				m[i][i+1] = true;
				s = i;
				mx = 2;
			}
		}
		
		for( k = 3 ; k <= n; ++k)
		{
			for ( i =0; i < n-k+1; ++i){
				j = i + k - 1;

				if ( m[i+1][j-1] && input[i] == input[j])
				{
					m[i][j] = true;
					if( k > mx)
					{
						s  = i;
						mx = k;
					}
				}
			}
		}
		//clean  up
		delete[] m;
		// input.substr(s, s + mx - 1 )
		std::string str;
		for( i = s; i <= s + mx - 1; ++i)
		{
			str += input[i];
		}
		std::cout << "Longest palindrome substring is: "<< mx << "\t" << str << std::endl;
		return mx;
	}

	int longest_palindrome_mod( char * input, int length )
	{
        int n = length;// input.length();
		int i = 0, k, j;

		int **m = new int*[n];
		for ( i = 0 ; i < n; ++i )
		{
			m[i] = new int[n];
			m[i][i]=true;
		}
		
	
		if(length<1){
				return -1;
		}
	
		if(length ==1){
			return 1;
		}
			
		if(length ==2)
		{	
			if(input[0]==input[1]){
				return 2;
			}
			return 1;
		}
	
	
		
		for( k = 3 ; k <= n; ++k)
		{
			for ( i =0; i < n-k+1; ++i){
				//j = i + k - 1;

				if (input[i] == input[i+k-1])
				{
					m[i][k] = 2+ m[i+1][k-2];
				}else{
					m[i][k] = max(m[i][k-1], m[i+1][k-1]);
				}
			}
		}
		//clean  up
		printArray(m,n,n);
		// input.substr(s, s + mx - 1 )
		std::string str;
		int mx = m[1][n-1];
		std::cout << "Longest palindrome mod substring is: "<< mx<< "\t" << str << std::endl;
		
		delete[] m;
		return mx;
	}

}
int main( int argc, char * argv[] )
{
	char  str[14] = {'A','C','G','T','G','T','C','A','A','A','A','T','C','G'};
	int length = 14;
	betacore::longest_palindrome(str, length);
	betacore::longest_palindrome_mod(str, length);
	return 0;
}