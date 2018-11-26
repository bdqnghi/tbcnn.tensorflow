/**
 * Created by hassaniiii on 6/18/17.
 */

import javafx.application.Application;
import javafx.stage.Stage;

import java.util.Arrays;

public class Main extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        int[][] A = {{20,15,3,14},{69,23,78,7},{9,2,58,46},{38,25,30,18}};
        int[][] B = {{10,23,65,48},{5,65,32,1},{54,3,89,25},{77,56,33,45}};
        System.out.print(Arrays.deepToString(matrixMultiplicationFinal(A, B)));
    }

    public static int[][] matrixMultiplicationFinal(int[][] A, int[][] B) {

        return matrixMultiplication(A, 0, 0,
                B, 0, 0,
                A.length);

    }


    public static int[][] matrixMultiplication(int[][] A, int rowA, int colA,
                                               int[][] B, int rowB, int colB,
                                               int size) {

        int[][] C = new int[size][size];

        if (size == 1)
            C[0][0] = A[rowA][colA] * B[rowB][colB];

        else {

            int newSize = size / 2;
            //C11 = (A11, B11) + (A12, B21)
            sumMatrix(C,
                    matrixMultiplication(A, rowA, colA, B, rowB, colB, newSize),
                    matrixMultiplication(A, rowA, colA + newSize, B, rowB + newSize, colB, newSize),
                    0, 0);

            //C12 = (A11, B12) + (A12, B22)
            sumMatrix(C,
                    matrixMultiplication(A, rowA, colA, B, rowB, colB + newSize, newSize),
                    matrixMultiplication(A, rowA, colA + newSize, B, rowB + newSize, colB + newSize, newSize),
                    0, newSize);

            //C21 = (A11, B12) + (A12, B22)
            sumMatrix(C,
                    matrixMultiplication(A, rowA + newSize, colA, B, rowB, colB, newSize),
                    matrixMultiplication(A, rowA + newSize, colA + newSize, B, rowB + newSize, colB, newSize),
                    newSize, 0);

            sumMatrix(C,
                    matrixMultiplication(A, rowA + newSize, colA, B, rowB, colB + newSize, newSize),
                    matrixMultiplication(A, rowA + newSize, colA + newSize, B, rowB + newSize, colB + newSize, newSize),
                    newSize, newSize);
        }

        return C;

    }


    private static void sumMatrix(int[][] C, int[][] A, int[][] B, int rowC, int colC) {
        int n = A.length;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                C[i + rowC][j + colC] = A[i][j] + B[i][j];
        }
    }
}
