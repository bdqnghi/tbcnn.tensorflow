

import java.io.*;
class Tower
{
	public static void main(String args[])throws IOException
	{
		int n;
		DataInputStream obj=new DataInputStream(System.in);
		System.out.println("Enter the no of discs:");
		n=Integer.parseInt(obj.readLine());
		
		hanoi(n,'A','C','B');
	}
	
	static void hanoi(int n,char from,char to,char temp)
	{
		if (n==1)
		{
			System.out.println("Disc "+n+" from "+from+" to "+to);
			return;
		}
		else
                {hanoi(n-1,from,temp,to);
		
			System.out.println("Disc "+(n)+" from "+from+" to "+to);
	
		
		
		hanoi(n-1,temp,to,from);
		
		
		}
	}
}

/*
Enter the no of discs:
3
Disc 1 from A to C
Disc 2 from A to B
Disc 1 from C to B
Disc 3 from A to C
Disc 1 from B to A
Disc 2 from B to C
Disc 1 from A to C

*/
