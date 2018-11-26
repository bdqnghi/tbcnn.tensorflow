import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class Heapsort {
	public static Scanner scan;
	public static int[] aTree;
	public static int[] originalTree;
	public static int numberInTree;
	
	public static void main(String[] args) {
		scan = new Scanner(System.in);
		aTree = new int[32];
		askUser();
	}
	
	public static void askUser() {
		System.out.println("Please select an option:\n1. Build a tree using random numbers\n2. Quit");
		String userChoice = scan.nextLine();
		if (userChoice.equals("1")) {
			makeTree();
		} else if (userChoice.equals("2")) {
			System.exit(0);
		}
	}
	
	public static void makeTree() {
		List<Integer> randomNumbers = new ArrayList<Integer>();
		randomNumbers.add(0);
		Random myRand = new Random();
		for (int i = 1; i < aTree.length; i++) {
			int aRandNum = myRand.nextInt(90) + 10;
			while (randomNumbers.contains(aRandNum)) {
				aRandNum = myRand.nextInt(90) + 10;
			}
			randomNumbers.add(aRandNum);
		}
		for (int i = 0; i < aTree.length; i++) {
			aTree[i] = randomNumbers.get(i);
		}
		System.out.println("Array: " + randomNumbers);
		originalTree = new int[aTree.length-1];
		for (int i = 0; i < originalTree.length; i++) {
			originalTree[i] = aTree[i+1];
		}
		viewTree(aTree);
		System.out.println("Press any key to continue...");
		if (!scan.nextLine().equals("©")) {
			doHeapsort();
		} else {
			System.out.println("Wow, how did you find that out?!");
			System.exit(0);
		}
	}
	
	public static void doHeapsort() {
		System.out.println("We will now \"heapify\" the tree.");
		System.out.println("Press any key to continue...");
		if (!scan.nextLine().equals("©")) {
			heapifyTree(aTree);
		} else {
			System.out.println("Wow, how did you find that out?!");
			System.exit(0);
		}
	}
	
	public static void heapifyTree(int[] anArray) {
		numberInTree = anArray.length-1;
		for (int i = numberInTree/2; i >= 1; i--) {
			heapifyBottomToTop(anArray, i);
		}
		System.out.println("We are done \"heapifying\" the tree. We will now \"Heapsort\" the tree.");
		System.out.println("Press any key to continue...");
		if (!scan.nextLine().equals("©")) {
			doSort(anArray);
		} else {
			System.out.println("Wow, how did you find that out?!");
			System.exit(0);
		}
	}
	
	public static void heapifyTreeSilent(int[] anArray) {
		numberInTree = anArray.length-1;
		for (int i = numberInTree/2; i >= 1; i--) {
			heapifyBottomToTop(anArray, i);
		}
	}
	
	public static void heapifyBottomToTop(int[] anArray, int i) {
		int parent = i; // The index containing the max value (the one that should be the parent)
		int leftChild = i*2;
		int rightChild = i*2 + 1;
		if (leftChild <= numberInTree && anArray[leftChild] > anArray[parent]) {
			parent = leftChild;
		}
		if (rightChild <= numberInTree && anArray[rightChild] > anArray[parent]) {
			parent = rightChild;
		}
		if (parent != i) {
			doSwap(anArray, i, parent);
			heapifyBottomToTop(anArray, parent);
		}
	}
	
	public static void doSwap(int[] anArray, int parent, int max) {
		int temp = anArray[parent];
		anArray[parent] = anArray[max];
		anArray[max] = temp;
		viewTree(anArray);
	}
	
	public static void doSort(int[] anArray) {
		heapifyTreeSilent(anArray);
		for (int i = numberInTree; i > 1; i--) {
			doSwap(anArray, 1, i);
			numberInTree = numberInTree-1;
			heapifyBottomToTop(anArray, 1);
		}
		int[] sortedTree = new int[anArray.length-1];
		for (int i = 0; i < sortedTree.length; i++) {
			sortedTree[i] = anArray[i+1];
		}
		System.out.println("\nWe are done!\nThe sorted tree is: \n" + Arrays.toString(sortedTree) + "\nThe original tree is: \n" + Arrays.toString(originalTree));
	}
	
	public static void viewTree(int[] anArray) {
		System.out.println("");
		System.out.println("                                                            " + anArray[1]);
		System.out.println("                                                          /    \\");
		System.out.println("                                                         /      \\");
		System.out.println("                                                        /        \\");
		System.out.println("                                                       /          \\");
		System.out.println("                                                      /            \\");
		System.out.println("                                                     /              \\");
		System.out.println("                                                    /                \\");
		System.out.println("                                                   /                  \\");
		System.out.println("                                                  /                    \\");
		System.out.println("                                                 /                      \\");
		System.out.println("                                                /                        \\");
		System.out.println("                                               /                          \\");
		System.out.println("                            " + anArray[2] + "                                                              " + anArray[3]);
		System.out.println("                          /    \\                                                          /    \\");
		System.out.println("                         /      \\                                                        /      \\");
		System.out.println("                        /        \\                                                      /        \\");
		System.out.println("                       /          \\                                                    /          \\");
		System.out.println("                      /            \\                                                  /            \\");
		System.out.println("                     /              \\                                                /              \\");
		System.out.println("            " + anArray[4] + "                              " + anArray[5] + "                              " + anArray[6] + "                              " + anArray[7]);
		System.out.println("          /    \\                          /    \\                          /    \\                          /    \\");
		System.out.println("         /      \\                        /      \\                        /      \\                        /      \\");
		System.out.println("        /        \\                      /        \\                      /        \\                      /        \\");
		System.out.println("    " + anArray[8] + "              " + anArray[9] + "              " + anArray[10] + "              " + anArray[11] + "              " + anArray[12] + "              " + anArray[13] + "              " + anArray[14] + "              " + anArray[15]);
		System.out.println("   /  \\            /  \\            /  \\            /  \\            /  \\            /  \\            /  \\            /  \\   ");
		System.out.println(anArray[16] + "\t" + anArray[17] + "\t" + anArray[18] + "\t" + anArray[19] + "\t" + anArray[20] + "\t" + anArray[21] + "\t" + anArray[22] + "\t" + anArray[23] + "\t" + anArray[24] + "\t" + anArray[25] + "\t" + anArray[26] + "\t" + anArray[27] + "\t" + anArray[28] + "\t" + anArray[29] + "\t" + anArray[30] + "\t" + anArray[31]);
	}
}