package Sorting;

public class Selectionsort {

	public static void main(String[] args) {
		int[] data = new int[]{4,5,7,3,6,1,2,9,8};
		data = sort(data,0);
		for(int n : data){
			System.out.println(n);
		}
	}
	
	private static int[] sort(int[] data, int start){
		if(start < data.length-1){
			swap(data, start, findMinIndex(data, start));
			sort(data,start+1);
		}
		return data;
	}
	
	private static int findMinIndex(int[] data, int start){
		int minpos=start;
		for(int i=start+1; i<data.length; i++){
			if(data[i]<data[minpos]){
				minpos=i;
			}
		}
		return minpos;
	}
	
	private static void swap(int[] data, int idx1, int idx2){
		int temp1 = data[idx1];
		int temp2 = data[idx2];
		data[idx1] = temp2;
		data[idx2] = temp1;
		//return data;
	}

}
