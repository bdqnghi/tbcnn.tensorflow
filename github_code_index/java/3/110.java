package DSA.TowerOfHanoi;
import java.util.Scanner;
public class TowerOfHanoi {
    public static void MoveTower(int i, String source, String Spare, String destination){
        if(i > 0){
            MoveTower(i-1, source, destination, Spare);
            System.out.println("Move disk " + i + " from " + source + " to " + destination);
            MoveTower(i-1, Spare, source, destination);
        }
    }
    public static void main(String[] args) {
        String s1 = "Peg 1";
        String s2 = "Peg 2";
        String s3 = "Peg 3";
        Scanner kb = new Scanner(System.in);
        int num = kb.nextInt();
        MoveTower(num, s1, s2, s3);
    }
}