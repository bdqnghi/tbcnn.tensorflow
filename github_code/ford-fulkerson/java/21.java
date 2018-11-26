import java.util.*;
import java.io.*;
import networkFlow.*;

/**
 * The Class FordFulk.
 * Contains main part of the Ford-Fulkerson implementation and code for file input
 */
public class FordFulk {

	/** The name of the file that encodes the given network. */
	private String filename;
	
	/** The network on which the Ford-Fulkerson algorithm is to be run. */
	private Network net; 

	/**
	 * Instantiates a new FordFulk object.
	 * @param s the name of the input file
	 */
	public FordFulk(String s) {
		filename = s; // store name of input file
	}

	/**
	 * Read in network from file.
	 * See assessed exercise specification for the file format.
	 */
	public void readNetworkFromFile() {
		FileReader fr = null;
		// open file with name given by filename
		try {
			try {
				fr = new FileReader (filename);
				Scanner in = new Scanner (fr);

				// get number of vertices
				String line = in.nextLine();
				int numVertices = Integer.parseInt(line);

				// create new network with desired number of vertices
				net = new Network (numVertices);

				// now add the edges
				while (in.hasNextLine()) {
					line = in.nextLine();
					String [] tokens = line.split("[( )]+");
					// this line corresponds to add vertices adjacent to vertex u
					int u = Integer.parseInt(tokens[0]);
					// get corresponding Vertex object
					Vertex uu = net.getVertexByIndex(u);
					int i=1;
					while (i<tokens.length) {
						// get label of vertex v adjacent to u
						int v = Integer.parseInt(tokens[i++]);
						// get corresponding Vertex object
						Vertex vv = net.getVertexByIndex(v);
						// get capacity c of (uu,vv)
						int c = Integer.parseInt(tokens[i++]);
						// add edge (uu,vv) with capacity c to network 
						net.addEdge(uu, vv, c);
					}
				}
			}
			finally { 
				if (fr!=null) fr.close();
			}
		}
		catch (IOException e) {
			System.err.println("IO error:");
			System.err.println(e);
			System.exit(1);
		}
	}

	/**
	 * Executes Ford-Fulkerson algorithm on the constructed network net.
	 */
	public void fordFulkerson() throws Exception {

        int newFlow = 0;
        // initialization step; set the flow everywhere to 0 initially
        for (int v = 0; v < net.getNumVertices(); v++) {
            Vertex vv = net.getVertexByIndex(v);
            for (int u = 0; u < net.getNumVertices(); u++) {
                Vertex vu = net.getVertexByIndex(u);
                Edge e = net.getAdjMatrixEntry(vv,vu);
                if (e != null) {
                    e.setFlow(newFlow);
                }
            }
        }

        for(;;){ // while an augmenting path exists
            ResidualGraph resG = new ResidualGraph(net); // construct the residual graph
            LinkedList<Edge> augmPath = resG.findAugmentingPath();
            if (augmPath == null) { // if there is no augm path, then we have found the max flow
                break;
            }
            else {
                newFlow = minC(augmPath); // the minimum of the cap of all edges in the augm path
                for (int i = 0; i < augmPath.size(); i++) {
                    // set the corresponding edges with the new flow:
                    net.updateFlow(augmPath.get(i),newFlow);
                }
            }
        }
	}

    /**
     * Finds the minimum flow of all edges specified in the @param
     * */
    private int minC(LinkedList<Edge> edges) {
        int minCapacity = edges.get(0).getCap();
        for (int i = 1; i < edges.size(); i++) {
            int currCapacity = edges.get(i).getCap();
            if (currCapacity < minCapacity) {
                minCapacity = currCapacity;
            }
        }
        return minCapacity;
    }

	/**
	 * Print the results of the execution of the Ford-Fulkerson algorithm.
	 */
	public void printResults() {
		if (net.isFlow()) {
			System.out.println("The assignment is a valid flow");
			System.out.println("A maximum flow has value: " + net.getValue());
			System.out.println("The flows along the edges are as follows:");
			net.printFlow();
		}
		else
			System.out.println("The assignment is not a valid flow");
	}
}