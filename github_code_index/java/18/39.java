import java.util.Arrays;
import java.util.List;

public class SelectionSort {
	
	public static List<Integer> selectionSort(List<Integer> lst){
		//go from last index to first
		for(int passes= lst.size()-1; passes != -1; --passes){
			int posOfMax = 0;			//default max is 0
			for(int i=1; i != passes+1; ++i){	//go from ]0, passes]
				if(lst.get(i) > lst.get(posOfMax)){
					posOfMax = i;		//find index of biggest
				}				//and place it at index
			}					//passes
			swap(lst, passes, posOfMax);
		}
		
		return lst;
	}//end selectionSort
	
	public static void swap(List<Integer> lst, int i, int j){
		int temp = lst.get(i);
		lst.set(i, lst.get(j));
		lst.set(j, temp);
	}//end swap
	
	public static void main(String[] args) {
		List<Integer> list = Arrays.asList(23,57,75,33,6,8,56);
		System.out.println( selectionSort(list).toString() );
	}

}
