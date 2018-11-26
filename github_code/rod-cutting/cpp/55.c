/*
Rod Cutting
https://practice.geeksforgeeks.org/problems/rod-cutting/0/?ref=self

Given a rod of length n inches and an array of prices that contains prices of all pieces of size smaller than n. 
Determine the maximum value obtainable by cutting up the rod and selling the pieces.

Input:
First line consists of T test cases. First line of every test case consists of N, 
denoting the size of array. 
Second line of every test case consists of price of ith length piece.

Output:
Single line output consists of maximum price obtained.

Constraints:
1<=T<=100
1<=N<=100
1<=Ai<=100

Example:
Input:
1
8
1 5 8 9 10 17 17 20
Output:
22



*/


/*


84
87 78 16 94 36 87 93 50 22 63 28 91 60 64 27 41 27 73 37 12 69 68 30 83 31 63 24 68 36 30 3 23 59 70 68 94 57 12 43 30 74 22 20 85 38 99 25 16 71 14 27 92 81 57 74 63 71 97 82 6 26 85 28 37 6 47 30 14 58 25 96 83 46 15 68 35 65 44 51 88 9 77 79 89

*/

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