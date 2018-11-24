#include <iostream>
#include <algorithm>
#define INF 987654321;
using namespace std;

int N, M, a, b;
int arr[101][101];

int main()
{
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			arr[i][j] = INF;
		}
		arr[i][i] = 0;
	}

	for (int i = 1; i <= M; i++)
	{
		cin >> a >> b;
		arr[a][b] = 1;
	}

	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				arr[i][j] = min(arr[i][j], arr[i][k] + arr[k][j]);
			}
		}
	}

	return 0;
}