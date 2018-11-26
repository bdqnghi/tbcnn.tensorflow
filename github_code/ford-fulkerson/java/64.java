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

    private int numStudents;

    private int numProjects;

    private int numLecturers;
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
				numStudents = Integer.parseInt(line);
                line = in.nextLine();
                numProjects = Integer.parseInt(line);
                line = in.nextLine();
                numLecturers = Integer.parseInt(line);

                int numVertices = numStudents + numProjects + numLecturers + 2; // +1 for source and +1 for sink
				// create new network with desired number of vertices
				net = new Network (numVertices);

				// process the students
				for (int i = 1; i <= numStudents; i++) { // every Student id is between 1 and numb of students
                    line = in.nextLine();
                    String [] tokens = line.split(" ");
                    String isSE = tokens[1];
                    ArrayList<Integer> choices = new ArrayList<>();
                    for (int j = 2; j < tokens.length; j++) {
                        int projectId = Integer.parseInt(tokens[j]) + numStudents;
                        choices.add(projectId);
                    }
                    Student si = new Student(i, isSE, choices);
                    net.addToVertices(si);
                    Vertex source = net.getSource();
                    net.addEdge(source, si, 1);
                }

                // process the projects
                // every Project id is between (numb of students) and (numb of students + numb of projects)
                for (int i = 1; i <= numProjects; i++) {
                    line = in.nextLine();
                    String[] tokens = line.split(" ");
                    String isSE = tokens[1];
                    int proposedBy = Integer.parseInt(tokens[2]);
                    //Vertex lecturer = net.getVertexByIndex(Integer.parseInt(tokens[2]) + numStudents + numProjects);
                    int capacity = Integer.parseInt(tokens[3]);
                    Project proji = new Project(i + numStudents, isSE, capacity, proposedBy);
                    net.addToVertices(proji);
                }

                /** add edges between student and project only if:
                 * 1. the project appears in te student's preference list
                 * 2. if the student is SE, then the project is for SE students
                 * */
                for (int i = 1; i <= numStudents; i++) {
                    Vertex s =  net.getVertexByIndex(i);
                    if (s instanceof Student) {
                        Student si = (Student) s;
                        for (Integer projID: si.getChoices()) {
                            Vertex pj = net.getVertexByIndex(projID);
                            if (pj instanceof Project){
                                Project p = (Project) pj;
                                if ((si.isSE() && p.isSE()) || (!si.isSE())) {
                                    net.addEdge(si, p, 1);
                                }
                            }
                        }
                    }
                }

                // process the lecturers
                // // every Lecturer id is between (numb of students + numb of projects) and (numb of students + numb of projects + numb of lecturers)
                for (int i = 1; i <= numLecturers; i++) {
                    line = in.nextLine();
                    String[] tokens = line.split(" ");
                    int lquota = Integer.parseInt(tokens[1]); // the min number of students the lecturer must supervise
                    int uquota = Integer.parseInt(tokens[2]); // the max number of students the lecturer can supervise
                    Lecturer lecturer = new Lecturer(i + numProjects + numStudents, uquota, lquota);
                    net.addToVertices(lecturer); // add instance to vertices
                    Vertex sink = net.getSink();
                    // set the capacity to lower quota initially
                    net.addEdge(lecturer, sink, lquota); // connect lecturer to the sink vertex.
                }

                /**
                 * Add edges between projects and lecturers
                 * the uquota is equal of the numb  of students that can take the project
                 * */
                for (int i = numStudents + 1; i <= numStudents+numProjects; i++) {
                    Vertex pi = net.getVertexByIndex(i);
                    if (pi instanceof Project) {
                        Project p = (Project) pi;
                        Vertex li = net.getVertexByIndex(p.getProposedBy() + numStudents + numProjects);
                        if (li instanceof Lecturer) {
                            Lecturer l = (Lecturer) li;
                            net.addEdge(p,l,p.getCapacity());
                        }
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
	public boolean fordFulkerson(int initFlow) throws Exception {
        int newFlow=initFlow;
        if (newFlow == 0) {
            // initialization step; set the flow everywhere to 0 initially
            for (int v = 0; v < net.getNumVertices(); v++) {
                Vertex vv = net.getVertexByIndex(v);
                for (int u = 0; u < net.getNumVertices(); u++) {
                    Vertex vu = net.getVertexByIndex(u);
                    Edge e = net.getAdjMatrixEntry(vv, vu);
                    if (e != null) {
                        e.setFlow(newFlow);
                    }
                }
            }
        }
        else if (newFlow == -1) {
            newFlow = net.getValue();
            System.out.println("hahahahhss " + newFlow);
            for (int i = 1; i <= numLecturers; i++) {
                Lecturer lecturer = (Lecturer) net.getVertexByIndex(i + numProjects + numStudents);
                int uquota = lecturer.getUquota();
                net.addToVertices(lecturer); // add instance to vertices
                Vertex sink = net.getSink();
                // set the capacity to upper quota during the second run of the algorithm
                Edge e = net.getAdjMatrixEntry(lecturer,sink);
                e.setCap(uquota);
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

        int minFlow = minAllowedFlow();

        if (net.getValue() < minFlow) {
            return false;
        }
        else{
            return true;
        }
	}

    public int minAllowedFlow(){
        int mini = 0;
        for (int i = numStudents+numProjects+1; i <= numStudents+numProjects+numLecturers; i++ ) {
            Lecturer lec = (Lecturer)net.getVertexByIndex(i);
            mini = mini + lec.getLquota();
        }
        return mini;
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
			net.printFlow(numStudents, numProjects, numLecturers);
		}
		else
			System.out.println("The assignment is not a valid flow");
	}
}