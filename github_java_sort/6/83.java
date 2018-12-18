package HW5_BurrowsWheeler;
import java.util.logging.Level;
import java.util.logging.Logger;

import edu.princeton.cs.algs4.BinaryIn;
import edu.princeton.cs.algs4.BinaryOut;

public class BurrowsWheeler {
    private static int R = 256; 
    
    
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
        int first = -1;
        for (int i = 0; i < n; i++) {
            
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
    
    private static int[] sort(char[] a) {
        int n = a.length;
        int[] order = new int[n];
        int[] count = new int[R + 1]; 
        char[] sorted = new char[n];
        
        for (int i = 0; i < n; i++) {
            count[((int) a[i]) + 1]++;
        }
        
        for (int i = 1; i <= R; i++) {
            count[i] += count[i - 1];
        }
        
        
        for (int i = 0; i < n; i++) {
            order[count[(int) a[i]]] = i;
            sorted[count[(int) a[i]]++] = a[i];            
        }
        
        for (int i = 0; i < n; i++) {
            a[i] = sorted[i];
        }        
        return order;
    }
    
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