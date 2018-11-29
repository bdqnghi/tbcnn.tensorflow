
/**
 * Shell sort implementation based on pseudocode from Wikipedia.
 *
 * @author  Nathan Fiedler
 */
public class Shellsort {

  static Counter counter = null;
  public Shellsort(Counter c) {
      this.counter = c;
    }

    /**
     * Sort the input array using the shell sort algorithm with the gap
     * sequence suggested by Gonnet and Baeza-Yates.
     *
     * @param  <T>    type of comparable to be sorted.
     * @param  input  array of comparable objects to be sorted.
     */
    public static <T extends Comparable<? super T>> void sort(T[] input) {
        if (input == null || input.length < 2) {
            return;
        }

        int inc = input.length / 2;
        while (inc > 0) {
            for (int ii = inc; ii < input.length; ii++) {
              count();
                T temp = input[ii];
                int jj = ii;
                while (jj >= inc && input[jj - inc].compareTo(temp) > 0) {
                    input[jj] = input[jj - inc];
                    jj -= inc;
                }
                input[jj] = temp;
            }
            // Another way of dividing by 2.2 to get an integer.
            inc = inc == 2 ? 1 : inc * 5 / 11;
        }
    }
    /**
     * Count.
     */
    private static void count() {
      if (counter != null) {
        counter.counterUp(1);
      }
    }
}