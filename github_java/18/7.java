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
		solution.selectionSort(a);
		for(int i = 0 ;i < a.length; i++)
		System.out.print(a[i] + " ");
	}
	
	public void selectionSort(int a[]){ //simple but inefficient 
		int min, temp;
		for(int i = 0; i< a.length - 1; i++){
			min = i;	
			for(int j = i+1; j<a.length; j++){
				if(a[j] < a[min]){
					min = j;
				}	
			}
			temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
	}
}

/***

Running time is O(n^2)
O(1) space complexity.

***/