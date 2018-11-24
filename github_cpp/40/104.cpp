/*
p_index: index of the last element
first: index of the first element
POST: (smaller than array[p_index]), array[p_index], (larger than array[p_index])
*/
int partition(int array[], int p_index, int first){
	int pivot = array[p_index];
	int wall = first;
	for(int i = first; i < p_index; i++){
		if(array[i] < pivot){
			swap(&array[i], &array[wall]);
			wall++;
		}
	}
	swap(&array[p_index], &array[wall]);
	return wall;
}

// sort array in increasing order
void quickSort(int array[], int first, int last){
	if(first >= last) return;
	else{
		int wall = partition(array, last, first);
		quickSort(array, first, wall - 1);
		quickSort(array, wall + 1, last);
	}
}
