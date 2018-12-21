package sortalgorithms.mergesort;

import sortalgorithms.SortAlgorithm;

public class Mergesort extends SortAlgorithm{

	private int[] numbers;
	private int[] helper;
	
	private int number;
	
	public int[] run(int[] values){
		this.numbers = values;
		number = numbers.length;
		this.helper = new int[number];
		mergesort(0, number - 1);
		
		
		
		return numbers;
	}
	
	
	
	private void mergesort(int low, int high) {
		
		if(low < high){
			
			int middle = low + (high - low) / 2;
			
			mergesort(low, middle);
			
			mergesort(middle+1, high);
			
			mergesort(low, middle, high);
		}
	}
	
	private void mergesort(int low, int middle, int high){
		
		for(int i = low; i <= high; i++) {
			helper[i] = numbers[i];
		}
		
		int i = low;
		int j = middle + 1;
		int k = low;
		
		
	    
		while(i <= middle && j <= high) {
			if(helper[i] <= helper[j]) {
				numbers[k]=helper[i];
				i++;
			} else {
				numbers[k] = helper[j];
				j++;
			}
			k++;
		}
		
		while(i <= middle) {
			numbers[k] = helper[i];
			k++;
			i++;
		}
	}
	
}
