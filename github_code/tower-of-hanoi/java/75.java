package com.InterviewPaperTest;


/*
 * tower(N,Src,Aux,Dest)
 * Step#1: tower(N-1,Src,End,Aux) : Move (N-1) Src to Aux
 * Step#2: tower(  1,Src,Aux,End) : Move (1) Src to End
 * Step#3: tower(N-1,Aux,Beg,End) : Move (N-1) Aux to End
 * 
 * */


public class TowerOfHanoi {

	static int stepCount=1;
		public static void tower(int disk, String sourceRod, String auxiliaryRod,String destinationRod) {
			
			int count=stepCount;
			
			if (disk == 1) {
				count=stepCount++;
				System.out.println("stepCount#"+ count +" Move the disk " + disk + " from " + sourceRod+ " to " + destinationRod); //Move (1) Src to End
			}
			else{
			
									tower(disk - 1, sourceRod, destinationRod, auxiliaryRod); //Move (N-1) Src to Aux
									count=stepCount++;
				System.out.println("stepCount#"+ count +" Move the disk " + disk + " from " + sourceRod+ " to " + destinationRod); //Move (1) Src to End
									tower(disk - 1, auxiliaryRod, sourceRod, destinationRod); //Move (N-1) Aux to End		
				}
		}

		public static void main(String[] args) {
			System.out.println("tower(3, 'Src', 'Aux', 'Dest')");
			tower(3, "Src", "Aux", "Dest");
		}

	
	
	
	
}
