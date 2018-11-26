import java.util.*;
import java.lang.*;
import java.io.*;

class Solution
{
	public static int findMaxElement(int a[]) {
		int max = Integer.MIN_VALUE;
		for(int i = 0; i < a.length; i++) {
			if(a[i] >= max) {
				max = a[i];
			} 
		}
		return max;
	}

	public static void countSort(int a[], int exp) {
		int output[] = new int[a.length];
		int count[] = new int[10];
		for(int i = 0; i < a.length; i++) {
			count[(a[i]/exp) % 10]++;
		}
		
		for(int i = 1; i < count.length; i++) {
			count[i] += count[i - 1];
		}
		
		for(int i = a.length - 1; i >= 0; i--) {
			output[count[ (a[i]/exp)%10 ] - 1] = a[i];
            count[ (a[i]/exp)%10 ]--;
		}
		for (int i = 0; i < a.length; i++)
            a[i] = output[i];
	}
	
	public static void radixSort(int a[]) {
		int m = findMaxElement(a);

		// Do counting sort for every digit. Note that instead
        // of passing digit number, exp is passed. exp is 10^i
        // where i is current digit number
        for (int exp = 1; m/exp > 0; exp *= 10)
            countSort(a, exp);
	}
	
	public static void main (String[] args) throws java.lang.Exception
	{
		int a[] = {170, 45, 75, 90, 802, 24, 2, 66};
		
		radixSort(a);
		for(int i = 0; i < a.length; i++) {
			System.out.print(a[i] + " ");
		}
	}
}


/***

Radix sort is algorithm for integers (and some other data type) that takes the advantage of the fact that integers have a finite number of bits.
Running time is O(kn), where n = number of elements and k = number of passes of the sorting algorithm.


What if the elements are in range from 1 to n2? 
We can’t use counting sort because counting sort will take O(n2) which is worse than comparison based sorting algorithms. Can we sort such an array in linear time?
Radix Sort is the answer. The idea of Radix Sort is to do digit by digit sort starting from least significant digit to most significant digit. Radix sort uses counting sort as a subroutine to sort.

***/