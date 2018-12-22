public class RadixSort {

	//Key-indexed counting(a[].key is an int in [0, R))
	//O(N) time
	public static void keyIndexCounting(String[] a) {
		int N = a.length;
		String[] aux = new String[N];
		int[] count = new [R + 1];

		//Count the each key's frenquency
		for(int i = 0; i < N; i++) {
			count[a[i].key() + 1]++;
		}

		//Transform frequency to indices
		for(int r = 0; r < R; r++) {
			count[r + 1] += count[r];
		}

		//Distribute data into aux
		for(int i = 0; i < N; i++) {
			aux[count[a[i].key()]++] = a[i];
		}

		//Copy back
		for(int i = 0; i < N; i++) {
			a[i] = aux[i];
		}
	}

	
	//LSD sort for same length strings, sort a[] on leading W characters
	//LSDstringsortuses~7WN􏰄3WRarrayaccessesand extra space proportional to N􏰄R to sort N items whose keys are W-character strings taken from an R-character alphabet.
	public static void sortLSD(String[] a, int W) {
		int N = a.length;
		int R = 256;
		String[] aux = new String[N];

		for(int d = W - 1; d >= 0; d--) {
			int[] count = new int[R + 1];
			for(int i = 0; i < N; i++) 
				count[a[i].charAt(d) + 1]++;

			for(int r = 0; r < R; r++)
				count[r + 1] += count[r];

			for(int i = 0; i < N; i++)
				aux[count[a[i].charAt(d)]++] = a[i];

			for(int i = 0; i < N; i++)
				a[i] = aux[i];
		}
	}

	//LSD for number for positive numbers
	public static void sort(int[] a) {
		int N = a.length;
		int R = 256;
		int[] aux = new int[N];
		for(int d = 0; d < 4; d++) {
			int mask = 255 << (8 * d);
			int[] count = new int[R + 1];
			for(int i = 0; i < N; i++) 
				count[(a[i] & mask) + 1]++;
			for(int r = 0; r < R; r++)
				count[r + 1] += count[r];
			for(int i = 0; i < N; i++) 
				aux[count[a[i] & mask]++] = a[i];
			for(int i = 0; i < N; i++)
				a[i] = aux[i];
		}
	}
}