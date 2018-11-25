#include <iostream>

using namespace std;

int main()
{
	double arr[] = {2.5, .7, 2, 1.2, 5, 1, .2};
	int iLength = 7;

	
	cout << "Initial Array: ";
	for (int iIndex = 0; iIndex < iLength; ++iIndex)
	{
		cout << arr[iIndex] << " ";
	}
	cout << endl;

	

	for (int iEnd = iLength - 1; iEnd > 0; --iEnd)
	{
		cout << "iEnd is: " << iEnd << endl;
		for (int iIndex = 0; iIndex < iEnd; ++iIndex)
		{
			
			
		if (arr[iIndex] > arr[iIndex + 1])
		{
			double dTemp = arr[iIndex];
			arr[iIndex] = arr[iIndex + 1];
			arr[iIndex + 1] = dTemp;
		}	
		}
	}

	
	cout << "Sorted Array: ";
	for (int iIndex =0; iIndex < iLength; ++iIndex)
	{
		cout << arr[iIndex] << " ";
	}
	cout << endl;

	system("pause");

	return 0;
}