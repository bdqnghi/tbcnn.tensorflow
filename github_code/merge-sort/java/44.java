/**
 * 
 * @author ashijune
 * 
 * 	Merge-Sort(A,p,r)
 * 1.	If p<r
 * 2.		q=(p+r)/2;
 * 3.		Merge-Sort(A, p, q);
 * 4.		Merge-Sort(A, q+1, r);
 * 5.		Merger (A,p,q,r);
 *
 *	A[p,r] is divided into 2 subarrays A[p,q] and A[q+1,r]
 *
 *	Merge (A,p,q,r)
 *1.	n1=q-p+1;
 *2.	n2=r-q;
 *3.	//Let L[1..n1+1] and R[1..n2+1] be two arrays. n1+1 means n1 elements and 1 for sentinal value
 *4.	for i=1 to n1 
 *5.		L[i] = A[p+i-1]
 *6.	for j=1 to n2
 *7.		R[j] = A[q+j]
 *8.	L[n1+1]=oo;
 *9.	R[n2+1]=oo;
 *10.	i=1;
 *11.	j=1;
 *12	for k=p to r
 *13.		if L[i]<= R[j]
 *14.			A[k]=L[i]
 *15.			i=i+1
 *16.			else
 *17.				A[k]=R[j]
 *18.				j=j+1
 */

public class MergeSort {
	int[] arrayToSort={34,54,87,98,99,13,38,45,51,90}; 
	MergeSort () {
		System.out.println("Before Sorting");
		for (int i=0; i<arrayToSort.length;i++) {
			System.out.print(arrayToSort[i]+" ");
		}
		mergeSort(arrayToSort, 0, arrayToSort.length-1);
		System.out.println(" ");
		System.out.println("After Sorting");
		for (int i=0; i<arrayToSort.length;i++) {
			System.out.print(arrayToSort[i]+" ");
		}
	}
	void merge (int[] arr, int p, int q, int r) {
		int n1=q-p;	//A[p,q]
		int n2=r-q-1;		//A[q+1,r]
		int[] L=new int[n1+1];
		int[] R=new int[n2+1];
		for (int i=0;i<n1+1;i++) {
			L[i]=arr[p+i];
		}
		for (int j=0;j<n2+1;j++) {
			R[j]=arr[q+j+1];
		}
		int i=0;
		int j=0;
		System.out.println("");
		try {
		for (int k=p;k<=r;k++)	{
			
			if (i<n1+1 && j<n2+1 && L[i]<=R[j] ) {
				arr[k]=L[i];
				System.out.println("arr["+k+"] in if is "+arr[k]);
				if (i<n1)
				i++;
				System.out.println("i is "+i);
			} 
		  else if (i>=n1+1) {
			 arr[k]=R[j];
			 j++;
			 } 
		  else if (j>=n2+1) {
				 arr[k]=L[i];
				 i++;
			 } 
		  else {
					arr[k]=R[j];
					System.out.println("arr["+k+"] in else is "+arr[k]);
					j++;
					System.out.println("j is "+j);
				} 
		}} catch (Exception e) {
			e.printStackTrace();
		}
	}
	void mergeSort(int[] arr, int p, int r) {
		if (p<r) {
			int q=(p+r)/2;
	//	mergeSort(arr,p,q);
	//		mergeSort(arr,q+1,arr.length);
			merge(arr,p,q,r);
		}
	}
	public static void main (String [] args) {
		new MergeSort();
	}
}
