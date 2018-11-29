class insertionsort
	{public static void main(String[] args) throws java.lang.Exception
	{int array[] = {12,34,23,3423,2,3};
	System.out.println("array before sorting");
	for(int i=0;i<6;i++)
	System.out.println(array[i]);
	System.out.println("array after sorting");
	insertionSort(array);
	for(int i=0;i<6;i++)
	System.out.println(array[i]);
	
	}
	
	public static void insertionSort(int[] arr) {

      int i, j, newValue;

      for (i = 1; i < arr.length; i++) {

            newValue = arr[i];

            j = i;

            while (j > 0 && arr[j - 1] > newValue) {

                  arr[j] = arr[j - 1];

                  j--;

            }

            arr[j] = newValue;

      }

}
	
}
	