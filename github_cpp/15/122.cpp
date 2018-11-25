#include <iostream>
#define MAX 50

using namespace std;

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int matrixA[MAX][MAX];
		int matrixB[MAX][MAX];
		int R1, C1;
		cin >> R1 >> C1;
		for (int i = 0; i < R1; i++)
		{
			for(int j = 0; j < C1; j++)
				cin >> matrixA[i][j];
		}
		int R2, C2;
		cin >> R2 >> C2;
		for (int i = 0; i < R2; ++i)
		{
			for(int j = 0; j < C2; j++)
				cin >> matrixB[i][j];
		}
		for (int i = 0; i < R1; i++)
		{
			for(int j = 0; j < C2; j++)
			{
				int sum = 0;
				for(int k = 0; k < C1; k++)
				{
					sum = sum + matrixA[i][k]*matrixB[k][j];
				}
				if(j == C2-1)
					cout << sum;
				else
					cout << sum << " ";
			}
			cout << endl;
		}
	}
	return 0;
}