import java.util.Arrays;

public class Heapsort {
    
    private Integer vac;
    
    private Integer open;
    
    private Integer bc;
    
    private Integer sc;
    
    private Integer st;
    
    
    private Studentdetails[] array;
    
    private int size;
    
    public Heapsort() {

    }
    
    public Heapsort(final Integer v, final Integer o, final Integer bc, final Integer sc, final Integer st, final Studentdetails[] a, final int n) {
        this.vac = v;
        this.open = o;
        this.bc = bc;
        this.sc = sc;
        this.st = st;
        this.array = a;
        this.size = n;
    }
    
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
    
    public void swap(final int i, final int j) {
        Studentdetails temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    
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
    
    public boolean contains(final int[] arr, final int val) {
        for (int n : arr) {
            if (val == n) {
                return true;
            }
        }
        return false;
    }
    
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
