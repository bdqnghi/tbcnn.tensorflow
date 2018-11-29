import java.util.*;
import java.util.stream.*;

class Main {

	public static void quickSort(int A[]) {
		quickSort(A, 0, A.length - 1);
	}

	public static void quickSort(int A[], int l, int r) {
		if(l < r) {
			int pivot = partition(A, l, r);

			quickSort(A, l, pivot - 1);
			quickSort(A, pivot + 1, r);
		}
	}

	public static int partition(int A[], int l, int r) {
		int pivot = A[r], i = l;

		for(int j = l; j < r; j++) {
			if(A[j] <= pivot) {
				int t = A[j];
				A[j] = A[i];
				A[i] = t;
				i++;
			}
		}

		A[r] = A[i];
		A[i] = pivot;

		return i;
	}



	public static void main(String args[]) {
		int A[] = {1, 7, 5, 18, 13, 9};
		quickSort(A);
		System.out.println(Arrays.stream(A).boxed().collect(Collectors.toList()));
	}
}

// Quick Sort - https://www.geeksforgeeks.org/quick-sort/

// Iterative Quick Sort - https://www.geeksforgeeks.org/iterative-quick-sort/

// Quick Sort using random pivot - https://www.geeksforgeeks.org/quicksort-using-random-pivoting/

// Quick Sort on Singly Linked List - https://www.geeksforgeeks.org/quicksort-on-singly-linked-list/

// Quick Sort on Doubly Linked List - https://www.geeksforgeeks.org/quicksort-for-linked-list/

// Run time analysis - https://www.khanacademy.org/computing/computer-science/algorithms/quick-sort/a/analysis-of-quicksort

