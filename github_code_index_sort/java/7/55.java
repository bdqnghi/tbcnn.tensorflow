package arrayTest;

import java.util.Arrays;

public class ShellSortJava {

	public static int[] shellSort(int[] data){
		  int lenD = data.length;
		  int inc = lenD/2;
		  while(inc>0){
		    for(int i=inc;i<lenD;i++){
		      int tmp = data[i];
		      int j = i;
		      while(j>=inc && data[j-inc]>tmp){
		        data[j] = data[j-inc];
		        j = j-inc;
		      }
		      data[j] = tmp;
		    }
		    inc = (inc /2);
		  }
		  return data;
		}

	
	public static void main(String[] args) {
		int []arra = {8,2,13,11,4,9,14,5,10,7,12,6,15,3};
		arra = shellSort(arra);
		System.out.println(Arrays.toString(arra));
	}
}
