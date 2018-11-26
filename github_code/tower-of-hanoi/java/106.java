/**
 * Programming Fundamental Assignment 4
 * 
 * Tower of Hanoi
 * List<String> towerOfHanoi(String source, String destination, String temp, int numOfDisk)
 *
 * @author Prateek Jain
 * Dated 18/07/2017
 *
 */
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

public class TowerOfHanoi {
	List<String> towerOfHanoi(String source, String destination,
			String temporary, int numOfDisk) {
		List<String> movements = new ArrayList<String>();
		// Show error if number of disks is less than 1
		try {
			if (numOfDisk <= 0) {
				throw new IllegalArgumentException("Number of disks Should be greater than 0");
			}
			/*
			 * if number of disk is 1 then Move single disk from source to
			 * destination else move smaller disks
			 */
			if (numOfDisk == 1) {
				movements.add("Move disk " + numOfDisk + " from " + source+ " to " + destination + "\n");
			} else {
				// Moving smaller disks form source to temporary
				movements.addAll(towerOfHanoi(source, temporary, destination,numOfDisk - 1)); 
				movements.add("Move disk " + numOfDisk + " from " + source+ " to " + destination + "\n"); 
				// Moving Smaller disk from temporary to destination
				movements.addAll(towerOfHanoi(temporary, destination, source,numOfDisk - 1)); 
			}
		} catch (IllegalArgumentException exception) {
			System.out.println(exception.getMessage());
		}
		return movements;
	}

	public static void main(String[] args) throws InputMismatchException {
		TowerOfHanoi towerOfHanoi = new TowerOfHanoi();
		Scanner scanner = new Scanner(System.in);
		int numberOfDisk;
		System.out.println("Enter the Number of disks to move from A to B");
		try {
			//Enter the number of disks to move from A to B
			 numberOfDisk = scanner.nextInt();
			// hanoiTower contains the list of movements required for moving disks
			List<String> hanoiTower = towerOfHanoi.towerOfHanoi("A", "B", "C",numberOfDisk);
			for (String string : hanoiTower) {
				System.out.println(string);
			}
		} catch (InputMismatchException exception) {
			System.out.println("Enter the correct input");
		} finally {
			scanner.close();
		}
	}
}
