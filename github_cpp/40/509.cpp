void Swap(int anArray[], int x1, int x2)
{
	int tempValue = anArray[x1];
	anArray[x1] = anArray[x2];
	anArray[x2] = tempValue;
}

void QuickSort(int anArray[], int startIndex, int endIndex)
{
	if (endIndex - startIndex < 1)
		return;

	int pivot = endIndex;
	int i = startIndex - 1;

	for (int j = startIndex; j <= endIndex; ++j)
	{
		if (anArray[j] <= anArray[pivot])
		{
			++i;
			Swap(anArray, i, j);
		}
	}

	QuickSort(anArray, startIndex, i - 1);
	QuickSort(anArray, i + 1, endIndex);
}

int main()
{
	int myArray[] = { 10,7,2,1,0,8,9,11,20,5,32,89,44 };
	QuickSort(myArray,0, 12);
	
	return 0;
}