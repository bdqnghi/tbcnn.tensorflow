public class QuickSort{
  private void printArray(int[] array){
    for(int i = 0 ; i < array.length; i++){
      System.out.print(array[i]+"  ");
    }
    System.out.println();
  }

  private void swapArrayElements(int[] array, int indexa, int indexb){
    int tmp = array[indexa];
    array[indexa] = array[indexb];
    array[indexb] = tmp;
  }

  private int partition(int[] array, int low, int high){
    int pivot = array[high];
    int result;
    int left = low;
    int right = high-1;

    while(left<right){
      while(left<right && array[left] < pivot){ left++; }
      while(left<right && array[right] >= pivot){ right--; }
      if(left!=right){ swapArrayElements(array,left,right); }
    }

    if(array[left] >= pivot) {
      swapArrayElements(array,left,high);
      result = left;
    } else {
      result = high;
    }

    return result;
  }

  public void quickSort(int[] arrayToSort,int low,int high){
    if(low>=high){return;}

    int pivotPosition = partition(arrayToSort,low,high);
    quickSort(arrayToSort, low, pivotPosition-1);
    quickSort(arrayToSort, pivotPosition+1, high);
  }

  public static void main(String[] args){
    QuickSort quickSort = new QuickSort();

    int[] array = new int[]{54,26,93,17,77,31,44,55,20,57};
    System.out.println("Array before sorting");
    quickSort.printArray(array);
    quickSort.quickSort(array,0,array.length-1);
    System.out.println("Array after sorting");
    quickSort.printArray(array);
    System.out.println("----------------------\n\n\n");

    array = new int[]{5,0,1,8,7};
    System.out.println("Array before sorting");
    quickSort.printArray(array);
    quickSort.quickSort(array,0,array.length-1);
    System.out.println("Array after sorting");
    quickSort.printArray(array);
    System.out.println("----------------------\n\n\n");

    array = new int[]{4,5,3,7,2};
    System.out.println("Array before sorting");
    quickSort.printArray(array);
    quickSort.quickSort(array,0,array.length-1);
    System.out.println("Array after sorting");
    quickSort.printArray(array);
    System.out.println("----------------------\n\n\n");

    array = new int[]{5,8,1,3,7,9,2};
    System.out.println("Array before sorting");
    quickSort.printArray(array);
    quickSort.quickSort(array,0,array.length-1);
    System.out.println("Array after sorting");
    quickSort.printArray(array);
    System.out.println("----------------------\n\n\n");

    array = new int[]{3,2,4,5,1,6,8,7};
    System.out.println("Array before sorting");
    quickSort.printArray(array);
    quickSort.quickSort(array,0,array.length-1);
    System.out.println("Array after sorting");
    quickSort.printArray(array);
    System.out.println("----------------------\n\n\n");
  }

}
