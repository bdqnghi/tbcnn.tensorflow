
inline void swap(int &a, int &b) { int t = a; a = b; b = t; }
inline int parent(int i) { return (i - 1) >> 1; }
inline int leftchild(int i) { return (i << 1) + 1; }
inline int rightchild(int i) { return (i << 1) + 2; }

int heap_size, heap_length;	

void max_heapify(int *a, int i)	
{
	int l = leftchild(i), r = rightchild(i);
	int largest = 0;
	if (l < heap_size && a[l] > a[i])
		largest = l;
	else
		largest = i;
	if (r < heap_size && a[r] > a[largest])
		largest = r;
	if (largest != i)
	{
		swap(a[i], a[largest]);
		max_heapify(a, largest);
	}
}

void build_max_heap(int *a) {             
	heap_size = heap_length;
	for (int i = heap_length / 2 - 1; i >= 0; --i)   
		max_heapify(a, i);              
}

void heapsort(int *a, int n) {           
	heap_length = n;
	build_max_heap(a);
	for (int i = heap_length - 1; i >= 1; --i) {
		swap(a[0], a[i]);
		--heap_size;	
		max_heapify(a, 0);	
	}
}