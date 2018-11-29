/* program: TOwer of hanoi
   name : Ravi Kumar Kuril
   class:Msc Operational Research
   college:ramjas college
*/

//_____________________________________________________________________________

import java.io.*;
class tower
{
public static void main(String args[]) throws IOException
{
System.out.println("printing the tower of hanoi of height 10");
int ctl2=10;
int ctl=10;
for(int x=0;x<10;x++)
	{ctl=ctl2;
	while(ctl>0)
	{
	System.out.print(" ");
	ctl--;
	}
		for (int y=0;y<=x;y++)
			{
				System.out.print(" *");
			}
		ctl=ctl2--;
	System.out.println(" ");	
          } 
    }
}


//********************************************************************************
output:

C:\Users\ravi kuril\Desktop\java\practical>java tower
printing the tower of hanoi of height 10
           *
          * *
         * * *
        * * * *
       * * * * *
      * * * * * *
     * * * * * * *
    * * * * * * * *
   * * * * * * * * *
  * * * * * * * * * *

C:\Users\ravi kuril\Desktop\java\practical>javac tower.java
