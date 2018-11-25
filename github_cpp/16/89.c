





#include <iostream>
#define MAXSIZE 100

using namespace std;






void ShellSort(int[], int);

int main()
{
	int data[MAXSIZE];
	int input;
	int count = 0;
	cout << "����������Ԫ�أ�";
	while (cin >> input)
		data[count++] = input;
	cin.clear();
	ShellSort(data, count);
	cout << "����ϣ������֮��Ľ��Ϊ��";
	for (int i = 0; i < count; i++)
		cout << data[i] << " ";
	cout << endl;
	system("pause");
	return 0;
}

void ShellSort(int data[], int n)
{
	
	
	
	int i, j, d;
	int tmp;
	for (d = n / 2; d > 0; d /= 2)
		for (i = d; i < n; i++)
		{
			tmp = data[i];
			for (j = i; j > 0 && data[j - d] > tmp; j -= d)
				data[j] = data[j - d];
			data[j] = tmp;
		}
}