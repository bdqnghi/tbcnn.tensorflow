package tcss543;
import java.io.FileWriter;
import java.io.IOException;

import graph.*;
import graphGenerate.*;
import algorithms.*;
import residualgraph.*;

/**
 * @author Sisi Wang
 *
 * Dec 5, 2015
 */
public class TCSS543 
{
    private static final String FILENAME = "g.txt";
    
	public static void main(String[] args) 
    {
        // TODO Auto-generated method stub
		//if there is command line arguments, take the first one as the path and filename and run each algorithms 
		if(args.length >0){
			SimpleGraph g = new SimpleGraph();
	        GraphInput graphInput = new GraphInput();
	        graphInput.LoadSimpleGraph(g,args[0]);	        
	        RunFiveTime(g);
		}
		/*
		 * eles, automatically  generate graphs with 
		 * different number of nodes, capacity range, probability
		 * and run each algorithm on those graphs.
		 * write the average running time into 4 files
		 * */
		else{
			try {
				RunAll();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
//			SimpleGraph g = new SimpleGraph();
//	        GraphInput graphInput = new GraphInput();
//	        graphInput.LoadSimpleGraph(g);	  
//	        int i =0;
//	        while(i<5)
//	        {
//	        	RunFiveTime(g); i++;
//	        }
//	        
//	        //RunFiveTime(g);
		}
    }
    



	/**
	 * to automatically  generate graphs with 
		 * different number of nodes, capacity range, probability
		 * and run each algorithm on those graphs.
		 * write the average running time into 4 files:
		 * Random.csv, Bipartite.csv, FixedDegree.csv,Mesh.csv
	 * @throws IOException
	 */
	public static void RunAll() throws IOException{
		
		
		//number of graphs to generate for each variable of a certain type of graph
		int size = 10;
		
        SimpleGraph[] sg = new SimpleGraph[size];
        
        GraphGenerate gg = new GraphGenerate();
        FileWriter writer;
        /*Random Graph*/
        
        writer = new FileWriter("Random.csv");
        writer.append("Random Graph: \n"); 
        writer.append("The min Capacity is always 1: \n"); 
		writer.append("# of Nodes,Density,Max Capacity,Average Running Time\n"); 
		writer.append(" , , ,Preflow push,FordFulkerson,Scaling FF\n"); 
       
		sg = gg.GraphsNumNodes(size,"Random");        
        writer.append("Different # of Nodes: \n"); 
        for(int i = 0;i<size;i++){
//        	SimpleGraph simple = sg[i];
        	System.out.println(sg[i].numVertices()+" - "+sg[i].numEdges());
        	String str = RunFiveTime(sg[i]);
        	System.out.println(i+" "+ str);
        	writer.append((i+1)*10+",50,50,"+ str);
        }
        
        sg = gg.GraphsPro(size, "Random");       
        writer.append("Different Density: \n"); 
        for(int i = 0;i<size;i++){
//        	SimpleGraph simple = sg[i];
        	System.out.println(sg[i].numVertices()+" - "+sg[i].numEdges());
        	String str = RunFiveTime(sg[i]);
        	System.out.println(i+" "+ str);
        	writer.append("100,"+(i+1)*10+",50,"+str);
        }
        
        sg = gg.GraphsRange(size, "Random");
        writer.append("Different Capacity Range: \n"); 
        for(int i = 0;i<size;i++){
        	
//        	SimpleGraph simple = sg[i];
        	System.out.println(sg[i].numVertices()+" - "+sg[i].numEdges());    	
        	String str = RunFiveTime(sg[i]);
        	System.out.println(i+" "+ str);
        	writer.append("100,50,"+(i+1)*5+","+str);
        }
        writer.flush();
        writer.close();
        
        /*Bipartite*/
        writer = new FileWriter("Bipartite.csv");
        writer.append("Bipartite Graph: \n"); 
        writer.append("The min Capacity is always 1: \n"); 
		writer.append("# of Nodes on sink & source side,Probability,Max Capacity,Average Running Time\n"); 
		writer.append(" , , ,Preflow push,FordFulkerson,Scaling FF\n"); 
        
        sg = gg.GraphsNumNodes(size,"bipartite");
        writer.append("Different # of Nodes: \n"); 
        for(int i = 0;i<size;i++){

        	System.out.println(sg[i].numVertices()+" - "+sg[i].numEdges());
        	String str = RunFiveTime(sg[i]);
        	System.out.println(i+" "+ str);
        	writer.append((i+1)*5+",0.5,50,"+str);
        }
        
        sg = gg.GraphsPro(size, "bipartite");
        writer.append("Different probability: \n"); 
        for(int i = 0;i<size;i++){

        	System.out.println(sg[i].numVertices()+" - "+sg[i].numEdges());
        	String str = RunFiveTime(sg[i]);
        	System.out.println(i+" "+ str);
        	writer.append("50,"+((100/size)*0.01*(i+1))+",50,"+str);
        }
        
        sg = gg.GraphsRange(size, "bipartite");
        writer.append("Different Max Capacity: \n"); 
        for(int i = 0;i<size;i++){

        	System.out.println(sg[i].numVertices()+" - "+sg[i].numEdges());
        	String str = RunFiveTime(sg[i]);
        	System.out.println(i+" "+ str);
        	writer.append("50,0.5,"+((i+1)*10)/2+","+str);
        }

        writer.flush();
        writer.close();
        
        /*FixedDegree Graph*/
        
        writer = new FileWriter("FixedDegree.csv");
        writer.append("FixedDegree Graph: \n"); 
        writer.append("The min Capacity is always 1: \n"); 
		writer.append("# of Nodes,Degree,Max Capacity,Average Running Time\n"); 
		writer.append(" , , ,Preflow push,FordFulkerson,Scaling FF\n"); 
        
		sg = gg.GraphsNumNodes(size,"fixedDegree");        
        writer.append("Different # of Nodes: \n"); 
        for(int i = 0;i<size;i++){

        	System.out.println(sg[i].numVertices()+" - "+sg[i].numEdges());
        	String str = RunFiveTime(sg[i]);
        	System.out.println(i+" "+ str);
        	writer.append((i+1)*10+",3,50,"+str);
        }
        
        sg = gg.GraphsPro(size, "fixedDegree");
        writer.append("Different Degree: \n"); 
        for(int i = 0;i<size;i++){

        	System.out.println(sg[i].numVertices()+" - "+sg[i].numEdges());
        	String str = RunFiveTime(sg[i]);
        	System.out.println(i+" "+ str);
        	writer.append("100,"+(i+1)+",50,"+str);
        }
        
        sg = gg.GraphsRange(size, "fixedDegree");
        writer.append("Different Max Capacity: \n"); 
        for(int i = 0;i<size;i++){

        	System.out.println(sg[i].numVertices()+" - "+sg[i].numEdges());
        	String str = RunFiveTime(sg[i]);
        	System.out.println(i+" "+ str);
        	writer.append("100,3,"+(i+1)*5+","+str);
        }
        writer.flush();
        writer.close();
        
        /*Mesh Graph*/
        
        writer = new FileWriter("Mesh.csv");
        writer.append("Mesh Graph: \n"); 
        writer.append("The min Capacity is always 1: \n"); 
		writer.append("# of Rows & Columns,Max Capacity,Average Running Time\n"); 
		writer.append(" , ,Preflow push,FordFulkerson,Scaling FF\n"); 

        
        sg = gg.GraphsNumNodes(size,"mesh");      
        writer.append("Different # of Rows & Columns: \n"); 
        for(int i = 0;i<size;i++){

        	System.out.println(sg[i].numVertices()+" - "+sg[i].numEdges());
        	String str = RunFiveTime(sg[i]);
        	System.out.println(i+" "+ str);
        	writer.append((i+1)+",50,"+str);
        }
        
        sg = gg.GraphsRange(size, "mesh");
        writer.append("Different max capacity: \n"); 
        for(int i = 0;i<size;i++){

        	System.out.println(sg[i].numVertices()+" - "+sg[i].numEdges());
        	String str = RunFiveTime(sg[i]);
        	System.out.println(i+" "+ str);
        	writer.append("10,"+(i+1)*5+","+str);
        }
        	        
        writer.flush();
        writer.close();
	}
	
	
	/**
	 * Running three algorithms 5 times each on the given graph,return a string of the average running time of 3 algorithms
	 * @param g - simple graph
	 * @return result - a string of running time of 3 algorithms4
	 */
	public static String RunFiveTime(SimpleGraph g){
    	
        long[] runTime = new long[5];
        long startTime = 0;
        String result;
        System.out.println("Result: ");
        
        
        //Run Preflow Push
        double preFlowMaxflow = 0;
        for(int i = 0;i<5;i++){   
//        	System.out.println(i+"th time for preFlow push");
        	startTime = System.currentTimeMillis();
        	preFlowMaxflow = PreflowPush.PreflowPush(g);
            runTime[i] = System.currentTimeMillis() - startTime;
            
        } 
        System.out.println("The maximum flow of the input Graph calculated by Preflow Push is "+preFlowMaxflow);
        System.out.println("The average running time of 5 preflow push algorithm runs is : " + averageTime(runTime) + " Milliseconds.");
        result = String.valueOf(averageTime(runTime));
       
        
        //Run Ford-Fulkerson
    	double FFMaxflow = 0;
        for(int i = 0;i<5;i++){ 
        	startTime = System.currentTimeMillis();
        	FFMaxflow = FordFulkerson.FordFulkerson(g);
            runTime[i] = System.currentTimeMillis() - startTime;
        }
        System.out.println("The maximum flow of the input Graph calculated by Ford-Fulkerson algorithm is "+FFMaxflow);
        System.out.println("The average running time of 5 preflow Ford-Fulkerson algorithm is : " + averageTime(runTime) + " Milliseconds.");
        result = result+","+String.valueOf(averageTime(runTime));
        
        //Run scaling Ford-Fulkerson
        double SFFMaxflow = 0.0;
        for(int i = 0;i<5;i++){      	
        	startTime = System.currentTimeMillis();
        	SFFMaxflow = ScalingFordFulkerson.ScalingFordFulkerson(g);
            runTime[i] = System.currentTimeMillis() - startTime;
        }   
        System.out.println("The maximum flow of the input Graph calculated by scaling Ford-Fulkerson algorithm is "+SFFMaxflow);
        System.out.println("The average running time of 5 scaling Ford-Fulkerson algorithm is : " + averageTime(runTime) + " Milliseconds.");
        result = result+","+String.valueOf(averageTime(runTime))+"\n";

        return result;    
} 
   
    /**
     * Calculate average running time
     * @param runTime
     * @return average Time
     */
    public static long averageTime(long[] runTime){
		int len = runTime.length;
		long sum = 0;
		for(int i = 0;i<len;i++)
			sum +=runTime[i];
		return sum/len;    	
    }   
}

