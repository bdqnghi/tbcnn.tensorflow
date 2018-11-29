package eu.shiny.hackathon;



/**
The towers of hanoi is a popular problem. You have three poles and n disks which fit on the poles. All disks have different size. 
They are stacked on pole 1 in the orders of their size. The largest disk is on the bottom, the smallest is on the top.

The task is to move all disk from pole 1 to pole 3 under the following restrictions.

==>Only one disk can be moved

==>A larger disk can not be placed on a smaller disk.

The recursive algorithm works like the following: 
move n-1 disk from the starting pole to the pole which is neither start nor target (intermediate), 
move disk n to the target pole and then move n-1 disk from the intermediate pole to the target pole. The n-1 disks are moved recursively.
 *
 */
public class TowerOfHanoi {
    
    public static void main(String[] args) {
        move(5, 1, 3);
    }
    
    public static void move(int n, int startPole, int endPole){
        
        if(n == 0){
            return;
        }
        
        int intermediatePole = 6 - startPole - endPole;
        
        move(n -1 , startPole, intermediatePole);
        
        System.out.println("Move " +n + " from " + startPole + " to " +endPole);
        
        move(n-1, intermediatePole, endPole);
        
    }
}
