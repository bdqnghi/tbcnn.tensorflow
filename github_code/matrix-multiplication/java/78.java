package com.teamrocket.infotracker;

import android.util.Log;

/**
 * Created by dwy on 12/2/15.
 */
public class MatrixMultiplication extends Thread {

    private long A[][];
    private long B[][];
    private long C[][];
    private int start;
    private int end;
    private long sum = 0;

    public MatrixMultiplication(){
        Log.i("TAG","MatrixMultiplication");

    }

    public MatrixMultiplication(long a[][], long b[][], int st, int en){
        Log.i("TAG","MatrixMultiplication");
        this.A = a;
        this.B = b;
        this.start = st;
        this.end = en;
        this.C = new long[en][en];
    }
    public void run(){
        int i,j,k;
        for( i=start; i< end; i += 2)
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
        for( i=start; i<end; i+=2)
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
        Log.i("TAG","serial");

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
        MatrixMultiplication Serial = new MatrixMultiplication(a, b, 0, leng);
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
        MatrixMultiplication thread1 = new MatrixMultiplication(a, b, 0, leng);
        MatrixMultiplication thread2 = new MatrixMultiplication(a, b, 1, leng);
        startTime = System.currentTimeMillis();
        thread1.start();
        thread2.start();
        thread1.join();
        thread2.join();
        endTime = System.currentTimeMillis();
        long result = (thread1.getSum() + thread2.getSum());
        Log.i("AAAAAAAAA", String.valueOf(result));
        Log.i("AAAAAAAAA", String.valueOf(endTime - startTime));
        return endTime - startTime;

    }

}
