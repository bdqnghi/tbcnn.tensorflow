package practicalseven.sort;

/**
 * An implementation of the (new BubbleSort()).sorting algorithm.
 *
 * @author Gregory M. Kapfhammer
 */

public class BubbleSort extends Sorter {

  /** Define the index at which an array starts. */
  private static int ARRAY_START = 0;

  /** Define the name of this sorting algorithm. */
  public BubbleSort() {
    name = "BubbleSort";
  }

  /** Bubble-sort of an array of chars into a nondecreasing order. This
   * implementation of the sort method makes a complete copy of the input array,
   * thus ensuring that it does not modify the input parameter.
   *
   * <p>Please refer to this site:
   * https://docs.oracle.com/javase/7/docs/api/java/lang/System.html
   * for more details about the System.arraycopy() method.
   *
   * @param source the source array that will be copied and sorted
   * @return the copied and sorted array in a nondecreasing order
   */
  public char[] sort(char[] source) {
    int length = source.length;
    char[] sorted = new char[source.length];
    // TODO: Add the full implementation of the BubbleSort
    return sorted;
  }

  /** Bubble-sort of an array of ints into a nondecreasing order. This
   * implementation of the sort method makes a complete copy of the input array,
   * thus ensuring that it does not modify the input parameter.
   *
   * <p>Please refer to this site:
   * https://docs.oracle.com/javase/7/docs/api/java/lang/System.html
   * for more details about the System.arraycopy() method.
   *
   * @param source the source array that will be copied and sorted
   * @return the copied and sorted array in a nondecreasing order
   */
  public int[] sort(int[] source) {
    int length = source.length;
    int[] sorted = new int[source.length];
    // TODO: Add the full implementation of the BubbleSort
    return sorted;
  }

  /** Demonstrate the use of the BubbleSort algorithm. */
  public static void main(String[] args) {
    char[] letters = {'C', 'E', 'B', 'D', 'A', 'I', 'J', 'L', 'K', 'H', 'G', 'F'};
    System.out.println("Before: " + java.util.Arrays.toString(letters));
    char[] sortedLetters = (new BubbleSort()).sort(letters);
    System.out.println("After : " + java.util.Arrays.toString(sortedLetters));
    int[] numbers = {1, 2, 4, 4, 9, 10, -10, 3, 8, 7, 20, 0};
    System.out.println("Before: " + java.util.Arrays.toString(numbers));
    int[] sortedNumbers = (new BubbleSort()).sort(numbers);
    System.out.println("After : " + java.util.Arrays.toString(sortedNumbers));
  }
}
