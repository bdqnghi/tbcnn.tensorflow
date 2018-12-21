package sort;

public class ShellSort {					
	public static void shellSort(int t[]) {
		
		int n = t.length;
		int h = 1;
		while (h <= n / 3) {     
			h = 3 * h + 1;
		}
		while (h > 0) {
			for (int i = h; i < n; i++) {        			
				for (int j = i; j>= h ; j-=h) { 			
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
