package org.koropets.test_assignment;

import scala.Tuple2;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

public class Multiplication {

    private static final int SIZE = 500;
    private static final int SEED = 1000 * 1000;
    private static volatile Matrix secondMatrix;

    public static void main(String[] args) throws InterruptedException {
        Matrix matrix_1 = new Matrix(SIZE, SEED);
        Matrix matrix_2 = new Matrix(SIZE, SEED);
        secondMatrix = matrix_2;

        System.out.println("First matrix");
        //If you want to see the first matrix - uncomment it
//        matrix_1.printMatrix();
        System.out.println();
        System.out.println("Second matrix");
        //If you want to see the second matrix - uncomment it
//        matrix_2.printMatrix();
        System.out.println();
        System.out.println("Result matrix WITHOUT concurrency");
        long startWithoutConcurrency = System.currentTimeMillis();
        //If you do not want to multiply matrices without concurrency comment the row below
        Matrix result =  multiplicationBruteForce(matrix_1, matrix_2);
        long endWithoutConcurrency = System.currentTimeMillis();
        long calculatingWithoutConcurrency = endWithoutConcurrency-startWithoutConcurrency;
        System.out.println("Time = " + calculatingWithoutConcurrency);
        //If you want to see the result matrix - uncomment it
//        result.printMatrix();

        long startWithConcurrency = System.currentTimeMillis();
        List<Tuple2<Thread, MultiplicationUsingConcurrency>> threads = startThreads(matrix_1, matrix_2);

        Matrix resultMatrixUsingConcurrency = new Matrix(SIZE);
        for (int i = 0; i < SIZE; i++){
            Thread t = threads.get(i)._1;
            t.join();
            resultMatrixUsingConcurrency.getMatrix()[i] = threads.get(i)._2.getLocalResult();
        }

        long endWithConcurrency = System.currentTimeMillis();
        System.out.println("Result matrix using threads");
        //If you want to see the result matrix using concurrency - uncomment it
//        resultMatrixUsingConcurrency.printMatrix();
        System.out.println("Using concurrency = " + (endWithConcurrency-startWithConcurrency));
    }

    private static Matrix multiplicationBruteForce(Matrix matrix_1, Matrix matrix_2){
        Matrix resultMatrix = new Matrix(SIZE);
        BigInteger sum = new BigInteger("0");
        for (int i = 0; i < SIZE; i++){
            for (int k = 0; k < SIZE; k++){
                for (int j = 0; j < SIZE; j++){
                    sum = sum.add(matrix_1.getMatrix()[i][j].multiply(matrix_2.getMatrix()[j][k]));
                }
                resultMatrix.getMatrix()[i][k] = sum;
                sum = new BigInteger("0");
            }
        }
        return resultMatrix;
    }


    private static List<Tuple2<Thread, MultiplicationUsingConcurrency>> startThreads(Matrix matrix_1, Matrix matrix_2){
        List<Tuple2<Thread, MultiplicationUsingConcurrency>> tuple2List = new ArrayList<Tuple2<Thread, MultiplicationUsingConcurrency>>();
        for (int i = 0; i < SIZE; i++){
            MultiplicationUsingConcurrency multiplication = new MultiplicationUsingConcurrency();
            multiplication.setLocalRow(matrix_1.getMatrix()[i]);
            Thread t = new Thread(multiplication);
            Tuple2<Thread, MultiplicationUsingConcurrency> tuple2 = new Tuple2<Thread, MultiplicationUsingConcurrency>(t, multiplication);
            tuple2List.add(tuple2);
            t.start();
        }
        return tuple2List;
    }

    private static class MultiplicationUsingConcurrency implements Runnable{

        private BigInteger[] result = new BigInteger[SIZE];
        private BigInteger[] localRow;

        public void setLocalRow(BigInteger[] row) {
            localRow = row;
        }

        public BigInteger[] getLocalResult(){
            return result;
        }

        private void multiplicationBruteForceWithTreading(BigInteger[] row){
            BigInteger sum = new BigInteger("0");
            for (int j = 0; j < SIZE; j++){
                for (int k = 0; k < SIZE; k++){
                    sum = sum.add(row[k].multiply(secondMatrix.getMatrix()[k][j]));
                }
                result[j] = sum;
                sum = new BigInteger("0");
            }
        }

        public void run() {
            multiplicationBruteForceWithTreading(localRow);
        }
    }
}
