


#include <stdio.h>
#include<conio.h>

void PrintArray(int arr[], int size, int index);
void StringReverse(char *str);
int RecursiveMinimum(int arr[], int size);
int main()
{
	int arr[50], n, i, choice = 0;
	int endKey = 0, min = 0;
	char s[10], str[30];
	printf("\n***********************Menu driven program **************************");
	do
	{
		printf("\n1. Print array recursively");
		printf("\n2. Print reverse string recursively");
		printf("\n3. Find minimum number recursively");
		printf("\nEnter your choice: ");
		scanf_s("%d", &choice);
		gets_s(s);
		switch(choice)
		{
		case 1:
			printf("\nEnter size of array: ");
			scanf_s("%d", &n);
			printf("\nEnter %d elements: ", n);
			for (i = 0; i < n; i++)
			{
				scanf_s("%d", &arr[i]);
			}

			printf("\nEntering into printArray function.\n\nArray elements are:\n");
			PrintArray(arr, n, 0);
			printf("\nExiting from printArray function");
			break;
		case 2:
			printf("\nEnter string: ");
			gets_s(str);
			printf("\nEntering into stringReverse function\n\t");
			StringReverse(str);
			printf("\nExiting from stringReverse function");
			break;
		case 3:
			printf("\nEnter size of array: ");
			scanf_s("%d", &n);
			printf("\nEnter %d elements: ", n);
			for (i = 0; i < n; i++)
			{
				scanf_s("%d", &arr[i]);
			}
			min = RecursiveMinimum(arr, n -1);
			printf("\n\nRecursive Minimum: %d", min);
			break;
		default:
			printf("\nWrong input.");
			break;
		}
		printf("\n\nDo you want to continue (0 to exit) : ");
		scanf_s("%d", &endKey);
	} while (endKey != 0);
    return 0;
}

void PrintArray(int arr[], int size, int index)
{
	printf("\tElement %d: %d", index, arr[index]);
		if (index == size - 1)
			return;
	PrintArray(arr, size, index + 1);
}


void StringReverse(char *str)
{
	if(*str)
	{
		StringReverse(str + 1);
		printf("%c ", *str);
	}
}

int RecursiveMinimum(int arr[], int size)
{
	static int i = 0, min = 1000;
	if(i < size)
	{
		if (arr[i] < min)
			min = arr[i];
		i++;
		RecursiveMinimum(arr, size);
	}
	return min;
}