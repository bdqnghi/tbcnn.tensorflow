/**
* Selection Sort
*/
class selectionsort{
	public static void main(String args[]){
		int A[] = new int[100];
		
		// create a random list of unsorted order
		for(int i = 0;i < A.length -1;i++){
			A[i] = 0 + (int)(Math.random()*100 + 0);
		}

		// print initial array
		for(int i = 0;i < A.length -1;i++){
			System.out.println(Integer.toString(A[i]));
		}

		// selection sort algo
		for(int i = 0;i < A.length -1;i++){
			int minElement = A[i];
			int elemIndex = i;
			for(int j = i; j < A.length-1;j++){
				if(A[j] < minElement){
					minElement = A[j];
					elemIndex = j;
				}
			}

			// swap values
			if(elemIndex != i){
				// if comes here,it means swap has been performed
				int temp = A[elemIndex];
				A[elemIndex] = A[i];
				A[i] = temp;
			}
		}
		// selection sort algo ends

		// print final array
		for(int i = 0;i < A.length -1;i++){
			System.out.println(Integer.toString(A[i]));
		}
	}
}