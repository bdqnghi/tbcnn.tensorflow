import java.util.Arrays;
/**
 * Class for heapsort.
 */
public class Heapsort {
    /**
         * no. of vacancies.
         */
    private Integer vac;
    /**
     * no of open vacancies.
     */
    private Integer open;
    /**
     * no of bc vacancies.
     */
    private Integer bc;
    /**
     * no of sc vacancies.
     */
    private Integer sc;
    /**
     * no. of st vacancies.
     */
    private Integer st;
    /**
     * Constructs the object.
     */
    /**
     * array.
     */
    private Studentdetails[] array;
    /**
     * size.
     */
    private int size;
    /**
     * Constructs the object.
     */
    public Heapsort() {

    }
    /**
     * constuctor.
     *
     * @param      v   vancancies
     * @param      o   open vacancies
     * @param      bc  bc vacancies
     * @param      sc  sc vacancies
     * @param      st  st vacancies
     */
    public Heapsort(final Integer v, final Integer o, final Integer bc, final Integer sc, final Integer st, final Studentdetails[] a, final int n) {
        this.vac = v;
        this.open = o;
        this.bc = bc;
        this.sc = sc;
        this.st = st;
        this.array = a;
        this.size = n;
    }
    /**
     * sorts.
     * Best case: O(N)
     *  worst case: O(N)
     *  Average case: O(N)
     * @return     { description_of_the_return_value }
     */
    public Studentdetails[] sort() {
        for (int i = (size / 2) - 1; i >= 0; i--) {
            heapify(size, i);
        }
        for (int i = size - 1; i >= 0; i--) {
            swap(0, i);
            heapify(i, 0);
        }
        return array;
    }
    /**
     * swaps.
     *  Best case: O(1)
     *  worst case: O(1)
     *  Average case: O(1)
     * @param      i     { parameter_description }
     * @param      j     { parameter_description }
     */
    public void swap(final int i, final int j) {
        Studentdetails temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    /**
     * heapifies.
     *  Best case: O(logN)
     *  worst case: O(logN)
     *  Average case: O(logN)
     * @param      n     { parameter_description }
     * @param      i     { parameter_description }
     */
    public void heapify(final int n, final int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && array[l].compareTo(array[largest]) < 0) {
            largest = l;
        }
        if (r < n && array[r].compareTo(array[largest]) < 0) {
            largest = r;
        }
        if (largest != i) {
            swap(i, largest);
            heapify(n, largest);
        }
    }
    /**
     * contains.
     *
     * @param      arr   The arr
     * @param      val   The value
     * Best case: O(1)
     *  worst case: O(N)
     *  Average case: O(N)
     * @return     { description_of_the_return_value }
     */
    public boolean contains(final int[] arr, final int val) {
        for (int n : arr) {
            if (val == n) {
                return true;
            }
        }
        return false;
    }
    /**
     * gets item.
     *
     * Best case: O(1)
     *  worst case: O(1)
     *  Average case: O(1)
     * @param      index  The index
     *
     * @return     { description_of_the_return_value }
     */
    public void board(final int n) {
        for (int i = 0; i < n; i++) {
            System.out.println(array[i]);
        }
        System.out.println();
        for (int j = 0; j < open; j++) {
            System.out.println(array[j]);
        }
        int[] indices = new int[bc + sc + st];
        int i = 0;
        for (int k = open; k < n; k++) {
            if (array[k].getres().equals("BC") && bc > 0) {
                indices[i++] = k;
                bc--;
            } else if (array[k].getres().
                       equals("SC") && sc > 0) {
                indices[i++] = k;
                sc--;
            } else if (array[k].getres().
                       equals("ST") && st > 0) {
                indices[i++] = k;
                st--;
            }
        }
        if (bc > 0) {
            for (int k = open; k < n; k++) {
                if (array[k].getres().equals("Open") && bc > 0) {
                    if (!contains(indices, k)) {
                        indices[i++] = k;
                        bc--;
                    }
                }
            }
        }
        if (sc > 0) {
            for (int k = open; k < n; k++) {
                if (array[k].getres().equals("Open") && sc > 0) {
                    if (!contains(indices, k)) {
                        indices[i++] = k;
                        sc--;
                    }
                }
            }
        }
        if (st > 0) {
            for (int k = open; k < n; k++) {
                if (array[k].getres().equals("Open") && st > 0) {
                    if (!contains(indices, k)) {
                        indices[i++] = k;
                        st--;
                    }
                }
            }
        }
        Arrays.sort(indices);
        for (int k = 0; k < indices.length; k++) {
            System.out.println(array[indices[k]]);
        }
    }
}
