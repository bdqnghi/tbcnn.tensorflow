package Recursion;

/**
 * Created by piyush.bajaj on 13/03/16.
 Suppose there are three towers here: A(Source), B(Auxillary), C(Destination).
 The ultimate goal is to move all the disk from tower A to C
*/
/*
public class TowerOfHanoi {
    public static void main(String args[]) {
    ToH(3, 'A', 'C', 'B');
    }
    public static void ToH(int n, char sourcePeg, char destPeg, char auxPeg){
        if(n==1){
            System.out.println("Moved disk "+ n + " from " + sourcePeg + " to " + destPeg);
            return;
        }

        //Move the top n-1 disks from source to Auxillary.
        ToH(n-1, sourcePeg, auxPeg, destPeg );
        System.out.println("Moved " + (n - 1) + " disk from " + sourcePeg + " to " + auxPeg);

        //Move the last disk from source to destination.
        ToH(1, sourcePeg, destPeg, auxPeg);
        System.out.println("Moved last disk from " + sourcePeg + " to " + destPeg);

        //Move n-1 disk from Auxillary to Destination
        ToH(n-1, auxPeg, destPeg, sourcePeg);
        System.out.println("Moved " + (n-1) + " disk from " + auxPeg + " to " + destPeg);
    }
}
*/


public class TowerOfHanoi {

    public void solve(int n, String start, String auxiliary, String end) {
        if (n == 1) {
            System.out.println(start + " -> " + end);
        } else {
            solve(n - 1, start, end, auxiliary);
            System.out.println(start + " -> " + end);
            solve(n - 1, auxiliary, start, end);
        }
    }

    public static void main(String[] args) {
        TowerOfHanoi towersOfHanoi = new TowerOfHanoi();

        //System.out.print("Enter number of discs: ");
        //Scanner scanner = new Scanner(System.in);
        //int discs = scanner.nextInt();

     towersOfHanoi.solve(3, "A", "B", "C");
    }
}
