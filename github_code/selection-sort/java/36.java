package arrayTest;

import java.util.Arrays;

public class SelectionSortJava {

	public static void main(String[] args) {
		int []arra = {8,2,1,13,11,4,9,14,5,10,7,12,6,15,3};
		arra = selectionSort(arra);
		System.out.println(Arrays.toString(arra));
	}
	
	public static int[] selectionSort(int[] data){
		int lenD = data.length;
		int j = 0;
		int tmp = 0;
		for(int i=0;i<lenD;i++){
			j = i;
			for(int k = i+1;k<lenD;k++){
				if(data[j]>data[k]){
					j = k;
				}
			}
			tmp = data[i];
			data[i] = data[j];
			data[j] = tmp;
		}
		return data;
	}
}

