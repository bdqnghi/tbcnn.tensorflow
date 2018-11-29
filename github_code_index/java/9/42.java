import java.util.Arrays;

public class HeapSort<T extends Comparable<? super T>> extends RunTime implements SortInterface<T> {

	// private Vector<T> heap = new Vector<T>();
	private T[] heap;
	private int heapSize = 0;

	private long startTime;
	private long endTime;
	protected long runTime;
	
	RunTime hsRun = new RunTime() {
		{
			setTimeUnits(TimeUnits.MicroSeconds);
			setMemoryUnits(MemoryUnits.KiloBytes);
		}
	};

	public static void main(String[] args) {
//		HeapSort<Integer> sort = new HeapSort();
//		// // //
//		Integer[] array = { 5, 10, 6, 9, 3, 1 };
//		System.out.println(Arrays.toString(array));
//		// // //
//		// //
//		// // for (int i = 0; i < array.length; i++) {
//		// // sort.heap.add(array[i]);
//		// // }
//		// //
//		// // sort.setHeap(sort.heap);
//		// //
//		// //// sort.showHeap();
//		// //
//		sort.sort(array);
//		// //
//		// // System.out.println(sort.heapSize);
//		System.out.println(Arrays.toString(array));
	}

	@Override
	public void sort(T[] arrayToSort) {

		// start time for loop execution
		this.startTime = System.nanoTime();
		
		this.heap = arrayToSort;
		this.heapSize = this.heap.length;

		setHeap(arrayToSort);
		
		this.heapify();

		this.heapSort();

		// endtime for loop execution
		this.endTime = System.nanoTime();
		// grab end run time for loop execution
		this.runTime = endTime - startTime;
//		System.out.println(runTime);
		// add runtime to runtime method in RunTime class
		hsRun.addRuntime(runTime);

	}

	public T[] getHeap() {
		return this.heap;
	}

	public void setHeap(T[] heap) {
		this.heap = heap;
		this.heapSize = this.heap.length;
		this.heapify();
	}

	public void showHeap() {
		System.out.print("Heap = {");
		for (int i = 0; i < this.heapSize; i++) {
			if (i != this.heapSize - 1) {
				System.out.print(this.heap[i] + ", ");
			} else {
				System.out.print(this.heap[i]);
			}
		}
		System.out.println("}\n\n");
	}

	public void heapSort() {

		while (this.heapSize >= 1) {
			int last = this.heapSize - 1;
			T temp = this.heap[0];
			this.heap[0] = this.heap[last];
			this.heap[last] = temp;
			this.heapSize--;
			this.heapify();
			this.heapSort();
			// this.showHeap();
		}
		//
		// this.heapSize = this.heap.length;
		// this.heapify();

	}

	/*********************************************/
	/* private methods */
	/*********************************************/

	private void heapify() {
		int last = this.heapSize - 1;
		int parent = (last - 1) / 2;

		while (parent >= 0) {
			siftDown(parent);
			parent--;
		}
	}

	private void siftDown(int node) {
		while (node < this.heapSize) {
			int leftChild = (2 * node) + 1;
			int rightChild = (2 * node) + 2;

			T root = this.heap[node];
			int max = node;

			if (leftChild < this.heapSize) {
				T left = this.heap[leftChild];
				if (root.compareTo(left) < 0) {
					max = leftChild;
				}
			}

			if (rightChild < this.heapSize) {
				T right = this.heap[rightChild];
				if (this.elementAtMax(max).compareTo(right) < 0) {
					max = rightChild;
				}
			}

			if (max == node) {
				return;
			} else {
				T temp = this.heap[node];
				this.heap[node] = this.heap[max];
				this.heap[max] = temp;
				node = max;
			}
		}
	}

	private T elementAtMax(int max) {
		return this.heap[max];
	}

}
