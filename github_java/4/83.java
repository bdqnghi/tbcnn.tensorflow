/*****Introduction to Algorithms java code for Insertion Sort *******/

class javaInsertionSort{
	
public static void insertionSort(int A[] ){

	int n = A.length;
	for(int i=1; i < n; i++)
	{
		int key = A[i];
		int j = i - 1;
/* the item could be in the 0th spot so it could be >= 0 or >-1**/
		while ((j > -1) && (A[j] > key) )
		{
			A[j+1] = A[j];
			j = j-1;
		}	
		A[j+1] = key;
	}
 }

 static void printArray(int A[])
 {
	int n = A.length;
	for(int i=0; i < n; i++)
		System.out.print(A[i] + " ");

	System.out.println(); 
 }

 public static void main(String args[])
 {
 	int A[] = {24, 13, 2, 45, 22, 0};
 	javaInsertionSort ob = new javaInsertionSort();
 	ob.insertionSort(A);
 	printArray(A);
 }
}

