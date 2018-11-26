
public class MergeSort {
	
	public static void printArray(int[] a){
		for(int i =0; i < a.length; i++){
			System.out.print(a[i] + " ");
		}
		System.out.println();
	}
	
	public static void fillArray(int[] a){
		//Fill an array sort later
		for(int i = 0; i <a.length; i++){
			a[i] = a.length - i;
		}
	}
	
	public static void merge(int[] a, int startIndex, int midIndex, int endIndex){
		/* MERGE(A,p,q,r)
		 * 	n1 = q - p +1
		 * 	n2 = r - q
		 * let L[1..n1 + 1] and R[1..n2 + 1] be new arrays
		 * for i = 1 to n1
		 * 		L[i] = A[p + i -1]
		 * for j = 1 to n2
		 * 		R[j] = A[q + j]
		 * L[n1 + 1] = INFINITY
		 * R[n2 + 1] = INFINITY
		 * i = 1
		 * j = 1
		 * for k = p to r
		 * 		if L[i] <= R[j]
		 * 			A[k] = L[i]
		 * 			i = i + 1
		 * 		else A[k] = R[j]
		 * 			j = j + 1
		 */		
		int leftArraySize = midIndex - startIndex + 1;
		int rightArraySize = endIndex - midIndex;
		
		//let L[1..n1 + 1] and R[1..n2 + 1] be new arrays
		int[] L = new int[leftArraySize + 1];
		int[] R = new int[rightArraySize + 1];
		int i, j = 1;
		//Copy the left sub array into L
		for (i = 0; i < leftArraySize; i++){
			L[i] = a[startIndex + i];
		}		
		//Copy the right sub array into R
		for (j = 0; j < rightArraySize; j++){
			R[j] = a[midIndex + j +1];
		}		
		
		//Establish sentinel values
		L[leftArraySize] = Integer.MAX_VALUE;
		
		R[rightArraySize] = Integer.MAX_VALUE;
		
		//reset i,j to the start of the array
		i = 0;
		j = 0;
		for (int k = startIndex; k <= endIndex; k++){
			if (L[i] <= R[j]){
				a[k] = L[i];
				i = i + 1;
			}//end if
			else{ 
				a[k] = R[j];
				j = j + 1;
			}//end else
		}//end for		
	}

	public static void mergeSort(int[] a, int p, int r){
		/*
		 * MERGE-SORT(A, p, r)
		 * if p < r
		 * 		q = floor(p +r)/2)
		 * 		MERGE-SORT(A, p, q)
		 * 		MERGE-SORT(A, q + 1, r)
		 * 		MERGE(A, p, q, r)
		 */
		int q = 0;
		if (p < r){
			q = (p + r)/2;
			mergeSort(a, p, q);
			mergeSort(a, q + 1, r);
			merge(a, p, q, r);
		}
	}
	
	public static void main(String[] args) {
		System.out.println("This is merge sort.");
		
		int ArraySize = 5;
		int[] ArrayToSort = new int[ArraySize];
		
		fillArray(ArrayToSort);
		printArray(ArrayToSort);
		
		mergeSort(ArrayToSort, 0, ArrayToSort.length - 1);
		printArray(ArrayToSort);
		
	}//end main
}