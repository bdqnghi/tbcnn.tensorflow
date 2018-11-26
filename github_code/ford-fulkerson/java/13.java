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

	private boolean hasMinMatching = false;

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

			int guid = 1;
			int id;
			// Make Student Objects from File
			for (int counter = 1; counter <= numStudents; counter++, guid++) {
				line = in.nextLine();
				String[] tokens = line.split(" ");
				id = Integer.parseInt(tokens[0]);
				Student s = new Student(guid, id, tokens[1].equals("Y") ? true
						: false, tokens);
				students[counter - 1] = s;

			}
			// Make Project Objects from File
			for (int counter = 1; counter <= numProjects; counter++, guid++) {
				line = in.nextLine();
				String[] tokens = line.split(" ");
				id = Integer.parseInt(tokens[0]);
				int lecturer = Integer.parseInt(tokens[2]);
				int capacity = Integer.parseInt(tokens[3]);
				Project p = new Project(guid, id, tokens[1].equals("Y") ? true
						: false, lecturer, capacity);
				projects[counter - 1] = p;
			}
			// Make Lecturer Objects from File
			for (int counter = 1; counter <= numLecturers; counter++, guid++) {
				line = in.nextLine();
				String[] tokens = line.split(" ");
				id = Integer.parseInt(tokens[0]);
				Lecturer l = new Lecturer(guid, id,
						Integer.parseInt(tokens[1]),
						Integer.parseInt(tokens[2]));
				lecturers[counter - 1] = l;
			}
			
			in.close();
			fr.close();

			for (Lecturer l : lecturers) {
				// Each edge from a Lecturer node to the Sink starts off with
				// capacity
				// equal to the minimum bound of that lecturer.
				net.addEdge(l, net.getSink(), l.min());
			}
			for (Project p : projects) {
				net.addEdge(p, lecturers[p.lecturer() - 1], p.capacity());
			}
			for (Student s : students) {
				net.addEdge(net.getSource(), s, 1);
				for (int project : s.choices()) {
					if ((s.isSE() && projects[project - 1].se()) || !s.isSE()) {
						net.addEdge(s, projects[project - 1], 1);
					}
				}
			}

		} catch (IOException e) {
			System.err.println("IO error:");
			System.err.println(e);
			System.exit(1);
		}
	}

	public void computeMatching() {
		// Reset from any previous invocations of this.
		hasMinMatching = false;
		net.reset();
		for (Student s : students) {
			s.unassign();
		}
		// Run the Ford Fulkerson with the minimum capacities of each
		// lecturer. If the maximum flow here is equal to the sum of all
		// lecturers minimum bounds then we know that the minimum bound
		// can be obtained. This is checked by determining that every
		// edge incoming to the source is saturated, due to our initial
		// network creation.
		fordFulkerson();
		for (Lecturer l : lecturers) {
			Edge e = net.getAdjMatrixEntry(l, net.getSink());
			if (e.getFlow() != e.getCap())
				return;
		}
		// If this minimum allocation is achievable then we definitely
		// have a matching.
		hasMinMatching = true;

		// We know the Ford Fulkerson algorithm only ever increases the
		// flow in a directed graph, and will not reduce the flow down
		// an an edge leading to the sink.

		// Because of this fact, we are able to increase the capacity
		// of each Lecturer-Sink edge to their full capacity - safely
		// knowing that the flow down that edge will never reduce below
		// their minimum capacity.
		for (Lecturer l : lecturers) {
			Edge lecturerSink = net.getAdjMatrixEntry(l, net.getSink());
			lecturerSink.setCap(l.capacity());
		}

		// Finally, rerun the Ford Fulkerson on the "full" network to obtain
		// the maximum matching.
		fordFulkerson();
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
					if (netEdge != null	&& (netEdge.getCap() - netEdge.getFlow()) >= increase) {
						netEdge.setFlow(netEdge.getFlow() + increase);
						// If starting vertex is a Student and this is a forwards edge,
						// then the corresponding end vertex is a Project, so this is an
						// assignment this of a Project to a Student, so assign this
						// Project to the Student.
						if (start.getLabel() > 0 && start.getLabel() <= numStudents) {
							Project p = projects[end.getLabel() - numStudents - 1];
							students[start.getLabel() - 1].assignProject(p);
						}
					} else { // Backwards edge
						netEdge = net.getAdjMatrixEntry(end, start);
						netEdge.setFlow(netEdge.getFlow() - increase);
						// If end vertex is a Student and this is a backwards edge, then
						// the corresponding starting vertex is a Project, so this is an
						// unassignment of this Project to this Student, so unassign this
						// Project from the Student.
						if (end.getLabel() > 0 && end.getLabel() <= numStudents) {
							students[end.getLabel() - 1].unassign();
						}
					}
				}
			} else {
				break;
			}
		}
	}

	/**
	 * Print the results of the execution of the Ford-Fulkerson algorithm.
	 */
	public void printResults() {
		if (hasMinMatching) {
			for (Student s : students) {
				System.out.print("Student " + s.id() + " is ");
				if (s.getProject() != null) {
					System.out.println("assigned to project "
							+ s.getProject().id());
				} else {
					System.out.println("is not assigned");
				}
			}
			System.out.println();
			for (Project p : projects) {
				int flow = net
						.getAdjMatrixEntry(p, lecturers[p.lecturer() - 1])
						.getFlow();
				System.out.println("Project " + p.id() + " with capacity "
						+ p.capacity() + " is asssigned " + flow
						+ (flow != 1 ? " students" : " student"));
			}
			System.out.println();
			for (Lecturer l : lecturers) {
				int flow = net.getAdjMatrixEntry(l, net.getSink()).getFlow();
				System.out.println("Lecturer " + l.id() + " with lower quota "
						+ l.min() + " and upper quota " + l.capacity()
						+ " is assigned " + flow + " student"
						+ (flow != 1 ? "s" : ""));
			}
		} else
			System.out
					.println("No assignment exists that meets all the lecturer lower quotas");
	}
}