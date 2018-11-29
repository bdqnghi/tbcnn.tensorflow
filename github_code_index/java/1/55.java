package main;

public class Runner {//the runner is the main method for all
	public static void main(String[] args) {
		UI ui = new UI();
		intro();
		ui.UserInput();
	} //end main
	
	public static void intro() { //just dome introductory remarks
		System.out.println("#######################################################################################################");
		System.out.println("                        Welcome to the Graph!");
		System.out.println();
		System.out.println("This graph has predefined nodes(people) that are connected by edges(friendships)");
		System.out.println();
		System.out.println("To search for a person, starting at the root node(A), first type the ");
		System.out.println("name of the person, in this case any letter A - Z, press enter");
		System.out.println();
		System.out.println("Then type type 'bfs' or 'dfs' to search for that person either by a ");
		System.out.println("breadth-first-search or a depth-first search.");
		System.out.println("You may be wondering: what is a bread search and a depth search?");
		System.out.println("So, I may as well tell you that first.");
		System.out.println();
		System.out.println("A breadth-first-search searches through the nodes utilizing a queue.");
		System.out.println("- \tStarting at the root node, the nodes who A is friends with are added to a queue.");
		System.out.println("- \tThe search checks for people who enter the node first, so the search spreads wider");
		System.out.println("  \tover the network before it goes deeper");
		System.out.println();
		System.out.println("A depth-first-search searches through the nodes utilizing a stack.");
		System.out.println("- \tStarting at the root node, the search goes to the first friend of A and adds it to the stack.");
		System.out.println("- \tThe stack adds nodes to the top and takes them from the top, so this friend of A");
		System.out.println("  \thas his first friend added then, and the search goes as deep as it can before if backs");
		System.out.println("  \tout all and looks for the next friend network to look through");
		System.out.println();
		System.out.println("Well, I hope you enjoy the program!");
		System.out.println("#######################################################################################################");
	} //end intro
}//end class
