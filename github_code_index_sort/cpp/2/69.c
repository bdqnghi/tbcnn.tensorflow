//Divide and Conquer Merge Sort


/*
first: index of the first element from left half of the array
last: index of the last element from right half of the array
mid: (first + last) / 2

Note: it isn't in place; extra space temp is used to store sorted array
*/
void merge(int array[], int first, int mid, int last){
	int temp[last - first + 1];
	int left = first; int right = mid + 1;
	int index = 0;

	while(left <= mid || right <= last){
		if(left > mid){
			for(int i = 0; i < (last - mid); i++, index++)
				temp[index] = array[right + i];
			break;
		}
		if(right > last){
			for(int i = 0; i < (mid + 1 - first); i++, index++)
				temp[index] = array[left + i];
			break;
		}
		else{
			if(array[left] <= array[right]){
				temp[index] = array[left];
				left++;
			}
			else{
				temp[index] = array[right];
				right++;
			}

			index++;
		}		
	}

	for(int i = 0; i < (last - first + 1); i++){
		array[first + i] = temp[i];
	}				
}

void mergeSort(int array[], int first, int last){
	if(first == last)
		return;
	else{
		int mid = (first + last)/2;
		mergeSort(array, first, mid);
		mergeSort(array, mid+1, last);
		merge(array, first, mid, last);
	}
}
