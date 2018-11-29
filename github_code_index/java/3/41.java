import java.util.InputMismatchException;
import java.util.Scanner;

import Model.HanoiTower;
import Model.IllegalStateException;

public class gameHanoiTower {

	public static void main(String[] args) throws IllegalStateException {
		
		int size = 0;
		int depart = 0;
		int arrival = 0;
		
		Scanner scanner = new Scanner(System.in);
		
		System.out.println("Welcome to Tower of Hanoi (by Debesson & Isautier).");
		System.out.println("First, give me the size of your towers. It must be a positive integer striclty greater than 2.");
		try {
			size = scanner.nextInt();
		}
		catch(InputMismatchException ex)
		{
			scanner.next();
		}
		
		while(size < 3)
		{
			System.out.println("Well, your input does not match the criterias. Try again.");
			try {
				size = scanner.nextInt();
			}
			catch (InputMismatchException ex){
				scanner.next();
			}
		}
		
		System.out.println("Thank you.");
		HanoiTower hanoi = new HanoiTower(size);
		
		//AutoSolve mode
		hanoi.print();
		System.out.println();
		hanoi.autoMove(size, 0, 2, 1);
		
		//Play mode
		/*System.out.println("Let's start! Your goal is to move all disks, one by one from Tower n�1 to Tower n�3. One disk cannot be placed on a smaller one.");
		while(!hanoi.checkVictory())
		{
			depart = 0;
			arrival = 0;
			
			hanoi.print();
			System.out.println("Where do you want to pick a disk? (1, 2, 3)");
			try {
				depart = scanner.nextInt();
			}
			catch (InputMismatchException ex){
				scanner.next();
			}
			
			while(depart > 3 || depart < 1)
			{
				System.out.println("Well, your input does not match the criterias. Try again.");
				try {
					depart = scanner.nextInt();
				}
				catch (InputMismatchException ex){
					scanner.next();
				}
			}
			
			System.out.println("Great! Where do you want to place it? (1, 2, 3) It must be a different than the one you just picked.");
			
			try {
				arrival = scanner.nextInt();
			}
			catch (InputMismatchException ex){
				scanner.next();
			}
			
			while(arrival > 3 || arrival < 1 || depart == arrival)
			{
				System.out.println("Well, your input does not match the criterias. Try again.");
				try {
					arrival = scanner.nextInt();
				}
				catch (InputMismatchException ex){
					scanner.next();
				}
			}
			try
			{
				hanoi.move(depart-1, arrival-1);
				System.out.println("Great! Keep doing this!");
			}
			catch(IllegalStateException ise)
			{
				System.out.println(ise.getMessage());
			}
		}
		hanoi.print();
		System.out.println("You beat the game! Congrats!");*/
	}

}
