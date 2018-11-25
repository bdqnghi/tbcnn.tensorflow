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