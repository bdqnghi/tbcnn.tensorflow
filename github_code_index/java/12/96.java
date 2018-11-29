package matrixMultiplication;

public class BoxMatrixMultiplication extends DivideAndConquerMatrixMultiplication {

    public String getName() {
        return "Box Multiplication";
    }

    public int[][] mult(int[][] dest, int[][] a, int[][] b) {
        IntMatrixMultiplication brute = new BruteForceMatrixMultiplication();
        int size = a.length;

        if (size == 2)
            dest = brute.mult(dest, a, b);
        else {
            int[][][] quadrantsA = new int[4][size / 2][size / 2];
            int[][][] quadrantsB = new int[4][size / 2][size / 2];

            setQuadrants(a, quadrantsA);
            setQuadrants(b, quadrantsB);

            computeMultiplicationAndMerge(quadrantsA, quadrantsB, dest);
        }

        return dest;
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

        int[][] a11xb11 = mult(new int[childSize][childSize], getQuadrant(a, childSize, 0), getQuadrant(b, childSize, 0));
        int[][] a12xb21 = mult(new int[childSize][childSize], getQuadrant(a, childSize, 1), getQuadrant(b, childSize, 2));
        int[][] a11xb12 = mult(new int[childSize][childSize], getQuadrant(a, childSize, 0), getQuadrant(b, childSize, 1));
        int[][] a12xb22 = mult(new int[childSize][childSize], getQuadrant(a, childSize, 1), getQuadrant(b, childSize, 3));
        int[][] a21xb11 = mult(new int[childSize][childSize], getQuadrant(a, childSize, 2), getQuadrant(b, childSize, 0));
        int[][] a22xb21 = mult(new int[childSize][childSize], getQuadrant(a, childSize, 3), getQuadrant(b, childSize, 2));
        int[][] a21xb12 = mult(new int[childSize][childSize], getQuadrant(a, childSize, 2), getQuadrant(b, childSize, 1));
        int[][] a22xb22 = mult(new int[childSize][childSize], getQuadrant(a, childSize, 3), getQuadrant(b, childSize, 3));

        int[][] c11 = addMatrices(a11xb11, a12xb21);
        int[][] c12 = addMatrices(a11xb12, a12xb22);
        int[][] c21 = addMatrices(a21xb11, a22xb21);
        int[][] c22 = addMatrices(a21xb12, a22xb22);

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

}
