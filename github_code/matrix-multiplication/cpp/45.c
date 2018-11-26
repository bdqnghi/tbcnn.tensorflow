#include<iostream>
#include<vector>
#include<climits>

using namespace std;

void Print(vector< vector<int> > s,int i, int j)
{
	if(i == j)
	{
		cout << "A" <<i;
		return;
	}
	else 
	{
		cout << "(";
		Print(s,i,s[i][j]);
		Print(s,s[i][j]+1,j);
		cout  <<")";
	}
}

int main(void)
{
	int n,i,j,k,l;
	cout << "Enter the number of matrices" << endl;
	cin >> n;
	vector<int>p(n+1);
	cout << "Enter the dimensions of matrices" << endl;
	for(i=0;i<=n;i++)
		cin >> p[i];
	vector< vector<int> > m(n+1,vector<int>(n+1,0));
	vector< vector<int> > s(n+1,vector<int>(n+1,0));
	int q =0;
	for(l=2;l<=n;l++)
	{
		for(i=1;i<=n-l+1;i++)
		{
			j = i+l-1;
			m[i][j] = INT_MAX;
			for(k =i;k<=j-1;k++)
			{
				q = m[i][k] + m[k+1][j] + p[i-1]*p[j]*p[k];
				if(q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	Print(s,1,n);
	cout << endl;
}

