public class shellsort {
	public void shellSort(int[] array) {
		for(int gap = array.length / 2; gap > 0; gap /= 2) {
			for(int i = 0; i < gap; i++) {
			    for(int j = i; j < array.length; j += gap) {
				    int min = j;
				    for(int k = j + gap; k < array.length; k += gap) {
					    if(array[k] < array[min]) {
						    min = k;
						}
					}
					swap(array, j, min);
				}
			}
		}
	}

	public void swap(int[] array, int a, int b) {
		int temp = array[a];
		array[a] = array[b];
		array[b] = temp;
	}
	public static void main(String[] args) {
		int[] array = {1,2,2,2,3, 10, 3, 40, 20, 50, 80, 70,12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56};
		shellsort ss = new shellsort();
		ss.shellSort(array);
		for(int i : array)
			System.out.println(i);
	}
}