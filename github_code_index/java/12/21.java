package debug.hack;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

/**
 * Created by Wen Ke on 2016/9/15.
 */
public class Matrix {
    private final int row;
    private final int col;
    private double[][] data;

    /**
     * Constructor which create an <b>all-zero, <pre>row</pre> by <pre>col</pre></b> matrix.
     *
     * @param row The number of rows for the new matrix.
     * @param col The number of cols for the new matrix.
     */
    public Matrix(int row, int col) {
        if (row < 1 || col < 1)
            throw new RuntimeException("Matrix size should be a pair of positive integers.");
        data = new double[row][col];
        this.row = row;
        this.col = col;
    }

    /**
     * Read a matrix from a text file in such format
     * <pre>
     * 3 2
     * 1 2
     * 3 4
     * 5 6
     * </pre>
     * The first line indicates the number of rows and columns, and the following lines are the data of this matrix.
     * Here in this example, a 3x2 matrix will be generated.
     *
     * @param file A text file formatted as above.
     * @return A matrix object.
     */
    public static Matrix read(String file) {
        try (Scanner scanner = new Scanner(new File(file))) {
            int _row = scanner.nextInt();
            int _col = scanner.nextInt();

            Matrix matrix = new Matrix(_row, _col);

            for (int i = 0; i < matrix.row; ++i)
                for (int j = 0; j < matrix.col; ++j)
                    matrix.data[i][j] = scanner.nextDouble();

            return matrix;
        } catch (FileNotFoundException e) {
            System.err.printf("File \"%s\" does not exist!", file);
            e.printStackTrace();
            return null;
        }
    }

    /**
     * Write a matrix as an ASCII text file.
     *
     * @param file The file name to hold the matrix. If the file exists, it will be rewritten. \
     *             Otherwise it will be automatically created.
     * @param m
     */
    public static void write(String file, Matrix m) {
        try (PrintWriter out = new PrintWriter(file)) {
            out.printf("%d %d \n", m.row, m.col);
            for (int i = 0; i < m.row; ++i) {
                for (int j = 0; j < m.col; ++j)
                    out.printf("%s ", Double.toString(m.data[i][j]).replaceAll("0+$", "").replaceAll("\\.$", ""));
                out.printf("\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * A uni-thread implementation of matrix multiplication.
     * Already optimized for cache-hit rate and sparse matrix.
     *
     * @param m The right operand of matrix multiplication.
     * @return The result of <b><pre>this</pre> by <pre>m</pre></b>.
     */
    public Matrix multiply(final Matrix m) {
        if (this.col != m.row)
            throw new RuntimeException("Matrix dimension mismatch!");
        Matrix result = new Matrix(this.row, m.col);
        for (int k = 0; k < m.row; ++k)
            for (int i = 0; i < this.row; ++i) {
                double r = this.data[i][k];
                if (Math.abs(r) < 1e-5)
                    continue;
                for (int j = 0; j < m.col; ++j)
                    result.data[i][j] += r * m.data[k][j];
            }
        return result;
    }

    /**
     * This implementation divide the left operand into 4 parts by row.
     *
     * @param m The right operand of matrix multiplication.
     * @return The result of <b><pre>this</pre> by <pre>m</pre></b>.
     */
    public Matrix quickMultiply(final Matrix m)
            throws BrokenBarrierException, InterruptedException {
        if (this.col != m.row)
            throw new RuntimeException("Matrix dimension mismatch!");
        Matrix result = new Matrix(this.row, m.col);

        // the width of each slice
        double slice = row / 4.0;

        CyclicBarrier barrier = new CyclicBarrier(5);

        for (int i = 0; i < 4; ++i) {
            Thread t = new Worker(this, m, result, (int) Math.round(slice * i),
                    (int) Math.round(slice * (i + 1)), barrier);
            t.start();
        }

        barrier.await();

        return result;
    }

    /**
     * The worker thread for matrix multiplication.
     */
    class Worker extends Thread {
        private Matrix a;
        private Matrix b;
        private Matrix res;
        private int a_row_from;
        private int a_row_to;
        private CyclicBarrier barrier;

        /**
         * Creating a worker thread for matrix multiplication.
         *
         * @param a          The left operand of matrix multiplication.
         * @param b          The right operand of matrix multiplication.
         * @param res        The result of matrix multiplication.
         * @param a_row_from The beginning row index of matrix <pre>a</pre>.
         * @param a_row_to   The ending index of matrix <pre>a</pre>.
         */
        public Worker(Matrix a, Matrix b, Matrix res, int a_row_from,
                      int a_row_to, CyclicBarrier barrier) {
            this.a = a;
            this.b = b;
            this.res = res;
            this.a_row_from = a_row_from;
            this.a_row_to = a_row_to;
            this.barrier = barrier;
        }

        @Override
        public void run() {
            for (int k = 0; k < b.row; ++k) {
                for (int i = a_row_from; i < a_row_to; ++i) {
                    double r = a.data[i][k];
                    if (Math.abs(r) < 1e-5)
                        continue;
                    for (int j = 0; j < b.col; ++j)
                        res.data[i][j] += r * b.data[k][j];
                }
            }

            try {
                // Wait for the other worker threads.
                barrier.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (BrokenBarrierException e) {
                e.printStackTrace();
            }
        }
    }
}






































/**
 * An Easter egg here ~~
 *
 * Glory sacrificing for the state,
 * Darned escaping because of fate.
 *                  ---- The Elder.
 */
