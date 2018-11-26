package alg;

/**
 * Matrix
 * 
 * Placeholder for solution to the matrix-multiplication problem:
 * 
 * Given the dimensions of a sequence of matrices to be multiplied
 * represented as an array of the dimensions (so that for n matrices
 * there would be n+1 dimensions: matrix 0 would be dim[0] by dim[1],
 * matrix 1 would be dim[1] by dim[2], ... matrix n-1 would be 
 * dim[n-1] by dim[n]), return the order of multiplication that 
 * would result in the fewest arithmetic operations, represented
 * by a string showing the product parenthesized in the ideal ordering.
 * 
 * @author Thomas VanDrunen
 * CSCI 345, Wheaton College
 * July 13, 2015
 */
public class Matrix {

    /**
     * Compute the best order of multiplication for a given
     * sequence of matrices.
     * @param dimensions The dimensions of the matrices indicating
     * that matrix i is a dimensions[i] by dimensions[i+1] matrix.
     * @return The optimal order of multiplications represented
     * by a string showing the matrices optimally parenthesized
     */
    public static String planMatrixMult(int[] dimensions) {
        int numMatrices = dimensions.length - 1;
        
        // after which matrix should we break a
        // given subsequence of matrices?
        // The best way to order the multiplications of matrices 
        // i through j (inclusive), is to multiply i through 
        // bestBreak[i][j] and then multiply bestBreak[i][j]+1 through j.
        int[][] bestBreaks = new int[numMatrices][numMatrices];

        // the number of multiplications necessary if we break up
        // a subsequence of matrices in the best way
        int[][] numMults = new int[numMatrices][numMatrices];


        // -----------------------------------
        // TODO: populate the bestBreaks table and the numMults table
        // -----------------------------------

        
        
        return printResult(bestBreaks, 0, numMatrices-1);
    }

    /**
     * Convert the "bestBreaks" table built by planMatrixMult()
     * into a string displaying the parenthesization of the 
     * matrices.
     * @param bestBreaks A table indicating the best place to break
     * a subsequence of matrices to be multiplied.
     * @param i The first matrix in the subsequence
     * @param j The last (inclusive) matrix in the subsequence
     * @return A string showing the best multiplication order for
     * these matrices by parenthesization.
     */
    private static String printResult(int[][] bestBreaks, int i, int j) {
        if (i == j) return ""+i;
        else return "(" + printResult(bestBreaks, i, bestBreaks[i][j]) +
                printResult(bestBreaks, bestBreaks[i][j] + 1, j) + ")";
    }
    
}
