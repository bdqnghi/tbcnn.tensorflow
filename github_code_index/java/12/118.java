package other;

// Please read the following before proceeding :
//
// https://en.wikipedia.org/wiki/Matrix_chain_multiplication (Introduction Paras)
// https://en.wikipedia.org/wiki/Matrix_chain_multiplication#A_Dynamic_Programming_Algorithm
// 
// * Solve the matrix multiplication problem :
// * 
// * Given n matrices, find the optimal way 
// * to multiply them such that least
// * number of scalar multiplications is required.
// * 
// * An m*n matrix when multipled with an n*r 
// * matrix (which outputs an m*r matrix)
// * requires m*n*r multiplications. Thus, 
// * to multiply three matrics M1, M2 and
// * M3, with orders p1*q1; q1*q2 and q2*q3 :
// * 
// * 1) if we first multiply M1 with M2, 
// * the number of multiplications required is
// * p1*q1*q2 + p1*q2*q3
// * 
// * 2) However, other way round, q1*q2*q3 + p1*q1*q3
// * 
// * Clearly, the two can be different. Thus 
// * the number of scalar multiplications
// * required varies. It happens because 
// * with one method, we compute
// * duplicate products.
// * 
// * @author rajatpawar
// *
// 
public class MatrixMultiplication {

    Matrix[] matrixArray;
    static int INFINITY = 1999999999;
    int[][] twoDMemoizationArray;
    boolean memoizationEnabled;

    public int computeMinimumScalerMultiplicationsUsingDynamic(Matrix[] inputMatrices,
            boolean enableMemoization) {

        memoizationEnabled = enableMemoization;
        matrixArray = inputMatrices;
        // the x,y th entry of array represents minimum number of scalar
        // multiplications required to multiply matrices between index i and
        // index j

        twoDMemoizationArray = new int[inputMatrices.length][inputMatrices.length];

        for (int a = 0; a < inputMatrices.length; a++) {
            for (int b = 0; b < inputMatrices.length; b++) {
                twoDMemoizationArray[a][b] = -1;
            }
        }

        minimumScalarMultiplicationsRecursive(0, inputMatrices.length - 1);

        // the simple case of i*i+1 and j*j-1 the
        // minimum number of scalar multiplications are clear.

        // let us compute a recursive implementation

        return 0;
    }

    public int minimumScalarMultiplicationsRecursive(int startI, int endI) {

    	// if the solution exists in the array
    	// (since it was previously computed
    	// and is basically a repeating problem) 
    	// just return it from the array.
    	
    	// we initialize array with value -1
    	// because the number of scalar
    	// multiplications required cannot
    	// be negative. 
 
    	if (twoDMemoizationArray[startI][endI] != -1) {
            return twoDMemoizationArray[startI][endI];
        } else {

        // if value is -1, compute the minimum 
        // no. of scalar multiplications required.
        // (for the first time!)
            System.out.println("Min scalar mul b/w " + startI + " and " + endI);

            // 1 2 3 4 5 6 7 8 9
            int min;
            if (endI == (startI + 2)) {

                // the case where we only have three matrices.
            	// just considering both the permutations!
            	// (AB)(C) and (A)(BC)
            	// this is called a "trivial/base case"
            	// in the "recursive algorithms" language.
            	// Although relatively simple, it is very 
            	// important to get the base cases right!
            	// Or else, it might be one of the most common
            	// mistakes!

                int possibility1part1 = matrixArray[startI].rows * matrixArray[startI].columns
                        * matrixArray[startI + 1].columns;
                int possibility1part2 = matrixArray[startI].rows * matrixArray[startI + 1].columns
                        * matrixArray[startI + 2].columns;
                int possibility1 = possibility1part1 + possibility1part2;
                int possibility2part1 = matrixArray[startI + 1].rows
                        * matrixArray[startI + 1].columns * matrixArray[startI + 2].columns;
                int possibility2part2 = matrixArray[startI].rows * matrixArray[startI + 1].rows
                        * matrixArray[startI + 2].columns;
                int possibility2 = possibility2part1 + possibility2part2;

                System.out.println("---------------------");
                System.out.println("Special three matrices multiplication case. ");
                System.out.println(" 1 and 2 first and then the 3: " + possibility1);
                System.out.println(" 2 and 3 first and then the 1: " + possibility2);
                if (possibility1 < possibility2) {
                    min = possibility1;
                    System.out.println(" Minimum is " + min);
                } else {
                    min = possibility2;
                    System.out.println(" Minimum is " + min);
                }
                return min;
            }

            // yet another trivial case where
            // we have only two matrices. 
            else if ((startI == (endI + 1)) || (endI == (startI + 1))) {
                min = matrixArray[startI].rows * matrixArray[startI].columns
                        * matrixArray[endI].columns;
                System.out.println("------------------");
                System.out.println("Min is " + min);
                System.out.println("------------------");
                return (matrixArray[startI].rows * matrixArray[startI].columns * matrixArray[endI].columns);
                
                
            } 
            // the typical case where we have more than 
            // 3 matrices. 
            else {

            	// notice how we use capital 
            	// lettered names to denote 
            	// constants for more readability! 
            	min = INFINITY;
                int current;

                // as the algorithm says, 
                // iterate from start to end, 
                // comparing the number of multiplications
                // in all the cases and, thus,
                // computing the minimum.
                
                for (int i = startI + 1; i < (endI - 1); i++) {
                    // initial range : startI,i
                    // final range : i,endI
                    System.out.println(" consider (" + startI + "," + i + ") and (" + (i + 1) + ","
                            + endI + ").");
                    
                    // dividing the computation at the 
                    // iteration point and making computations
                    // on both sides. 
                    current = minimumScalarMultiplicationsRecursive(startI, i)
                            + minimumScalarMultiplicationsRecursive(i + 1, endI);
                    System.out.println(current + " scalar multiplications.");
                    if (current < min)
                        min = current;
                }
                System.out.println("------------------");
                System.out.println("Min is " + min);
                System.out.println("------------------");
                // store the solution to the subproblem 
                // in the memoization array. 
                if (memoizationEnabled)
                    twoDMemoizationArray[startI][endI] = min;
                return min;
            }
        }
    }

    public class Matrix {

        public Matrix(int rows, int columns) {
            this.columns = columns;
            this.rows = rows;
        }

        int columns;
        int rows;
    }

}
