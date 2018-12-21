import java.util.*;
import java.lang.*;
import java.io.*;

class Solution
{

	public static void bucketSort(double a[], int n) {

		LinkedList<Double> buckets[] = new LinkedList[10];
		Double result[] = new Double[10];

		int count = 0;

		for(int i = 0; i < a.length; i++) {
			if(buckets[(int) (n * a[i])] == null)
				buckets[(int) (n * a[i])] = new LinkedList<Double>();
			buckets[(int) (n * a[i])].addLast(a[i]);
		}

		for(int i = 0; i < 10; i++) {
			if(buckets[i]!= null) {
				Collections.sort(buckets[i]);
			}
		}

		for(int i = 0; i < 10; i++) {
			if(buckets[i] != null) {
				for(Double val : buckets[i]) {
					result[count++] = val;
				}
			}
		}

		for(int i = 0; i < count; i++)
			a[i] = result[i];

	}


	public static void main (String[] args) throws java.lang.Exception
	{
	double arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
	    int n = arr.length;
	    bucketSort(arr, n);
	 
	    for (int i=0; i<n; i++)
	       System.out.print(arr[i] + " ");

	}
}



