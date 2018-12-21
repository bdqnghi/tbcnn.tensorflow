public class RadixSort {

	
	
	public static void keyIndexCounting(String[] a) {
		int N = a.length;
		String[] aux = new String[N];
		int[] count = new [R + 1];

		
		for(int i = 0; i < N; i++) {
			count[a[i].key() + 1]++;
		}

		
		for(int r = 0; r < R; r++) {
			count[r + 1] += count[r];
		}

		
		for(int i = 0; i < N; i++) {
			aux[count[a[i].key()]++] = a[i];
		}

		
		for(int i = 0; i < N; i++) {
			a[i] = aux[i];
		}
	}

	
	
	
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