package TowerOfHanoi.test;

/**
 * Implementing the Tower of Hanoi classical algorithm
 * @author Muhammed Ahad
 * e-mail: ahad3112@yahoo.com
 */

// import package
import java.util.*;
import TowerOfHanoi.test.Tower.HanoiTower;
import TowerOfHanoi.test.Plate.TowerPlate;
import TowerOfHanoi.test.CreateTower.CreateTowers;
import TowerOfHanoi.Graphics.DrawNow;


public class TowerOfHanoi {
	// total nof plates 
	public static int n =3;
	public static void main(String[] args ){
				
		// Creating Three towers aling with n plates in the left tower
		CreateTowers towers = new CreateTowers();
		
		
		// getting the details of towers
		 //getTowerDetails(towers.left);
		 //getTowerDetails(towers.center);
		 //getTowerDetails(towers.right);
		 
		
		// get the getails of the plateList
		//getPlateDetails(towers.left.getPlateList());
		//getPlateDetails(towers.center.getPlateList());	// initially it is empty
		//getPlateDetails(towers.right.getPlateList());	// initially it is empty
		
		//  			Solver					//

		// Calling the solve method to solve the hanoi puzzle
		Solve(n,towers.left,towers.center,towers.right);
		System.out.println("Total moves: "+towers.right.getMoveCount());
		//				Solver				//
		
		
		
		// checking tower details again
		// getting the details of towers
		 //getTowerDetails(towers.left);
		 //getTowerDetails(towers.center);
		 //getTowerDetails(towers.right);
		 
		// get the getails of the plateList again
		//getPlateDetails(towers.left.getPlateList()); // this should be empty now
		//getPlateDetails(towers.center.getPlateList());	// this should be empty now
		//getPlateDetails(towers.right.getPlateList());	// this should have every plates now
		
		// drawing the destination tower.i.e right tower
		//new DrawNow(towers.right.getPlateList());
	}
	
	
	// a method to get the details of all towers
	public static void getTowerDetails(HanoiTower tower){
		// left towers
		System.out.println(tower);
		// center towers
		//System.out.println(towers.center);
		// right towers
		//System.out.println(towers.right);
	}
	
	// a method to get the details of the plates
	public static void getPlateDetails(LinkedList<TowerPlate> plateList){
		for(TowerPlate plate: plateList){
			System.out.println(plate);
		}
	} 
		
	// Solve method to solve the tower problem
	public static void Solve(int N,HanoiTower source, HanoiTower aux, HanoiTower dest){	
				
		if(N==1){
			//System.out.println("I got one plate.");
			moveAndAddPlate(source.getPlateList().get(0),source,dest);
		} 
		// recursively calling the Solve method.
		else if (N>1){ // need to edit this statement
			Solve(N-1,source,dest,aux);
			moveAndAddPlate(source.getPlateList().get(0),source,dest);
			/* index 0. as the top N-1 has been virtually gone with the call of Solve.
			 * N-1 will be moved first and the source plate list will contain only one plate 
			 * by the time the call recursvely come back to this point.
			 */
			Solve(N-1,aux,source,dest);
		}
	}
	
	// move and add plate from the source to the dest
	public static void moveAndAddPlate(TowerPlate plate,HanoiTower source, HanoiTower dest){
		System.out.printf("Moving plate %d from %sTower to %sTower.\n",plate.getPlateNo(),
				source.getTowerName(),dest.getTowerName());
		// adding to the dest
		dest.getPlateList().addFirst(plate); 
		// need to edit the tower name and the plate coordinates
		plate.editPlateDetails(dest.getTowerName(), dest.getNoOfPlates()); 
		dest.addPlate();
		// remove plate from the source
		Iterator<TowerPlate> it = source.getPlateList().iterator();
		while(it.hasNext()){
			if(it.next().getPlateNo()==plate.getPlateNo()){
				//System.out.println("Removing plate.");
				it.remove();
			}
		}	
		//source.getPlateList().remove(0); 
		//source.getPlateList().remove(source.getPlateList().size()-1);
		source.removePlate(); // removing one plate from the source
		
		// adding 1 to the moveCount. moveCount is a class variable. so it's enough to edit move in source tower
		source.editMoveCount();
	}
}
