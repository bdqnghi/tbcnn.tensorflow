#include "my_project_app.h"
void quickSort(int A[], int l, int h);
void bubble_sort_int_arr(int* int_arr, int lenght){

	
	bool flag = true;
	for (int i = 0, count = 1, ex_count = 1; (i < lenght) && flag; i++, count++){
		flag = false;
		cout << "\ncomparison count: " << count;
		cout << "\texchange count: " << ex_count << std::endl;
		for (int j = 0; j < (lenght - i - 1); j++){
			if (int_arr[j] > int_arr[j + 1]){
				int temp = int_arr[j];
				int_arr[j] = int_arr[j + 1];
				int_arr[j + 1] = temp;
				flag = true;
				ex_count++;
			}
		}
	}
}

























void print_arr(int* arr, int len_arr){
	for (int i = 0; i < len_arr; i++){
		std::cout << arr[i] << " ";
	}
	std::cout<<std::endl;
}

#ifdef SORT_MAIN

int main (){
	int arr[] = { 2, 1, 7, 5, 11, 100, 6, 200, -3};
	int len_arr = sizeof (arr) / sizeof (arr[0]);
	bubble_sort_int_arr(arr, len_arr);
	cout << "\nAfter Bubble Sort:\n";
	print_arr(arr, len_arr);
	
	
	
	int reset_arr[] = { 2, 1, 7, 5, 11, 100, 6, 200, -3 };
	int len_reset_arr = sizeof(reset_arr) / sizeof (reset_arr[0]);
	cout << "Quick Sort:\n";
	cout << "\n\nBefore:\n";
	print_arr(reset_arr, len_reset_arr);
	cout << "\nAfter:\n";
	quickSort(reset_arr, 0, 8);
	print_arr(reset_arr, len_reset_arr);

	
	
	
}



void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}




int partition(int arr[], int l, int h)
{
	int x = arr[h];
	int i = (l - 1);

	for (int j = l; j <= h - 1; j++)
	{
		if (arr[j] <= x)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[h]);
	return (i + 1);
}



void quickSort(int A[], int l, int h)
{
	if (l < h)
	{
		int p = partition(A, l, h); 
		quickSort(A, l, p - 1);
		quickSort(A, p + 1, h);
	}
}

#endif 