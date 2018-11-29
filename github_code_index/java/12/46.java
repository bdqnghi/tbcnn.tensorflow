package ru.ifmo.ctddev.nechaev.task6;

import java.util.Random;

/**
 * Created with IntelliJ IDEA.
 * User: flevix
 * Date: 19.05.13
 * Time: 20:15
 */



public class MatrixMultiplication {
    /** First matrix */
    private int[][] A;
    /** Second matrix */
    private int[][] B;
    /** Result of {@link MatrixMultiplication#A} * {@link MatrixMultiplication#B} */
    private int[][] C;
    /** Size of matrix {@link MatrixMultiplication#A}, {@link MatrixMultiplication#B},
     *  {@link MatrixMultiplication#C} */
    int size;

    /**
     * Constructs {@link MatrixMultiplication#A} and {@link MatrixMultiplication#B}
     * as a random matrix with size {@code n}.
     * Initialising field {@link MatrixMultiplication#size} as {@code n}.
     *
     * @param n matrix size
     * @throws IllegalArgumentException {@code n} less then one
     */
    public MatrixMultiplication(int n) {
        if (n < 1) {
            throw new IllegalArgumentException("size should be greater then zero");
        }
        this.size = n;
        this.A = generate();
        this.B = generate();
    }

    /**
     * Generating random matrix with {@link MatrixMultiplication#size}
     *
     * @return random generated matrix
     */
    private int[][] generate() {
        Random r = new Random();
        int[][] tmp = new int[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                tmp[i][j] = r.nextInt();
            }
        }
        return tmp;
    }

    /**
     * Multi-threading matrix multiplication.
     * Calculating {@link MatrixMultiplication#A} * {@link MatrixMultiplication#B}.
     * Stored result in a field {@link MatrixMultiplication#C}.
     *
     * @param m count of the threads
     * @return {@link MatrixMultiplication#C} as result
     *
     * @throws IllegalArgumentException if one of threads is interrupt
     * @see java.lang.Thread
     */
    public int[][] multiply(int m) throws InterruptedException {
        if (m < 1) {
            throw new IllegalArgumentException("Threads counts should be greater then zero");
        }
        this.C = new int[size][size];
        int size2 = size * size;
        if (m > size2)
            m = size2;
        Thread[] threads = new Thread[m];
        int remainder = size2 % m;
        int step = size2 / m;
        int count = 0;
        int top = (step + 1) * remainder;

        for (int i = 0; i < top; i += step + 1, count++) {
            threads[count] = new Thread(new Worker(size, i, i + step + 1, A, B, C));
        }
        for (int i = top; i < size2; i += step, count++) {
            threads[count] = new Thread(new Worker(size, i, i + step, A, B, C));
        }
        for (int i = 0; i < m; i++) {
            threads[i].start();
        }
        try {
            for (int i = 0; i < m; i++) {
                threads[i].join();
            }
        } catch (InterruptedException ie) {
            throw ie;
        }
        return C;
    }


    /**
     * Calculation {@code sum} of cells matrix {@link MatrixMultiplication#C}.
     * @return {@code sum}
     */
    public int sumOfElements() {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                sum += C[i][j];
            }
        }
        return sum;
    }
}
