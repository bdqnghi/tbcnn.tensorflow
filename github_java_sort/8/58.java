import java.util.*;
import java.lang.*;
import java.io.*;

class Solution
{
	public static void main (String[] args) throws java.lang.Exception
	{
		Scanner sc = new Scanner(System.in);
		int size = sc.nextInt();
		int a[] = new int[size];
		for(int i = 0; i < size; i++)
			a[i] = sc.nextInt();
		Solution solution = new Solution();
		solution.quickSort(a, 0, a.length - 1);
		for(int i = 0 ;i < a.length; i++)
			System.out.print(a[i] + " ");
	}

	public void quickSort(int a[], int low, int high) {
		 if(low < high) {
		 	int p = partition(a, low, high);
		 	quickSort(a, low, p - 1);
		 	quickSort(a, p + 1, high);
		 }
	}
	public void swap(int a[], int i, int j) {
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}

	public int partition(int a[], int low, int high) {
		int pivot = a[high];
		int i = low - 1;
		for(int j = low; j <= high - 1; j++) {
			if(a[j] <= pivot) {
				i++;
				swap(a, i, j);
			}
		}
		swap(a, i + 1, high);
		return (i + 1);
	}
	
	
}

