import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Driver {
    public static class Direction {
        String from;
        String to;
        int capacity;

        public Direction(String _from, String _to, int _capacity) {
            from = _from;
            to = _to;
            capacity = _capacity;
        }
    }

    private static Direction[] test = { new Direction("San Francisco", "Redwood City", 12), 
                                        new Direction("Redwood City", "Palo Alto", 18),
                                        new Direction("Palo Alto", "Sunnyvale", 20),
                                        new Direction("Sunnyvale", "Santa Clara", 8),
                                        new Direction("Santa Clara", "San Jose", 200),
                                        new Direction("San Francisco", "Oakland", 9),
                                        new Direction("Redwood City", "Oakland", 6),
                                        new Direction("Oakland", "Palo Alto", 3),
                                        new Direction("Oakland", "Fremont", 4),
                                        new Direction("Fremont", "Milpitas", 12),
                                        new Direction("Sunnyvale", "Fremont", 11),
                                        new Direction("Sunnyvale", "Milpitas", 2),
                                        new Direction("Milpitas", "San Jose", 200) };
    private static int size = 13;
    
	private static void readFromFile(FordFulkerson<String> graph){
	    //!!!remember to change to your file path
		String filename = "input2.txt"; 
		boolean failed = false;
		
		try{
			FileReader file = new FileReader(filename);
			BufferedReader buff = new BufferedReader(file);
			boolean eof = false;
			
			while(!eof) {
				String line = buff.readLine();
				if(line == null) {
					eof = true;
					break;
				}
				
				String[] aline = line.split(", ");
				if(aline.length != 3){
					System.out.println("Unable to add: " + line);
				}
				else{
					String from = aline[0];
					String to = aline[1];
					String caps = aline[2];
					int cap = -1;
					try {
						cap = Integer.parseInt(caps);
					} catch (Exception inv) { // If unable to parse input as int,
												// close window and return
						System.out.println("Unable to add: " + line);
						failed = true;
					}
					if(cap < 1 && !failed){ // If capacity is 0 or negative
						System.out.println("Unable to add: " + line);
						failed = true;
					}
					if(!failed){ // Do not add if failed
						graph.addEdge(from, to, cap);
					}
				}
				failed = false; // Reset for next line
			}
			buff.close();
		} catch (IOException e) {
			
		}
	} // end readFromFile

    public static void main(String[] args) {
/*        System.out.println("TESTING FORD-FULKERSON:");
        FordFulkerson<String> ff = new FordFulkerson<String>();
        for(int i = 0; i < size; i++) {
            ff.addEdge(test[i].from, test[i].to, test[i].capacity);
        }     

        long startTime, stopTime;
        double elapsedTime = 0;

        
        Vertex<String> from = ff.getVertex("San Francisco");
        Vertex<String> to = ff.getVertex("San Jose");

        startTime = System.nanoTime();
        System.out.println("Path from " + from.data.toString() + " to " + to.data.toString() + ": " + ff.hasAugmentingPath(from, to));
        ff.applyFordFulkerson(from, to);
        stopTime = System.nanoTime();  

        System.out.println("Max flow from SF to SJ using Ford-Fulkerson: " + ff.getMaxFlow()); // should be 12
        System.out.println("\nPaths:\n" + ff.getPathsToString());

        elapsedTime =(double)(stopTime - startTime)/1000000.0;
        System.out.println("\nFord-Fulkerson Time: " + elapsedTime + " milliseconds.");
*/
        //add test part to test another input file (25 vertices, US map)
        System.out.println("TESTING FORD-FULKERSON:");
        FordFulkerson<String> ff2 = new FordFulkerson<String>();
        readFromFile(ff2); // use added method
        // ff2.addEdge("Seattle", "Las Vegas", 120);
        System.out.println(ff2.displayAdjacencyList());
        ff2.remove("Seattle", "Las Vegas");
        ff2.remove("Denver", "Houston");
        System.out.println(ff2.displayAdjacencyList());
        
        long startTime, stopTime;
        double elapsedTime = 0;

        
        Vertex<String> from = ff2.getVertex("Seattle");
        Vertex<String> to = ff2.getVertex("Miami");

        startTime = System.nanoTime();
        System.out.println("Path from " + from.data.toString() + " to " + to.data.toString() + ": " + ff2.hasAugmentingPath(from, to));
        ff2.applyFordFulkerson(from, to);
        stopTime = System.nanoTime();  

        System.out.println("Max flow using Ford-Fulkerson: " + ff2.getMaxFlow()); // should be 12
        // System.out.println("\nPaths:\n" + ff2.getPathsToString());

        elapsedTime =(double)(stopTime - startTime)/1000000.0;
        System.out.println("\nFord-Fulkerson Time: " + elapsedTime + " milliseconds.");
        
        
        System.out.println("\n\n" + ff2.displayAdjacencyList() + "\n\n");
        
        Visitor<String> vis = new FlowVisitor<>();
        
        // System.out.println("Breath First Traversal:");
        // ff2.breadthFirstTraversal("Seattle", vis);
        
        // System.out.println("\n\nDepth First Traversal:");
        // ff2.depthFirstTraversal("Seattle", vis);
        /*
        System.out.println("\n--------------------------------------------\nTESTING EDMONDS-KARP:");
        EdmondsKarp<String> ek = new EdmondsKarp<String>();
        for(int i = 0; i < size; i++) {
            ek.addEdge(test[i].from, test[i].to, test[i].capacity);
        }     

        startTime = 0;
        stopTime = 0;
        elapsedTime = 0;

        from = ek.getVertex("San Francisco");
        to = ek.getVertex("San Jose");

        startTime = System.nanoTime();
        System.out.println("Path from " + from.data.toString() + " to " + to.data.toString() + ": " + ek.hasAugmentingPath(from, to));
        ek.applyEdmondsKarp(from, to);
        stopTime = System.nanoTime();  

        System.out.println("Max flow from SF to SJ using Edmonds-Karp: " + ek.getMaxFlow()); // should be 12
        // System.out.println("\nPaths:\n" + ek.getPathsToString());

        elapsedTime =(double)(stopTime - startTime)/1000000.0;
        System.out.println("\nEdmonds-Karp Time: " + elapsedTime + " milliseconds.");
        */
    }
}
//output 
/*
TESTING FORD-FULKERSON:
------------------------ 
Adj List for Detroit: Nashville(126.0) Cleveland(56.0) 
Adj List for Portland: San Francisco(81.0) 
Adj List for Cleveland: Columbia(22.0) Philadelphia(36.0) Boston(88.0) 
Adj List for San Diego: Phoenix(71.0) 
Adj List for Minneapolis: Chicago(76.0) Salt Lake City (88.0) 
Adj List for Atlanta: Orlando(83.0) 
Adj List for Phoenix: Houston(105.0) 
Adj List for Salt Lake City: Denver(192.0) Las Vegas(85.0) 
Adj List for Denver: Minneapolis(110.0) Chicago(159.0) Phoenix(34.0) Memphis(120.0) Houston(66.0) 
Adj List for Salt Lake City : 
Adj List for Memphis: Orlando(42.0) Miami(77.0) Houston(38.0) 
Adj List for Las Vegas: Phoenix(27.0) Los Angeles(174.0) Denver(39.0) 
Adj List for Boston: New York(45.0) 
Adj List for New York: Philadelphia(31.0) 
Adj List for Seattle: Portland(65.0) Minneapolis(97.0) Salt Lake City(66.0) Denver(42.0) Las Vegas(78.0) 
Adj List for Chicago: Detroit(149.0) Memphis(33.0) 
Adj List for Nashville: Atlanta(59.0) 
Adj List for Miami: 
Adj List for San Francisco: Salt Lake City(21.0) Los Angeles(62.0) 
Adj List for Washington DC: Columbia(49.0) 
Adj List for Columbia: Atlanta(19.0) Orlando(65.0) 
Adj List for Orlando: Miami(233.0) 
Adj List for Los Angeles: San Diego(55.0) Phoenix(39.0) 
Adj List for Philadelphia: Washington DC(137.0) 
Adj List for Houston: Miami(187.0) 

Exception in thread "main" java.lang.NullPointerException
	at FordFulkerson.hasAugmentingPathRecursive(FordFulkerson.java:221)
	at FordFulkerson.hasAugmentingPathRecursive(FordFulkerson.java:226)
	at FordFulkerson.hasAugmentingPathRecursive(FordFulkerson.java:226)
	at FordFulkerson.hasAugmentingPathRecursive(FordFulkerson.java:226)
	at FordFulkerson.hasAugmentingPathRecursive(FordFulkerson.java:226)
	at FordFulkerson.hasAugmentingPathRecursive(FordFulkerson.java:226)
	at FordFulkerson.hasAugmentingPathRecursive(FordFulkerson.java:226)
	at FordFulkerson.hasAugmentingPathRecursive(FordFulkerson.java:226)
	at FordFulkerson.hasAugmentingPath(FordFulkerson.java:199)
	at Driver_Test_FF.main(Driver_Test_FF.java:128)
*/

