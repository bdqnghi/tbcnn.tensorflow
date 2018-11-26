package de.soft.sortieralgorithmen;

/**
 * @author michaelhahn
 *
 */
public class Insertionsort {
	
	private long sortTime;
	private int[] data;

	/**
	 * 
	 */
	public Insertionsort(int[] array) {
		if(array != null) {
			long start = System.currentTimeMillis();
			
			data = array;
			insertionsort();
			
			sortTime = System.currentTimeMillis() - start;
			
		} else {
			//Default Werte
			sortTime = 0;
			data = new int[] {0};
		}
	}
	
	private void insertionsort() {
		int temp, j;

		 for (int i=1; i < data.length; i++){
		   temp = data[i];
		   j = i-1;

		   while (j >= 0 && data[j] > temp){
		     data[j + 1] = data[j];
		     j--;
		   }

		   data[j+1] = temp;
		 }
	}
	
	public int[] getData() {
		assert(data != null);
		return data;
	}
	
	public long getSortTime() {
		assert(sortTime <= 0);
		return sortTime;
	}
}
