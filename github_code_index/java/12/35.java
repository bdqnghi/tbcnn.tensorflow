package com.teamrocket.infotracker;

import android.util.Log;

/**
 * Created by ShangLiu on 12/8/15.
 */
public class MatrixMultiplication_2 extends Thread {
    private long A[][];
    private long B[][];
    private long C[][];
    private int start;
    private int end;
    private long sum = 0;

    public MatrixMultiplication_2(){
        Log.i("TAG","MatrixMultiplication_2 initialize");

    }

    public MatrixMultiplication_2(long a[][], long b[][], int st, int en){
        Log.i("TAG","MatrixMultiplication_2");
        this.A = a;
        this.B = b;
        this.start = st;
        this.end = en;
        this.C = new long[en][en];
    }
    public void run(){
        int i,j,k;
        for( i=start; i< end; i += 4)
        {
            for( j=0;j<end;j++)
            {
                C [i][j] = 0;
                for( k=0; k< end;k++)
                {
                    C[i][j]+=A[i][k]*B[k][j];
                }
            }
        }
        for( i=start; i<end; i+=4)
            for( j=0; j<end; j++)
                sum += C[i][j];
    }

    public void serial() {  //first method
        int i,j,k;
        for( i=0; i< end; i ++)
        {
            for( j=0;j<end;j++)
            {
                C[i][j]=0;
                for( k=0; k< end;k++)
                {
                    C[i][j]+=A[i][k]*B[k][j];
                }
            }
        }
        for( i=0; i<end; i++)
            for( j=0; j<end; j++)
                sum += C[i][j];
    }
    public long getSum() {
        return this.sum;
    }


    public long main_serial(int leng) throws InterruptedException {
        Log.i("TAG", "serial");

        int i,j,t = 0;
        long startTime,endTime;
        long a[][] = new long[leng][leng];
        long b[][] = new long[leng][leng];
        //--------------Initialization-------------
        for(i=0;i<leng;i++)
        {
            t=i+1;
            for(j=0;j<leng;j++)
            {
                a[i][j]=t++;
                b[i][j]=1;
            }
        }


        //-------------------Serial--------------------
        startTime = System.currentTimeMillis();
        MatrixMultiplication_2 Serial = new MatrixMultiplication_2(a, b, 0, leng);
        Serial.serial();
        endTime = System.currentTimeMillis();
        long result = Serial.getSum();
        Log.i("AAAAAAAAA", String.valueOf(result));
        Log.i("AAAAAAAAA", String.valueOf(endTime-startTime));
        return endTime - startTime;

    }

    public long main_parallel(int leng) throws InterruptedException {

        int i,j,t = 0;
        long startTime,endTime;
        long a[][] = new long[leng][leng];
        long b[][] = new long[leng][leng];
        //--------------Initialization-------------
        for(i=0;i<leng;i++)
        {
            t=i+1;
            for(j=0;j<leng;j++)
            {
                a[i][j]=t++;
                b[i][j]=1;
            }
        }

        //-------------------Parallel--------------------
        MatrixMultiplication_2 thread1 = new MatrixMultiplication_2(a, b, 0, leng);
        MatrixMultiplication_2 thread2 = new MatrixMultiplication_2(a, b, 1, leng);
        MatrixMultiplication_2 thread3 = new MatrixMultiplication_2(a, b, 2, leng);
        MatrixMultiplication_2 thread4 = new MatrixMultiplication_2(a, b, 3, leng);
        startTime = System.currentTimeMillis();
        thread1.start();
        thread2.start();
        thread3.start();
        thread4.start();
        thread1.join();
        thread2.join();
        thread3.join();
        thread4.join();
        endTime = System.currentTimeMillis();
        long result = (thread1.getSum() + thread2.getSum()+thread3.getSum() + thread4.getSum());
        Log.i("AAAAAAAAA", String.valueOf(result));
        Log.i("AAAAAAAAA", String.valueOf(endTime - startTime));
        return endTime - startTime;

    }

}
