package sorting;

public class Heap {

	Integer[] A;
	Integer heapSize;

	void maxHeapify(Integer A[], Integer i) {
		int l = left(i);
		int r = right(i);
		int largest;

		if (l <= heapSize && A[l - 1] > A[i - 1]) {
			largest = l;
		} else {
			largest = i;
		}

		if (r <= heapSize && A[r - 1] > A[largest - 1]) {
			largest = r;
		}

		if (largest != i) {
			int temp = A[i - 1];
			A[i - 1] = A[largest - 1];
			A[largest - 1] = temp;
			maxHeapify(A, largest);
		}
	}

	void maxHeapifyIterative(Integer A[], Integer i) {

		while (true) {
			int l = left(i);
			int r = right(i);
			int largest;

			if (l <= heapSize && A[l - 1] > A[i - 1]) {
				largest = l;
			} else {
				largest = i;
			}

			if (r <= heapSize && A[r - 1] > A[largest - 1]) {
				largest = r;
			}

			if (largest != i) {
				int temp = A[i - 1];
				A[i - 1] = A[largest - 1];
				A[largest - 1] = temp;

				i = largest;

			} else {
				return;
			}
		}

	}

	void minHeapify(Integer A[], Integer i) {
		int l = left(i);
		int r = right(i);
		int smallest;

		if (l <= heapSize && A[l - 1] < A[i - 1]) {
			smallest = l;
		} else {
			smallest = i;
		}

		if (r <= heapSize && A[r - 1] < A[smallest - 1]) {
			smallest = r;
		}

		System.out.println("smallest is " + A[smallest - 1]);

		if (smallest != i) {
			int temp = A[i - 1];
			A[i - 1] = A[smallest - 1];
			A[smallest - 1] = temp;
			minHeapify(A, smallest);
		}
	}

	void buildMaxHeap(Integer[] A) {
		this.heapSize = A.length;

		for (int i = (int) Math.floor(A.length / 2); i >= 1; i--) {
			maxHeapify(A, i);
		}
	}

	void heapSort(Integer[] A) {

		buildMaxHeap(A);

		for (int i = A.length; i >= 2; i--) {
			int temp = A[0];
			A[0] = A[i - 1];
			A[i - 1] = temp;
			this.heapSize--;
			maxHeapify(A, 1);
		}
	}

	public static void main(String[] args) throws Exception {
		
		Integer[] data = { 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };

		Heap heapSort = new Heap();

		heapSort.A = data;
		heapSort.heapSize = 10;
		heapSort.maxHeapifyIterative(heapSort.A, 2);

		for (int i = 0; i < heapSort.heapSize; i++) {
			System.out.print(heapSort.A[i] + " ");
		}

		data = new Integer[10];
		data[0] = 12;
		data[1] = 2;
		data[2] = 3;
		data[3] = 4;
		data[4] = 5;
		data[5] = 6;
		data[6] = 7;
		data[7] = 8;
		data[8] = 9;
		data[9] = 10;

		heapSort.A = data;
		heapSort.minHeapify(heapSort.A, 1);
		System.out.println();
		for (int i = 0; i < heapSort.heapSize; i++) {
			System.out.print(heapSort.A[i] + " ");
		}

		data = new Integer[10];
		data[0] = 4;
		data[1] = 1;
		data[2] = 3;
		data[3] = 2;
		data[4] = 16;
		data[5] = 9;
		data[6] = 10;
		data[7] = 14;
		data[8] = 8;
		data[9] = 7;

		heapSort.A = data;
		heapSort.buildMaxHeap(heapSort.A);
		System.out.println();
		for (int i = 0; i < heapSort.heapSize; i++) {
			System.out.print(heapSort.A[i] + " ");
		}

		data = new Integer[11];
		data[0] = 4;
		data[1] = 1;
		data[2] = 3;
		data[3] = 2;
		data[4] = 16;
		data[5] = 9;
		data[6] = 10;
		data[7] = 14;
		data[8] = 8;
		data[9] = 7;
		data[10] = 7;
		heapSort.heapSize = 11;
		heapSort.A = data;
		heapSort.heapSort(heapSort.A);
		System.out.println();
		for (int i = 0; i < heapSort.A.length; i++) {
			System.out.print(heapSort.A[i] + " ");
		}

		// -----------priority queue

		data = new Integer[10];
		data[0] = 16;
		data[1] = 14;
		data[2] = 10;
		data[3] = 8;
		data[4] = 7;
		data[5] = 9;
		data[6] = 3;
		data[7] = 2;
		data[8] = 4;
		data[9] = 1;

		heapSort.A = data;
		heapSort.heapSize = 10;

		System.out.println("\nPriority key");
		//System.out.println(heapSort.extractMax(heapSort.A));
		heapSort.increaseKey(heapSort.A, 9, 15);
		heapSort.insert(heapSort.A, 17);
		for (int i = 0; i < heapSort.heapSize; i++) {
			System.out.print(heapSort.A[i] + " ");
		}

	}

	// get the parent of node i
	Integer parent(Integer i) {
		return (int) Math.floor(i / 2);
	}

	// get the left child of node i
	Integer left(Integer i) {
		return 2 * i;
	}

	// get the right child of node i
	Integer right(Integer i) {
		return 2 * i + 1;
	}

	//priority queue - extract the max key from maxheap
	Integer extractMax(Integer[] A) throws Exception {
		if (heapSize < 1) {
			throw new Exception("Heap underflow!");
		}
		int max = A[0];
		A[0] = A[heapSize - 1];
		heapSize--;
		maxHeapify(A, 1);
		return max;
	}
	
	//priority queue  - increase the value of a key
	void increaseKey(Integer A[], int i, int key) throws Exception {
		if (key < A[i - 1]) {
			throw new Exception("New key is smaller than current key");
		}

		A[i - 1] = key;
		while (i > 1 && A[i - 1] > A[parent(i) - 1]) {
			int temp = A[i - 1];
			A[i - 1] = A[parent(i) - 1];
			A[parent(i) - 1] = temp;
			i = parent(i);
		}
	}
	
	//insert a key to priority queue
	void insert(Integer[] A, int key) throws Exception{
		heapSize ++;
		Integer[] temp = new Integer[heapSize];
		System.arraycopy(A, 0, temp, 0, heapSize-1);
		this.A = temp;
		this.A[heapSize - 1] = Integer.MIN_VALUE;
		increaseKey(this.A, heapSize, key);
	}
}
