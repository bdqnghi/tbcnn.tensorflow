//Implements selection sort algorithm

//Olu Gbadebo
//Oct 3, 2016

public class Selectionsort {
	
	public static int[] sort(int[] list){
		if (list == null || list.length < 2)
			return null;

		int indexOfMin; //holds the index of the minimum element in the array
		for (int i = 0; i < list.length - 1; i++){
			indexOfMin = i;
			//to find index of the minimum element in the whole list
			for (int j = i + 1; j < list.length; j++){
				if (list[j] < list[indexOfMin])
					indexOfMin = j;
			}
			//swap minimum with corresponding "i" index element
			if (i != indexOfMin && list[i] != list[indexOfMin]){
				int temp = list[i];
				list[i] = list[indexOfMin];
				list[indexOfMin] = temp;
			}
		}
		
		return list;
	}
}