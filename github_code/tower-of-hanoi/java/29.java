package algorithms.hanoi_tower;

public class HanoiTower {
    // Java recursive program to solve tower of hanoi puzzle

    // Java recursive function to solve tower of hanoi puzzle
    public static void towerOfHanoi(int numberDisks, char from_rod, char to_rod, char aux_rod) {
        if (numberDisks == 1) {
            System.out.println("Move disk 1 from rod " + from_rod + " to rod " + to_rod);
            return;
        }
        towerOfHanoi(numberDisks - 1, from_rod, aux_rod, to_rod);
        System.out.println("Move disk " + numberDisks + " from rod " + from_rod + " to rod " + to_rod);
        towerOfHanoi(numberDisks - 1, aux_rod, to_rod, from_rod);
    }

    //  Driver method
    public static void main(String args[]) {
        int n = 4; // Number of disks
        towerOfHanoi(n, 'A', 'C', 'B');  // A, B and C are names of rods
    }
}
