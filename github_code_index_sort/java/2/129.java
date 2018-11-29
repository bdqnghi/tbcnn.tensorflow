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
		solution.mergeSort(a, 0, a.length - 1);
		for(int i = 0 ;i < a.length; i++)
			System.out.print(a[i] + " ");
	}
	
	public void mergeSort(int a[], int l, int r){
		if(l < r){
			int mid = (l + r)/2;
			mergeSort(a, l, mid);
			mergeSort(a, mid + 1, r);
			merge(a,l,mid,r);	
		}
	}
	
	public void merge(int a[], int l, int mid, int r){
		int n1 = mid - l + 1;
		int n2 = r - mid;
		//System.out.println(n1 + " " + n2);
		int L[] = new int[n1];
		int R[] = new int[n2];
		
		for(int i = 0; i< n1; i++)
			L[i] = a[l + i];
		for(int j = 0; j < n2; j++)
			R[j] = a[mid + 1 +j];
		/*for(int i = 0 ;i < n1; i++)
			System.out.print(L[i] + " ");
		System.out.println();
		for(int i = 0 ;i < n2; i++)
			System.out.print(R[i] + " ");
		System.out.println();*/
			
		int i = 0;
		int j = 0;
		int k = l;
		
		while(i<n1 && j<n2){
			if(L[i] <= R[j]){
				a[k] = L[i];
				i++;
			}
			else{
				a[k] = R[j];
				j++;
			}
			k++;
		}
		while(i<n1){
			a[k] = L[i];
			i++;
			k++;
		}
		while(j<n2){
			a[k] = R[j];
			j++;
			k++;
		}
		/*for(int x= 0 ;x < a.length; x++)
			System.out.print(a[x] + " ");
		System.out.println();*/
	}
}

/***

Running time : O(n log(n))
Memory: depends, Space complexity of merge sort is O(n)

***/