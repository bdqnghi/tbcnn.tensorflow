

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class BFS {
	/*public static void main(String[] args) {
		HashMap<String, ArrayList<edge>> adjLists_dict = new HashMap<String, ArrayList<edge>>();

		//Create an arraylist of all nodes
		ArrayList<String> nodeList = new ArrayList<String>();
		nodeList.add("A");
		nodeList.add("B");
		nodeList.add("C");
		nodeList.add("D");
		nodeList.add("E");
		nodeList.add("F");
		nodeList.add("G");
		nodeList.add("H");
		nodeList.add("I");

		for (String temp : nodeList) {
	//		System.out.println(temp);
			adjLists_dict.put(temp, new ArrayList<edge>());

		}

		adjLists_dict.get("A").add(new edge("B", 12, ""));
		adjLists_dict.get("A").add(new edge("E", 3, "2-4,1-5,9-10"));
		adjLists_dict.get("E").add(new edge("H", 2, "1-2"));
		adjLists_dict.get("H").add(new edge("D", 5, "5-6,2-3"));
		adjLists_dict.get("I").add(new edge("C", 6, "10-14"));

		String start = "A";
		int startTime = 3;
		ArrayList<String> goals = new ArrayList<String>();
		goals.add("B");
		goals.add("D");
		goals.add("C");


		breadthFirstSearch(start, startTime, adjLists_dict, goals);


	}*/


	String breadthFirstSearch(String start, int startTime, HashMap<String, ArrayList<edge>> graph, List<String> goals, HashMap<String, Integer> costBfsDfs){

		ArrayList<String> explored = new ArrayList<String>();
		//System.out.println("starttime: "+startTime);
		//System.out.println(graph);
		Queue<String> frontier=new LinkedList<String>();
		int finishTime = 0;

		frontier.add(start);
		String currentNode = start;

		if (goals.contains(currentNode)){
			finishTime = startTime + costBfsDfs.get(start);
			return (start + " " + startTime);
		}
		do {
			if (frontier.isEmpty()){
				return "None";
			}
			else{
				currentNode = frontier.poll();
				explored.add(currentNode);
				//do the goal test now
				//				System.out.println("this is the current node " +currentNode);
				//				System.out.println(graph.get(currentNode).getClass().getName());
				ArrayList<edge> currentAdjList = (ArrayList<edge>)graph.get(currentNode);

				ArrayList<String> children = new ArrayList<String>();

				for (edge adj : currentAdjList){
					//System.out.println(adj.getDest());
					children.add(adj.getDest());
				} 
				//System.out.println("unorderd: "+ children);
				Collections.sort(children, String.CASE_INSENSITIVE_ORDER);	//ordering the children
				//System.out.println("orderd: "+ children);

				for (String child : children){
					//need to check the following if condition
					if (!frontier.contains(child) && !(explored.contains(child))){
						if (goals.contains(child)){
							//System.out.println("!!!Solution found: " + child);
							finishTime = startTime + costBfsDfs.get(child);
							return child + " " + finishTime;
						}
					}
					frontier.add(child);
				}
				//System.out.println("frontier now: " + frontier);
			}

		}while(!frontier.isEmpty());
		//System.out.println("No solution to this problem");
		return "None";
	}
}
