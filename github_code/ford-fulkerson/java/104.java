/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package graphs1;

public class tcss543 {
    public static void main(String args[])
    {
       
        
    
        SimpleGraph G1, G2, G3;
         GraphInput g= new GraphInput();
         G1 = new SimpleGraph();
        G2 = new SimpleGraph();
        G3 = new SimpleGraph();
        if(args.length!=0)
        {
        G1= GraphInput.LoadSimpleGraph(G1,args[0]);
        G2=GraphInput.LoadSimpleGraph(G2, args[0]);
        G3 = GraphInput.LoadSimpleGraph(G3,args[0]);
        FordFulkerson ff = new FordFulkerson();
        long startTime = System.nanoTime();
        double maxflow1 = ff.Ford_Fulkerson(G1);
        long endTime = System.nanoTime();
        System.out.println("Ford Fulkerson took: " + (endTime - startTime) / 100000 + " ms");
        ScalingFF ff2 = new ScalingFF();
        long startTime2 = System.nanoTime();
        double maxflow2 = ff2.Scaling_Ford_Fulkerson(G2);
        long endTime2 = System.nanoTime();
        System.out.println("Scaling Ford-Fulkerson took: " + (endTime2 - startTime2) / 100000 + " ms");
        PreflowPush ff3 = new PreflowPush();
        long startTime3 = System.nanoTime();
        double maxflow3 = ff3.Preflow(G3);
        long endTime3 = System.nanoTime();
        System.out.println("Preflow Push took: " + (endTime3 - startTime3) / 100000 + " ms");
        System.out.println("Ford-Fulkerson Maximum Flow: " + maxflow1);
        System.out.println("Scaling Ford-Fulkerson Maximum Flow: " + maxflow2);
        System.out.println("Preflow Push Maximum Flow: " + maxflow3);
    
    }
        else
        {
            
        }
    }
    
}
