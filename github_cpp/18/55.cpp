




#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int RodCutting(int*a, int N)
{
	vector<int> rc(N + 1, INT_MIN);
	rc[0] = 0;

	for (int l = 1; l <= N; ++l)
	{
		for (int i = 1; i <= N; ++i)
		{
			if (l >= i && rc[l - i] != INT_MIN)
			{
				if (rc[l - i] + a[i]>rc[l])
				{
					rc[l] = rc[l - i] + a[i];
				}
			}
		}
	}

	cout << rc[N] << endl;

	return 0;

}

int main()
{
	int t = 0;
	int N = 0;

	int a[101] = { 0 };

	cin >> t;

	while (t--)
	{
		cin >> N;
		int i = 1;
		a[0] = 0;
		while (i <= N)
		{
			cin >> a[i++];
		}
		RodCutting(a, N);
	}

}