import java.util.Iterator;
import java.io.*;

public class tcss543 {

	public static void main(String[] args) {
		
		System.out.println("Please input the full path and file name of the graph:");
		
        String userinput;
        userinput = KeyboardReader.readString();
        
        if(userinput.equals(""))
        {
        	System.exit(0);
        }
        while(userinput.equals("END_OF_INFO_1234")==false&&userinput.equals("")==false){
        
	        System.out.println("------------------------------------------------------");
	        System.out.println("Generate the graph from: " + userinput);
	        
	        File varTmpDir = new File(userinput);
	        if(!varTmpDir.exists()){
	        	System.out.println("please put the correct full path and file name in the input.txt ");
	        	userinput = KeyboardReader.readString();
	        }
	        
	        else {
		        
				SimpleGraph G_PP = new SimpleGraph();
				SimpleGraph G_FF = new SimpleGraph();
				SimpleGraph G_SFF = new SimpleGraph();
		       
		        GraphInput.LoadSimpleGraph(G_PP,userinput);
		        GraphInput.LoadSimpleGraph(G_FF,userinput);
		        GraphInput.LoadSimpleGraph(G_SFF,userinput);
		
		        
		//debug      
		        //String filename = "/Users/fang_work/fang.txt";
		        //GraphInput.LoadSimpleGraph(G, filename);
		
		
		//Preflow-Push algorithm
		        PreflowPush p = new PreflowPush(G_PP);
		        p.Preflow_Push_Algorithm();
		
		        
		//Ford-Fulkerson algorithm 
		        
		        Vertex source = (Vertex) G_FF.vertexList.getFirst();
		        Vertex target = (Vertex) G_FF.vertexList.getLast();
		        Iterator k;
		        Vertex ee;
		      
		        // make sure the source and target are real source and target vertex
		        for(k = G_FF.vertices();k.hasNext();) {
		        	ee = (Vertex) k.next();
		        	if(ee.getName().equals("t")) target = ee;
		        	else if(ee.getName().equals("s")) source = ee;
		        }
		        folkAlgorithm ffa = new folkAlgorithm(G_FF,source,target);
		        
		        Long startTime = System.nanoTime();
		        System.out.print("The flow value f(v) by Ford-Fulkerson is:         "+ ffa.FoldFulkImpl() + ".");
		        Long endTime = System.nanoTime();
		        Long durration = endTime - startTime;
		        System.out.println(" Running Time is: " + durration);
		           
		//Scaling Ford-Fulkerson
		        FordScaling fs = new FordScaling();
		        
		        // Running Time
		        Long startTime2 = System.nanoTime();
		        
		        double maxflow = fs.ScalingFordFulkerson(G_SFF);
		        
		        Long endTime2   = System.nanoTime();
				long totalTime = endTime2 - startTime2;
		
		        System.out.print("The flow value f(v) by Scaling Ford-Fulkerson is: "+maxflow + ".");
				System.out.println(" Running time is: "+totalTime);
				System.out.println("------------------------------------------------------");
				
				userinput = KeyboardReader.readString();
	        }
			
        } //end of while
       
	}//end of main

}
