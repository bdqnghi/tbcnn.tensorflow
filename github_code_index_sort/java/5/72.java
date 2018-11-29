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
		solution.bubbleSort(a);
		for(int i = 0 ;i < a.length; i++)
		System.out.print(a[i] + " ");
	}
	
	public void bubbleSort(int a[]){
		for(int i = 0; i < a.length - 1; i++){
			for(int j =  0; j< a.length - i -1; j++){
				if(a[j] > a[j + 1]){
					int temp = a[j];
					a[j] = a[j+1];
					a[j+1] = temp;
				}
			}
		}
		
	}
}

/***

Running time is O(n^2) independent of input data. O(1) space complexity.

***/