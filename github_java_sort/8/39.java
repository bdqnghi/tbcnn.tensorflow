import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;

public class Quick {
	private static void shuffleArray(int[] a) {
		int index;
		Random random = new Random();
		for(int i = a.length - 1; i >= 0; i--) {
			index = random.nextInt(i + 1);
			exch(a, index, i);
		}
	}

	public static void sort(int[] a) {
		
		shuffleArray(a);
		sort(a, 0, a.length - 1);
	}

	private static void sort(int[] a, int lo, int hi) {
		
		if(hi <= lo)	return;
		int j = partition(a, lo, hi);
		sort(a, lo, j - 1);
		sort(a, j + 1, hi);
	}

	private static int partition(int[] a, int lo, int hi) {
		int i = lo, j = hi + 1;
		while(true){
			
			while(a[lo] > a[++i]) {
				if(i == hi)	break;
			}
			
			while(a[lo] < a[--j]) {
				if(j == lo)	break;
			}
			
			if(j <= i) break;
			
			exch(a, i, j);
		}
		
		exch(a, lo, j);
		return j;
	}

	private static void exch(int[] a, int i, int j) {
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}

	public static boolean isSorted(int[] a) {
		for(int i = 0; i < a.length - 1; i++){
			if(a[i] > a[i + 1])	return false;
		}
		return true;
	}

	public static void main(String[] args) throws FileNotFoundException {
		Scanner s = new Scanner(new File("./dataset.txt"));
		int[] a = new int[s.nextInt()];
		for(int i = 0; i < a.length; i++){
			a[i] = s.nextInt();
		}
		System.out.println("Size of the array is: " + a.length);
		if(!Quick.isSorted(a))	Quick.sort(a);
		if(Quick.isSorted(a))	System.out.println("Array is sorted");
		else	System.out.println("Array is not sorted");
		
	}
}
