package ue4;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

public class Insertionsort {

	public static void main(String[] args) {
		
		ArrayList<Integer> n = new ArrayList<>();
		int max = 100000;
		int min = 1;
		









		long midel = 0;
		long lg = 0;
		
		for (int k = 0; k < 100; k++) {
			for (int i = 0; i < 500; i++) {
				int randomNum = ThreadLocalRandom.current().nextInt(min, max + 1);
				n.add(randomNum);
			}
			int[] conv = convertIntegers(n);
			long timeStart = System.nanoTime();
			insertionSort(conv);
			long timeStop = System.nanoTime();
			midel += (timeStop - timeStart);
			lg += conv.length;
			System.out.println(lg/100 + ";" + midel/100);
			
		}
	}
	
	public static void insertionSort(int[] A)
	{
	    int i, key;
	    for (int j=1; j<A.length; j++){
	        key=A[j];
	        i=j-1;
	        while (i>=0 && A[i]>key){
	            A[i+1]=A[i];
	            i--;
	        }
	        A[i+1]=key;
	    }
	    
	    
	}
	
	public static int[] convertIntegers(List<Integer> integers)
	{
	    int[] ret = new int[integers.size()];
	    Iterator<Integer> iterator = integers.iterator();
	    for (int i = 0; i < ret.length; i++)
	    {
	        ret[i] = iterator.next().intValue();
	    }
	    return ret;
	}

}

