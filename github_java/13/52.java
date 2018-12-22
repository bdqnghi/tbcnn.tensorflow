package sort;

public class ShellSort {					// tri non stable
	public static void shellSort(int t[]) {
		// sequence h = 3 * h + 1
		int n = t.length;
		int h = 1;
		while (h <= n / 3) {     //erreur 1: n/3 et non n
			h = 3 * h + 1;
		}
		while (h > 0) {
			for (int i = h; i < n; i++) {        			// i = h et non i = 0
				for (int j = i; j>= h ; j-=h) { 			// j = i et non j = h
					if (t[j] < t[j-h]) {
						int temp = t[j];
						t[j] = t[j-h];
						t[j-h] = temp;
					}
				}
			}			
			h = h / 3;
		}
	}
	
	// complexité dans le pire des cas en O(n^3/2)
	// pas de preuve mathématique donnant la meilleure séquence
	// complexité moyenne non démontrée non plus
	
	public static void main(String[] args) {
		int tableau[] = { 5, 8, 4, 3, 7, 1, 9, 6, 2, 0 };
		shellSort(tableau);
		display(tableau);
	}
	
	public static void display (int t[]) {
		for (int i = 0; i < t.length; i++) {
			System.out.println(t[i]);
		}
	}
}
