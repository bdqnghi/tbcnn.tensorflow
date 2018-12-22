import java.util.*;
public class towerofhanoi {


		static int c = 0;

		public static void main(String[] args) {
			Scanner nm = new Scanner(System.in);
			System.out.println("Enter how many Disk:");
			int n = nm.nextInt();
			towerofhanoi(n, "Stack a", "Stack b", "Stack c");
		}

		public static void towerofhanoi(int topDisk, String from, String inter,String to) {
			if (topDisk == 1) {
				c++;
				System.out.println("Step " + c + " :");
				System.out.println("disk 1 " + from + " to " + to);
			} else {
				towerofhanoi(topDisk - 1, from, to, inter);
				c++;
				System.out.println("Step " + c + " :");
				System.out.println("disk " + topDisk + " from " + from + " to "+ to);
				towerofhanoi(topDisk - 1, inter, from, to);
			}

		}

	}


