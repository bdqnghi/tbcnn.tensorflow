import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.io.FileReader;

public class tcss543 {
	
	public static void main(String args[]) throws Exception
	{
		
         //Scaling Ford Fulkerson
		long total_time = 0;
		double max_flow = 0;
		
		long num_iterations = 10;
		System.out.println("Started SCALING FORD FULKERSON ALGORITHM");
        for(int i =0;i<num_iterations;i++){
        	
        	long startTime = System.currentTimeMillis();
        	
        	max_flow = ScalingFordFulkerson.scalingFordFulkersonDriver(args[0]);
        	
        	long endTime =  System.currentTimeMillis();
            
			long estimatedTime = endTime - startTime;
			
			total_time = total_time+estimatedTime;

        }
        
        long average_time = total_time/num_iterations;

        System.out.println("running time for scaling Ford Fulkerson is = " + average_time + " milliseconds ");
        System.out.println("Max flow calculated by scaling Ford Fulkerson for given graph is " + max_flow + "\n\n");
        System.out.println("Finished  SCALING FORD FULKERSON ALGORITHM");
		System.out.println();
        
        // Ford Fulkerson and Push Relabel
        Driver(args[0]);
	}
	

    private static void Driver(String fileName) throws Exception{
        
        ArrayList<InputEdge> inputEdges = getDataFromStandardInput(fileName);
       
		long total_time = 0;
		double max_flow = 0;
		
		long num_iterations = 10;
		
        for(int i =0;i<num_iterations;i++){
        	
			PushRelabelAlgorithm pushRelabel = new PushRelabelAlgorithm(inputEdges);
			
        	long startTime = System.currentTimeMillis();
        	max_flow = pushRelabel.getMaxFlow();
			long endTime =  System.currentTimeMillis();
            
			long estimatedTime = endTime - startTime;
			total_time = total_time+estimatedTime;
        	
        }
		
        long average_time = total_time/num_iterations;
        System.out.println("Started PUSH RELABEL");
        System.out.println("running timeScaling push relabel Algorithm is = " + average_time + " milliseconds ");
        System.out.println("Max flow calculated by Push-Relabel Algorithm for given graph is " + max_flow + "\n\n");
        System.out.println("Finished  PUSH RELABEL Algorithm");
		System.out.println();

//		pushRelabel.addEdge("s", "1", 13);
//		pushRelabel.addEdge("s", "2", 10);
//		pushRelabel.addEdge("2", "1", 3);
//		pushRelabel.addEdge("1", "t", 7);
//		pushRelabel.addEdge("3", "4", 10);
//		pushRelabel.addEdge("4", "t", 5);
//		pushRelabel.addEdge("1", "3", 6);
		
//		pushRelabel.addEdge("s", "1", 3);
//		pushRelabel.addEdge("1", "2", 1);
//		pushRelabel.addEdge("2", "t", 2);
		
		
//		pushRelabel.addEdge("s", "1", 16);
//		pushRelabel.addEdge("s", "2", 13);
//		pushRelabel.addEdge("1", "2", 10);
//		pushRelabel.addEdge("2", "1", 4);
//		pushRelabel.addEdge("1", "3", 12);
//        pushRelabel.addEdge("2", "4", 14);
//        pushRelabel.addEdge("3", "2", 9);
//        pushRelabel.addEdge("3", "t", 20);
//        pushRelabel.addEdge("4", "3", 7);
//        pushRelabel.addEdge("4", "t", 4);
				
		
		total_time = 0;
		int maxFlowFordFulkerson = 0;
		average_time=0;
				
		FordFulkersonAlgorithm fordFulkersonAlgorithm = new FordFulkersonAlgorithm();
	
        for(int i =0;i<num_iterations;i++){
        	
        	long startTime = System.currentTimeMillis();
    		maxFlowFordFulkerson = (int)fordFulkersonAlgorithm.calculateMaxFlow(inputEdges);
			long endTime =  System.currentTimeMillis();
            
			long estimatedTime = endTime - startTime;
			total_time = total_time+estimatedTime;
        	
        }
		
        average_time = total_time/num_iterations;

        System.out.println("Started FORD FULKERSON Algorithm");
        System.out.println("running timeScaling push relabel Algorithm is = " + average_time + " milliseconds ");
		System.out.println("Max flow calculated by Ford-Fulkerson Algorithm for given graph is " + maxFlowFordFulkerson + "\n\n");
        System.out.println("Finished  FORD FULKERSON Algorithm");
		System.out.println();

    }
	
	private static ArrayList<InputEdge> getDataFromStandardInput(String filePath) throws IOException
    {
    	ArrayList<InputEdge> inputEdges = new ArrayList<>();
    	
    	BufferedReader in = null;
        try {
            in = new BufferedReader(new FileReader(filePath));
            String line;
            while ((line = in.readLine()) != null) {
                //System.out.println(line);
                
                String[] splited = line.split("\\s+");
                
                int offset = splited.length - 3;
                
                String first = splited[offset + 0] ;
                String second = splited[offset + 1];
                int capacity = Integer.parseInt(splited[offset + 2]);  
                
                inputEdges.add(new InputEdge(first, second, capacity));
            }
        }
        catch (IOException e) {
            throw e;
        }
        finally {
            if (in != null) {
                in.close();
            }
        }
        
        return inputEdges;
    }
	
}
