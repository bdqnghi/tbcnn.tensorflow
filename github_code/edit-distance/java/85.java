import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.security.spec.ECField;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;

/**
 * Compute edit distance using dynamic programming
 * YOUR_NAME_HERE_PLEASE
 * GBI, Daniel Huson, 4.2018
 */
public class EditDistance {
    String x = new String();
    String y = new String();
    Matrix D;
    /**
     * computes the edit distance between two sequences using dynamic programming
     *  This method sets up and fills the dynamic programming matrix
     *
     * @param x first sequence
     * @param y second sequence
     * @return edit distance
     */
    public int align(String x, String y) throws Exception{
        this.x = x;
        this.y = y;
        this.D = new Matrix(x.length() + 1, y.length() + 1);
        for(int i = 0; i <= x.length(); ++i){
            D.set(i, 0, i);
        }
        for(int j = 0; j <= y.length(); ++j){
            D.set(0,j,j);
        }

        for(int i = 1; i <= x.length(); ++i){
            for(int j = 1; j <= y.length(); ++j){
                int delta = 1;
                if(x.charAt(i - 1) == y.charAt(j - 1)){
                    delta = 0;
                }
                ArrayList<Integer> prev_values = new ArrayList<>();
                prev_values.add(D.get(i-1, j) +1);
                prev_values.add(D.get(i,j-1) +1);
                prev_values.add(D.get(i-1,j-1) + delta);
                D.set(i, j, Collections.min(prev_values));
            }
        }
        // PLEASE IMPLEMENT (first assignment task)
        return D.get(x.length(),y.length());
    }

    /**
     * perform traceback and print an optimal alignment to  the console (standard output)
     *  This method assumes that the method align has already been run and that the dynamic programming
     *  matrix has been computed and is stored in the class
     */
    public void traceBackAndShowAlignment(int n, int m) throws Exception{
        // PLEASE IMPLEMENT (second assignment task)
        int i = n;
        int j = m;
        StringBuilder sb_xalign = new StringBuilder();
        StringBuilder sb_yalign = new StringBuilder();
        while( (i > 0) && (j > 0)){
            int delta = 1;
            if(x.charAt(i-1) == y.charAt(j-1)){
                delta = 0;
            }
            if(D.get(i,j) == D.get(i - 1,j) +1){
                sb_xalign.append(x.charAt(i-1));
                sb_yalign.append("_");
                i--;

            }else if( D.get(i,j) == D.get(i-1,j-1) + delta){
                sb_xalign.append(x.charAt(i-1));
                sb_yalign.append(y.charAt(j-1));
                j--;
                i--;
            }else if(D.get(i,j) == D.get(i,j-1) +1){
                sb_xalign.append("_");
                sb_yalign.append(y.charAt(j-1));
                j--;
            }else{
                System.out.println("Nothing applies");
                throw new Exception("D not correct");
            }
        }
        while(j > 0){
            sb_xalign.append("_");
            sb_yalign.append(y.charAt(j-1));
            j--;
        }
        while(i > 0){
            sb_xalign.append(x.charAt(i-1));
            sb_xalign.append("_");
            j--;
        }
        String x_align = sb_xalign.reverse().toString();
        String y_align = sb_yalign.reverse().toString();
        System.out.println("x: "+x_align);
        System.out.println("y: "+y_align);
    }

    /**
     * main program: reads two sequences in fastA format and computes their optimal alignment score.
     *
     * @param args commandline arguments
     */
    public static void main(String[] args) throws Exception {
        System.out.println("Klara Reichard");

        /*if (args.length != 1)
            throw new IOException("Usage: EditDistanceDP fileName");*/

        String fileName1 = args[0];
        String fileName2 = args[1];

        FastA fasta1 = new FastA();
        fasta1.read(fileName1);

        FastA fasta2 = new FastA();
        fasta2.read(fileName2);


        EditDistance editDistanceDP = new EditDistance();

        if (fasta1.getLength() == 2) {
            System.out.println("sequence 1 = "+ fasta1.getSequence(0));
            System.out.println("sequence 2 = "+ fasta1.getSequence(1));
            int editDistance = editDistanceDP.align(fasta1.getSequence(0), fasta1.getSequence(1));

            System.out.println("DNA Edit distance is=" + editDistance);

            int[][] distance = editDistanceDP.D.matrix;

            System.out.println("An optimal alignment=");
            //editDistanceDP.D.printMatrix();
            System.out.println("x = "+editDistanceDP.x);
            System.out.println("y = "+editDistanceDP.y);
            editDistanceDP.traceBackAndShowAlignment(fasta1.getSequence(0).length(), fasta1.getSequence(1).length());
        }

        if (fasta2.getLength() == 2) {
            System.out.println("sequence 1 = "+ fasta2.getSequence(0));
            System.out.println("sequence 2 = "+ fasta2.getSequence(1));
            int editDistance = editDistanceDP.align(fasta2.getSequence(0), fasta2.getSequence(1));

            System.out.println("DNA Edit distance is=" + editDistance);

            int[][] distance = editDistanceDP.D.matrix;

            System.out.println("An optimal alignment=");
            //editDistanceDP.D.printMatrix();
            System.out.println("x = "+editDistanceDP.x);
            System.out.println("y = "+editDistanceDP.y);
            editDistanceDP.traceBackAndShowAlignment(fasta2.getSequence(0).length(), fasta2.getSequence(1).length());
        }
    }
}
