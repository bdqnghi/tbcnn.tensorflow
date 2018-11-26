import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class MatrixMultiplication extends Thread
{
	private static int[][] fMatrixA;
	private static int[][] fMatrixB;
	private static int[][] fResult;
	private int fRow;
	
	public static void populateMatrix(int[][] aMatrixA,int[][] aMatrixB)
	{
		MatrixMultiplication.fMatrixA = aMatrixA;
		MatrixMultiplication.fMatrixB = aMatrixB;
		fResult = new int[fMatrixA.length][fMatrixA[0].length]; // NxN Matrix
		
	}
	
	public static int[][] getResult()
	{
		return fResult;
	}
	
	public MatrixMultiplication(int aRow)
	{
		this.fRow = aRow;
	}
	
	public void run()
	{
		for(int i = 0; i < fResult.length;i++)
		{
			for(int j = 0; j < fResult[0].length;j++)
				fResult[fRow][i] += (fMatrixA[fRow][j] * fMatrixB[j][i]); 
			
		}
	}
	
	public static void main(String[] args)
	{
		FileIO lFile = new FileIO(args[0]);
		lFile.read();
		MatrixMultiplication.populateMatrix(lFile.getMatrixA(),lFile.getMatrixB());
		
		int N = lFile.getN();
		int S = lFile.getS();
		int P = lFile.getP();
		
		if(S > 0)
		{
			//System.out.println("POOL");
			ExecutorService exec = Executors.newFixedThreadPool(S); 
			for(int i = 0; i < N;i++)
			{
				exec.submit(new MatrixMultiplication(i));
			}
			try
			{
				exec.shutdown();
				exec.awaitTermination(1, TimeUnit.SECONDS);
			}
			catch(InterruptedException  e)
			{
				e.printStackTrace();
			} 
		}
		else
		{
			//System.out.println("NO POOL");
			MatrixMultiplication[] myThreads = new MatrixMultiplication[P];
			for(int i  = 0; i < P;i++)
			{
				myThreads[i] = new MatrixMultiplication(i);
				myThreads[i].start();
			}
			for(int i  = 0; i < P;i++)
			{
				try
				{
					myThreads[i].join();
				}
				catch(InterruptedException e)
				{
					e.printStackTrace();
				}
			} 

		}
		lFile.write(MatrixMultiplication.getResult()); 
	}
	

}
