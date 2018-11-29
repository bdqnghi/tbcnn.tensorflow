#include<iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int num[100];
	for (int i = 0; i < n; i++)
	{
		cin >> num[i];
	}
	int key;
	if (n == 1)
	{
		cout << "insertion-sort: " <<num[0];
	}
	else
	{
		for (int j = 1; j < n; j++)
		{
			key = num[j];
			int i = j - 1;
			while (i >= 0 && num[i]>key)
			{
				num[i + 1] = num[i];
				i = i - 1;
			}
			num[i + 1] = key;
		}
		cout << "insertion-sort: " << endl;
		for (int i = 0; i < n; i++)
		{
			cout << num[i] << " ";
		}
		cout << endl;
	}
	return 0;
}