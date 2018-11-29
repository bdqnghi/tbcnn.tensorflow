package reference;

import com.aparapi.Kernel;
import com.aparapi.Range;

/**
 * Created by anuradhawick on 12/29/17.
 */
public class MatrixMultiplication {

    public static void main(String[] args) {
        // Width of the matrix
        final int SIZE = 1000;

        // We should use linear arrays as supported by the API
        final int[] a = new int[SIZE * SIZE];
        final int[] b = new int[SIZE * SIZE];
        int[] c = new int[SIZE * SIZE];
        final int[] d = new int[SIZE * SIZE];
        int val;

        // Creating random matrices
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                a[i * SIZE + j] = (int) (Math.random() * 100);
                b[i * SIZE + j] = (int) (Math.random() * 100);
            }
        }
        long time = System.currentTimeMillis();

        // CPU multiplication
        System.out.println("Starting single threaded computation");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                val = 0;
                for (int k = 0; k < SIZE; k++) {
                    val += a[i * SIZE + k] * b[k * SIZE + j];
                }
                c[i * SIZE + j] = val;
            }
        }
        System.out.println("Task finished in " + (System.currentTimeMillis() - time) + "ms");

        // Kernel for multiplication
        Kernel kernel = new Kernel() {
            @Override
            public void run() {
                int row = getGlobalId() / SIZE;
                int col = getGlobalId() % SIZE;
                if (row > SIZE || col > SIZE) return;

                d[row * SIZE + col] = 0;


                for (int i = 0; i < SIZE; i++) {
                    d[row * SIZE + col] += a[row * SIZE + i] * b[i * SIZE + col];
                }
            }
        };

        // Array size for GPU to know
        Range range = Range.create(SIZE * SIZE);

        System.out.println("Starting GPU computation");
        time = System.currentTimeMillis();
        kernel.execute(range); // Running the Kernel
        System.out.println("Task finished in " + (System.currentTimeMillis() - time) + "ms");

        // Verifying the result
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (c[i * SIZE + j] != d[i * SIZE + j]) {
                    System.out.println("ERROR");
                    return;
                }
            }
        }
    }
}
