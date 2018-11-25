
#include <iostream>
#include <new>
#include <string>
using namespace std;



void solution(int s[], int r[], int n)
{
	while(n>=1)
	{
		cout << s[n] << " ";
		n=n-s[n];
	}
	cout << endl;
}


void rodcut(int p[], int n)
{
	int* r=new int[n+1];
	int* s=new int[n+1];
	r[0]=0;
	for (int i = 1; i <=n; ++i)
	{
		int q=0;
		for (int j = 1; j <= i; ++j)
		{
			int x=p[j-1]+r[i-j];
			if(x>q)
			{
				q=x;
				s[i]=j;
			}
			r[i]=q;
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		cout << r[i] << " ";
	}
	cout << endl;
	cout << r[n]<< endl;
	solution(s,r,n);
}

int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	int p[n];
	for (int i = 0; i < n; ++i)
	{
		cin >> p[i];
	}
	rodcut(p,n);
	return 0;
}