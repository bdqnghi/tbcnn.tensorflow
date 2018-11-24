int heap_size = 0;

/*
lchild, rchild: index of the left and right child
return the index of the smaller child
*/
int min(int array[], int lchild, int rchild){
	if(array[lchild] < array[rchild]) return lchild;
	else return rchild;
}


/*
compare current element with its children
return the index of the smaller child
if not exist, return negtive
*/
int compare(int array[], int index, int lchild, int rchild){
	if(rchild >= 0){
		if(array[index] > array[lchild] && array[rchild]) return min(array, lchild, rchild);
		if(array[index] > array[rchild]) return rchild;
	}
	if(array[index] > array[lchild]) return lchild;
	else return -1;
}

// swap down elements to maintain min heap feature
void sinkDown(int array[], int index, int offset){
	if(index > ((heap_size - offset)/2 - 1)) return;
	else{
		int lchild = 2*index + 1;
		int rchild = (2*index + 2 > (heap_size - offset) - 1)? -1 : 2*index + 2;   // when size is even -> out of boundary
		int child_index = compare(array, index, lchild, rchild);
		if(child_index >= 0){
			swap(&array[index], &array[child_index]);
			sinkDown(array, child_index, offset);
		}
		else return;
	}
}

// build heap starting from the second last level
void buildHeap(int array[], int offset){
	for(int i = ((heap_size - offset)/2 - 1); i >= 0; i--){
		sinkDown(array, i, offset);
	}
}

// sort array in increasing order
void heapSort(int array[], int first, int last){
	heap_size = last + 1;
	for(int i = 0; i < heap_size - 1; i++)
		buildHeap(array + i, i);
}

