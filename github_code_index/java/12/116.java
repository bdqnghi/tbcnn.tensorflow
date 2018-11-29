package projects.matrix_multiplication.parallel;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import projects.matrix_multiplication.InapropriateSizeForMultiplicationException;
import projects.matrix_multiplication.Logger;
import projects.matrix_multiplication.MatrixMultiplication;

public class MatrixMultiplicationParallel implements MatrixMultiplication
{

	public double[][] multiply (double[][] leftMatrix, double[][] rightMatrix, int threadNumber) throws InapropriateSizeForMultiplicationException 
	{
		//if leftMatrix has n*m size and rightMatrix has k*l size we check if m = k
		if (leftMatrix[0].length != rightMatrix.length)
		{
			throw new InapropriateSizeForMultiplicationException ("Cannot multiply matrices of such size!");
		}
		
        double[][] resultMatrix = new double[leftMatrix.length][rightMatrix[0].length];
        ExecutorService executor = Executors.newFixedThreadPool (threadNumber);
        List<Future<double[][]>> list = new ArrayList<Future<double[][]>>();

        int part = leftMatrix.length / threadNumber;
        int difference = leftMatrix.length % threadNumber;
        
        if (part < 1)
        {
        	part = 1;
        	difference = 0;
        }
        
        //start counting time for multiplying
        Callable<double[][]> worker;
        long startTime = System.currentTimeMillis();
        
        for (int i = 0; i < leftMatrix.length-difference; i += part) 
        {
        	if (i+part < leftMatrix.length-difference)
        	{
        		worker = new MatrixMultiplicationParallelTask (leftMatrix, rightMatrix, i, i+part);
        		//will get worker.call result when ready
            	Future<double[][]> submit = executor.submit (worker);
            	//store results
            	list.add (submit);
        	}
        	else
        	{	
        		worker = new MatrixMultiplicationParallelTask (leftMatrix, rightMatrix, i, (i+part+difference));
                //will get worker.call result when ready
                Future<double[][]> submit = executor.submit (worker);
                //store results
                list.add (submit);
        	}
        }
        
        // now retrieve the result
        int start = 0;
        double parts[][];
        for (Future<double[][]> future : list)
        {
            try
            {
                parts = future.get();
                //parts - matrix with start+part columns and secondMatrix.length rows
                for (int i = start; i < start+part; i++)
                {
                	resultMatrix[i] = parts[i];
                }
            } 
            catch (InterruptedException IEx) 
            {
            	System.out.println ("Interrupted exception" + IEx);
            } 
            catch (ExecutionException EEx) 
            {
            	System.out.println ("Execution exception" + EEx);
            }
            if (start+2*part < leftMatrix.length-difference)
            {
            	start += part;
            }
            else
            {
            	start += part;
            	part = part + difference;
            }
        }
        
        long estimatedTime = System.currentTimeMillis() - startTime;
        String message = "Paralel multiplication time with " + threadNumber + " threads";
		Logger.logTime (estimatedTime, message);

        executor.shutdown();

        return resultMatrix;
    }

}
