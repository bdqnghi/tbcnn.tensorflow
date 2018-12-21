

 
public class InsertionSort {


  
  public static void main (String[] args) {
    int[] array = {10,23,49,2,49,29,85,14,9,48,60,30};
    System.out.println("Original Array = " + toString(array));
    insertionSort(array);
    System.out.println("Sorted Array   = " + toString(array));
  }

  
  static void insertionSort(int[] arr) {
    if (arr == null || arr.length <= 0) {
      return;
    }
    for (int i = 0; i < arr.length; i++) {
      insertValue(arr, i);
    }
  }

  
  static void insertValue(int[] arr, int index) {
    if (index <= 0) {
      return;
    }
    int insertIndex = index;
    int value = arr[index];
    for (int i = index-1; i >= 0; i--) {
      if (value < arr[i]) {
        slide(arr, i);
        insertIndex = i;
      } else {
        break;
      }
    }
    arr[insertIndex] = value;
  }

  
  static void slide(int[] arr, int index) {
    if (index+1 >= arr.length) {
      return; 
    }
    arr[index+1] = arr[index];
  }

  
  static String toString(int[] arr) {
    StringBuilder b = new StringBuilder("[");
    if (arr != null && arr.length > 0) {
      for (int i=0; i < arr.length; i++) {
        if (i != 0) {
          b.append(',');
        }
        b.append(arr[i]);
      }
    }
    b.append("]");
    return b.toString();
  }

}