package Question9;
import java.util.Scanner;
public class Tower_of_Hanoi {
    public static int Moves(int disk){
        int moves = 0;
        if (disk <= 0){
        return moves;
        } else {
            moves += 2*Moves(disk - 1) + 1;
        }
        return moves;
    }
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String exit = "";
        while (true){
            System.out.println("Enter the number of disk in the tower of Hanoi game.");
            int disk = input.nextInt();
            
            if(disk > 0){
                System.out.println("The number of moves needed to win the Tower of Hanoi game is:  " + Moves(disk));
            }
            else{
                System.out.println("Enter a number greater than 0");
            }
        }
    
}
}
