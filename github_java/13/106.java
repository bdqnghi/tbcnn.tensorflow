/*package elementarySorts;
import java.util.Arrays;
import java.util.Random;

import edu.princeton.cs.algs4.*;

public class Shell extends SortTemplate {
	
	private static int[] incrementSequence;
	private static int SIZE;
	
	private static void createIncrementSequence() {
		int hSize = (int) (Math.log(1+ 2*SIZE/3)/Math.log(3)) + 1;
		incrementSequence = new int[hSize];
		for(int i = 0, k = 1; i < hSize && incrementSequence[i] <= SIZE/3; i++, k++)
			incrementSequence[i] = (int)(Math.pow(3, k)-1)/2;
	}
	
	public static void sort(Comparable[] a) {
		int n = a.length;

        // 3x+1 increment sequence:  1, 4, 13, 40, 121, 364, 1093, ... 
        int h = 1;
        while (h < n/3) h = 3*h + 1; 

        while (h >= 1) {
            // h-sort the array
            for (int i = h; i < n; i++) {
                for (int j = i; j >= h && less(a[j], a[j-h]); j -= h) {
                    exch(a, j, j-h);
                }
            }
        	//For each h-array
        	for(int i = 0; i < n-h; i++) {
        		for(int j = i; j < SIZE && less(a[j+h], a[j]); j += h) {
        			exch(a, j, j+h);
        		}
        		
        	}
            //assert isHsorted(a, h); 
            h /= 3;
        }
        assert isSorted(a);
		}
	
	public static void main(String[] args) {
		int n = 40; Random rand = new Random(47);
		Integer[] arr = new Integer[n];
		for(int i = 0; i < n; i++) arr[i] = rand.nextInt(100);
		System.out.println(Arrays.toString(arr));
		Shell.sort(arr); System.out.println(Arrays.toString(arr));
	}


}
*/
package elementarySorts;
import java.lang.Math;

public class Shell extends Sort {
//Don't initialize this class
	
	public static void sort(Comparable[] a) {
		
		final int N  = a.length; int h = 1;
		while(h < N/3) h = 3*h + 1;
		/*final int kMax = (int) (Math.log(2*N/3 + 1)/Math.log(3));*/
		
		while(h >= 1) {
		//Looping through h < N/3 to h = 1
			/*h = h + (int)Math.pow(3, k-1);*/
			
			for(int i = h; i < N; i++) {
			//Looping through the h independent sub sequences for each h
				
				//h-sort the subsequence
				for(int j = i; j >= h && less(a[j], a[j-h]); j -= h) exch(a, j, j-h);
				
			}
			h /= 3;
		}
		
		
	}
	
	
}






























