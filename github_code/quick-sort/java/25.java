// quick sort-algorithm

public class SortUtils {

  public static void quickSort(int[] array) {
    quickSort(array, 0, array.length - 1);
  }

  public static void quickSort(int[] array, int start, int end) {
    if (start >= end) {
      return;
    }
    // partition this array to two parts.
    int partProv = partition(array, start, end);
    quickSort(array, start, partProv - 1);
    quickSort(array, partProv + 1, end);
  }

  private static int partition(int[] array, int start, int end) {
    int resultIndex = start - 1;
    int compareKey = array[end];
    for (int i = start; i < end - 1; i++) {
      if (array[i] <= compareKey) {
        resultIndex++;
        exchange(array, resultIndex, i);
      }
    }
    exchange(array, resultIndex + 1, end);
    return resultIndex + 1;
  }

  private static void exchange(int[] array, int left, int right) {
    int temp = array[left];
    array[left] = array[right];
    array[right] = temp;
  }

  public static void main(String[] args) {
    int[] array1 = new int[] {2, 1, 3, 4, -1};
    int[] array2 = new int[] {2};
    int[] array3 = new int[] {8, 8, 8};
    quickSort(array1);
    quickSort(array2);
    quickSort(array3);
    for (int item : array1) {
      System.out.print(item + " ");
    }
    System.out.println();
    for (int item : array2) {
      System.out.print(item + " ");
    }
    System.out.println();
    for (int item : array3) {
      System.out.print(item + " ");
    }
  }
}
