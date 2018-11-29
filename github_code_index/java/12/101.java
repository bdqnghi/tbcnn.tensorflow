package matrixMultiplication;

public class StrassenMatrixMultiplication extends DivideAndConquerMatrixMultiplication {

	public String getName() {
		return "Strassen Method";
	}

	public int[][] mult(int[][] dest, int[][] a, int[][] b) {
        int size = a.length;

        if (size == 2)
            baseCase(dest,a,b);
        else {
            int[][][] quadrantsA = new int[4][size / 2][size / 2];
            int[][][] quadrantsB = new int[4][size / 2][size / 2];

            setQuadrants(a, quadrantsA);
            setQuadrants(b, quadrantsB);

            computeMultiplicationAndMerge(quadrantsA, quadrantsB, dest);
        }

        return dest;
    }

    private void baseCase(int[][] dest, int[][] a, int[][] b) {
    	int m1 = (a[0][0]+a[1][1])*(b[0][0]+b[1][1]);
		int m2 = (a[1][0]+a[1][1])*b[0][0];
		int m3 = a[0][0]*(b[0][1]-b[1][1]);
		int m4 = a[1][1]*(b[1][0]-b[0][0]);
		int m5 = (a[0][0]+a[0][1])*b[1][1];
		int m6 = (a[1][0]-a[0][0])*(b[0][0]+b[0][1]);
		int m7 = (a[0][1]-a[1][1])*(b[1][0]+b[1][1]);
		
		dest[0][0] = m1+m4-m5+m7;
		dest[0][1] = m3+m5;
		dest[1][0] = m2+m4;
		dest[1][1] = m1+m3-m2+m6;
	}

	private void setQuadrants(int[][] a, int[][][] quadrants) {
        for (int i = 0; i < 4; i++) {
            setQuadrantI(a, quadrants, i);
        }
    }

    private void setQuadrantI(int[][] a, int[][][] quadrants, int quadrant) {
        int childSize = a.length / 2;
        int iOffset = childSize*(quadrant/2);
        int jOffset = childSize*(quadrant%2);

        for (int i = 0; i < childSize; i++) {
            for (int j = 0; j < childSize; j++) {
                quadrants[quadrant][i][j] = a[i + iOffset][j + jOffset];
            }
        }
    }

    private void computeMultiplicationAndMerge(int[][][] a, int[][][] b, int[][] dest) {
        int childSize = dest.length / 2;

        int[][] m1 = mult(new int[childSize][childSize],
			 addMatrices(getQuadrant(a, childSize, 0), getQuadrant(a, childSize, 3)),
			 addMatrices(getQuadrant(b, childSize, 0), getQuadrant(b, childSize, 3)));
        int[][] m2 = mult(new int[childSize][childSize],
   			 addMatrices(getQuadrant(a, childSize, 2), getQuadrant(a, childSize, 3)),
   			 getQuadrant(b, childSize, 0));
        int[][] m3 = mult(new int[childSize][childSize],
   			 getQuadrant(a, childSize, 0),
   			 substractMatrices(getQuadrant(b, childSize, 1), getQuadrant(b, childSize, 3)));
        int[][] m4 = mult(new int[childSize][childSize],
  			 getQuadrant(a, childSize, 3),
   			 substractMatrices(getQuadrant(b, childSize, 2), getQuadrant(b, childSize, 0)));
        int[][] m5 = mult(new int[childSize][childSize],
  			 addMatrices(getQuadrant(a, childSize, 0), getQuadrant(a, childSize, 1)),
   			 getQuadrant(b, childSize, 3));
        int[][] m6 = mult(new int[childSize][childSize],
   			 substractMatrices(getQuadrant(a, childSize, 2), getQuadrant(a, childSize, 0)),
   			 addMatrices(getQuadrant(b, childSize, 0), getQuadrant(b, childSize, 1)));
        int[][] m7 = mult(new int[childSize][childSize],
  			 substractMatrices(getQuadrant(a, childSize, 1), getQuadrant(a, childSize, 3)),
   			 addMatrices(getQuadrant(b, childSize, 2), getQuadrant(b, childSize, 3)));

        int[][] c11 = addMatrices(m1,addMatrices(substractMatrices(m4, m5),m7));
        int[][] c12 = addMatrices(m3, m5);
        int[][] c21 = addMatrices(m2, m4);
        int[][] c22 = addMatrices(m1,addMatrices(substractMatrices(m3, m2),m6));

        copySubMatrix(c11, dest, 0, 0);
        copySubMatrix(c12, dest, 0, childSize);
        copySubMatrix(c21, dest, childSize, 0);
        copySubMatrix(c22, dest, childSize, childSize);
    }

    private int[][] getQuadrant(int[][][] quadrants, int childSize, int quadrant) {
        int [][] matrix = new int[childSize][childSize];

        for (int i = 0; i < childSize; i++) {
            for (int j = 0; j < childSize; j++) {
                matrix[i][j] = quadrants[quadrant][i][j];
            }
        }

        return matrix;
    }
    /*
     * n = 512
Brute Force took 241ms
Strassen Method took 6800ms

n = 512
Brute Force took 248ms
Strassen Method took 4233ms

     */
}

