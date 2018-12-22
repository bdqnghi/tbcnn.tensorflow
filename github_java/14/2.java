package bTree;

import static gdi.MakeItSimple.*;

public class BTreeMenu {

	/* TPE Tasksheet #1
	 * Task 1
	 * Richard Vladimirskij (1527970)
	 * Konstantin Pelevin   (1525950)
	 */

	public static void main(String[] args) {

		// define values: storage + initial objects
		BTree[] storage = new BTree[3];

		// define values: menu helpers
		int magnitude;
		int active = 0;
		int command = 0;
		int value = 0;
		int index = 0;
		boolean toggled = false;
		boolean shutdown = false;
		boolean activeSet = false;

		// collection of printed messages
		String empty = "Error: The B-tree is empty.";
		String invalid = "Error: Invalid input line. Please try again.";
		String loopInsert = "Would you like to insert other values?\nEnter: [1] for 'yes', [2] for 'no'.";
		String loopRemove = "Would you like to remove other values?\nEnter: [1] for 'yes', [2] for 'no'.";


		println("Welcome to the B-tree menu!");
		println("Please specify a magnitude for each B-tree.");

		// set magnitudes for B-trees to work with
		for (int i = 0; i != storage.length; i++){
			println("Enter the magnitude for tree #" + (i+1));
			magnitude = readInt();

			// check criteria
			if (magnitude <= 0){
				println("Error: Please enter values above 0.");
				i--;
			}
			else {
				storage[i] = new BTree(magnitude);
			}
		}

		while (!shutdown){

			// Pick a working B-tree
			if (!activeSet){
				println("Please pick a B-tree to work with.");
				println("Enter: [1] to choose tree #1.");
				println("Enter: [2] to choose tree #2.");
				println("Enter: [3] to choose tree #3.");

				active = readInt();

				// check input
				if (active < 1 | active > 3){
					println(invalid);
				}
				else {
					// -1 to match object array index
					activeSet = true; 
					active = active -1;
				}	
			}

			// Step 2: working tree is set, provide commands
			if (activeSet && !shutdown && command == 0){
				println("\nActive B-tree: #" + (active+1) + " | Size: {" + storage[active].size() + "} elements.");

				// displaying commands may be toggled
				if (!toggled){
					println("Enter: [1] to insert a value to the B-tree.");
					println("Enter: [2] to insert values contained within a file.");
					println("Enter: [3] to check if the B-tree is empty");
					println("Enter: [4] to check if the B-tree contains a certain value.");
					println("Enter: [5] to get the maximal value contained within the B-tree.");
					println("Enter: [6] to get the minimal value contained within the B-tree.");
					println("Enter: [7] to get the size of the B-tree.");
					println("Enter: [8] to get the height of the B-tree.");
					println("Enter: [9] to add all elements of another B-tree to the current tree.");
					println("Enter: [10] to print the current B-tree using inorder strategy.");
					println("Enter: [11] to print the current B-tree using postorder strategy.");
					println("Enter: [12] to print the current B-tree using preorder strategy.");
					println("Enter: [13] to print the current B-tree using levelorder strategy.");
					println("Enter: [14] to switch to another active B-tree.");
				}
				println("Enter: [15] to view /hide command lines.");
				println("Enter: [16] to shutdown the program.\n");

				// Step 3: get input and execute command
				command = readInt();

				// Command 1: insert value
				while (command == 1){
					println("Please enter a value you would like to insert.");
					value = readInt();

					// insert: success
					if (storage[active].insert(new Integer(value))){
						println("Value: [" + value + "] has been successfully added.");
						println(loopInsert);
						command = readInt();

						if (command != 1){
							command = 0;
						}
					}
				}

				// Command 2: insert from file
				if (command == 2){
					command = 0;
					readLine();
					println("Please enter the path of the file you would like to insert.");
					String file = readLine();

					// insertion: success
					if (storage[active].insert(file)){
						println("Values from the file '" + file + "' have been added.");
					}
				}
				
				// Command XX: remove value
				while (command == 10000){
					println("Please enter a value you would like to remove.");
					value = readInt();

					// remove: success
					if (storage[active].delete(new Integer(value))){
						println("Value: [" + value + "] has been successfully removed.");
						println(loopRemove);
						command = readInt();

						if (command != 10000){
							command = 0;
						}
					}
				}
				
				// Command 3: check if empty
				if (command == 3){
					command = 0;

					if (storage[active].isEmpty()){
						println("The B-tree is empty.");
					}
					else {
						println("The B-tree contains elements.");
					}
				}

				// Command 4: check for certain value
				if (command == 4){	
					println("Please enter a value to look for.");
					command = 0;
					value = readInt();

					if (storage[active].contains(new Integer(value))){
						println("Value [" + value + "] has been found!");
					}
					else {
						println("Value [" + value + "] has not been found.");
					}
				}

				// Command 5: get max-value
				if (command == 5){
					command = 0;

					if (!(storage[active].getMax().toString().equals("-1"))){
						println("Max value contained within the B-tree is [" + value + "].");
					}
					else {
						println(empty);
					}
				}

				// Command 6: get min-value
				if (command == 6){
					command = 0;

					if (!(storage[active].getMin().toString().equals("-1"))){
						println("Min value contained within the B-tree is [" + value + "].");
					}
					else {
						println(empty);
					}
				}

				// Command 7: get the size of the tree
				if (command == 7){
					command = 0;
					value = storage[active].size();
					println("The B-tree contains {" + value + "} elements.");
				}

				// Command 8: get the height of the tree
				if (command == 8){
					command = 0;
					value = storage[active].height();
					println("The height of the B-tree is {" + value + "}.");
				}

				// Command 9: add all
				while (command == 9){

					// get index: other tree
					println("Pick a tree # to be added.");
					println("Active B-tree: #" + (active+1) + ".");
					index = readInt();

					// check input
					if (index > 0 && index < 4){
						if (index -1 != active){
							storage[active].addAll(storage[index-1]);
							command = 0;
						}
						else {
							println("Error: Cannot add the B-tree to itself.");
						}
					}
					else {
						println(invalid);
					}	
				}

				// Command 10: print inorder
				if (command == 10){
					command = 0;
					println("\nActive tree elements - inorder transversion:"); 
					storage[active].printInorder();
					println();
				}

				// Command 11: print postorder
				if (command == 11){
					command = 0;
					println("\nActive tree elements - postorder transversion:"); 
					storage[active].printPostorder();
					println();
				}

				// Command 12: print inorder
				if (command == 12){
					command = 0;
					println("\nActive tree elements - preorder transversion:"); 
					storage[active].printPreorder();
					println();
				}

				// Command 13: print levelorder
				if (command == 13){
					command = 0;
					println("\nActive tree elements - levelorder transversion:"); 
					storage[active].printLevelorder();
					println();
				}

				// Command 14: pick another active tree
				if (command == 14){
					command = 0;
					activeSet = false;
				}

				// Command 15: view /hide commands
				if (command == 15){
					command = 0;

					// check: toggled
					if (toggled){
						toggled = false;
					}
					else {
						toggled = true;
					}
				}

				// Command 16: shutdown execution
				if (command == 16){
					command = 0;
					shutdown = true;
					println("Shutting down... Have a nice day!");
				}

				// validate command input
				if (command != 0 && (command > 16 | command < 0)){
					command = 0;
					println("Error: Wrong command line. Please try again.");
				}	
			}	
		}
	}
}
