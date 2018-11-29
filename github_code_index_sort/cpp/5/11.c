#include "my_project_app.h"
void quickSort(int A[], int l, int h);
void bubble_sort_int_arr(int* int_arr, int lenght){

	//optimized bubble-sort
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


//void selection_sort_int_arr(int* int_arr, int lenght){
//
//	//optimized bubble-sort
//	
//	for (int i = 0, count = 1, ex_count = 1; i < lenght ; i++, count++, ex_count){
//		
//		int max_index = 0;
//		cout << "\ncomparison count: " << count;
//		cout << "\texchange count: " << ex_count << std::endl;
//
//		for (int j = 0; j < (lenght - i - 1); j++){
//			if (int_arr[j] > int_arr[j + 1]){
//				max_index = j;
//				ex_count++;
//			}
//		}
//		int temp = int_arr[lenght - i-1];
//		int_arr[lenght - i-1] = int_arr[max_index];
//		int_arr[max_index] = temp;
//	}
//}


void print_arr(int* arr, int len_arr){
	for (int i = 0; i < len_arr; i++){
		std::cout << arr[i] << " ";
	}
	std::cout<<std::endl;
}

#ifdef SORT_MAIN
/*
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

	//cout << "\nAfter Selection Sort:\n";
	//selection_sort_int_arr(arr, len_arr);
	//print_arr(arr, len_arr);
}
*/

// A utility function to swap two elements
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/* A typical recursive implementation of quick sort */

/* This function takes last element as pivot, places the pivot element at its
���correct position in sorted array, and places all smaller (smaller than pivot)
   ���to left of pivot and all greater elements to right of pivot */
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


/* A[] --> Array to be sorted, l� --> Starting index, h� --> Ending index */
void quickSort(int A[], int l, int h)
{
	if (l < h)
	{
		int p = partition(A, l, h); /* Partitioning index */
		quickSort(A, l, p - 1);
		quickSort(A, p + 1, h);
	}
}

#endif //SORT_MAIN