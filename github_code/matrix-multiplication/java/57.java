package ru.ifmo.ctddev.tkachenko.task6;

/**
 * Created with IntelliJ IDEA.
 * User: gtkachenko
 * Date: 11.05.13
 * Time: 20:07
 */

/**
 * This class is multiplying two {@link SquareMatrix} in several threads
 *
 * @see Thread
 */
public class MatrixMultiplication {
    /**
     * Value that returning when we can't calculate result matrix
     */
    private static final int NOT_CALCULATED_VALUE = -1;

    /**
     * This method is multiplying two {@link SquareMatrix} in particular
     * number of threads. Besides it prints the sum of the result matrix.
     *
     * @param a               first matrix
     * @param b               second matrix
     * @param numberOfThreads number of available for this operation threads
     * @return time elapsed during the multiplication
     * @throws MatrixArithmeticException if the size of first and second matrix are not equal
     */
    public static long multiply(SquareMatrix a, SquareMatrix b, int numberOfThreads) throws InterruptedException {
        if (a.size() != b.size()) {
            throw new MatrixArithmeticException("Matrix size in multiplication is incorrect");
        }
        int n = a.size();
        SquareMatrix res = new SquareMatrix(n);
        long start = System.currentTimeMillis();
        Thread[] threads = new CalcThread[numberOfThreads];
        int indexLength = (n * n < numberOfThreads) ? 1 : n * n / numberOfThreads;
        int left = 0;
        for (int i = 0; i < numberOfThreads; i++) {
            if (left == n * n) {
                break;
            }
            int right = (numberOfThreads == i + 1) ? n * n : left + indexLength;
            int[] indexes = new int[right - left];
            for (int j = left; j < right; j++) {
                indexes[j - left] = j;
            }
            threads[i] = new CalcThread(a, b, res, indexes);
            threads[i].start();
            left += indexLength;
        }
//        Thread.currentThread().interrupt();
        for (int i = 0; i < numberOfThreads; i++) {
            if (threads[i] == null) {
                break;
            }
            threads[i].join();
        }
        long sum = 0;
        for (int i = 0; i < res.size(); i++) {
            for (int j = 0; j < res.size(); j++) {
                sum += res.get(i, j);
            }
        }

        long elapsedTime = System.currentTimeMillis() - start;
        System.out.println("Elapsed time with " + numberOfThreads + " threads is " + elapsedTime + " milliseconds. Sum of result matrix is " + sum);
        return elapsedTime;
    }

    /**
     * This class calculates part of matrix in his own thread.
     * It guarantees that the matrices have a correct size.
     *
     * @see SquareMatrix
     */
    private static class CalcThread extends Thread {
        /**
         * positions that needs to be calculated
         */
        private int[] indexes;
        /**
         * first matrix
         */
        private SquareMatrix a;
        /**
         * second matrix
         */
        private SquareMatrix b;
        /**
         * result matrix
         */
        private SquareMatrix res;

        /**
         * Constructor from two {@link SquareMatrix}, result {@link SquareMatrix} and number of
         * indexes that need to be calculated
         *
         * @param a       first matrix
         * @param b       second matrix
         * @param res     result matrix
         * @param indexes indexes for calculating
         */
        public CalcThread(SquareMatrix a, SquareMatrix b, SquareMatrix res, int[] indexes) {
            this.indexes = indexes;
            this.a = a;
            this.b = b;
            this.res = res;
        }

        /**
         * Code to evaluate in current thread
         *
         * @see SquareMatrix#get(int, int)
         * @see SquareMatrix#set(int, int, int)
         */
        @Override
        public void run() {
            for (int currentIndex : indexes) {
                int ans = 0;
                int i = currentIndex / a.size();
                int j = currentIndex % a.size();
                for (int k = 0; k < a.size(); k++) {
                    ans += a.get(i, k) * b.get(k, j);
                }
                res.set(i, j, ans);
            }
        }
    }

}
