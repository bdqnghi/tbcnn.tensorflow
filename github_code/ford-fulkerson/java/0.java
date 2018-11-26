import java.util.*;
import java.io.*;
import networkFlow.*;

/**
 * The Class FordFulk. Contains main part of the Ford-Fulkerson implementation
 * and code for file input
 */
public class FordFulk {

	/** The name of the file that encodes the given network. */
	private String filename;

	private int numStudents;
	private int numProjects;
	private int numLecturers;
	
	private Student[] students;
	private Project[] projects;
	private Lecturer[] lecturers;
	
	/** The network on which the Ford-Fulkerson algorithm is to be run. */
	private Network net;

	/**
	 * Instantiates a new FordFulk object.
	 * 
	 * @param s
	 *            the name of the input file
	 */
	public FordFulk(String s) {
		filename = s; // store name of input file
	}

	/**
	 * Read in network from file. See assessed exercise specification for the
	 * file format.
	 */
	public void readNetworkFromFile() {
		FileReader fr = null;
		// open file with name given by filename
		try {
			try {
				fr = new FileReader(filename);
				Scanner in = new Scanner(fr);
				String line;
				
				// get number of vertices
				numStudents = Integer.parseInt(in.nextLine());
				numProjects = Integer.parseInt(in.nextLine());
				numLecturers = Integer.parseInt(in.nextLine());
				
				students = new Student[numStudents];
				projects = new Project[numProjects];
				lecturers = new Lecturer[numLecturers];
				// create new network with desired number of vertices
				net = new Network(numStudents + numProjects + numLecturers + 2);
				
				int id = 1;
				// Make Student Objects from File
				for (int counter = 1; counter <= numStudents; counter++, id++){
					line = in.nextLine();
					String[] tokens = line.split(" ");
					Student s = new Student(id, counter, tokens[1].equals("Y") ? true : false, tokens);
					students[counter - 1] = s;
					
				}
				// Make Project Objects from File
				for (int counter = 1; counter <= numProjects; counter++, id++){
					line = in.nextLine();
					String[] tokens = line.split(" ");
					int lecturer = Integer.parseInt(tokens[2]);
					int capacity = Integer.parseInt(tokens[3]);
					Project p = new Project(id, counter, tokens[1].equals("Y") ? true : false, lecturer, capacity);
					projects[counter - 1] = p;
				}
				// Make Lecturer Objects from File
				for (int counter = 1; counter <= numLecturers; counter++, id++){
					line = in.nextLine();
					String[] tokens = line.split(" ");
					Lecturer l = new Lecturer(id ,counter, Integer.parseInt(tokens[1]));
					lecturers[counter - 1] = l;
				}
				
				for (Lecturer l : lecturers){
					net.addEdge(l, net.getSink(), l.capacity());
				}
				for (Project p : projects){
					net.addEdge(p, lecturers[p.lecturer() - 1], p.capacity());
				}
				for (Student s : students){
					net.addEdge(net.getSource(), s, 1);
					for (int project : s.choices()){
						if ((s.isSE() && projects[project - 1].se()) ||	!s.isSE()){
							net.addEdge(s, projects[project - 1], 1);
						}
					}
				}
				
			} finally {
				if (fr != null)
					fr.close();
			}
		} catch (IOException e) {
			System.err.println("IO error:");
			System.err.println(e);
			System.exit(1);
		}
	}

	/**
	 * Executes Ford-Fulkerson algorithm on the constructed network net.
	 */
	public void fordFulkerson() {
		while (true) {
			ResidualGraph rg = new ResidualGraph(net);
			LinkedList<Edge> path = rg.findAugmentingPath();
			if (path.size() > 0) {
				int increase = path.peek().getCap();
				for (Edge e : path) {
					if (e.getCap() < increase)
						increase = e.getCap();
				}
				for (Edge e : path) {
					Vertex start = e.getSourceVertex();
					Vertex end = e.getTargetVertex();
					Edge netEdge = net.getAdjMatrixEntry(start, end);
					// Forwards Edge
					if (netEdge != null
							&& (netEdge.getCap() - netEdge.getFlow()) >= increase) {
						netEdge.setFlow(netEdge.getFlow() + increase);
						// If starting vertex is a Student and this is a forwards edge, 
						// then the corresponding end vertex is a Project, so this is an 
						// assignment this of a Project to a Student, so assign this
						// Project to the Student. 
						if (start.getLabel() > 0 && start.getLabel() <= numStudents){
							Project p = projects[end.getLabel() - numStudents - 1];
							students[start.getLabel() -1].assignProject(p);
						}
					}
					else { // Backwards edge
						netEdge = net.getAdjMatrixEntry(end, start);
						netEdge.setFlow(netEdge.getFlow() - increase);
						// If end vertex is a Student and this is a backwards edge, then
						// the corresponding starting vertex is a Project, so this is an
						// unassignment of this Project to this Student, so unassign this
						// Project from the Student.
						if (end.getLabel() > 0 && end.getLabel() <= numStudents){
							students[end.getLabel() - 1].unassign();
						}
					}
				}
			}
			else {
				break;
			}
		}
	}

	/**
	 * Print the results of the execution of the Ford-Fulkerson algorithm.
	 */
	public void printResults() {
		if (net.isFlow()) {
			for (Student s : students){
				System.out.print("Student " + s.id() + " is ");
				if (s.getProject() != null){
					System.out.println("assigned to project " + s.getProject().id());
				}
				else {
					System.out.println("is not assigned");
				}
			}
			System.out.println();
			for (Project p : projects){
				int flow = net.getAdjMatrixEntry(p, lecturers[p.lecturer() - 1]).getFlow();
				System.out.println("Project " + p.id() + " with capacity " + p.capacity() +
						" is asssigned " + flow + (flow != 1 ? " students" : " student"));
			}
			System.out.println();
			for (Lecturer l : lecturers){
				int flow = net.getAdjMatrixEntry(l, net.getSink()).getFlow();
				System.out.println("Lecturer " + l.id() + " with capacity " +
						l.capacity() + " is assigned " + flow +	" student" + 
						(flow != 1 ? "s" : ""));
			}
		} else
			System.out.println("The assignment is not a valid flow");
	}
}