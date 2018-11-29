import java.util.ArrayList;
import java.util.Arrays;

public class RadixSort extends Sort {

    private static final double LOG2 = Math.log(2);

    private int temp[];
    private ArrayList<Integer> tempSorted;
    /**
     * b - liczba bitów w słowie
     * r - liczba bitów w "cyfrze"
     * k - ilość wartości jakie może przyjmować cyfra
     * d - ilość cyfr w słowie
     * n - ilość danych do posortowania
     */
    private int b,r,k,d,n;

    public RadixSort(boolean type, int size, int scope) {
        super(type, size, scope);
        n = size;
        // 2^b = scope
        b = (int)Math.ceil(log2(scope));
        // n > 2^b
        if (b < Math.floor(log2(n))){
            r = b;
        } else {
            r = (int) Math.floor(log2(n));
        }
        k = (int) Math.pow(2,r); // k = 2^r
        d = (int) Math.ceil((double)b/(double)r);
    }

    public void sort() {
        temp = new int[k];
        for (int position=0; position<d; position++) {
            countingSort(data.size(), position);
        }
    }


    private void countingSort(int n, int position) {
        tempSorted = new ArrayList<>(data);
        Arrays.fill(temp, 0);

        for (int j=0; j<n; j++) {
            // C[A[j]] = C[A[j]]+1
            // AFTER THIS LOOP temp[i] CONTAINS NUMBER OF ELEMENTS EQUAL TO i
            temp[(data.get(j) >> r*position) % k]++;
        }

        for (int i=1; i<k; i++) {
            // C[i] = C[i] + C[i-1]
            // SUMMING UP ONE BY ONE VALUES OF temp ARRAY
            // AFTER THIS temp[i] CONTAINS NUMBER OF ELEMENTS LESSER OR EQUAL i
            temp[i] += temp[i-1];
        }

        for (int j=n-1; j>=0; j--) {
            // B[C[A[j]]] = A[j]
            // ALL ELEMENTS FROM data ARE PUT IN RIGHT POSITIONS IN tempSorted
            tempSorted.set(temp[(data.get(j) >> r*position) % k] - 1, data.get(j));
            // C[A[j]] = C[A[j]]-1
            // BECAUSE ELEMENTS ARE NOT ALWAYS PAIRWISE DIFFERENT, WE DECREASE temp[data[j]] WHENEVER data[j]
            // IS PUTTED TO tempSorted ARRAY
            temp[(data.get(j) >> r*position) % k]--;
        }

        for (int i=0; i<dataSize; i++) {
            if (compare(tempSorted.get(i), data.get(i)) != 0) {
                data.set(i, tempSorted.get(i));
                swaps++;
            }
        }
    }

    public void sortLog() {
        print_log("radix sort is starting");
        temp = new int[k];
        for (int position=0; position<d; position++) {
            print_log("position = " + position);
            countingSortLog(data.size(), position);
        }
    }

    private void countingSortLog(int n, int position) {
        print_log("counting sort is starting");

        tempSorted = new ArrayList<>(data);
        Arrays.fill(temp, 0);

        print_log("temp array is filled with 0's now");

        for (int j=0; j<n; j++) {
            temp[(data.get(j) >> r*position) % k]++;
        }

        for (int i=1; i<k; i++) {
            temp[i] += temp[i-1];
        }

        for (int j=n-1; j>=0; j--) {
            tempSorted.set(temp[(data.get(j) >> r*position) % k] - 1, data.get(j));
            temp[(data.get(j) >> r*position) % k]--;
        }

        for (int i=0; i<dataSize; i++) {
            if (compare(tempSorted.get(i), data.get(i)) != 0) {
                data.set(i, tempSorted.get(i));
                print_log(tempSorted.get(i) + " was swapped, now on index " + i);
                swaps++;
            }
        }

        for (int i : data) {
            print_log(i + "");
        }
    }

    private double log2(double a) {
        return Math.log(a)/LOG2;
    }

    public static void main(String[] args) {
        boolean type;
        if(Integer.parseInt(args[0]) <= 0)
            type = false;
        else
            type = true;

        int size = Integer.parseInt(args[1]);
        int scope = Integer.parseInt(args[2]);
        //*/
        RadixSort rs = new RadixSort(type, size, scope);
        rs.sortLog();

        System.out.println("data is now sorted (" + rs.compares + " compares, " + rs.swaps + " swaps)!");
        System.out.println("");
        System.out.println("b - liczba bitów w słowie: " + rs.b);
        System.out.println("r - liczba bitów w 'cyfrze': " + rs.r);
        System.out.println("k - ilość wartości jakie może przyjmować cyfra: " + rs.k);
        System.out.println("d - ilość cyfr w słowie: " + rs.d);
        System.out.println("n - ilość danych do posortowania: " + rs.n);
        rs.printBinary(rs.b);
        rs.print();
        /*/
        RadixSort rs;
        double swaps = 0;
        for (int i=0; i<1000; i++) {
            rs = new RadixSort(true, 1000, 10);
            rs.sort();
            swaps += rs.swaps;
        }
        System.out.println((double)swaps/1000);
        //*/
    }

}
