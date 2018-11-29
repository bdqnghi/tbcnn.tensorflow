package HW5_BurrowsWheeler;
import java.util.logging.Level;
import java.util.logging.Logger;

import edu.princeton.cs.algs4.BinaryIn;
import edu.princeton.cs.algs4.BinaryOut;

public class BurrowsWheeler {
    private static int R = 256; //size of alphabet
    // apply Burrows-Wheeler encoding, reading from standard input and writing to standard output
    // output the last column in sorted circular suffix array plus the index of string
    public static void encode(String inputfile, String outputfile) {
        Logger logger = Logger.getLogger("BWT encode");
        long time = System.nanoTime();
        int count = 0;
        BinaryIn in = new BinaryIn(inputfile);        
        String input = in.readString();
        System.out.println(input.length());
        CircularSuffixArray array = new CircularSuffixArray(input);
        int n = input.length();
        char[] bwt = new char[input.length()];
        int first = -1;//index of original string in sorted circular suffix array
        for (int i = 0; i < n; i++) {
            //we want the last char in the circular shifted string
            bwt[i] = input.charAt((n - 1 + array.index(i)) % n);
            if (array.index(i) == 0) {
                first = i;
            }
        }
        BinaryOut out = new BinaryOut(outputfile);
        out.write(first, 32);
        out.write(new String(bwt));
        out.close();
        count += n;
        time = System.nanoTime() - time;
        logger.log(Level.INFO, "processed " + count + " ASCII chars in " + time + " nano seconds");
    }

    // apply Burrows-Wheeler decoding, reading from standard input and writing to standard output
    /**
     * based on the index of original string in sorted circular suffix array
     * and the last column of characters, recover the original string
     * 
     * there are two keys here:
     * 1) the first column is exactly the same as sorted last column
     * 2) for a column that begins with 'X', the next cicurlar suffix
     *    will end with 'X'. And the characters in the middle will be 
     *    the same as the characters in the prefix.
     *    
     * to recover the original string, we only need to sort the last column
     * of sorted circular suffix array, then use the sorted indeces as pointers
     * of next character.
     * 
     * @param inputfile
     * @param outputfile
     */
    public static void decode(String inputfile, String outputfile) {
        Logger logger = Logger.getLogger("BWT decode");
        long time = System.nanoTime();
        int count = 0;
        BinaryIn in = new BinaryIn(inputfile);
        int first = in.readInt(32);
        String lastColumn = in.readString();
        int n = lastColumn.length();
        int[] next = new int[n];
        char[] original = new char[n];
        char[] firstColumn = lastColumn.toCharArray();

        for (int i = 0; i < n; i++) {
            next[i] = i;
        }
        //use radix sort to sort next based on last column
        //and first column
        sort(lastColumn.toCharArray(), next);
        sort(firstColumn);
        int i = 0;
        while(i < n){
            original[i++] = firstColumn[first];
            first = next[first];
        }
        BinaryOut out = new BinaryOut(outputfile);
        out.write(new String(original));        
        out.close();
        count += n;
        time = System.nanoTime() - time;
        logger.log(Level.INFO, "processed " + count + " ASCII chars in " + time + " nano seconds");
    }
    /**
     * radix-sort char[] a, return sorted indeces
     * @param a
     * @return
     */
    private static int[] sort(char[] a) {
        int n = a.length;
        int[] order = new int[n];
        int[] count = new int[R + 1]; //record start position of each character
        char[] sorted = new char[n];
        
        for (int i = 0; i < n; i++) {
            count[((int) a[i]) + 1]++;
        }
        //cumulative sum
        for (int i = 1; i <= R; i++) {
            count[i] += count[i - 1];
        }
        
        //order array
        for (int i = 0; i < n; i++) {
            order[count[(int) a[i]]] = i;
            sorted[count[(int) a[i]]++] = a[i];            
        }
        //copy back
        for (int i = 0; i < n; i++) {
            a[i] = sorted[i];
        }        
        return order;
    }
    /**
     * radix-sort a, and sort b based on a
     * @param a
     * @param b
     */
    private static void sort(char[] a, int[] b) {
        assert(a.length == b.length);
        int n = a.length;
        int[] order = sort(a);
        int[] tmp = new int[n];
        for (int i = 0; i < n; i++) {
            tmp[i] = b[order[i]];
        }
        for (int i = 0; i < n; i++) {
            b[i] = tmp[i];
        }        
    }
    // if args[0] is '-', apply Burrows-Wheeler encoding
    // if args[0] is '+', apply Burrows-Wheeler decoding
    public static void main(String[] args) {
        if (args[0].equals("-")) {
            encode(args[1], args[2]);
        } else if (args[0].equals("+")) {
            decode(args[1], args[2]);
        } else {
            throw new IllegalArgumentException();
        }
    }
}