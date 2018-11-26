public class Selectionsort {

  public static void main(String[]args) {

    int[] numbers = { 10,9,8,7,6,5,4,3,2,1 };
    int size = numbers.length;

    int[] sorted = selectionSort(numbers,size);

    for(int i=0; i < sorted.length; i++) {
      System.out.print(sorted[i]);
    }



  }

  public static int[] selectionSort(int[] unsorted, int n) {

    // given an unsorted list
    // starting with the first index find the max (next best element) swap the index of it and the last element of the sorted array
    for(int i=0; i < unsorted.length; i++) {
      int max = unsorted[i]; 
      for(int j=i+1; j < unsorted.length; j++) {
        System.out.println("max: " + max);
        System.out.println("compared: " + unsorted[j]);
        if( max > unsorted[j] ) {
          unsorted = swap(unsorted,i,j);
        }
      }
    }

    return unsorted;

  }

  public static int[] swap(int[] list, int indexA, int indexB) {

    int temp = list[indexB];
    list[indexB] = list[indexA];
    list[indexA] = temp;

    return list;

  }

}
