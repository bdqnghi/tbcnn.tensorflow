import java.io.*;
class TowersOfHanoi
{
	static int k=0;
	public static void main(String args[])
    {
        int n = 4; // Number of disks
        towerOfHanoi(n, '1', '2', '3');  // A, B and C are names of rods
		System.out.println("total no. of steps : "+(k-1));
    }
        
		static void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod)
		{
			if (n == 1)
			{
				k++;
				System.out.println("Move disk 1 from rod " +  from_rod + " to rod " + to_rod);
				return;
			}
			towerOfHanoi(n-1, from_rod, aux_rod, to_rod);
			System.out.println("Move disk " + n + " from rod " +  from_rod + " to rod " + to_rod);
			towerOfHanoi(n-1, aux_rod, to_rod, from_rod);
		}
     
}