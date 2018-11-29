class TestClass {
    public static void main(String[] args) {
        int[][] A = new int[][]{
                {1, 2},
                {3, 4}
        };
        int[][] B = new int[][]{
                {5, 6, 7},
                {8, 9, 10}
        };
        int n = A.length;
        int p = B[0].length;
        int m = A[0].length;
        int[][] C = new int[n][p];
        int sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < p; j++) {
                for (int k = 0; k < m; k++) {
                    sum += A[i][k] * B[k][j];
                }
                C[i][j] = sum;
                sum = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < p; j++) {
                System.out.print(C[i][j] + " ");
            }
            System.out.println();
        }
    }
}