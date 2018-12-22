package SortAlgorthm;

public class shellsort{
	//shell sort it is a kind of insertion sort 
	//to decrease increments continuously untile incremets equals 1;
	//if a[j] bigger than a[j+increments] then change the place of the two elecmets
	public static void sort(int[] arrays){
		if(arrays==null || arrays.length<=1)
			return;
		int increments = arrays.length/2;
		while(increments>=1){
			for(int i=0; i<arrays.length;i++){
				for(int j=i;j<arrays.length-increments;j=j+increments){
					if(arrays[j]>arrays[j+increments]){
						int temp = arrays[j];
						arrays[j] = arrays[j+increments];
						arrays[j+increments]  = temp;
					}
				}
				
			}
			increments = increments/2;
		}
	}
	public static void AtoString(int[] array){
        for(int i:array){
            System.out.print(i+" ");
        }
    }
	 public static void main(String[] args) {
	 	int[] array = {87,45,78,32,17,65,53,9,122};
	 	sort(array);
	 	AtoString(array);
	 }	
	
}