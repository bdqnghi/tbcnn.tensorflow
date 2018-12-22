import java.util.concurrent.*;

/*
 * David Hau
 * CS3700
 * 10/8/2018
 */

public class MatrixMultiplication
{
	public static float[][] populateMatrix(int row, int col)
	{
		float[][] temp = new float[row][col];

        for (int i = 0; i < temp.length; i++)
        {
            for (int j = 0; j < temp[0].length; j++)
            {
                temp[i][j] = ThreadLocalRandom.current().nextFloat();
            }
        }
        
        return temp;
	}
	
	private void matrixMultiplication(Phaser phaser, float[][] A, float[][] B, 
			float[][] C, int mStart, int mEnd, int n, int pStart, int pEnd)
	{
        phaser.register();

        new Thread(() ->
        {
            for (int row = mStart; row < mEnd; row++)
            {
                for (int col = pStart; col < pEnd; col++)
                {
                    C[row][col] = 0;
                    for (int k = 0; k < n; k++)
                    {
                        C[row][col] += A[row][k] * B[k][col];
                    }
                }
            }
            phaser.arriveAndDeregister();
        }).start();
    }
	
	public static void main(String[] args) throws InterruptedException
	{
		Phaser phaser = new Phaser();
		float[][] matrixA, matrixB, matrixC;
		int m = 100, n = 100, p = 100;
		
		long start, end;
		int sleepTime = 1000;
		
		matrixA = populateMatrix(m, n);
		matrixB = populateMatrix(n, p);
		matrixC = new float[m][p];
		
		// ----------------------------------------------------------------------------------------------------------------
		
		System.out.println("Matrix batch with 100 max size");
		
		// 1 Thread
		start = System.currentTimeMillis();
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, 0, m, n, 0, p);

        phaser.awaitAdvance(phaser.getPhase());
        Thread.sleep(sleepTime);
        end = System.currentTimeMillis() - start;
        
        System.out.println("Time with 1 Threads: " + end + " ms");

        // 2 Threads
        matrixC = new float[m][p];
        start = System.currentTimeMillis();

        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, 0, m, n, 0, p / 2);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, 0, m, n, p / 2, p);

        phaser.awaitAdvance(phaser.getPhase());
        Thread.sleep(sleepTime);
        end = System.currentTimeMillis() - start;
        
        System.out.println("Time with 2 Threads: " + end + " ms");

        // 4 Threads
        matrixC = new float[m][p];
        start = System.currentTimeMillis();

        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, 0, m / 2, n, 0, p / 2);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, 0, m / 2, n, p / 2, p);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m / 2, m, n, 0, p / 2);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m / 2, m, n, p / 2, p);

        phaser.awaitAdvance(phaser.getPhase());
        Thread.sleep(sleepTime);
        end = System.currentTimeMillis() - start;
        
        System.out.println("Time with 4 Threads: " + end + " ms");

        // 8 Threads
        matrixC = new float[m][p];
        start = System.currentTimeMillis();

        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, 0, m / 4, n, 0, p / 2);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m / 4, m / 2, n, 0, p / 2);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m / 4, m / 2, n, p / 2, p);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, 0, m / 4, n, p / 2, p);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m / 2, m * 3 / 4, n, 0, p / 2);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m / 2, m * 3 / 4, n, p / 2, p);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m * 3 / 4, m, n, 0, p / 2);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m / 2, m, n, p / 2, p);
        
        
        phaser.awaitAdvance(phaser.getPhase());
        Thread.sleep(sleepTime);
        end = System.currentTimeMillis() - start;
        
        System.out.println("Time with 8 Threads: " + end + " ms\n");
        
        // ----------------------------------------------------------------------------------------------------------------
        
        m = 1000;
        n = 1000;
        p = 1000;
        
        matrixA = populateMatrix(m, n);
		matrixB = populateMatrix(n, p);
		matrixC = new float[m][p];
		
		System.out.println("Matrix batch with 1000 max size");
		
		// 1 Thread
		start = System.currentTimeMillis();
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, 0, m, n, 0, p);

        phaser.awaitAdvance(phaser.getPhase());
        Thread.sleep(sleepTime);
        end = System.currentTimeMillis() - start;
        
        System.out.println("Time with 1 Threads: " + end + " ms");

        // 2 Threads
        matrixC = new float[m][p];
        start = System.currentTimeMillis();

        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, 0, m, n, 0, p / 2);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, 0, m, n, p / 2, p);

        phaser.awaitAdvance(phaser.getPhase());
        Thread.sleep(sleepTime);
        end = System.currentTimeMillis() - start;
        
        System.out.println("Time with 2 Threads: " + end + " ms");

        // 4 Threads
        matrixC = new float[m][p];
        start = System.currentTimeMillis();

        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, 0, m / 2, n, 0, p / 2);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, 0, m / 2, n, p / 2, p);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m / 2, m, n, 0, p / 2);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m / 2, m, n, p / 2, p);

        phaser.awaitAdvance(phaser.getPhase());
        Thread.sleep(sleepTime);
        end = System.currentTimeMillis() - start;
        
        System.out.println("Time with 4 Threads: " + end + " ms");

        // 8 Threads
        matrixC = new float[m][p];
        start = System.currentTimeMillis();

        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, 0, m / 4, n, 0, p / 2);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m / 4, m / 2, n, 0, p / 2);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m / 4, m / 2, n, p / 2, p);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, 0, m / 4, n, p / 2, p);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m / 2, m * 3 / 4, n, 0, p / 2);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m / 2, m * 3 / 4, n, p / 2, p);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m * 3 / 4, m, n, 0, p / 2);
        new MatrixMultiplication().matrixMultiplication(phaser, matrixA, matrixB, matrixC, m / 2, m, n, p / 2, p);

        phaser.awaitAdvance(phaser.getPhase());
        Thread.sleep(sleepTime);
        end = System.currentTimeMillis() - start;
        
        System.out.println("Time with 8 Threads: " + end + " ms\n");

	}

}
