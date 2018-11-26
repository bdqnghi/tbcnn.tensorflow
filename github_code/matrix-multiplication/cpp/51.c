#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> maxCost(int p[], int n, int *saveCost)
{
	vector<vector<int>> cost(n);
	for (int i = 0; i < n; i++)
		cost[i] = vector<int>(n);

	vector<vector<int>> s(n);
	for (int i = 0; i < n; i++)
		s[i] = vector<int>(n);

	for (int i = 0; i < n; i++)
		cost[i][i] = 0;

	int length, i, j, k, curCost;
	for (length = 2; length <= n; length++)
	{
		for (i = 0; i < n - length + 1; i++)
		{
			j = i + length - 1; cost[i][j] = INT_MAX;
			for (k = i; k < j; k++)
			{
				curCost = cost[i][k] + cost[k + 1][j] + p[i]*p[k + 1]*p[j + 1];
				if (curCost < cost[i][j])
				{
					cost[i][j] = curCost;
					s[i][j] = k;
				}
			}
		}
	}

	*saveCost = cost[0][n - 1];
	return s;
}

void printOptimalParen(vector<vector<int>> s, int i, int j, int a[])
{
	if (i == j)
	{
		cout << a[i];
		return;
	}

	cout << "(";
	printOptimalParen(s, i, s[i][j], a);
	cout << "*";
	printOptimalParen(s, s[i][j] + 1, j, a);
	cout << ")";

	return;
}

// I just used integers for testing purposes, so "*" suffices,
// in real application, a matrix-multiplication function will be needed.
// It'll be "return matrixmul(matmul(...), matmul(...));"
int matmul(int a[], vector<vector<int>> s, int i, int j)
{
	if (i == j) return a[i];
	return matmul(a, s, i, s[i][j]) * matmul(a, s, s[i][j] + 1, j);
}

int main(void)
{
	int n;
	cout << "Number of matrices: ";
	cin >> n;
	cin.ignore();

	cout << "Enter matrix values: ";
	int a[n], i = 0; string line;
	getline(cin, line);

	istringstream iss(line);
	while (getline(iss, line, ' '))
		a[i++] = stoi(line);
	iss.str(""); iss.clear(); i = 0;

	cout << "Enter dimensions: ";
	getline(cin, line);

	iss.str(line); int p[n + 1];
	while (getline(iss, line, ' '))
		p[i++] = stoi(line);

	int cost;
	vector<vector<int>> s = maxCost(p, n, &cost);
	cout << "Minimum Cost: " << cost << endl;

	cout << "Parenthesization: ";
	printOptimalParen(s, 0, n - 1, a);
	cout << endl;

	cout << "Result: " << matmul(a, s, 0, n - 1) << endl;
	return 0;
}		
